#ifndef MAP_HPP
#define MAP_HPP

#include "GameObject.hpp"

class Map : public GameObject
{
    public:
        Map(int x, int y, int width, int height, int img_width, int img_height, char* image_path, SDL_Renderer* renderer);
        ~Map();

        void resize(int width, int height);
        void refresh_map();
        SDL_Rect get_spritebox();
        void change_sprite_sheet(char* image_path);
        void move_screen(int x, int y);
        void move_sprite_texture(int x, int y);
};


#endif