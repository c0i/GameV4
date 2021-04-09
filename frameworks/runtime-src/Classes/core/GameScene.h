#pragma once

#include "cocos2d.h"
#include "FairyGUI.h"

USING_NS_CC;
USING_NS_FGUI;

class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);

	~GameScene();

	virtual bool init();

protected:
	GRoot* _groot = nullptr;
};

