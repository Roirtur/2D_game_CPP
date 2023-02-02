#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {
    public:
        SDL_Renderer* renderer;
        SDL_Rect spritebox;
        SDL_Surface *surface;
        SDL_Texture *texture;
        SDL_Rect img_rect;
        bool is_flip;


        Sprite(int x, int y, int width, int height, int img_width, int img_height, bool flip, char* image_path, SDL_Renderer* renderer);
        ~Sprite();

        SDL_Rect get_spritebox();
        void change_sprite_sheet(char* image_path);
        void move_sprite_texture(int x, int y);
        void flip();
};

#endif