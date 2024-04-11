#include "SecondLoginScene.h"
#include "ui/CocosGUI.h"
#include "CreateRoleScene.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace cocos2d::ui;

SecondLoginScene::SecondLoginScene()
{
}


SecondLoginScene::~SecondLoginScene()
{
}

bool SecondLoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	float scale = Director::getInstance()->getContentScaleFactor();

	//background
	Sprite* bgSprite = Sprite::create("bg_login_second.png");
	bgSprite->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	bgSprite->setScale(scale);
	this->addChild(bgSprite);

	//start btn
	Button* startButton = Button::create("ic_enter_main.png","ic_enter_main.png");
	startButton->setPosition(Vec2(236/2+846,236/2+172));
	startButton->setScale(scale);
	startButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(CreateRoleScene::create());
	});
	this->addChild(startButton);


	return true;
}

void SecondLoginScene::saveLoginInfo(const std::string &normalImage) {
	json userInfo= json ::parse(normalImage);
    UserDefault::getInstance()->setStringForKey("username",userInfo["username"]);
    UserDefault::getInstance()->setStringForKey("level",userInfo["level"]);
    UserDefault::getInstance()->setStringForKey("gold",userInfo["gold"]);
}
