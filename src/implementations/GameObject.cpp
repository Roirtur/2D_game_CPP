#include "GameObject.hpp"


GameObject::GameObject(int x, int y, int width, int height, int img_width, int img_height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer) {
    Sprite* sprite {new Sprite{x, y, width, height, img_width, img_height, false, image_path, renderer}};
    this->sprite = sprite;
    this->renderer = renderer;
    this->hitbox = SDL_Rect{0,0,0,0};
    this->current_direction = direction;
    (img_width == 0) ? this->size_multiplicator_w = 1: this->size_multiplicator_w = width/img_width;
    (img_height == 0) ? this->size_multiplicator_h = 1: this->size_multiplicator_h = height/img_height;
    (speed == 0) ? this->speed = 1 : this->speed = speed;
    move_to(x, y);
    resize(width, height);
};

GameObject::~GameObject() {
    
};

SDL_Rect GameObject::get_hitbox() {
    return hitbox;
};

Sprite GameObject::get_sprite() {
    return *sprite;
};

void GameObject::move_to(int x, int y) {
    sprite->spritebox.x = x;
    sprite->spritebox.y = y;
    hitbox.x = x + (EMPTY_PIX_X/2) * size_multiplicator_w;
    hitbox.y = y + (EMPTY_PIX_Y/2) * size_multiplicator_h;
};
void GameObject::resize(int width, int height) {
    sprite->spritebox.w = width;
    sprite->spritebox.h = height;
    hitbox.w = (sprite->img_rect.w - EMPTY_PIX_X) * size_multiplicator_w;
    hitbox.h = (sprite->img_rect.h - EMPTY_PIX_Y) * size_multiplicator_h;
};
void GameObject::show_object() {
    show_hitbox();
    SDL_RenderCopyEx(renderer, sprite->texture, &(sprite->img_rect), &(sprite->spritebox), 0, NULL, sprite->is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};

void GameObject::move_to(Direction direction) {
    int new_position_x = sprite->spritebox.x;
    int new_position_y = sprite->spritebox.y;
    current_direction = direction;
    switch (direction) {
        case UP:
            new_position_y -= MOVING_STEP*speed;
            break;
        case DOWN:
            new_position_y += MOVING_STEP*speed;
            break;
        case RIGHT:
            new_position_x += MOVING_STEP*speed;
            break;
        case LEFT:
            new_position_x -= MOVING_STEP*speed;
            break;
    };
    sprite->spritebox.x = new_position_x;
    sprite->spritebox.y = new_position_y;

    hitbox.x = sprite->spritebox.x + (EMPTY_PIX_X/2) * size_multiplicator_w;
    hitbox.y = sprite->spritebox.y + (EMPTY_PIX_Y/2) * size_multiplicator_h;
};


void GameObject::show_hitbox() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    SDL_RenderFillRect(renderer, &(hitbox));
};

bool GameObject::collision_check(SDL_Rect other_hitbox) {
    SDL_Rect result;
    //printf("hitbox 1: %d %d %d %d\n hitbox 2: %d %d %d %d\n", hitbox.x, hitbox.y, hitbox.w, hitbox.h, other_hitbox.x, other_hitbox.y, other_hitbox.w, other_hitbox.h);
    return SDL_IntersectRect(&hitbox, &other_hitbox, &result) == SDL_TRUE;
};


void GameObject::set_speed(double new_speed) {
    this->speed = new_speed;
};