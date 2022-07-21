#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <map>
#include <algorithm>
#include <numeric>
#include <string>
#include "gd.h"
#include "classes/Tile.hpp"
#include "classes/Cell.hpp"
#include "classes/WaveFunctionCollapse.hpp"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int canvasRows = 20;

    // Adjust for different aspect ratios
    int canvasColumns = canvasRows / 2;

    // Resize tiles (in pixels)
    int tileResolutionX = 100;
    int tileResolutionY = 100;

    std::string path = __FILE__;
    auto pathEnd = path.find_last_of("/\\");
    auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);

    std::string imagePath = pathName + "/tiles/train-tracks";

    std::unordered_map<int, Tile> tiles = {
        { 0, Tile(imagePath + "/blank.png", { {"UP", "A"}, {"RIGHT", "A"}, {"DOWN", "A"}, {"LEFT", "A"} }, 0, tileResolutionX, tileResolutionY) },
        { 1, Tile(imagePath + "/down.png",  { {"UP", "A"}, {"RIGHT", "B"}, {"DOWN", "B"}, {"LEFT", "B"} }, 1, tileResolutionX, tileResolutionY) },
        { 2, Tile(imagePath + "/left.png",  { {"UP", "B"}, {"RIGHT", "A"}, {"DOWN", "B"}, {"LEFT", "B"} }, 2, tileResolutionX, tileResolutionY) },
        { 3, Tile(imagePath + "/right.png", { {"UP", "B"}, {"RIGHT", "B"}, {"DOWN", "B"}, {"LEFT", "A"} }, 3, tileResolutionX, tileResolutionY) },
        { 4, Tile(imagePath + "/up.png",    { {"UP", "B"}, {"RIGHT", "B"}, {"DOWN", "A"}, {"LEFT", "B"} }, 4, tileResolutionX, tileResolutionY) }
    };

    WaveFunctionCollapse wfc;
    wfc.setup(canvasRows, canvasColumns, pathName + "/output/train-tracks.png", &tiles);
    wfc.execute();

    return 0;
}
