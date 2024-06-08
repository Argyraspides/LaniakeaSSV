#include "my_view.h"
#include "hermes.h"
#include "BUILD_EMCC.h"

#include <iostream>
// Add whatever ImGui stuff you want to render here
void MyView::RenderImGui(ImGuiIO &io)
{
    ImGui::ShowDemoWindow(); // ImGui demo window as an example
}

// Add whatever SDL stuff you want to render here.
void MyView::RenderSDL(SDL_Renderer &renderer)
{
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 0);
    SDL_RenderClear(&renderer); // Clear the renderer with the set color (black in this case: (0,0,0,0))
    DrawCircle(renderer);       // Draw a circle as an example.
}

// Handle SDL events here
void MyView::HandleSDLEvents(SDL_Event &event)
{
    QuitOnPressQ(event); // Quit the program when 'q' is pressed as an example
}

// SETUP & EXAMPLE FUNCTIONS BELOW ************************************************************************************
// ********************************************************************************************************************

// Set up SDL stuff here. This will be called after SDLWindowSetup.
void MyView::SDLSetup(SDL_Renderer **renderer, SDL_Window **window)
{
    SDL_WindowFlags f = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
    *window = SDL_CreateWindow("Telos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, f);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

// Set up anything related to ImGui here. This is the last thing called before the application loop starts.
// An example on how to set up ImGui is provided below.
ImGuiIO &MyView::ImGuiSetup()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.FontGlobalScale = 1.25f;

    ImGui::StyleColorsDark();
    ImGui::GetStyle().Colors[ImGuiCol_Separator] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    return io;
}

// Create functions here or wherever else you'd like to render your stuff and handle input events. Here is a function
// to get SDL2 to draw a circle as an example.
void MyView::DrawCircle(SDL_Renderer &renderer)
{
    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, 255);

    int centerX = 100;
    int centerY = 100;
    int radius = 50;

    for (int x = centerX - radius; x <= centerX + radius; x++)
    {
        for (int y = centerY - radius; y <= centerY + radius; y++)
        {
            int dx = x - centerX;
            int dy = y - centerY;
            int distanceSquared = dx * dx + dy * dy;

            if (distanceSquared <= radius * radius)
            {
                SDL_RenderDrawPoint(&renderer, x, y);
            }
        }
    }
}

// Here is an example function on event handling. It just quits the program if 'q' is pressed.
void MyView::QuitOnPressQ(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_q)
        {
            #ifdef BUILD_EMCC
            Hermes::GET("https://httpbin.org/get");
            #endif
        }
    }
}