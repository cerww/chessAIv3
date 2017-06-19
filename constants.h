#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "vectors2.h"

constexpr cw::vector2i bishMove[4] = { { 1,1 },{ -1,1 },{ -1,-1 },{ 1,-1 } };
constexpr cw::vector2i rookMove[4] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
constexpr cw::vector2i horseMove[8] = { { 1,2 },{ -1,2 },{ 1,-2 },{ -1,-2 },{ 2,1 },{ 2,-1 },{ -2,1 },{ -2,-1 } };
constexpr cw::vector2i kingMove[8] = { { 1,1 },{ 1,0 },{ 1,-1 },{ 0,1 },{ 0,-1 },{ -1,1 },{ -1,0 },{ -1,-1 } };

#endif
