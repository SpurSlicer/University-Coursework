#include "textures.h"

void textures::loadTextures(std::vector<std::string> names) {
    for (std::string name : names) {
        this->textures.insert(std::pair<std::string, unsigned int>(name, LoadTexBMP(name.c_str())));
    }
}

unsigned int textures::getTextureId(std::string name) {
    return this->textures.at(name);
}