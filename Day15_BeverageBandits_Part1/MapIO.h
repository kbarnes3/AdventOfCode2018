#pragma once
#include "RoomState.h"

class MapIO
{
public:
    template<size_t Rows, size_t Columns>
    static void LoadInitialMap(
        const std::array<std::array<char, Columns + 1>, Rows>& initialMap,
        MapGrid<Rows, Columns>& loadedMap,
        std::vector<std::shared_ptr<Elf>>& elves,
        std::vector<std::shared_ptr<Goblin>>& goblins)
    {
        for (size_t y = 0; y < Rows; ++y)
        {
            for (size_t x = 0; x < Columns; ++x)
            {
                char contents = initialMap[y][x];
                switch (contents)
                {
                case EmptyChar:
                    loadedMap[y][x] = Empty();
                    break;
                case WallChar:
                    loadedMap[y][x] = Wall();
                    break;
                case ElfChar:
                {
                    std::shared_ptr elf = std::make_shared<Elf>(x, y);
                    loadedMap[y][x] = elf;
                    elves.push_back(elf);
                    break;
                }
                case GoblinChar:
                {
                    std::shared_ptr goblin = std::make_shared<Goblin>(x, y);
                    loadedMap[y][x] = goblin;
                    goblins.push_back(goblin);
                    break;
                }
                default:
                    RaiseFailFastException(nullptr, nullptr, 0);
                }
            }
        }
    }

    template<size_t Rows, size_t Columns>
    static void PrintMap(const MapGrid<Rows, Columns>& map)
    {
        for (size_t y = 0; y < Rows; ++y)
        {
            for (size_t x = 0; x < Columns; ++x)
            {
                SquareContents square = map[y][x];
                if (std::holds_alternative<Empty>(square))
                {
                    std::cout << EmptyChar;
                }
                else if (std::holds_alternative<Wall>(square))
                {
                    std::cout << WallChar;
                }
                else if (std::holds_alternative<std::shared_ptr<Elf>>(square))
                {
                    std::cout << ElfChar;
                }
                else if (std::holds_alternative<std::shared_ptr<Goblin>>(square))
                {
                    std::cout << GoblinChar;
                }
                else
                {
                    RaiseFailFastException(nullptr, nullptr, 0);
                }
            }
            std::cout << std::endl;
        }
    }

private:
    static const char EmptyChar = '.';
    static const char WallChar = '#';
    static const char ElfChar = 'E';
    static const char GoblinChar = 'G';
};

