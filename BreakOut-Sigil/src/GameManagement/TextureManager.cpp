#include "GameManagement/TextureManager.h"
#include "sl.h"

static Textures textures;

void SetTextures()
{
	textures.backGround = slLoadTexture("assets/textures/SpaceBackground.png");
	textures.paddle= slLoadTexture("assets/textures/PaddleNormal.png");
	textures.paddleHitted = slLoadTexture("assets/textures/PaddleHit.png");
	textures.playerHpHitted = slLoadTexture("assets/textures/HitBloodScreen.png");
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
	default:
		break;
	}
}