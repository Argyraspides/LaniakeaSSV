#pragma once
#include <SDL.h>
#include "my_view_interface.h"
#include "imgui.h"
#include <stdio.h>

class MyView : public MyViewInterface {
protected:
    
public:
    void RenderImGui(ImGuiIO &io) override;
    void RenderSDL(SDL_Renderer &renderer) override;
    void HandleSDLEvents(SDL_Event &event) override;

    SDL_Renderer* m_sdlRenderer;

};
