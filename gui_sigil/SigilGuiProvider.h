#include "GuiProvider.h"

class SigilGuiProvider : public IGuiProvider 
{
private:
    int Texture;
public:
    virtual bool Init(IVec2 WindowSize, const char *WindowName) override;
    virtual bool IsKeyDown(EKey K) override;
    virtual bool ShouldExit() override;
    virtual void Tick() override;
    virtual void FillBackground(Color C) override;
    virtual void DrawRectangle(FVec2 Origin, FVec2 Size, Color C) override;
    virtual bool LoadImage(const char *ImagePath) override;
    virtual bool LoadFont(const char *FontPath) override;
    virtual void DrawImage(FVec2 Origin, FVec2 Size) override;
    virtual void DrawText(FVec2 Origin, const char* Text, Color C) override;
    virtual void EndFrame() override;
    virtual void Deinit() override;
    virtual ~SigilGuiProvider() override;
};