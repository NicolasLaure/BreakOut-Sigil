#pragma once

enum class TextureIdentifier
{
	BackGround,
	Paddle,
	Brick,
	PaddleHitted,
	PlayerHpHitted
};

struct Textures
{
	int backGround;
	int paddle;
	int paddleHitted;
	int playerHpHitted;
	int brick;
};

void SetTextures();
int GetTexture(TextureIdentifier texture);
