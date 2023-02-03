#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#include "AllClass.hpp"
#include "AllControllers.hpp"

bool init_sdl(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error INIT SDL" << std::endl;
        return false;
    }
    return true;
}

int main(int ac, char **av) {
    assert(init_sdl());

//---------------------------------------------------------------------------------------------------

    Window* screen { new Window{ "Window", 1000, 700 } };

//---------------------------------------------------------------------------------------------------

    Map* map { new Map{0, 0, 1000, 700, (char*)"../ressources/spritesheets/map.png", screen->get_render()} };
    map->change_img_size(600,300);

//---------------------------------------------------------------------------------------------------

    Player* player { new Player{100, 280, 72, 72, 2, DOWN, (char *)"../ressources/spritesheets/Link_Standing.png", screen->get_render()}};
    player->change_img_size(24,24);

//---------------------------------------------------------------------------------------------------

    std::vector<Projectile*> all_projectile_array;

    Projectile* projectile1 { new Projectile{500, 500, 24, 24, 1, DOWN, (char *)"../ressources/spritesheets/Link_Standing.png", screen->get_render()} };
    projectile1->change_img_size(24,24);
    all_projectile_array.push_back(projectile1);
    
    Projectile* projectile2 { new Projectile{20, 20, 24, 24, 1, DOWN, (char *)"../ressources/spritesheets/Link_Standing.png", screen->get_render()} };
    projectile2->change_img_size(24,24);
    all_projectile_array.push_back(projectile2);

//---------------------------------------------------------------------------------------------------

    Obstacle* rock {new Obstacle(0, 0, 72, 72, (char *)"../ressources/spritesheets/Rock.png", screen->get_render())};

//---------------------------------------------------------------------------------------------------

    ControllerCollision* controllerCollision { new ControllerCollision() };

//---------------------------------------------------------------------------------------------------
    SDL_Event event;

    while (screen->get_isOpen()) {
        SDL_PumpEvents();
        const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) screen->close_screen();
        }

        if (keyboard_state[SDL_SCANCODE_A]) {
            player->move_to(LEFT);
            player->set_animation(&Player::walk_animation);
        }
        if (keyboard_state[SDL_SCANCODE_D]) {
            player->move_to(RIGHT);
            player->set_animation(&Player::walk_animation);
        }
        if (keyboard_state[SDL_SCANCODE_W]) {
            player->move_to(UP);
            player->set_animation(&Player::walk_animation);
        }
        if (keyboard_state[SDL_SCANCODE_S]) {
            player->move_to(DOWN);
            player->set_animation(&Player::walk_animation);
        }
        if (keyboard_state[SDL_SCANCODE_SPACE]) {
            player->set_animation(&Player::spin_animation);
        }
        if (!(keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_SPACE])) {
            player->set_animation(&Player::stand_animation);
        }
        if (keyboard_state[SDL_SCANCODE_LSHIFT]) {
            player->set_speed(RUN_SPEED);
        } else {
            player->set_speed(WALK_SPEED);
        }
        screen->resize();

        screen->clear_screen();
        map->show_object();
        for (Projectile* projectile: all_projectile_array) {
            /*
            if (player->collision_check(projectile->get_hitbox())) {
                printf("true\n");
            } else {
                printf("false\n");
            }
            */
            projectile->show_object();
        }
        //printf("Player %d %d %d %d\n", player->get_hitbox().x, player->get_hitbox().y, player->get_hitbox().w, player->get_hitbox().h);
        //printf("Projectile %d %d\n", projectile1->get_hitbox().x, projectile1->get_hitbox().y);
        player->show_object();
        rock->show_object();
        screen->draw_screen();

        SDL_Delay(16);
    }

    delete screen;
    delete player;

    SDL_Quit();
    return EXIT_SUCCESS;

}