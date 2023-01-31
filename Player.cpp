#include "Player.hpp"


Player::Player(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer) {
    this->timer_retain = 0;
    this->frame_number = 0;
    this->renderer = renderer;

    SDL_Rect sprite1 = {0,0,24,24};
    this->sprite = sprite1;
    this->size_multiplicator_w = width/sprite.w;
    this->size_multiplicator_h = height/sprite.h;

    SDL_Rect sprite_rect;
    this->spritebox = sprite_rect;
    this->move_to(x, y);
    this->resize(width, height);

    this->current_animation = &Player::stand_animation;
    this->speed = 1;
    this->is_flip = false;
    change_sprite_sheet(image_path);
};

Player::~Player() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
};

void Player::move_to(int x, int y) {
    this->spritebox.x = x;
    this->spritebox.y = y;
    this->hitbox.x = spritebox.x + (EMPTY_PIX_X/2) * size_multiplicator_w;
    this->hitbox.y = spritebox.y + (EMPTY_PIX_Y/2) * size_multiplicator_h;
};

bool Player::collision_check(SDL_Rect othex_hitbox, void (Player::*action)()) {
    SDL_Rect result;
    if (SDL_IntersectRect(&hitbox, &othex_hitbox, &result) == SDL_TRUE) {
        (this->*action)();
    }
    return SDL_IntersectRect(&hitbox, &othex_hitbox, &result) == SDL_TRUE;
};

void Player::resize(int width, int height) {
    this->spritebox.w = width;
    this->spritebox.h = height;
    this->hitbox.w = (sprite.w - EMPTY_PIX_X) * size_multiplicator_w;
    this->hitbox.h = (sprite.h - EMPTY_PIX_Y) * size_multiplicator_h;
    printf("resized\n");
    printf("sprite %d %d\n",hitbox.w,hitbox.h);
    printf("hitbox %d %d\n",hitbox.w,hitbox.h);
};

void Player::refresh_player() {
    //show_hitbox();
    (this->*current_animation)();
    SDL_RenderCopyEx(this->renderer, this->texture, &(this->sprite), &(this->spritebox), 0, NULL, this->is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};

SDL_Rect Player::get_spritebox() {
    return this->spritebox;
}

void Player::stand_animation() {
    this->frame_number = 0;
    this->timer_retain = 0;
    this->sprite.x = 0;
    change_sprite_sheet((char*)"../Link_Standing.png");
}

void Player::spin_animation() {
    int ticks_ms = SDL_GetTicks();
    this->sprite.y = 0;
    this->is_flip = false;
    change_sprite_sheet((char*)"../Spin_Spritesheet.png");

    if (ticks_ms > this->timer_retain + ANIMATION_SPEED/this->speed) {
        this->timer_retain = ticks_ms;
        this->frame_number++;
        this->frame_number%=4;
        this->sprite.x = (frame_number * 32)%(4*32);
    }
}

void Player::walk_animation() {
    int ticks_ms = SDL_GetTicks();
    change_sprite_sheet((char*)"../Walk_Spritesheet.png");

    if (ticks_ms > this->timer_retain + ANIMATION_SPEED/this->speed) {
        this->timer_retain = ticks_ms;
        this->frame_number++;
        this->frame_number%=8;
        this->sprite.x = (frame_number * 32)%(8*32);
        switch (this->current_direction) {
            case DOWN:
                this->sprite.y = 0;
                this->is_flip = false;
                break;
            case UP:
                this->sprite.y = 50;
                this->is_flip = false;
                break;
            case LEFT:
                this->sprite.y = 25;
                this->is_flip = false;
                break;
            case RIGHT:
                this->sprite.y = 25;
                this->is_flip = true;
            break;
        }
    }
}

void Player::change_sprite_sheet(char* image_path) {
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
}

int Player::get_frame_number() {
    return this->frame_number;
}

void Player::set_animation(void (Player::*animation_function)()) {
    this->current_animation = animation_function;
}


void Player::move_to(Direction direction) {
    int new_position_x = this->spritebox.x;
    int new_position_y = this->spritebox.y;
    this->current_direction = direction;
    switch (direction) {
        case UP:
            new_position_y -= PLAYER_STEP*this->speed;
            break;
        case DOWN:
            new_position_y += PLAYER_STEP*this->speed;
            break;
        case RIGHT:
            new_position_x += PLAYER_STEP*this->speed;
            break;
        case LEFT:
            new_position_x -= PLAYER_STEP*this->speed;
            break;
    };
    this->spritebox.x = new_position_x;
    this->spritebox.y = new_position_y;

    this->hitbox.x = spritebox.x + (EMPTY_PIX_X/2) * size_multiplicator_w;
    this->hitbox.y = spritebox.y + (EMPTY_PIX_Y/2) * size_multiplicator_h;
}

double Player::get_speed() {
    return this->speed;
}
void Player::set_speed(double speed) {
    this->speed = speed;
}

void Player::player_die() {
    this->set_animation(&Player::spin_animation);
}

void Player::show_hitbox() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    SDL_RenderFillRect(renderer, &(hitbox));
}

SDL_Rect Player::get_hitbox() {
    return hitbox;
}