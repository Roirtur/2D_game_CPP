#include <cassert>
#include "../headers/Window.hpp"

Window::Window() {
    this->width     = 900;
    this->height    = 600;
    this->isOpen    = true;
    this->title     ="default";
    this->window    = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    assert(this->window);

    this->render    = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    assert(this->render);
}

Window::Window(std::string title, int width, int height) {
    this->width     = width;
    this->height    = height;
    this->isOpen    = true;
    this->title     = title;

    this->window    = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    assert(this->window);

    this->render    = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    assert(this->render);
    SDL_RaiseWindow(this->window);
}

Window::~Window() {
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->window);
}


bool Window::get_isOpen() {
    return this->isOpen;
}

void Window::set_isOpen(bool value) {
    this->isOpen = value;
}


void Window::resize() {
    SDL_GetWindowSize(this->window, &this->width, &this->height);
    SDL_RenderSetLogicalSize(this->render, this->width, this->height);
}

void Window::clear_screen() {
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
    SDL_RenderClear(this->render);
}

void Window::draw_screen() {
    SDL_RenderPresent(this->render);
}

SDL_Renderer* Window::get_render() {
    return this->render;
}

void Window::close_screen() {
    this->isOpen = false;
}

SDL_Window* Window::get_window() {
    return this->window;
}
