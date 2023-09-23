#include "GameManagement/TextureManager.h"
#include "sl.h"

static Textures textures;

void SetTextures()
{
	textures.backGround = slLoadTexture("assets/textures/SpaceBackground.png");
	textures.paddle = slLoadTexture("assets/textures/PaddleNormal.png");
	textures.paddleHitted = slLoadTexture("assets/textures/PaddleHit.png");
	textures.playerHpHitted = slLoadTexture("assets/textures/HitBloodScreen.png");
	textures.brick = slLoadTexture("assets/textures/BrickTexture.png");
	textures.brickMultiBall = slLoadTexture("assets/textures/BrickTextureMultiBall.png");
	textures.brickHpUp = slLoadTexture("assets/textures/BrickTextureHpUp.png");
	textures.brickSlowDown = slLoadTexture("assets/textures/BrickTextureSlowDown.png");
}
int GetTexture(TextureIdentifier texture)
{
	switch (texture)
	{
	case TextureIdentifier::BackGround:
		return textures.backGround;
		break;
	case TextureIdentifier::Paddle:
		return textures.paddle;
		break;
	case TextureIdentifier::PaddleHitted:
		return textures.paddleHitted;
		break;
	case TextureIdentifier::PlayerHpHitted:
		return textures.playerHpHitted;
		break;
	case TextureIdentifier::Brick:
		return textures.brick;
		break;
	case TextureIdentifier::BrickMultiBall:
		return textures.brickMultiBall;
		break;
	case TextureIdentifier::BrickHpUp:
		return textures.brickHpUp;
		break;
	case TextureIdentifier::BrickSlowDown:
		return textures.brickSlowDown;
		break;
	default:
		break;
	}
}