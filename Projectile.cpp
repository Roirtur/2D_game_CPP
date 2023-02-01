#include "Projectile.hpp"


Projectile::Projectile(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer) {
    this->timer_retain = 0;
    this->frame_number = 0;
    this->speed = 1;
    this->renderer = renderer;
    this->is_flip = false;

    SDL_Rect sprite_rect;
    this->hitbox = sprite_rect;
    SDL_Rect sprite1 = {0,0,24,24};
    this->sprite = sprite1;

    move_to(x, y);
    resize(width, height);
    change_sprite_sheet(image_path);
};

Projectile::~Projectile() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
};

void Projectile::move_to(int x, int y) {
    this->hitbox.x = x;
    this->hitbox.y = y;
};

bool Projectile::is_hit() {
    return false;
};

void Projectile::resize(int width, int height) {
    this->hitbox.w = width;
    this->hitbox.h = height;
};

void Projectile::refresh_projectile() {
    SDL_RenderCopyEx(this->renderer, this->texture, &(this->sprite), &(this->hitbox), 0, NULL, this->is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};

SDL_Rect Projectile::get_hitbox() {
    return this->hitbox;
};

void Projectile::change_sprite_sheet(char* image_path) {
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        printf("Error: %s\n", IMG_GetError());
    }
    
    this->surface = IMG_Load(image_path);
    if (!this->surface) {
        printf("Error: %s\n", IMG_GetError());
    }

    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    if (!this->texture) {
        printf("Error: %s\n", SDL_GetError());;
    }
};

int Projectile::get_frame_number() {
    return this->frame_number;
};


void Projectile::move_to(Direction direction) {
    int new_position_x = this->hitbox.x;
    int new_position_y = this->hitbox.y;
    this->current_direction = direction;
    switch (direction) {
        case UP:
            new_position_y -= PROJECTILE_STEP*this->speed;
            break;
        case DOWN:
            new_position_y += PROJECTILE_STEP*this->speed;
            break;
        case RIGHT:
            new_position_x += PROJECTILE_STEP*this->speed;
            break;
        case LEFT:
            new_position_x -= PROJECTILE_STEP*this->speed;
            break;
    };
    this->hitbox.x = new_position_x;
    this->hitbox.y = new_position_y;
};

double Projectile::get_speed() {
    return this->speed;
};
void Projectile::set_speed(double speed) {
    this->speed = speed;
};