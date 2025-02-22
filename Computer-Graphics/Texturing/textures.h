#ifndef TEXTURES_H
#define TEXTURES_H

#include "helpers.h"
#include <vector>
#include <string>
#include <map>

class textures {
    private:
        std::map<std::string, unsigned int> textures;
    public:
        void loadTextures(std::vector<std::string>);
        unsigned int getTextureId(std::string);
};

#endif