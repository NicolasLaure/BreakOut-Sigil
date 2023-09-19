#pragma once

struct Color
{
	double r{};
	double g{};
	double b{};
};

//namespace colors
//{
//	/*const Color WHITE = { 252, 252, 252 };
//	const Color LIGHT_GRAY = { 196, 196, 196 };
//	const Color GRAY = { 125, 125, 125 };
//	const Color DARK_GRAY = { 69, 69, 69 };
//	const Color BLACK = { 15, 15, 15 };
//	const Color RED = { 230, 11, 11 };
//	const Color GREEN = { 27, 194, 33 };
//	const Color BLUE = { 23, 51, 232 };
//	const Color YELLOW = { 235, 213, 16 };*/
//};

struct Colors
{
	const Color WHITE = { 252.0 / 255, 252.0 / 255, 252.0 / 255 };
	const Color LIGHT_GRAY = { 196.0 / 255, 196.0 / 255, 196.0 / 255 };
	const Color GRAY = { 125.0 / 255, 125.0 / 255, 125.0 / 255 };
	const Color DARK_GRAY = { 69.0 / 255, 69.0 / 255, 69.0 / 255 };
	const Color BLACK = { 15.0 / 255, 15.0 / 255, 15.0 / 255 };
	const Color RED = { 230.0 / 255, 11.0 / 255, 11.0 / 255 };
	const Color GREEN = { 27.0 / 255, 194.0 / 255, 33.0 / 255 };
	const Color BLUE = { 23.0 / 255, 51.0 / 255, 232.0 / 255 };
	const Color YELLOW = { 235.0 / 255, 213.0 / 255, 16.0 / 255 };
};