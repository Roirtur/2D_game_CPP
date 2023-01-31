#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include "Enum.hpp"

#define PROJECTILE_STEP 3

class Projectile
{
protected:
    SDL_Rect hitbox;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect sprite;
    int frame_number;
    int timer_retain;
    double speed;
    SDL_Renderer* renderer;
    Direction current_direction;
    bool is_flip;


public:
    Projectile(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer);
    ~Projectile();

    void move_to(int x, int y);
    bool is_hit();
    void resize(int width, int height);
    void refresh_projectile();
    SDL_Rect get_hitbox();
    int get_frame_number();
    void move_to(Direction direction);
    double get_speed();
    void set_speed(double speed);
    void change_sprite_sheet(char* image_path);
};


#endif