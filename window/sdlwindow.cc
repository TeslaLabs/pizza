#include "sdlwindow.h"
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <string>
#include <gl/gl_headers.h>
#include <SDL2/SDL.h>
#include "../log/ilog.h"

static bool INITIALIZED = false;

SdlWindow::SdlWindow(ILog& log)
  : log_ { log },
    title_ { "Untitled" },
    resize_func_ { [](int width, int height) {} },
    window_handle_ { nullptr },
    width_ { 640 },
    height_ { 480 }
{
  if (!INITIALIZED) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
      std::stringstream error_message;
      error_message << "Could not initialize: " << SDL_GetError();
      log_.Error(error_message.str());
    }
    INITIALIZED = true;

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2)) {
      log_.Error("Error setting OpenGL major version");
    }
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1)) {
      log_.Error("Error setting OpenGL minor version");
    }

    window_handle_ = SDL_CreateWindow(title_.c_str(),
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      width_, height_,
                                      SDL_WINDOW_OPENGL |
                                      SDL_WINDOW_HIDDEN);
    if (window_handle_ == nullptr) {
      log_.Error("Could not create SDL Window");
    }

    glcontext_ = SDL_GL_CreateContext(window_handle_);

    if (glcontext_ == nullptr) {
      log_.Error("Could not create OpenGL context");
    }
  }
}

SdlWindow::~SdlWindow() {
  SDL_GL_DeleteContext(glcontext_);
  SDL_DestroyWindow(window_handle_);
  SDL_Quit();
}

std::string SdlWindow::title() const {
  return title_;
}

void SdlWindow::set_title(const std::string& title) {
  title_ = title;
  SDL_SetWindowTitle(window_handle_, title_.c_str());
}

unsigned int SdlWindow::width() const {
  return width_;
}

unsigned int SdlWindow::height() const {
  return height_;
}

void SdlWindow::Resize(int width, int height) {
  width_ = width;
  height_ = height;
  SDL_SetWindowSize(window_handle_, width_, height_);
  resize_func_(width_, height_);
}

void SdlWindow::set_resize_func(std::function<void(int,int)> resize_func) {
  resize_func_ = resize_func;
}

void SdlWindow::ShowCursor() {
  SDL_ShowCursor(SDL_ENABLE);
}

void SdlWindow::HideCursor() {
  SDL_ShowCursor(SDL_DISABLE);
}

void SdlWindow::SetCursorPosition(int x, int y) {
  SDL_WarpMouseInWindow(window_handle_, x, y);
}

void SdlWindow::Show() {
  SDL_ShowWindow(window_handle_);
  SDL_RaiseWindow(window_handle_);
}

void SdlWindow::Hide() {
  SDL_HideWindow(window_handle_);
}

void SdlWindow::Update() {
  SDL_GL_SwapWindow(window_handle_);
}
