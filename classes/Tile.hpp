#ifndef HEADER_TILE
#define HEADER_TILE

#include <vector>
#include <unordered_map>
#include <string>
#include "gd.h"

class Tile
{
public:
    Tile();
    Tile(std::string path, std::unordered_map<std::string, std::string> edgeOptions, int index, int w, int h);
    void setEdges(std::unordered_map<std::string, std::string> edgeOptions);
    void loadImage(const std::string &path, int w, int h);

    int getHeight();
    int getWidth();
    const std::string& getEdge(std::string direction) const;

    void addUp(int i);
    const std::vector<int>& getUp() const;

    void addDown(int i);
    const std::vector<int>& getDown() const;

    void addLeft(int i);
    const std::vector<int>& getLeft() const;

    void addRight(int i);
    const std::vector<int>& getRight() const;

    int getIndex();
    gdImagePtr* getImage();

private:
    int m_index;
    gdImagePtr image;
    std::unordered_map<std::string, std::string> edges;

    std::vector<int> up;
    std::vector<int> down;
    std::vector<int> left;
    std::vector<int> right;
};

#endif