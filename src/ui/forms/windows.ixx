export module rf.ui.forms:windows;
import rf.core.types;
import rf.ui.system;
import :canvas;

export namespace rf {
class Window {
public:
	Window() {
		data.object = this;
		data.changeState = [](void* Sender, const WindowData& NewState) {
			reinterpret_cast<Window*>(Sender)->changeState(NewState);
			};
	}
	void changeState(const WindowData& NewState) {
		if (data.systemData == nullptr && NewState.systemData != nullptr) {

		}
		data = NewState;
	}
	const WindowData& getData()const { return data; }

        void setCanvas(Canvas &NewCanvas) { 
			CanvasData newCanvasState;
            createCanvas(this->data, NewCanvas.getData(), newCanvasState);
            NewCanvas.changeState(newCanvasState);
            data.canvasData = &NewCanvas.getData();
		}
      private:
	WindowData data;
};
}