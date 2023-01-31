#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include "Enum.hpp"

#define PLAYER_STEP 3
#define WALK_SPEED 1
#define RUN_SPEED 2
#define ANIMATION_SPEED 70
#define EMPTY_PIX_X 10
#define EMPTY_PIX_Y 5

class Player
{
protected:
    SDL_Rect spritebox;
    SDL_Rect hitbox;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect sprite;
    int frame_number;
    int timer_retain;
    void (Player::*current_animation)();
    double speed;
    SDL_Renderer* renderer;
    Direction current_direction;
    bool is_flip;
    int size_multiplicator_w;
    int size_multiplicator_h;



public:
    Player(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer);
    ~Player();

    void move_to(int x, int y);
    bool collision_check(SDL_Rect othex_spritebox, void (Player::*action)());
    void resize(int width, int height);
    void refresh_player();
    SDL_Rect get_spritebox();
    SDL_Rect get_hitbox();
    void spin_animation();
    int get_frame_number();
    void stand_animation();
    void walk_animation();
    void set_animation(void (Player::*animation_function)());
    void move_to(Direction direction);
    double get_speed();
    void set_speed(double speed);
    void change_sprite_sheet(char* image_path);
    void player_die();
    void show_hitbox();
};


#endif