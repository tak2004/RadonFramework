export module rf.core.threading:threadpool;
import rf.core.types;
import rf.core.collections;
import rf.core.os;
import rf.core.cpu;

export namespace rf {
enum class TaskStrategy { SerialPerThread, Concurrent };
using WorkerJob = void (*)(void *State);

class ThreadPool {
public:
  static ThreadPool &GetInstance();
  size getMaxParallelJobCount() const;

  bool queueWorkItem(WorkerJob Callback, void *State,
                     const TaskStrategy Strategy = TaskStrategy::Concurrent);
  void waitTillIdle();
  void shutdown();

protected:
  class Worker;
  struct Task;
  Queue<Task> *m_SerialTaskLists;
  size m_SerialTaskListsCount;
  Queue<Task> m_ConcurrentTaskList;
  size m_MaxParallelJobCount;
  Worker *m_WorkerList;
  size m_WorkerCount;
  i32 m_WorkingThreads;
  u64 m_Latency;
  bool m_Running;
  bool m_IsQueingAllowed;

private:
  ThreadPool(const size AvailableLogicalProcessor);
  ~ThreadPool();
};

struct ThreadPool::Task {
  void *State;
  WorkerJob Run;
};

class ThreadPool::Worker {
public:
  Worker()
      : m_Shutdown{false}, m_Pool{nullptr}, m_Thread{nullptr}, m_Group{0},
        m_Mask{1} {}
  void SetAffinity(const GroupID Group, const AffinityBitMask Mask) {
    m_Group = Group;
    m_Mask = Mask;
    if (m_Thread) {
      setThreadAffinityMask(*m_Thread, m_Group, m_Mask);
    }
  }
  void Start(ThreadPool &Pool) {
    m_Pool = &Pool;
    m_Thread = createThread(
        this,
        [](void *State) {
          auto *worker = reinterpret_cast<Worker *>(State);
          worker->Run();
        },
        nullptr, nullptr);
    setThreadAffinityMask(*m_Thread, m_Group, m_Mask);
    postThreadConfigurationComplete(*m_Thread);
  }
  void stop() {
    m_Shutdown = true;
    if (this->m_Thread) {
      destroyThread(this->m_Thread);
      this->m_Thread = nullptr;
    }
  }
  void Run() {
    bool gotTask = false;
    Task task;
    m_SerialGroup = getCurrentUniqueProcessorNumber() % m_Pool->m_WorkerCount;
    m_Pool->m_WorkingThreads++;
    while (!m_Shutdown) {
      gotTask = m_Pool->m_SerialTaskLists[m_SerialGroup].dequeue(task);
      if (!gotTask) {
        gotTask = m_Pool->m_ConcurrentTaskList.dequeue(task);
        if (!gotTask) {
          m_Pool->m_WorkingThreads--;
          sleep(m_Pool->m_Latency);
          m_Pool->m_WorkingThreads++;
        }
      }

      if (gotTask) {
        task.Run(task.State);
      }
    }
  }

private:
  bool m_Shutdown;
  ThreadPool *m_Pool;
  ThreadHandler *m_Thread;
  GroupID m_Group;
  AffinityBitMask m_Mask;
  size m_SerialGroup = 0;
};

ThreadPool &ThreadPool::GetInstance() {
  static ThreadPool singleton(getAvailableLogicalProcessorCount());
  return singleton;
}

ThreadPool::ThreadPool(const size AvailableLogicalProcessor)
    : m_WorkingThreads(0), m_IsQueingAllowed(true), m_Latency{1},
      m_Running{false}, m_SerialTaskListsCount{AvailableLogicalProcessor},
      m_SerialTaskLists{nullptr} {
  m_MaxParallelJobCount = AvailableLogicalProcessor;
  m_ConcurrentTaskList.setup(AvailableLogicalProcessor,
                             AvailableLogicalProcessor * 8);
  m_WorkerCount = m_MaxParallelJobCount;
  m_WorkerList = new Worker[m_WorkerCount];
  m_SerialTaskLists = new Queue<Task>[m_SerialTaskListsCount];
  for (auto i = 0; i < m_SerialTaskListsCount; ++i) {
    m_SerialTaskLists[i].setup(AvailableLogicalProcessor,
                               AvailableLogicalProcessor * 8);
  }
  // auto groups = lowlevel::GetProcessorGroupCount();
  for (auto i = 0; i < m_WorkerCount; ++i) {
    m_WorkerList[i].SetAffinity(0, i);
    m_WorkerList[i].Start(*this);
  }
}

ThreadPool::~ThreadPool() {
  m_IsQueingAllowed = false;
  m_Running = false;
  m_MaxParallelJobCount = 0;

  // clean up the list and trigger a change that the threads can leave Wait()
  m_ConcurrentTaskList.clear();
  for (auto i = 0; i < m_SerialTaskListsCount; ++i) {
    m_SerialTaskLists[i].clear();
  }
  // Signal all threads to cancel and wait until all are dead.
  for (auto i = 0; i < m_WorkerCount; ++i) {
    m_WorkerList[i].stop();
  }

  delete[] m_WorkerList;
  m_WorkerList = nullptr;
  m_WorkerCount = 0;

  // destroy per-thread task collector
  delete m_SerialTaskLists;
}

size ThreadPool::getMaxParallelJobCount() const {
  return m_MaxParallelJobCount;
}

bool ThreadPool::queueWorkItem(WorkerJob Callback, void *State,
                               const TaskStrategy Strategy) {
  if (m_IsQueingAllowed) {
    Task task;
    task.Run = Callback;
    task.State = State;
    if (Strategy == TaskStrategy::Concurrent) {
      m_ConcurrentTaskList.enqueue(task);
    } else {
      auto serialGroup = getCurrentUniqueProcessorNumber() % m_WorkerCount;
      m_SerialTaskLists[serialGroup].enqueue(task);
    }
    return true;
  }
  return false;
}

void ThreadPool::waitTillIdle() {
  bool idle;
  do {
    idle = true;
    for (size i = 0, end = m_SerialTaskListsCount; i < end; ++i) {
      idle = idle && m_SerialTaskLists[i].isEmpty();
    }
    idle = idle && m_ConcurrentTaskList.isEmpty();
    idle = idle && m_WorkerCount == 0;

    if (!idle) {
      sleep(1);
    }
  } while (!idle);
}

void ThreadPool::shutdown() {
  // Signal all threads to cancel and wait until all are dead.
  for (auto i = 0; i < m_WorkerCount; ++i) {
    m_WorkerList[i].stop();
  }
}
} // namespace rf