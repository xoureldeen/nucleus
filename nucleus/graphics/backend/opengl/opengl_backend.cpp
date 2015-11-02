/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "opengl_backend.h"
#include "nucleus/logger/logger.h"
#include "nucleus/graphics/backend/opengl/opengl_command_buffer.h"

namespace gfx {

OpenGLBackend::OpenGLBackend() : IBackend() {
}

OpenGLBackend::~OpenGLBackend() {
}

bool OpenGLBackend::initialize(DisplayHandler display) {
#if defined(NUCLEUS_PLATFORM_WINDOWS)
    // Retrieving OpenGL extension pointers requires in Windows owning a context
    HGLRC dummyRc = wglCreateContext(display);
    wglMakeCurrent(display, dummyRc);
    if (!gfx::initializeOpenGL()) {
        logger.warning(LOG_GRAPHICS, "OpenGLBackend::initialize: Could not initialize all OpenGL extensions");
        return false;
    }
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(dummyRc);

    // Create context and make it current
    static const int contextAttribs[] = { WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB, 0 };
    context = wglCreateContextAttribsARB(display, 0, contextAttribs);
    if (!context) {
        logger.warning(LOG_GRAPHICS, "OpenGLBackend::initialize: wglCreateContextAttribsARB failed");
        return false;
    }
    if (!wglMakeCurrent(display, context)) {
        logger.warning(LOG_GRAPHICS, "OpenGLBackend::initialize: wglMakeCurrent failed");
        return false;
    }
#elif defined(NUCLEUS_PLATFORM_LINUX) || defined(NUCLEUS_PLATFORM_OSX)
    XVisualInfo* info = glXChooseVisual(display, 0, nullptr/*TODO*/);
    context = glXCreateContext(display, info, NULL, GL_TRUE);
    if (!context) {
        logger.warning(LOG_GRAPHICS, "OpenGLBackend::initialize: glXCreateContext failed");
        return false;
    }
    if (!glXMakeCurrent(display, 0/*TODO*/, context)) {
        logger.warning(LOG_GRAPHICS, "OpenGLBackend::initialize: glXMakeCurrent failed");
        return false;
    }
#elif defined(NUCLEUS_PLATFORM_ANDROID) || defined(NUCLEUS_PLATFORM_IOS)
#endif
    return true;
}

ICommandQueue* OpenGLBackend::createCommandQueue() {
    return nullptr;
}

ICommandBuffer* OpenGLBackend::createCommandBuffer() {
    ICommandBuffer* commandBuffer = new OpenGLCommandBuffer();
    return commandBuffer;
}

void OpenGLBackend::createPipeline() {
}

void OpenGLBackend::createShader() {
}

}  // namespace gfx
