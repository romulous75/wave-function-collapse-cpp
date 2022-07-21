#include "Cell.hpp"

Cell::Cell() {}
Cell::Cell(int x, int y, int i) : m_x(x), m_y(y), m_index(i) {}

void Cell::setTile(Tile *tile) {
    m_tile = tile;
}
