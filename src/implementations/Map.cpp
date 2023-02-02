#include "../headers/Map.hpp"


Map::Map(int x, int y, int width, int height, int img_width, int img_height, char* image_path, SDL_Renderer* renderer) : GameObject(x,y,width,height,img_width,img_height, 0, DOWN,image_path,renderer) {

};

Map::~Map() {
};
