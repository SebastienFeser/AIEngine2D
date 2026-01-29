// =============================================================================
// AIEngine2D - Main Entry Point
// =============================================================================

#include "core/logger.h"
#include <SDL.h>
#include <SDL_opengl.h>

namespace SebF2DEngine
{

class Engine
{
public:
    bool init()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
        {
            LOG_ERROR("SDL initialization failed: %s", SDL_GetError());
            return false;
        }

        // Set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Create window
        m_window = SDL_CreateWindow(
            "AIEngine2D - Test",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if (!m_window)
        {
            LOG_ERROR("Window creation failed: %s", SDL_GetError());
            return false;
        }

        // Create OpenGL context
        m_glContext = SDL_GL_CreateContext(m_window);
        if (!m_glContext)
        {
            LOG_ERROR("OpenGL context creation failed: %s", SDL_GetError());
            return false;
        }

        // Enable VSync
        SDL_GL_SetSwapInterval(1);

        LOG_INFO("Engine initialized successfully");
        LOG_INFO("Window: 800x600");
        LOG_INFO("OpenGL context created");
        LOG_INFO("Press ESC to exit");

        // Test all log levels
        LOG_WARNING("This is a warning test");
        LOG_ERROR("This is an error test (not a real error)");

        return true;
    }

    void run()
    {
        m_running = true;

        while (m_running)
        {
            handleEvents();
            update();
            render();
        }
    }

    void shutdown()
    {
        if (m_glContext)
        {
            SDL_GL_DeleteContext(m_glContext);
            m_glContext = nullptr;
        }

        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }

        SDL_Quit();
        LOG_INFO("Engine shutdown complete");
    }

private:
    void handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    m_running = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        m_running = false;
                    }
                    break;
            }
        }
    }

    void update()
    {
        // Game logic will go here
    }

    void render()
    {
        // Clear screen (cornflower blue - classic test color)
        glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        SDL_GL_SwapWindow(m_window);
    }

private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
    bool m_running = false;
};

} // namespace SebF2DEngine

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    SebF2DEngine::Engine engine;

    if (!engine.init())
    {
        return 1;
    }

    engine.run();
    engine.shutdown();

    return 0;
}
