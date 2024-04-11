#pragma once
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;
USING_NS_CC;

class LearningCenterScene :public Scene
{
public:
	LearningCenterScene();
	~LearningCenterScene();

	CREATE_FUNC(LearningCenterScene);
	virtual bool init();
	void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
	void changeLessionUp();
	void changeLessionLevel();

	void onGetImage();

	void onGetFinished(Node* node, void * obj);//回调函数，这里有参数Node和void Finish(void* obj);


private:
	enum MoveEnum
	{
		left=1001,
		right
	};
	int _move;
	Button* nextButton;
	Sprite* bgSpriteOne;
	Sprite* bgSpriteTwo;
	Sprite* menSprite;
	Sprite* spriteImg;

	float centerX;
	int lastIndex;
	float lastMenPosX=0;
};

