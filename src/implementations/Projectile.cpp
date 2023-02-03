#include "Projectile.hpp"


Projectile::Projectile(int x, int y, int width, int height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer) 
: GameObject(x, y, width, height, speed, direction, image_path, renderer) {
    this->timer_retain = 0;
    this->frame_number = 0;
};

Projectile::~Projectile() {
};

int Projectile::get_frame_number() {
    return this->frame_number;
};