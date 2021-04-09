
#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_groot = GRoot::create(this);
	_groot->retain();
	
	return true;
}


GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_groot);
}
