#include "pch.h"
#include "SparseGrid.h"

void SparseGrid::Insert(_In_ int x, _In_ int y, _In_ GridValue value)
{
    bool firstInsert = false;
    if (m_grid.size() == 0)
    {
        firstInsert = true;
    }

    std::map<int, GridValue>& row = GetRow(x);
    row[y] = value;

    if (firstInsert)
    {
        m_minX = x;
        m_maxX = x;
        m_minY = y;
        m_maxY = y;
    }
    else
    {
        m_minX = std::min(m_minX, x);
        m_maxX = std::max(m_maxX, x);
        m_minY = std::min(m_minY, y);
        m_maxY = std::max(m_maxY, y);
    }
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
