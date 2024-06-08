#pragma once
#include "imgui.h"

class MyViewInterface
{
public:
    virtual void RenderImGui(ImGuiIO &io) = 0;
    virtual void RenderSDL(SDL_Renderer &renderer) = 0;
    virtual void HandleSDLEvents(SDL_Event &event) = 0;

    virtual void SDLSetup(SDL_Renderer **renderer, SDL_Window **window) = 0;
    virtual ImGuiIO &ImGuiSetup() = 0;
};
