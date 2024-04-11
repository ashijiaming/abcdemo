#include <iostream>
#include "CreateRoleScene.h"
#include "MainScene.h"
#include "SecondLoginScene.h"



CreateRoleScene::CreateRoleScene()
{
	
}


CreateRoleScene::~CreateRoleScene()
{
	_director->getEventDispatcher()->removeEventListener(_listener);
}



bool CreateRoleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	float scale = Director::getInstance()->getContentScaleFactor();
	
	//background
	Sprite* bgSprite = Sprite::create("bg_create_role.png");
	bgSprite->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	bgSprite->setScale(scale);
	this->addChild(bgSprite);

	//frame bg
	Sprite* fmSprite = Sprite::create("bg_role_frame.png");
	fmSprite->setPosition(Vec2(946+894 / 2, 301+558 / 2));
	fmSprite->setScale(scale);
	this->addChild(fmSprite);


	//back btn
	Button* backButton = Button::create("ic_back.png");
	backButton->setPosition(Vec2(20 + 172 / 2, 922 + 140 / 2));
	backButton->setScale(scale);
	backButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(SecondLoginScene::create());
	});
	this->addChild(backButton);

	//sprite men idle 
	_menSprite=spine::SkeletonAnimation::createWithJsonFile("anim/anim_boy.json", "anim/anim_boy.atlas");
	_menSprite->setPosition(Vec2(184 + 297 / 2,  598 / 2));
	_menSprite->setScale(scale);
	_menSprite->setAnimation(0, "idle", true);
	this ->addChild(_menSprite);
	_gender = 1;
	

	//sprite women idle
	_womenSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_girl.json", "anim/anim_girl.atlas");
	_womenSprite->setPosition(Vec2(470 + 322 / 2, 500 / 2));
	_womenSprite->setScale(scale);
	_womenSprite->setColor(Color3B(99, 99, 99));
	this->addChild(_womenSprite);

	
	//man icon
	_manImage = ImageView::create("ic_role_men.png");
	_manImage->setPosition(Vec2(1013 + 128 / 2, 687 + 128 / 2));
	_manImage->setScale(scale);
	this->addChild(_manImage);

	//woman icon
	_womanImage = ImageView::create("ic_role_women.png");
	_womanImage->setPosition(Vec2(1417 + 128 / 2, 687 + 128 / 2));
	_womanImage->setScale(scale);
	_womanImage->setColor(Color3B(99, 99, 99));
	this->addChild(_womanImage);

	//role name
    nameText = Text::create("Choose a name", "fonts/arial.ttf", 45);
	nameText->setColor(Color3B(155,95,0));
	nameText->setPosition(Vec2(1080 + nameText->getContentSize().width / 2, 492 + 154 / 2));
	this->addChild(nameText);

	//name arrow btn
	Button* menButton = Button::create("ic_role_arrow.png");
	menButton->setPosition(Vec2(1620 + 154 / 2, 492 + 154 / 2));
	menButton->setScale(scale);
	menButton->addClickEventListener([=](Ref* sender) {
		onIntoPickName();
	});
	this->addChild(menButton);


	//Dictionary* dictionary =Dictionary::createWithContentsOfFile("string.xml");
    //const char* name =static_cast<String*>(dictionary->objectForKey("name"))->getCString();
	//role birthday
	birthdayText = Text::create("Choose a Birthday", "fonts/arial.ttf", 45);
	birthdayText->setColor(Color3B(155, 95, 0));
	birthdayText->setPosition(Vec2(1080 + birthdayText->getContentSize().width / 2, 320 + 154 / 2));
	this->addChild(birthdayText);

	//birthday arrow btn
	Button* womenButton = Button::create("ic_role_arrow.png");
	womenButton->setPosition(Vec2(1620 + 154 / 2, 320+ 154 /2));
	womenButton->setScale(scale);
	womenButton->addClickEventListener([=](Ref* sender) {
		onIntoPickBirthday();
	});
	this->addChild(womenButton);

	//next btn
	Button* nextButton = Button::create("btn_role_next.png");
	nextButton->setPosition(Vec2(947 + 583 / 2, 103 + 168 / 2));
	nextButton->setScale(scale);
	nextButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(MainScene::create());
	});
	this->addChild(nextButton);


	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(CreateRoleScene::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(CreateRoleScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	return true;
}

bool CreateRoleScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
;
}

void CreateRoleScene::onTouchEnded(Touch * touch, Event * event)
{
	Vec2 location=touch->getLocation();
	if (_menSprite->getBoundingBox().containsPoint(location))
	{
		_gender = 1;
		_womenSprite->clearTracks();
		_womenSprite->setColor(Color3B(99, 99, 99));
		_menSprite->setColor(Color3B(255, 255, 255));
		_menSprite->setAnimation(0, "idle", true);
		_manImage->setColor(Color3B(255, 255, 255));
		_womanImage->setColor(Color3B(99, 99, 99));
		
		log("men x=%f,y=%f", location.x, location.y);
	}
	if (_womenSprite->getBoundingBox().containsPoint(location))
	{
		_gender = 2;
		_menSprite->clearTracks();
		_menSprite->setColor(Color3B(99, 99, 99));
		_womenSprite->setAnimation(0, "idle", true);
		_womenSprite->setColor(Color3B(255, 255, 255));

		_womanImage->setColor(Color3B(255, 255, 255));
		_manImage->setColor(Color3B(99, 99, 99));

		log("women x=%f,y=%f", location.x, location.y);
	}
	
}


void CreateRoleScene::onIntoPickName()
{
	json data;
	data["name"] = "Jamin";

	json info;
	info["type"] = TYPE_PICK_NAME;
	info["data"] = data;

	string json = info.dump();
	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", json);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}

void CreateRoleScene::onBackPickName(const std::string &data)
{
    nameText->setString(data);
}


void CreateRoleScene::onIntoPickBirthday()
{
	json data;
	data["birthday"] = "20190101";

	json info;
	info["type"] = TYPE_PICK_BIRTHDAY;
	info["data"] = data;

	string json = info.dump();

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", json);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}

void CreateRoleScene::onBackPickBirthday(const std::string & data)
{
    birthdayText->setString(data);
}
