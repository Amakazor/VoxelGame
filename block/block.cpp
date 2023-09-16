#include "block.h"
#include <iostream>

block::block(const vector3_i& position) : position_(position)
{
    faces_.reserve(6);
    
    faces_.emplace_back(vector3_i{ 1, 0, 0 } + position, vector3_i{ 1, 1, 0 } + position, vector3_i{ 0, 1, 0 } + position, vector3_i{ 0, 0, 0 } + position);
    faces_.emplace_back(vector3_i{ 0, 0, 1 } + position, vector3_i{ 0, 1, 1 } + position, vector3_i{ 1, 1, 1 } + position, vector3_i{ 1, 0, 1 } + position);
    faces_.emplace_back(vector3_i{ 0, 0, 0 } + position, vector3_i{ 0, 1, 0 } + position, vector3_i{ 0, 1, 1 } + position, vector3_i{ 0, 0, 1 } + position);
    faces_.emplace_back(vector3_i{ 1, 0, 1 } + position, vector3_i{ 1, 1, 1 } + position, vector3_i{ 1, 1, 0 } + position, vector3_i{ 1, 0, 0 } + position);
    faces_.emplace_back(vector3_i{ 0, 0, 1 } + position, vector3_i{ 1, 0, 1 } + position, vector3_i{ 1, 0, 0 } + position, vector3_i{ 0, 0, 0 } + position);
    faces_.emplace_back(vector3_i{ 0, 1, 0 } + position, vector3_i{ 1, 1, 0 } + position, vector3_i{ 1, 1, 1 } + position, vector3_i{ 0, 1, 1 } + position);
}

const vector3_i& block::position() const
{
    return position_;
}

const std::vector<quad>& block::faces() const
{
    return faces_;
}