#pragma once

#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <string>
#include <SDL2/SDL.h>

class Window {
    protected:
        int             width;
        int             height;
        SDL_Window*     window;
        SDL_Renderer*   render;
        SDL_Event       event;
        bool            isOpen;
        std::string     title;

    public:
        //constructeurs
        Window();
        Window(std::string title, int width, int height);
        //Destructeur
        ~Window();

        SDL_Renderer*   get_render();
        bool            get_isOpen();
        void            set_isOpen(bool value);
        void            resize();
        void            clear_screen();
        void            draw_screen();
        void            close_screen();
        SDL_Window*     get_window();
};

#endif //FENETRE_HPP