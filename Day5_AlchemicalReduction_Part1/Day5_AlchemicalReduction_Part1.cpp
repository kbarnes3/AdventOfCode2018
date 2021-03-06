// Day5_AlchemicalReduction_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

wchar_t toggleCase(_In_ char letter)
{
	if (isupper(letter))
	{
		return tolower(letter);
	}
	else
	{
		return toupper(letter);
	}
}

template<size_t Size>
void solve(_In_ const char(&input)[Size])
{
	static_assert(Size > 1);

	std::vector<char> units;
	units.assign(input, input + Size - 1); // Use Size - 1 since our input is null terminated;

	std::vector<char>::iterator iter = units.begin();

	// Go through the list of units that we have, looking for two letters next to each other that will react
	while (iter != units.end())
	{
		std::vector<char>::iterator next = iter + 1;
		wchar_t reactingLetter = toggleCase(*iter);
		if (*next == reactingLetter)
		{
			// We got a match, erase both the letters and then start over
			units.erase(iter, iter + 2);
			iter = units.begin();
		}
		else
		{
			iter++;
		}
	}

	std::wcout << units.size() << std::endl;
}

int main()
{
	solve(input_units);
}
