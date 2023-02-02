#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "GameObject.hpp"

#define PROJECTILE_STEP 3

class Projectile : public GameObject
{
protected:
    int frame_number;
    int timer_retain;

public:
    Projectile(int x, int y, int width, int height, int img_width, int img_height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer);
    ~Projectile();

    int get_frame_number();
};


#endif