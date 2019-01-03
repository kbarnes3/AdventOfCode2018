#include "pch.h"
#include "SparseGrid.h"

void SparseGrid::Insert(_In_ const Position& position, GridValue value)
{
    std::map<int, GridValue>& row = GetRow(position.x);
    row[position.y] = value;
}

std::map<int, GridValue>& SparseGrid::GetRow(_In_ int row)
{
    std::map<int, std::map<int, GridValue>>::iterator iter = m_grid.find(row);
    if (iter == m_grid.end())
    {
        std::pair< std::map<int, std::map<int, GridValue>>::iterator, bool> result = m_grid.insert({ row, std::map<int, GridValue>() });
        iter = result.first;
    }

    return iter->second;
}
