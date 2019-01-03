#pragma once
#include <Data.h>

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

    void Insert(_In_ const Position& point, GridValue value);

private:
    std::map<int, GridValue>& GetRow(_In_ int row);

    std::map<int, std::map<int, GridValue>> m_grid;
};
