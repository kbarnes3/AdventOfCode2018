#pragma once
#include <array>
#include <map>
#include <tuple>

// Convert the input data with these regex's:
// '<,'>s/#/    true,\r/g
// '<,'>s/\./    false,\r/g
const std::array<bool, 25> sampleInitialState = { {
    true,
    false,
    false,
    true,
    false,
    true,
    false,
    false,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    true,
    true,
    true,
    false,
    false,
    false,
    true,
    true,
    true,
} };

// Convert the input data with these regex's:
// '<,'>s/^\(.\)\(.\)\(.\)\(.\)\(.\) => \(.\)/    { { \1, \2, \3, \4, \5 }, \6 },
// '<,'>s/#/true/g
// '<,'>s/\./false/g
const std::map<std::tuple<bool, bool, bool, bool, bool>, bool> sampleRules = { {
    { { false, false, false, true, true }, true },
    { { false, false, true, false, false }, true },
    { { false, true, false, false, false }, true },
    { { false, true, false, true, false }, true },
    { { false, true, false, true, true }, true },
    { { false, true, true, false, false }, true },
    { { false, true, true, true, true }, true },
    { { true, false, true, false, true }, true },
    { { true, false, true, true, true }, true },
    { { true, true, false, true, false }, true },
    { { true, true, false, true, true }, true },
    { { true, true, true, false, false }, true },
    { { true, true, true, false, true }, true },
    { { true, true, true, true, false }, true },
} };
