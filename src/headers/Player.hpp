#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

#define PLAYER_STEP 3
#define WALK_SPEED 1
#define RUN_SPEED 2
#define ANIMATION_SPEED 70

class Player : public GameObject
{
protected:
    int frame_number;
    int timer_retain;
    void (Player::*current_animation)();

public:
    Player(int x, int y, int width, int height, int img_width, int img_height, double speed, Direction direction, char* image_path, SDL_Renderer* renderer);
    ~Player();

    void spin_animation();
    void stand_animation();
    void walk_animation();
    void set_animation(void (Player::*animation_function)());
    void player_die();
};


#endif