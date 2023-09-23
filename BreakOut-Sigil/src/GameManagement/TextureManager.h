#pragma once

enum class TextureIdentifier
{
	BackGround,
	Paddle,
	PaddleHitted,
	PlayerHpHitted
};

struct Textures
{
	int backGround;
	int paddle;
	int paddleHitted;
	int playerHpHitted;
};

void SetTextures();
int GetTexture(TextureIdentifier texture);
