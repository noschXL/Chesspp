#include <sys/types.h>
#include <vector>
#include "textures.hpp"
using namespace std;

typedef uint ID;

Texture defaultTexture;

TextureAtlas::TextureAtlas (){
  atlas.clear();
}
  
Texture TextureAtlas::GetTexture(ID id) {
  if (atlas.size() <= id) {
    return defaultTexture;
  }
  return atlas[id];
}

void TextureAtlas::LoadImage(const char *path) {
  atlas.push_back(LoadTexture(path));
}

void TextureAtlas::AddTexture(Texture texture){
  atlas.push_back(texture);
}

TextureAtlas entityTextures;
TextureAtlas backgroundTextures;
TextureAtlas tileTextures;


Texture GenDefaultTexture(){
  Image img = GenImageChecked(64, 64, 32, 32, PURPLE, BLACK);
  defaultTexture = LoadTextureFromImage(img);
  UnloadImage(img);
  return defaultTexture;
}

