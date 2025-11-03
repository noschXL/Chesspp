#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "../../include/raylib-cpp.hpp"
#include <vector>

typedef uint ID;

struct TextureAtlas {
  std::vector<Texture>atlas;

  Texture GetTexture(ID id);
  void LoadImage(const char *path);
  void AddTexture(Texture texture);
  TextureAtlas();
  

};

extern Texture defaultTexture;
extern TextureAtlas entityTextures;
extern TextureAtlas backgroundTextures;
extern TextureAtlas tileTextures;

Texture GenDefaultTexture();

#endif // !TEXTURES_HPP
