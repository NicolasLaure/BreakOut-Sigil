#pragma once

enum class TextureIdentifier
{
	BackGround,
	Paddle,
	Brick,
	PaddleHitted,
	PlayerHpHitted,
	BrickMultiBall,
	BrickHpUp,
	BrickSlowDown
};

struct Textures
{
	int backGround;
	int paddle;
	int paddleHitted;
	int playerHpHitted;
	int brick;
	int brickMultiBall;
	int brickHpUp;
	int brickSlowDown;
};

void SetTextures();
int GetTexture(TextureIdentifier texture);
