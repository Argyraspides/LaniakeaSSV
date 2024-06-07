#include "my_view.h"

// Add whatever ImGui stuff you want to render here
void MyView::RenderImGui(ImGuiIO &io)
{
    ImGui::ShowDemoWindow(); // ImGui demo window as an example
}

// Add whatever SDL stuff you want to render here.
void MyView::RenderSDL(SDL_Renderer &renderer)
{
    DrawCircle(renderer); // Draw a circle as an example.
}

// Handle SDL events here
void MyView::HandleSDLEvents(SDL_Event &event)
{
    QuitOnPressQ(event); // Quit the program when 'q' is pressed as an example
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
            exit(0);
        }
    }
}