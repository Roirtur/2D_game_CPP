#include "Map.hpp"


Map::Map(int x, int y, int width, int height, int img_width, int img_height, char* image_path, SDL_Renderer* renderer) : GameObject(x,y,width,height,img_width,img_height, 0, DOWN,image_path,renderer) {
    this->renderer = renderer;

    SDL_Rect sprite1 = {0,0,width/3,height/3};
    this->sprite = sprite1;
    this->size_multiplicator_w = width/sprite.w;
    this->size_multiplicator_h = height/sprite.h;

    SDL_Rect sprite_rect;
    this->spritebox = sprite_rect;
    this->resize(width, height);

    this->is_flip = false;
    change_sprite_sheet(image_path);
    move_screen(0, 0);
};

Map::~Map() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
};

void Map::resize(int width, int height) {
    this->spritebox.w = width;
    this->spritebox.h = height;
};

void Map::refresh_map() {
 SDL_RenderCopyEx(this->renderer, this->texture, &(this->sprite), &(this->spritebox), 0, NULL, this->is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};

SDL_Rect Map::get_spritebox() {
    return this->spritebox;
};

void Map::change_sprite_sheet(char* image_path) {
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

void Map::move_screen(int x, int y) {
    this->spritebox.x = x;
    this->spritebox.x = y;
};

void Map::move_sprite_texture(int x, int y) {
    this->sprite.x = x;
    this->sprite.y = y;
};