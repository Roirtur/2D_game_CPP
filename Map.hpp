#ifndef MAP_HPP
#define MAP_HPP

#include "GameObject.hpp"

class Map : public GameObject
{
    protected:
        SDL_Rect spritebox;
        SDL_Surface *surface;
        SDL_Texture *texture;
        SDL_Rect sprite;
        SDL_Renderer* renderer;
        bool is_flip;
        int size_multiplicator_w;
        int size_multiplicator_h;



    public:
        Map(int width, int height, char* image_path, SDL_Renderer* renderer);
        ~Map();

        void resize(int width, int height);
        void refresh_map();
        SDL_Rect get_spritebox();
        void change_sprite_sheet(char* image_path);
        void move_screen(int x, int y);
        void move_sprite_texture(int x, int y);
};


#endif