#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#include "Window.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Map.hpp"
#include "Sprite.hpp"

bool init_sdl(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error INIT SDL" << std::endl;
        return false;
    }
    return true;
}

int main(int ac, char **av) {
    assert(init_sdl());

    Window* screen { new Window{ "Window", 1000, 700 } };
    Map* map { new Map{0, 0, 1000, 700, 330, 250, (char*)"../map.png", screen->get_render()} };
    Player* player { new Player{100, 280, 72, 72, 24, 24, 2, DOWN, (char *)"../Link_Standing.png", screen->get_render()}};

    std::vector<Projectile*> all_projectile_array;

    Projectile* projectile1 { new Projectile{500, 500, 24, 24, 24, 24, 0, DOWN, (char *)"../Link_Standing.png", screen->get_render()} };
    all_projectile_array.push_back(projectile1);
    
    Projectile* projectile2 { new Projectile{20, 800, 24, 24, 24, 24, 0, DOWN, (char *)"../Link_Standing.png", screen->get_render()} };
    all_projectile_array.push_back(projectile2);
    
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
        /*
        Here is were we can add things to appear
        */
        for (Projectile* projectile: all_projectile_array) {
            player->collision_check(projectile->get_hitbox(), &Player::player_die);
            projectile->refresh_projectile();
        }
        //printf("Player %d %d %d %d\n", player->get_hitbox().x, player->get_hitbox().y, player->get_hitbox().w, player->get_hitbox().h);
        //printf("Projectile %d %d\n", projectile1->get_hitbox().x, projectile1->get_hitbox().y);
        player->refresh_player();
        screen->draw_screen();

        SDL_Delay(16);
    }

    delete screen;
    delete player;

    SDL_Quit();
    return EXIT_SUCCESS;

}