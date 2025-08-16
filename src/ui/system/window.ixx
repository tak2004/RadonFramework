module;
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <ShellScalingApi.h>
#include <Windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
export module rf.ui.system:window;
import rf.core.types;
import rf.core.cpu;

typedef BOOL (*SetProcessDpiAwarenessFunction)(PROCESS_DPI_AWARENESS value);

export namespace rf {
struct WindowData;

struct CanvasData {
  rf::u64 renderTimeUS{0};
  rf::u64 frameIndex{0};

  ptr object{nullptr};
  ptr systemData{nullptr};
  void (*changeState)(ptr, const CanvasData &){nullptr};
  void (*swapBuffer)(const WindowData &Sender){nullptr};
  void (*processFrame)(const CanvasData &){nullptr};
  ptr rendererUserData{nullptr};
  void (*renderer)(u8* Buffer, u16 Width, u16 Height, ptr UserData){nullptr};
};

struct WindowData {
  u16 x{0};
  u16 y{0};
  u16 width{640};
  u16 height{480};
  bool isVisible{true};
  bool hasBorder{true};
  bool hasFocus{false};
  strview title{"Unnamed"};
  CanvasData const *canvasData{nullptr};

  ptr object{nullptr};
  // Contains system specific data which are abstracted to a lower level API.
  ptr systemData{nullptr};
  void (*changeState)(ptr, const WindowData &){nullptr};
  u64 syncTimeUS{0};
  u64 syncIndex{0};
};

struct ApplicationData {
  bool shouldExit{false};
  const WindowData *mainWindow{nullptr};
};
} // namespace rf

struct WindowAPIData {
  HWND WindowHandle;
  HDC DeviceContext;
};

struct CanvasAPIData {
  rf::ptr drawBuffer{nullptr};
  rf::ptr frontBuffer{nullptr};
  rf::ptr backBuffer{nullptr};
  rf::u16 width = 0;
  rf::u16 height = 0;
};

struct WindowEntry {
  HWND handle;
  rf::WindowData *data{nullptr};
  WindowEntry *next{nullptr};
};
static WindowEntry *GlobalWindowLookupTable = nullptr;

rf::WindowData *windowHandleToDataLookup(HWND WindowHandle) {
  WindowEntry *result = GlobalWindowLookupTable;
  while (result) {
    if (result->handle == WindowHandle) {
      return result->data;
    }
    result = result->next;
  }
  return nullptr;
}

void AddToGlobalLookuptable(HWND Handle, rf::WindowData *Data) {
  auto *newEntry = new WindowEntry;
  newEntry->handle = Handle;
  newEntry->data = Data;
  newEntry->next = GlobalWindowLookupTable;
  GlobalWindowLookupTable = newEntry;
}

DWORD ConvertWindowFlags(const rf::WindowData &Data) {
  DWORD result = WS_CLIPCHILDREN;
  if (Data.isVisible) {
    result |= WS_VISIBLE;
  }
  if (Data.hasBorder) {
    result |= WS_OVERLAPPEDWINDOW;
  } else {
    result |= WS_POPUP;
  }
  return result;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  static const rf::u16 EXTENDEDKEYBIT = 1 << 8;
  rf::WindowData *data = windowHandleToDataLookup(hWnd);
  switch (uMsg) {
  case WM_ERASEBKGND:
    return 1; // avoid GDI to clean the background
  case WM_PAINT:
  case WM_DISPLAYCHANGE:
    if (data->canvasData) {
      data->canvasData->swapBuffer(*data);
    }
    break;
  case WM_MOVE:
    data->x = (int)(short)LOWORD(lParam);
    data->y = (int)(short)HIWORD(lParam);
    if (data->changeState) {
      data->changeState(data->object, *data);
    }
    break;
  case WM_SIZE:
    data->width = LOWORD(lParam);
    data->height = HIWORD(lParam);
    if (data->changeState) {
      data->changeState(data->object, *data);
    }
    break;
  case WM_SYSCOMMAND: {
    // disallow screensaver and window menu activation
    switch (wParam) {
    case SC_SCREENSAVE:
      return 0;
    case SC_KEYMENU:
      return 0;
    }
    break;
  }
  case WM_SETFOCUS: {
    data->hasFocus = true;
    if (data->changeState) {
      data->changeState(data->object, *data);
    }
    break;
  }
  case WM_KILLFOCUS: {
    data->hasFocus = false;
    if (data->changeState) {
      data->changeState(data->object, *data);
    }
    break;
  }
  case WM_DESTROY:
    return 0;
  case WM_CLOSE:
    data->isVisible = false;
    if (data->changeState) {
      data->changeState(data->object, *data);
    }
    break;
  }
  return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

export namespace rf {
void initializeApplication(ApplicationData &Data) {
  auto lib = LoadLibraryA("user32.dll");
  if (lib != NULL) {
    auto func = (SetProcessDpiAwarenessFunction)GetProcAddress(
        lib, "SetProcessDpiAwarenessInternal");
    if (func != nullptr) {
      func(PROCESS_PER_MONITOR_DPI_AWARE);
    }
    FreeLibrary(lib);
  }
}

void messageLoop(ApplicationData &Data) {
  MSG msg;

  while (Data.shouldExit == false &&
         (Data.mainWindow == nullptr ||
          (Data.mainWindow != nullptr && Data.mainWindow->isVisible))) {
    // process Asynchronous Procedure Call(APC) messages
    SleepEx(0, true);

    while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }
    if (Data.mainWindow->canvasData) {
      Data.mainWindow->canvasData->swapBuffer(*Data.mainWindow);
    }
    DwmFlush();
    if (Data.mainWindow->canvasData) {
      if (Data.mainWindow->canvasData->processFrame) {        
      //  Data.mainWindow->canvasData->processFrame(*Data.mainWindow->canvasData);        
      }
      //Data.mainWindow->canvasData->swapBuffer(*Data.mainWindow);
    }
  }
}

void createWindow(const WindowData &CurrentState, WindowData &NewState) {
  WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
  mbstowcs(languageUtf16,
           reinterpret_cast<const char *>(CurrentState.title.address),
           LOCALE_NAME_MAX_LENGTH);
  DWORD windowFlags = ConvertWindowFlags(CurrentState);
  RECT rect{CurrentState.x, CurrentState.y, CurrentState.width,
            CurrentState.height};
  AdjustWindowRect(&rect, windowFlags, 0);
  auto handle =
      CreateWindowExW(0, L"#32770", languageUtf16, windowFlags, CurrentState.x, CurrentState.y,
      rect.right-rect.left, rect.bottom - rect.top, 0, 0, 0, NULL);
  SetWindowLongPtrW(handle, GWLP_WNDPROC, (LONG_PTR)wndProc);
  NewState = CurrentState;
  NewState.systemData = new WindowAPIData{handle, GetDC(handle)};
  AddToGlobalLookuptable(handle, const_cast<WindowData *>(&CurrentState));
}

void swapBuffer(const rf::WindowData &Sender) {
  auto start = queryPerformanceCounter();
  WindowAPIData *winData = reinterpret_cast<WindowAPIData *>(Sender.systemData);
  CanvasAPIData *canvasData =
      reinterpret_cast<CanvasAPIData *>(Sender.canvasData->systemData);
  canvasData->drawBuffer =
      fetchAndExchange(&canvasData->frontBuffer, canvasData->drawBuffer);
  BITMAPINFO bmi = {};
  HDC targetContext;
  PAINTSTRUCT ps;
  InvalidateRect(winData->WindowHandle, NULL, false);
  targetContext = BeginPaint(winData->WindowHandle, &ps);
  bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
  bmi.bmiHeader.biWidth = Sender.width;
  bmi.bmiHeader.biHeight = -Sender.height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  SetDIBitsToDevice(targetContext, 0, 0, Sender.width, Sender.height, 0, 0, 0,
                    Sender.height, canvasData->drawBuffer, &bmi,
                    DIB_RGB_COLORS);
  EndPaint(winData->WindowHandle, &ps);
  auto end = queryPerformanceCounter();
  auto newState = Sender;
  newState.syncTimeUS = ((end - start)*1000000) / queryPerformanceFrequency();
  newState.syncIndex++;
  Sender.changeState(Sender.object, newState);
}

void processFrame(const CanvasData &Sender) {
  CanvasAPIData *canvas = reinterpret_cast<CanvasAPIData *>(Sender.systemData);
  u8 *p = reinterpret_cast<u8 *>(canvas->backBuffer);
  auto start = queryPerformanceCounter();
  Sender.renderer(p, canvas->width, canvas->height, Sender.rendererUserData);
  canvas->backBuffer =
      fetchAndExchange(&canvas->frontBuffer, canvas->backBuffer);
  auto end = queryPerformanceCounter();
  auto newState = Sender;
  newState.frameIndex++;
  newState.renderTimeUS =((end - start) * 1000000) / queryPerformanceFrequency();
  Sender.changeState(Sender.object, newState);  
}

void createCanvas(const WindowData &Window, const CanvasData &CurrentState,
                  CanvasData &NewState) {
  NewState = CurrentState;
  size bytes = Window.width * Window.height * 3;
  ptr draw = new u8[bytes];
  ptr front = new u8[bytes];
  ptr back = new u8[bytes];
  NewState.systemData = new CanvasAPIData{.drawBuffer = draw,
                                          .frontBuffer = front,
                                          .backBuffer = back,
                                          .width = Window.width,
                                          .height = Window.height};
  NewState.swapBuffer = swapBuffer;
  NewState.processFrame = processFrame;
}
} // namespace rf