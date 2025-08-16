export module rf.ui.screen:data;
import rf.core.memory;
import rf.core.types;

export namespace rf{
enum class ScreenError { None, ResolutionNotSupported, InvalidParameter };

struct Resolution{
    u16 width;
    u16 height;
    u16 bitsPerPixel;
    u16 refreshRate;
};

struct ScreenData{
    strview name;
    strview description;
    arr<Resolution> supportedResolutions;
    u32 id;
    u32 horizontalLengthInMilimeter;
    u32 verticalLengthInMilimeter;
    u32 x;
    u32 y;
    u32 currentResolution;
    bool isPrimary;
    bool isAttachedToDesktop;
    bool isMirroring;
};
}