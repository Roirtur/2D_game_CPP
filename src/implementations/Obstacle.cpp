#include "../headers/Obstacle.hpp"

Obstacle::Obstacle(int x, int y, int width, int height, char* image_path, SDL_Renderer* renderer) 
: GameObject(x, y, width, height, 0, DOWN, image_path, renderer)
{
}

Obstacle::~Obstacle()
{
}