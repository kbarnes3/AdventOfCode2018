#include "pch.h"
#include "SparseGrid.h"

SparseGrid::Bounds::Bounds(_In_ int minX, _In_ int maxX, _In_ int minY, _In_ int maxY) :
    MinX(minX),
    MaxX(maxX),
    MinY(minY),
    MaxY(maxY)
{
}

SparseGrid::SparseGrid() :
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0)
{
}

void SparseGrid::Insert(_In_ int x, _In_ int y, _In_ GridValue value)
{
    bool firstInsert = false;
    if (m_grid.size() == 0)
    {
        firstInsert = true;
    }

    std::map<int, GridValue>& row = GetRow(y);
    row[x] = value;

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

GridValue SparseGrid::GetValue(_In_ int x, _In_ int y) const
{
    std::map<int, std::map<int, GridValue>>::const_iterator iter = m_grid.find(y);

    if (iter == m_grid.cend())
    {
        return GridValue::Empty;
    }

    const std::map<int, GridValue>& row = iter->second;
    std::map<int, GridValue>::const_iterator row_iter = row.find(x);

    if (row_iter == row.cend())
    {
        return GridValue::Empty;
    }
    else
    {
        return row_iter->second;
    }
}

SparseGrid::Bounds SparseGrid::GetBounds() const
{
    return SparseGrid::Bounds(m_minX, m_maxX, m_minY, m_maxY);
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
