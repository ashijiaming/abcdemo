#include "FirstLoginScene.h"
#include "MainScene.h"

FirstLoginScene::FirstLoginScene()
{
}


FirstLoginScene::~FirstLoginScene()
{
}

bool FirstLoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	scale=Director::getInstance()->getContentScaleFactor();
	
	log("scale____________:%f", scale);
	//background
	Sprite* bgSprite = Sprite::create("bg_login_first.png");
	bgSprite->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	bgSprite->setScale(scale);
	this->addChild(bgSprite);

	//anim
	spine::SkeletonAnimation*  skeletonNode = spine::SkeletonAnimation::createWithJsonFile("anim/anim_login_first.json", "anim/anim_login_first.atlas");
	skeletonNode->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	skeletonNode->setScale(scale);
	this->addChild(skeletonNode);
	skeletonNode->setAnimation(0, "animation", false);
	skeletonNode->setAnimation(0, "animation", true);
  

	//second start btn
	Button* startButton = Button::create("ic_enter_main.png");
	startButton->setPosition(Vec2(_contentSize.width/2 , 236 / 2 + 172));
	startButton->setScale(scale);
	startButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(MainScene::create());
	});
	this->addChild(startButton);

	return true;
}
