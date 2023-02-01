#include "Sprite.hpp"


Sprite::Sprite(int x, int y, int width, int height, int img_width, int img_height, bool flip, char* image_path, SDL_Renderer* renderer) {
    this->img_rect = {x,y,img_width,img_height};
    this->spritebox = {x,y,img_width,img_height};
    this->renderer = renderer;

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
