#include "Common.h"

struct Image;

class IGuiProvider
{
public:
    virtual bool Init(IVec2 WindowSize, const char *WindowName) = 0;
    virtual bool IsKeyDown(EKey K) = 0;
    virtual bool ShouldExit() = 0;
    virtual void Tick() = 0;
    virtual void FillBackground(Color C) = 0;
    virtual void DrawRectangle(FVec2 Origin, FVec2 Size, Color C) = 0;
    virtual Image *LoadImage(const char *ImagePath) = 0;
    virtual void FreeImage(Image *) = 0;
    virtual bool LoadFont(const char *FontPath) = 0;
    virtual void DrawImage(FVec2 Origin, FVec2 Size, Image *I) = 0;
    virtual void DrawText(FVec2 Origin, const char* Text, Color C) = 0;
    virtual void DrawStartScreen() = 0;
    virtual void DrawEndScreen() = 0;
    virtual void EndFrame() = 0;
    virtual void Deinit() = 0;
    virtual ~IGuiProvider() {};
};

typedef IGuiProvider *(*ProviderGetter)(void);