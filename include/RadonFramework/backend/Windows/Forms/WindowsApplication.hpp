#ifndef RF_WINDOWSAPPLICATION_HPP
#define RF_WINDOWSAPPLICATION_HPP

#include <RadonFramework/Drawing/Forms/IApplication.hpp>

namespace RadonFramework { namespace Forms {
    
class WindowsApplication:public IApplication
{
public:
    WindowsApplication();
    virtual ~WindowsApplication() override;
    virtual void Run(Form *MainForm) override;
    virtual void End() override;
    virtual RF_Type::Bool IsRunningOnDesktop() override;
    virtual void ShowConsole(RF_Type::Bool isVisible) override;
    virtual RF_Type::String GetClipboardText() override;
    virtual void SetClipboardText(const RF_Type::String& NewText) override;
protected:
    RF_Type::Bool m_Active;
};

} }

#endif
