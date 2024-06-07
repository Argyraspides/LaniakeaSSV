#include "my_view.h"

// Add whatever ImGui stuff you want to render here
void MyView::RenderImGui(ImGuiIO &io)
{
    ImGui::ShowDemoWindow(); // ImGui demo window as an example
}

// Add whatever SDL stuff you want to render here
void MyView::RenderSDL(SDL_Renderer &renderer)
{

}

// Handle SDL events here
void MyView::HandleSDLEvents(SDL_Event &event)
{
    
}

// Create functions here or wherever else to render your stuff