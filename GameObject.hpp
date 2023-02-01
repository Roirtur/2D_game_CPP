#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include "Enum.hpp"
#include "Sprite.hpp"

#define EMPTY_PIX_X 6
#define MOVING_STEP 4
#define EMPTY_PIX_Y 3

class GameObject {
    protected:
        Sprite* sprite;
        SDL_Rect hitbox;

        SDL_Renderer* renderer;

        int size_multiplicator_w;
        int size_multiplicator_h;

        Direction current_direction;
        double speed;
        

    public:
        GameObject(int x, int y, int width, int height, int img_width, int img_height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer);
        ~GameObject();

        SDL_Rect get_hitbox();
        Sprite get_sprite();

        bool collision_check(SDL_Rect othex_hitbox);

        void move_to(int x, int y);
        void resize(int width, int height);
        void show_object();
        void move_to(Direction direction);
        void show_hitbox();
        void set_speed(double new_speed);
};

#endif