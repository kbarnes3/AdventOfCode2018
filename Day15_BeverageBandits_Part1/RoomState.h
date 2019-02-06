#pragma once

namespace MobStats
{
    static const int StartingHitPoints = 200;
}

class Empty
{
public:
    Empty()
    {}
};

class Wall
{
public:
    Wall()
    {}
};

class Elf
{
public:
    Elf(size_t row, size_t column) :
        m_hitPoints(MobStats::StartingHitPoints),
        m_row(row),
        m_column(column)
    {

    }

    int m_hitPoints;
    size_t m_row;
    size_t m_column;
};

class Goblin
{
public:
    Goblin(size_t row, size_t column) :
        m_hitPoints(MobStats::StartingHitPoints),
        m_row(row),
        m_column(column)
    {

    }

    int m_hitPoints;
    size_t m_row;
    size_t m_column;
};

using SquareContents = std::variant<Empty, Wall, std::shared_ptr<Elf>, std::shared_ptr<Goblin>>;

template<size_t Rows, size_t Columns>
using MapGrid = std::array<std::array<SquareContents, Columns>, Rows>;
