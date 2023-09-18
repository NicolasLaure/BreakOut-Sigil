#pragma once

struct Color
{
	double r{};
	double g{};
	double b{};
};

namespace colors
{
	const Color WHITE = { 252, 252, 252 };
	const Color LIGHT_GRAY = { 196, 196, 196 };
	const Color GRAY = { 125, 125, 125 };
	const Color DARK_GRAY = { 69, 69, 69 };
	const Color BLACK = { 15, 15, 15 };
	const Color RED = { 230, 11, 11 };
	const Color GREEN = { 27, 194, 33 };
	const Color BLUE = { 23, 51, 232 };
	const Color YELLOW = { 235, 213, 16 };
};