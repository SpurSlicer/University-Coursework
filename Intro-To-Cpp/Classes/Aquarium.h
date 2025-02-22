#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#ifndef AQUARIUM_H
#define AQUARIUM_H
struct Fish {
    std::string name;
    int gallons_required;
};
class Aquarium {
    private:
        std::string aquarist_name;
        static const int tank_size_gallons = 12;
        int gallons_used = 0;
        std::vector<Fish> available_fish;
        std::vector<Fish> selected_fish;
    public:
        Aquarium (std::string);
        bool checker(int n);
        std::string getAquaristName();
        int getGallonsUsed();
        bool loadFish(std::string);
        void displayAvailableFish();
        int addFish(std::string);
        bool removeFish(std::string);
        bool writeAquariumContents(std::string);
};
#endif