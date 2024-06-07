#pragma once
#include "imgui.h"

class MyViewInterface
{
protected:
    virtual void RenderImGui(ImGuiIO &io) = 0;
    virtual void RenderSDL(SDL_Renderer &renderer) = 0;
    virtual void HandleSDLEvents(SDL_Event &event) = 0;
};
