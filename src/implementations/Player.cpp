#include "Player.hpp"


Player::Player(int x, int y, int width, int height, int img_width, int img_height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer) 
: GameObject(x, y, width, height, img_width, img_height, speed, direction, image_path, renderer) {
    this->timer_retain = 0;
    this->frame_number = 0;
    
    this->current_animation = &Player::stand_animation;
};

Player::~Player() {
};

void Player::stand_animation() {
    this->frame_number = 0;
    this->timer_retain = 0;
    this->sprite->img_rect.x = 0;
    sprite->change_sprite_sheet((char*)"../Link_Standing.png");
};

void Player::spin_animation() {
    int ticks_ms = SDL_GetTicks();
    sprite->img_rect.y = 0;
    sprite->is_flip = false;
    sprite->change_sprite_sheet((char*)"../Spin_Spritesheet.png");

    if (ticks_ms > timer_retain + ANIMATION_SPEED/speed) {
        this->timer_retain = ticks_ms;
        this->frame_number++;
        this->frame_number%=4;
        sprite->img_rect.x = (frame_number * 32)%(4*32);
    }
};

void Player::walk_animation() {
    int ticks_ms = SDL_GetTicks();
    sprite->change_sprite_sheet((char*)"../Walk_Spritesheet.png");

    if (ticks_ms > timer_retain + ANIMATION_SPEED/speed) {
        this->timer_retain = ticks_ms;
        this->frame_number++;
        this->frame_number%=8;
        sprite->img_rect.x = (frame_number * 32)%(8*32);
        switch (this->current_direction) {
            case DOWN:
                sprite->img_rect.x = 0;
                sprite->is_flip = false;
                break;
            case UP:
                sprite->img_rect.y = 50;
                sprite->is_flip = false;
                break;
            case LEFT:
                sprite->img_rect.y = 25;
                sprite->is_flip = false;
                break;
            case RIGHT:
                sprite->img_rect.y = 25;
                sprite->is_flip = true;
            break;
        }
    }
};

void Player::set_animation(void (Player::*animation_function)()) {
    this->current_animation = animation_function;
};

void Player::player_die() {
    this->set_animation(&Player::spin_animation);
};