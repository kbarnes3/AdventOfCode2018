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
    struct Bounds
    {
        Bounds(_In_ int minX, _In_ int maxX, _In_ int minY, _In_ int maxY);
 
        int MinX;
        int MaxX;
        int MinY;
        int MaxY;
    };

    SparseGrid();

    void Insert(_In_ int x, _In_ int y, _In_ GridValue value);
    
    GridValue GetValue(_In_ int x, _In_ int y) const;
    Bounds GetBounds() const;

private:
    std::map<int, GridValue>& GetRow(_In_ int row);

    std::map<int, std::map<int, GridValue>> m_grid;

    int m_minX;
    int m_maxX;
    int m_minY;
    int m_maxY;
};
