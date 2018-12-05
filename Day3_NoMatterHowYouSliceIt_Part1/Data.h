#pragma once
struct Claim
{
    unsigned int claimId;
    size_t x;
    size_t y;
    size_t width;
    size_t height;
};

const std::array<Claim, 3> sample_claims = { {
    { 1, 1, 3, 4, 4 },
    { 2, 3, 1, 4, 4 },
    { 3, 5, 5, 2, 2 },
} };
