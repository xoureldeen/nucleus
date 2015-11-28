/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/common.h"
#include "nucleus/graphics/graphics.h"
#include "nucleus/ui/length.h"
#include "nucleus/ui/style.h"

#include <string>

namespace ui {

// Forward declarations
class UI;

struct WidgetInput {
    struct WidgetVertex {
        F32 position[2];
    } vertex[4];
};

class Widget {
protected:
    // Texture produced after rendering the contents of this widget
    gfx::Texture* texture;

public:
    // UI Manager
    UI* manager;

    // Parent widget if applicable
    Widget* parent = nullptr;

    std::string id;

    Style style;

    /**
     * Search children nodes for a particular identifier
     * @param[in]  query  Identifier to search for
     * @return            Pointer to the found widget or nullptr otherwise
     */
    virtual Widget* find(const std::string& query);

    /**
     * Pass the rendering commands to the UI command buffer
     * @param[in]  cmdBuffer  Command buffer to store the rendering commands in
     */
    virtual void render() = 0;

    static Length correctHeight(Length height);

    static float getCoordinateX(Length x);
    static float getCoordinateY(Length y);
};

}  // namespace ui
