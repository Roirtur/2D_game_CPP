#include "Sprite.hpp"


Sprite::Sprite(int x, int y, int width, int height, bool flip, char* image_path, SDL_Renderer* renderer) {
    this->renderer = renderer;
    change_sprite_sheet(image_path);
    this->img_rect = {0,0,this->surface->w,this->surface->h};
    this->spritebox = {x,y,this->surface->w,this->surface->h};

    this->is_flip = false;
};
Sprite::~Sprite() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
};

SDL_Rect Sprite::get_spritebox() {
    return this->spritebox;
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
    this->img_rect.x = x;
    this->img_rect.y = y;
};
void Sprite::flip() {
    this->is_flip = !(this->is_flip);
};
