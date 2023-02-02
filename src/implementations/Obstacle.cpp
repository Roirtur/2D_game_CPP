#include "../headers/Obstacle.hpp"

Obstacle::Obstacle(int x, int y, int width, int height, char* image_path) 
: GameObject(x, y, width, height, 0, DOWN, image_path, renderer)
{
}

Obstacle::~Obstacle()
{
}