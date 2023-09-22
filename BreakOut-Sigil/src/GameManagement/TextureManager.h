#pragma once

enum class TextureIdentifier
{
	BackGround,
	Paddle,
	PaddleHitted,
};

struct Textures
{
	int backGround;
	int paddle;
	int paddleHitted;
};

void SetTextures();
int GetTexture(TextureIdentifier texture);
