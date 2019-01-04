#pragma once

enum class GridValue
{
    Empty,
    Unseen,
    Seen,
};

class SparseGrid
{
public:
    SparseGrid() = default;

    void Insert(_In_ int x, _In_ int y, _In_ GridValue value);

private:
    std::map<int, GridValue>& GetRow(_In_ int row);

    std::map<int, std::map<int, GridValue>> m_grid;

    int m_minX;
    int m_maxX;
    int m_minY;
    int m_maxY;
};
