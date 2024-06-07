#pragma once
#include <SDL.h>
#include "my_view_interface.h"
#include "imgui.h"
#include <stdio.h>

class MyView : public MyViewInterface {
    
public:

    void RenderImGui(ImGuiIO &io) override;
    void RenderSDL(SDL_Renderer &renderer) override;
    void HandleSDLEvents(SDL_Event &event) override;

    void DrawCircle(SDL_Renderer &renderer);    // Example function to draw a circle using SDL2
    void QuitOnPressQ(SDL_Event &event);        // Example function to quit the program when 'q' is pressed

};
