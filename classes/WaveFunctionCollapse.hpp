#ifndef HEADER_WFC
#define HEADER_WFC

#include <vector>
#include <unordered_map>
#include <string>
#include "gd.h"
#include "Tile.hpp"
#include "Cell.hpp"

class WaveFunctionCollapse
{
public:
    void analyzeTiles(Tile *);
    void getCommon(std::vector<int> &, std::vector<int> &, std::vector<int> &);
    void writeAndClose();
    void setup(int, int, std::string, std::unordered_map<int, Tile>*);
    void execute();

private:
    std::unordered_map<int, Tile> *m_tiles;
    int m_pixelWidth;
    int m_pixelHeight;
    int m_canvasRows;
    int m_canvasColumns;
    gdImagePtr m_canvas;
    std::unordered_map<int, Cell> m_grid;
    std::vector<int> m_allTiles;
    std::string m_outputFile;
};


#endif