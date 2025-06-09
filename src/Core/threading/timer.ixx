export module rf.core.threading:timer;
import rf.core.time;
import rf.core.types;
import rf.core.os;

export namespace rf {
using TimerCallback = void (*)(void *);
class Timer {
public:
  Timer();
  bool update(TimeSpan DueTime, TimeSpan Period, void *Parameter,
              TimerCallback Callback);
  void start();
  void stop();
  bool isRunning();

private:
  ptr handler;
  TimeSpan dueTime;
  TimeSpan period;
  void *parameter;
  TimerCallback callback;
};

Timer::Timer() { this->handler = {0}; }

bool Timer::update(TimeSpan DueTime, TimeSpan Period, void *Parameter,
                   TimerCallback Callback) {
  bool result = false;
  if (this->handler == nullptr) {
    this->callback = Callback;
    this->parameter = Parameter;
    this->dueTime = DueTime;
    this->period = Period;
    result = true;
  }
  return result;
}

void Timer::start() {
  if (this->handler == nullptr) {
    this->handler = createTimerQueue(this->callback, this->parameter,
                                     this->dueTime.totalMilliseconds(),
                                     this->period.totalMilliseconds());
  }
}

void Timer::stop() { destroyTimerQueue(this->handler); }

bool Timer::isRunning() { return this->handler == nullptr; }
} // namespace rf