/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "ui.h"
#include "nucleus/core/config.h"
#include "nucleus/ui/screens/screen_logo.h"

// Platform specific drawing contexts
#ifdef NUCLEUS_PLATFORM_WINDOWS
#include "wrappers/windows/window.h"
extern Window* window;
#endif

namespace ui {

UI::UI(std::shared_ptr<gfx::IBackend> graphics) : graphics(std::move(graphics)), language() {
}

bool UI::initialize() {
    language.open(config.language);

    thread = std::thread([this]{
        task();
    });

    return true;
}

void UI::task() {
    // Prepare context
#ifdef NUCLEUS_PLATFORM_WINDOWS
    //TODO//wglSwapIntervalEXT(0);
#endif

    // Prepare state
    /*TODO*//*glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

    push_screen(new ScreenLogo());
    while (true) {
        // Process events
        if (surfaceChanged) {
            resize();
        }

        // Clear buffers
        //TODO//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Display screens
        auto it = m_screens.begin();
        while (it != m_screens.end()) {
            Screen* screen = *it;
            screen->prologue();
            screen->render();
            screen->update();
            screen->epilogue();

            if (screen->finished) {
                delete screen;
                it = m_screens.erase(it);
            } else {
                it++;
            }
        }

        // Add new screens
        while (!m_new_screens.empty()) {
            Screen* screen = m_new_screens.front();
            m_screens.push_back(screen);
            m_new_screens.pop();
        }

        // TODO: Adjusting the framerate manually at 60 FPS is a terrible idea
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

void UI::resize() {
    //TODO//glViewport(0, 0, surfaceWidth, surfaceHeight);
    surfaceChanged = false;
}

void UI::push_screen(Screen* screen) {
    m_new_screens.push(screen);
}

}  // namespace ui
