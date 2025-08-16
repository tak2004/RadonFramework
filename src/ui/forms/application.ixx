export module rf.ui.forms:application;
import :windows;
import rf.ui.system;

export namespace rf {
	class Application {
	public:
		static Application& getInstance(){
			static Application singleton;
			return singleton;
		}
		void run() { messageLoop(data); }
		void addWindow(Window& AWindow, bool AsMainWindow = false) {
			if (AsMainWindow) {
				data.mainWindow = &AWindow.getData();
			}
			WindowData newWindowState;
			createWindow(AWindow.getData(), newWindowState);
			AWindow.changeState(newWindowState);
		}

	private:
		Application(){ initializeApplication(data); }
		ApplicationData data;
	};
}