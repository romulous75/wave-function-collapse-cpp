#ifndef HEADER_CELL
#define HEADER_CELL

#include "Tile.hpp"

struct Cell
{
    Cell();
    Cell(int x, int y, int i);
    void setTile(Tile *tile);

    // Tile to be drawn
    Tile * m_tile;

    // Are we collapsed
    bool m_collapsed = false;

    // This cells index
    int m_index;

    // The cells x coordinate on the grid
    int m_x;

    // The cells y coordinate on the grid
    int m_y;
};

#endif