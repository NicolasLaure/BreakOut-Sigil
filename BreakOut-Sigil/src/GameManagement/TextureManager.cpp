#include "GameManagement/TextureManager.h"
#include "sl.h"

static Textures textures;

void SetTextures()
{
	textures.backGround = slLoadTexture("assets/textures/SpaceBackground.png");
	textures.paddle= slLoadTexture("assets/textures/PaddleNormal.png");
	textures.paddleHitted = slLoadTexture("assets/textures/PaddleHit.png");
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
	default:
		break;
	}
}