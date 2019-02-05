// Day15_BeverageBandits_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Data.h"
#include "MapIO.h"
#include "RoomState.h"



template<size_t Rows, size_t Columns>
void solve(_In_ const std::array < std::array<char, Columns + 1>, Rows>& initialMap)
{
    using Map = MapGrid<Rows, Columns>;
    Map map;
    std::vector<std::shared_ptr<Elf>> elves;
    std::vector<std::shared_ptr<Goblin>> goblins;

    MapIO::LoadInitialMap(
        initialMap,
        map,
        elves,
        goblins);

    MapIO::PrintMap(map);
}

int main()
{
    solve<5, 7>(moveTest1);
    return 0;
}
