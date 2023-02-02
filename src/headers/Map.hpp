#ifndef MAP_HPP
#define MAP_HPP

#include "GameObject.hpp"

class Map : public GameObject
{
    public:
        Map(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer);
        ~Map();
};


#endif