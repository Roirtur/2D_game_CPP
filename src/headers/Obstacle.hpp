#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "GameObject.hpp"

class Obstacle : public GameObject
{
private:

public:
    Obstacle(int x, int y, int width, int height, char* image_path);
    ~Obstacle();
};


#endif