#pragma once

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
    Elf() : m_hitPoints(200)
    {

    }

    int m_hitPoints;
};

class Goblin
{
public:
    Goblin() : m_hitPoints(200)
    {

    }

    int m_hitPoints;
};

using SquareContents = std::variant<Empty, Wall, std::shared_ptr<Elf>, std::shared_ptr<Goblin>>;

template<size_t Rows, size_t Columns>
using MapGrid = std::array<std::array<SquareContents, Columns>, Rows>;
