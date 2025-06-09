export module rf.ui.system:window;
import rf.core.types;

export namespace rf {
class Cursor;
class WindowService;
/*
class AbstractApplication {
public:
  virtual ~AbstractApplication() = default;
  virtual void Run(Form *MainForm) = 0;
  virtual void End() = 0;
  virtual RF_Type::Bool IsRunningOnDesktop() = 0;
  virtual void ShowConsole(RF_Type::Bool isVisible) = 0;
  virtual RF_Type::String GetClipboardText() = 0;
  virtual void SetClipboardText(const RF_Type::String &NewText) = 0;
};

class AbstractWindow {
public:
  virtual ~AbstractWindow() = default;
  virtual ptr handle() const = 0;
  virtual bool isVisible() const = 0;
  virtual void setVisible(bool Value) = 0;
  virtual strview title() const = 0;
  virtual void setTitle(const strview &Value) = 0;
  virtual void setSize(u16 Width, u16 Height) = 0;
  virtual void setPosition(u16 X, u16 Y) = 0;
  virtual void setClientRectSize(u16 Width, u16 Height) = 0;
  virtual void setBorder(bool Value) = 0;
  virtual void setCursorVisible(bool Value) = 0;
  virtual void changeCursor(const Cursor &NewCursor) = 0;
  virtual WindowService *getService() = 0;
  virtual void showCloseButton(bool Show) = 0;
  virtual bool hasFocus() const = 0;
  virtual void getCursorPosition(u16 &X, u16 &Y) const = 0;

  void (*OnEvent)() void (*OnResize)(u16 NewWidth, u16 NewHeight);

  RF_Pattern::Event<const RF_Geo::Size2D<> &> OnResize;
  RF_Pattern::Event<const RF_Geo::Point2D<> &> OnReposition;
  RF_Pattern::Signal OnIdle;
  RF_Pattern::Event<const RF_IO::KeyboardEvent &> OnKeyPress;
  RF_Pattern::Event<const RF_IO::KeyboardEvent &> OnKeyRelease;
  RF_Pattern::Event<const RF_IO::KeyboardEvent &> OnPrintableKeyPressed;
  RF_Pattern::Event<const RF_IO::MouseEvent &> OnMouseButtonPressed;
  RF_Pattern::Event<const RF_IO::MouseEvent &> OnMouseButtonReleased;
  RF_Pattern::Event<const RF_IO::MouseEvent &> OnMouseMove;
  RF_Pattern::Signal OnLostFocus;
  RF_Pattern::Signal OnGotFocus;
  RF_Pattern::Event<RF_Type::Int32> OnVerticalMouseWheelMoved;
  RF_Pattern::Event<RF_Type::Int32> OnHorizontalMouseWheelMoved;
  RF_Pattern::Event<const RF_Geo::Point2D<> &> OnDPIChanged;
};*/
} // namespace rf