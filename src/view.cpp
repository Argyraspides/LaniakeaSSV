#include "view.h"
#include "SDL2_gfxPrimitives.h"
#include "model.h"
#include "BUILD_EMCC.h"

#include <functional>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <filesystem>

#if BUILDING_WITH_EMSCRIPTEN
#include <emscripten/emscripten.h>
#include "emscripten_browser_clipboard.h"
#endif

View::View(Controller *controller, MyView *myView)
{
    m_myView = myView;
    m_controller = controller;

    ImVec4 m_clearColor = ImVec4(30.0f / 255, 30.0f / 255, 30.0f / 255, 30.0f / 255);

    m_VIEW_POLLING_RATE = 60;
    m_VIEW_INPUT_POLLING_RATE = 60;

    m_myView->SDLSetup(&m_renderer, &m_window);

    done = false;
    m_renderDone = true;
    m_inputDone = true;
}

View::~View()
{
    CleanupSDL(m_renderer, m_window);
    CleanupImGui();
}

void View::Render()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Initialize m_window

    // Initialize m_renderer and m_window
    if (m_renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return;
    }

    // Setup ImGui
    ImGuiIO &io = m_myView->ImGuiSetup();

    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer2_Init(m_renderer);

    pthread_t inputThreadId;
    pthread_create(&inputThreadId, nullptr, &View::threadEntry, this);

    const std::chrono::milliseconds frameDuration(1000 / m_VIEW_POLLING_RATE);
    auto startTime = std::chrono::high_resolution_clock::now();

#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        if (elapsed >= frameDuration)
        {
            HandleSDLEvents();
            RenderFrame(io);
            startTime = std::chrono::high_resolution_clock::now();
        }
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
    pthread_join(inputThreadId, nullptr);
}

void View::CleanupSDL(SDL_Renderer *m_renderer, SDL_Window *m_window)
{
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);
    if (m_window)
        SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void View::CleanupImGui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void View::HandleSDLEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        GetFrameEvents().push_back(event);
    }
    m_renderDone = false;
    for (SDL_Event &event : GetFrameEvents())
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window)))
        {
            done = true;
        }
    }
    if (m_inputDone)
        GetFrameEvents().clear();
    m_renderDone = true;
}

void View::RenderFrame(ImGuiIO &io)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    m_myView->RenderImGui(io);

    ImGui::Render();
    SDL_RenderSetScale(m_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
   
    m_myView->RenderSDL(*m_renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(m_renderer);
}


void View::SDL_EventHandlingLoop()
{
    const std::chrono::milliseconds frameDuration(1000 / m_VIEW_INPUT_POLLING_RATE);
    auto startTime = std::chrono::high_resolution_clock::now();
    while (!done)
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        m_inputDone = false;
        if (elapsed >= frameDuration)
        {
            for (SDL_Event &event : GetFrameEvents())
            {
                m_myView->HandleSDLEvents(event);
            }
            if (m_renderDone)
                GetFrameEvents().clear();
            m_inputDone = true;
            startTime = std::chrono::high_resolution_clock::now();
        }
    }
}