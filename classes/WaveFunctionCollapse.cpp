#include "WaveFunctionCollapse.hpp"
#include "Cell.hpp"
#include <iostream>

void WaveFunctionCollapse::setup(int canvasRows, int canvasColumns, std::string outputFile, std::unordered_map<int, Tile>* tiles)
{
    int gridIndex;
    m_tiles = tiles;
    m_canvasRows = canvasRows;
    m_canvasColumns = canvasColumns;
    m_outputFile = outputFile;

    for (size_t i = 0; i < m_tiles->size(); i++) {
        analyzeTiles(&(*m_tiles)[i]);
        m_allTiles.push_back((*m_tiles)[i].getIndex());
    }

    m_pixelWidth = (*m_tiles)[0].getWidth();
    m_pixelHeight = (*m_tiles)[0].getHeight();

    // Fill the grid with Cells
    for (int x = 0; x < m_canvasRows; x++) {
        for (int y = 0; y < m_canvasColumns; y++) {
            gridIndex = y * m_canvasRows + x;
            m_grid[gridIndex] = Cell(x, y, gridIndex);
        }
    }

    // Initialise GD
    int canvasPixelsWidth = m_canvasRows * m_pixelWidth;
    int canvasPixelsHeight = m_canvasColumns * m_pixelHeight;

    m_canvas = gdImageCreateTrueColor(canvasPixelsWidth, canvasPixelsHeight);
}

void WaveFunctionCollapse::analyzeTiles(Tile *tile)
{
    Tile *pt;

    for (size_t i = 0; i < m_tiles->size(); i++) {
        pt = &(*m_tiles)[i];

        // UP
        if (pt->getEdge("DOWN") == tile->getEdge("UP")) {
            tile->addUp(pt->getIndex());
        }

        // RIGHT
        if (pt->getEdge("LEFT") == tile->getEdge("RIGHT")) {
            tile->addRight(pt->getIndex());
        }

        // DOWN
        if (pt->getEdge("UP") == tile->getEdge("DOWN")) {
            tile->addDown(pt->getIndex());
        }

        // LEFT
        if (pt->getEdge("RIGHT") == tile->getEdge("LEFT")) {
            tile->addLeft(pt->getIndex());
        }
    }
}

void WaveFunctionCollapse::getCommon(std::vector<int> &src1, std::vector<int> &src2, std::vector<int> &dst)
{
    for (auto i : src1) {
        for (auto y : src2) {
            if (i == y) dst.push_back(i);
        }
    }
}

void WaveFunctionCollapse::writeAndClose()
{
    FILE* file = fopen(m_outputFile.c_str(), "w");
    gdImagePng(m_canvas, file);

    // CLEAN UP
    fclose(file);
    gdImageDestroy(m_canvas);
}

void WaveFunctionCollapse::execute()
{
    int idx, pixelX, pixelY, gridIndex;

    std::vector<int> leftPossible;
    std::vector<int> topPossible;
    std::vector<int> commonPossible;

    for (int x = 0; x < m_canvasRows; x++) {
        pixelX = x * m_pixelWidth;

        for (int y = 0; y < m_canvasColumns; y++) {
            pixelY = y * m_pixelHeight;
            gridIndex = y * m_canvasRows + x;

            if (x == 0) {
                leftPossible = m_allTiles;
            } else {
                leftPossible = m_grid[y * m_canvasRows + x - 1].m_tile->getRight();
            }

            if (y == 0) {
                topPossible = m_allTiles;
            } else {
                topPossible = m_grid[(y - 1) * m_canvasRows + x].m_tile->getDown();
            }

            commonPossible.clear();
            getCommon(leftPossible, topPossible, commonPossible);

            if (commonPossible.size() == 0) {
                std::cout << "No solution!" << '\n';
                writeAndClose();
                return;
            }

            int idx = rand() % commonPossible.size();
            m_grid[gridIndex].m_tile = &(*m_tiles)[commonPossible[idx]];

            Tile *t = m_grid[gridIndex].m_tile;

            gdImageCopyResized(m_canvas, *t->getImage(), pixelX, pixelY, 0, 0, t->getWidth(), t->getHeight(), t->getWidth(), t->getHeight());
        }
    }

    writeAndClose();
}