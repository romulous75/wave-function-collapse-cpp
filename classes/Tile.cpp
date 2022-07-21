#include "Tile.hpp"
#include <iostream>

Tile::Tile() {}

Tile::Tile(std::string path, std::unordered_map<std::string, std::string> edgeOptions, int index, int w, int h) : m_index(index)
{
    loadImage(path, w, h);
    setEdges(edgeOptions);
}

void Tile::setEdges(std::unordered_map<std::string, std::string> edgeOptions)
{
    std::copy(edgeOptions.begin(), edgeOptions.end(), std::inserter(edges, edges.end()) );
}

void Tile::loadImage(const std::string &path, int w, int h)
{
    FILE *in = fopen(path.c_str(), "r");
    image = gdImageScale(gdImageCreateFromPng(in), w, h);
    fclose(in);
}

int Tile::getHeight()
{
    return image->sy;
}

int Tile::getWidth()
{
    return image->sx;
}

const std::string& Tile::getEdge(std::string direction) const
{
    return edges.at(direction);
}

const std::vector<int>& Tile::getUp() const
{
    return up;
}

void Tile::addUp(int i)
{
    return up.push_back(i);
}

const std::vector<int>& Tile::getDown() const
{
    return down;
}

void Tile::addDown(int i)
{
    return down.push_back(i);
}

const std::vector<int>& Tile::getLeft() const
{
    return left;
}

void Tile::addLeft(int i)
{
    return left.push_back(i);
}

const std::vector<int>& Tile::getRight() const
{
    return right;
}

void Tile::addRight(int i)
{
    return right.push_back(i);
}

int Tile::getIndex()
{
    return m_index;
}

gdImagePtr* Tile::getImage()
{
    return &image;
}