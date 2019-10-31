#include "GuiProvider.h"

class SigilGuiProvider : public IGuiProvider 
{
public:
    virtual bool Init(IVec2 WindowSize, const char *WindowName) override;
    virtual bool IsKeyDown(EKey K) override;
    virtual bool ShouldExit() override;
    virtual void Tick() override;
    virtual void FillBackground(Color C) override;
    virtual void DrawRectangle(FVec2 Origin, FVec2 Size, Color C) override;
    virtual Image *LoadImage(const char *ImagePath) override;
    virtual void FreeImage(Image *Image) override;
    virtual void DrawImage(FVec2 Origin, FVec2 Size, Image *I) override;
    virtual void DrawText(FVec2 Origin, const char* Text, Color C) override;
    virtual void EndFrame() override;
    virtual void Deinit() override;
    virtual ~SigilGuiProvider() override;
};