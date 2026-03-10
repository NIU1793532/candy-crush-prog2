#include "board.h"

#include <algorithm>
#include <memory>
#include <iostream>

using namespace std;
Board::Board(int width, int height) :
        m_width(width),
        m_height(height),
        m_cells(vector(width, vector<Candy*>(height)))
{

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; i < height; i++)
        {
            m_cells[i][j] = new Candy(CandyType::NONE);
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < m_cells.size(); i++) {
        for (int j = 0; j < m_cells[i].size(); j++) {
            delete m_cells[i][j];
        }
    }
}


Candy* Board::getCell(int x, int y) const
{
    return m_cells[x][y];
}

void Board::setCell(Candy* candy, int x, int y)
{
    if (x >= m_width || y >= m_height || x < 0 || y < 0)
    {
        cout << "ERROR when setting cell bounds" << endl;
        exit(1); // TODO: change
    }
    m_cells[x][y] = candy;
}


int Board::getWidth() const
{
    // Implement your code here
    return m_width;
}


int Board::getHeight() const
{
    // Implement your code here
    return m_height;
}

bool Board::shouldExplode(int x, int y) const
{
    // Implement your code here
    return getConsecutiveRow(x, y).size() >= SHORTEST_EXPLOSION_LINE ||
           getConsecutiveColumn(x, y).size() >= SHORTEST_EXPLOSION_LINE ||
           getConsecutiveAscendingDiagonal(x, y).size() >= SHORTEST_EXPLOSION_LINE ||
           getConsecutiveDescendingDiagonal(x, y).size() >= SHORTEST_EXPLOSION_LINE;
}

vector<Candy*> Board::getConsecutiveColumn(int x, int y) const
{
    vector consecutiveCandies = {m_cells[x][y]};
    CandyType type = m_cells[x][y]->getType();


    int i = 1;
    while (type == m_cells[x][y+i]->getType() && y + i >= 0 && y + i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x][y+i]);
        i++;
    }
    i = -1;
    while (type == m_cells[x][y+i]->getType() && y + i >= 0 && y + i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x][y+i]);
        i--;
    }

    return consecutiveCandies;
}

vector<Candy*> Board::getConsecutiveRow(int x, int y) const
{
    vector consecutiveCandies = {m_cells[x][y]};
    CandyType type = m_cells[x][y]->getType();


    int i = 1;
    while (type == (*m_cells[x+i][y]).getType() && x + i >= 0 && x + i < m_width)
    {
        consecutiveCandies.push_back(m_cells[x+i][y]);
        i++;
    }
    i = -1;
    while (type == m_cells[x+i][y]->getType() && x + i >= 0 && x + i < m_width)
    {
        consecutiveCandies.push_back(m_cells[x+i][y]);
        i--;
    }

    return consecutiveCandies;
}

vector<Candy*> Board::getConsecutiveAscendingDiagonal(int x, int y) const
{
    vector consecutiveCandies = {m_cells[x][y]};
    CandyType type = m_cells[x][y]->getType();


    int i = 1;
    while (type == m_cells[x+i][y+i]->getType() && x + i >= 0 && x + i < m_width && y + i >= 0 && y + i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x+i][y+i]);
        i++;
    }
    i = -1;
    while (type == m_cells[x+i][y+i]->getType() && x + i >= 0 && x + i < m_width && y + i >= 0 && y + i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x+i][y+i]);
        i--;
    }

    return consecutiveCandies;
}

vector<Candy*> Board::getConsecutiveDescendingDiagonal(int x, int y) const
{
    vector consecutiveCandies = {m_cells[x][y]};
    CandyType type = m_cells[x][y]->getType();


    int i = 1;
    while (type == m_cells[x+i][y-i]->getType() && x + i >= 0 && x + i < m_width && y - i >= 0 && y - i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x+i][y-i]);
        i++;
    }
    i = -1;
    while (type == m_cells[x+i][y-i]->getType() && x + i >= 0 && x + i < m_width && y - i >= 0 && y - i < m_height)
    {
        consecutiveCandies.push_back(m_cells[x+i][y-i]);
        i--;
    }

    return consecutiveCandies;
}

std::vector<Candy*> Board::explodeAndDrop()
{
    // Implement your code here
    return {};
}

bool Board::dump(const std::string& output_path) const
{
    // Implement your code here
    return false;
}

bool Board::load(const std::string& input_path)
{
    // Implement your code here
    return false;
}
