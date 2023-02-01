#include "Sprite.hpp"


Sprite::Sprite(int x, int y, int width, int height, int img_width, int img_height, bool flip, char* image_path, SDL_Renderer* renderer) {
    SDL_Rect sprite1 = {x,y,img_width,img_height};
    this->on_sprite_rect = sprite1;

    this->renderer = renderer;

    SDL_Rect sprite_rect;
    this->spritebox = sprite_rect;
    this->resize(width, height);

    this->is_flip = false;
    change_sprite_sheet(image_path);
};
Sprite::~Sprite() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
};

SDL_Rect Sprite::get_spritebox() {
    return this->spritebox;
};
void Sprite::resize(int width, int height) {
    this->spritebox.w = width;
    this->spritebox.h = height;
};
void Sprite::change_sprite_sheet(char* image_path) {
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
void Sprite::move_sprite_texture(int x, int y) {
    this->on_sprite_rect.x = x;
    this->on_sprite_rect.y = y;
};
void Sprite::refresh_sprite() {
    SDL_RenderCopyEx(this->renderer, this->texture, &(this->on_sprite_rect), &(this->spritebox), 0, NULL, this->is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};
void Sprite::flip() {
    this->is_flip = !(this->is_flip);
};
