#include "GuiProvider.h"

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class SDLGuiProvider : public IGuiProvider 
{
private:
    SDL_Window      *Window = NULL;
    SDL_Surface     *WindowSurface = NULL;
    SDL_Renderer    *Renderer = NULL;
    TTF_Font        *Font = NULL;
    bool            RequestingExit = false;
    bool            keyStates[256];
public:
    virtual bool Init(IVec2 WindowSize, const char *WindowName) override;
    virtual bool IsKeyDown(EKey K) override;
    virtual bool ShouldExit() override;
    virtual void Tick() override;
    virtual void FillBackground(Color C) override;
    virtual void DrawRectangle(FVec2 Origin, FVec2 Size, Color C) override;
    virtual Image *LoadImage(const char *ImagePath) override;
    virtual bool LoadFont(const char *FontPath) override;
    virtual void DrawImage(FVec2 Origin, FVec2 Size, Image *I) override;
    virtual void FreeImage(Image *) override;
    virtual void DrawText(FVec2 Origin, const char* Text, Color C) override;
    virtual void EndFrame() override;
    virtual void Deinit() override;
    virtual ~SDLGuiProvider() override;
};