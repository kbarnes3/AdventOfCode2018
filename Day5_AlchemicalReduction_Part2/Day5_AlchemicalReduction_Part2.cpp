// Day5_AlchemicalReduction_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

std::vector<char> react(_In_ const std::vector<char>& input)
{
	std::vector<char> units = input;
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

	return units;
}

size_t improve(_In_ const std::vector<char>& input)
{
	size_t best_size = input.size();

	// Try and remove a single letter and see how small we can get
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		char upperLetter = toupper(letter);
		std::vector<char> improved_units = input;
		std::vector<char>::iterator toErease = std::remove_if(
			improved_units.begin(),
			improved_units.end(),
			[letter, upperLetter](_In_ char c) -> bool
			{
				return (c == letter || c == upperLetter);
			});

		improved_units.erase(toErease, improved_units.end());

		improved_units = react(improved_units);
		size_t new_size = improved_units.size();
		best_size = std::min(best_size, new_size);
	}

	return best_size;
}

template<size_t Size>
void solve(_In_ const char(&input)[Size])
{
	static_assert(Size > 1);

	std::vector<char> units;
	units.assign(input, input + Size - 1); // Use Size - 1 since our input is null terminated;

	// First do all the reactions we can do normally
	units = react(units);

	// Then improve it
	size_t improved_result = improve(units);


	std::wcout << improved_result << std::endl;
}

int main()
{
	solve(input_units);
}
