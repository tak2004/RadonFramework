export module rf.ui.forms:canvas;
import rf.core.types;
import rf.ui.system;

export namespace rf {
class Canvas {
public:
  Canvas() {
    data.object = this;
    data.changeState = [](ptr Sender, const CanvasData &NewState) {
      reinterpret_cast<Canvas *>(Sender)->changeState(NewState);
    };
  }
  void changeState(const CanvasData &NewState) { this->data = NewState; }
  const CanvasData &getData() const { return data; }
  void setRenderer(void (*Callback)(u8 *Buffer, u16 Width, u16 Height,
                                    ptr UserData),ptr UserData) {
    data.rendererUserData = UserData;
    data.renderer = Callback;
  }
  void processFrame() { this->data.processFrame(this->data);
  }

private:
  CanvasData data;
};
} // namespace rf