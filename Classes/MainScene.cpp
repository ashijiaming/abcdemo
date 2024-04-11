#include "MainScene.h"
#include "LearningCenterScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
	_director->getEventDispatcher()->removeEventListener(_listener);

}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//background
	Sprite* bgSprite = Sprite::create("main_bg.png");
	bgSprite->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	bgSprite->setScale(scale);
	this->addChild(bgSprite);

	//info sp
	_infoSprite = Sprite::create("ic_person_info.png");
	_infoSprite->setPosition(Vec2(35 + 653 / 2, 810 + 246 / 2));
	_infoSprite->setScale(scale);
    this->addChild(_infoSprite);


    _nameText=Text::create();
	_nameText->setFontSize(32);
	_nameText->setPosition(Vec2(440,1000));
	_nameText->setColor(Color3B(28,28,28));
    this->addChild(_nameText);

    _levelText=Text::create();
    _levelText->setFontSize(32);
    _levelText->setPosition(Vec2(450,940));
    _levelText->setColor(Color3B(28,28,28));
    this->addChild(_levelText);

    _goldText=Text::create();
	_goldText->setFontSize(32);
	_goldText->setPosition(Vec2(440,870));
	_goldText->setColor(Color3B(28,28,28));
    this->addChild(_goldText);

	//setting btn
	Button* settingButton = Button::create("ic_main_setting.png");
	settingButton->setPosition(Vec2(_contentSize.width - 90, _contentSize.height-120));
	settingButton->setScale(scale);
	settingButton->addClickEventListener([=](Ref* sender) {
		intoSetting(sender);
	});
	this->addChild(settingButton);

	//setting btn
	_messageSprite = Button::create("ic_main_message.png");
	_messageSprite->setPosition(Vec2(_contentSize.width - 280, _contentSize.height - 120));
	_messageSprite->setScale(scale);
	_messageSprite->setVisible(true);
	_messageSprite->addClickEventListener([=](Ref* sender) {
		intoShowList(sender);
	});
	this->addChild(_messageSprite);


	//book store sp
	_bookSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_book_store.json", "anim/anim_book_store.atlas");
	_bookSprite->setPosition(Vec2(_contentSize.width / 2-500, _contentSize.height / 2-80));
	_bookSprite->setAnimation(0, "animation", false);
	_bookSprite->setAnimation(0, "animation", true);
	this->addChild(_bookSprite);

	//music hall sp
    _musicSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_music_hall.json", "anim/anim_music_hall.atlas");
	_musicSprite->setPosition(Vec2(_contentSize.width / 2 - 900, _contentSize.height / 2 - 500));
	_musicSprite->setAnimation(0, "animation", false);
	_musicSprite->setAnimation(0, "animation", true);
	this->addChild(_musicSprite);


	 //learning center sp
	_learningSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_learning_center.json","anim/anim_learning_center.atlas");
	_learningSprite->setPosition(Vec2(_contentSize.width/2, _contentSize.height / 2-220));
	_learningSprite->setAnimation(0, "animation", false);
	_learningSprite->setAnimation(0, "animation", true);
	 this->addChild(_learningSprite);

	//cinema sp
	_cinemaSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_cinema.json", "anim/anim_cinema.atlas");
	_cinemaSprite->setPosition(Vec2(_contentSize.width/2 +530, _contentSize.height/2 + 150));
	_cinemaSprite->setAnimation(0, "animation", false);
	_cinemaSprite->setAnimation(0, "animation", true);
	this->addChild(_cinemaSprite);

	//pouidm sp
	_pouidmSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_podium.json", "anim/anim_podium.atlas");
	_pouidmSprite->setPosition(Vec2(_contentSize.width/2 +680, _contentSize.height/2-380));
	_pouidmSprite->setAnimation(0, "animation", false);
	_pouidmSprite->setAnimation(0, "animation", true);
	this->addChild(_pouidmSprite);
	


	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	getUserInfo();
	return true;
}


bool MainScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void MainScene::onTouchEnded(Touch * touch, Event * event)
{
	Vec2 location = touch->getLocation();
	if (_bookSprite->getBoundingBox().containsPoint(location))
	{
		intoBookStore(event);
	}
	else if (_musicSprite->getBoundingBox().containsPoint(location))
	{
		intoMusicHall(event);
	}
	else if (_learningSprite->getBoundingBox().containsPoint(location))
	{
		Director::getInstance()->replaceScene(LearningCenterScene::create());
	}
	else if (_pouidmSprite->getBoundingBox().containsPoint(location))
	{
		intoPodium(event);
	} 
	else if (_cinemaSprite->getBoundingBox().containsPoint(location))
	{
		intoCinema(event);
	}
	else if (_infoSprite->getBoundingBox().containsPoint(location))
	{
		intoStudyReport(event);
	}

}

void MainScene::showMessageIcon(bool isVisible)
{
	_messageSprite->setVisible(isVisible);
}

void  MainScene::setGoldCount(const std::string &result){
	_goldText->setString(result);
}



//获取用户信息，调原生的用户信息为界面赋值 服务器返回什么传回什么{ "avatar": "","createtime" : "",...}
void MainScene::getUserInfo()
{

	std::string result;

	json info;
	info["type"] = TYPE_USER_INFO;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	result = JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
	changeViewForData(result);
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	result = CCBridgeToOCManager::dealEventFromGame(param);
	changeViewForData(result);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	//string url="http://oss.hkxdjy.com/My%20World/headPic/L6/2.png";
	string url="//img.xiaogj.com/ece30ddf-4891-4b33-b053-6e679df4e5d4/H/cd9ac0457adb4d1698ba8de41508ae80-13e5ade58f1b4bb1a4430196f4f25f4a-00.jpg?x-oss-process=image/resize,w_360/crop,x_0,y_10,w_360,h_360";
	onGetIcon(url);
#endif



}


//通过用户信息更新界面
void MainScene::changeViewForData(std::string &result)
{
	if (result.size()==0)
	{
		return;
	}
	json user_json = json::parse(result);

	int hasSex=user_json.contains("sex");
	if (hasSex)
	{
		extern_sex = user_json["sex"];
	}

    bool hasNick= user_json.contains("nickname");
    if (hasNick){
		string nickname = user_json["nickname"];
		_nameText->setString(nickname);
    }

	bool hasLevel= user_json.contains("userLevel");
	if (hasLevel){
		string level = user_json["userLevel"];
		_levelText->setString(level);
	}
	bool hasGold=user_json.contains("goldCount");
	if (hasGold){
        int gold = user_json["goldCount"];
        string result=to_string(gold);
        _goldText->setString(result);
	}
	bool hasAvatar =user_json.contains("avatar");
	if (hasAvatar)
	{
		string url = user_json["avatar"];
		onGetIcon(url);
	}
	bool hasSort = user_json.contains("sort");
	if (hasSort)
	{
		extern_level_num= user_json["sort"];
	}

	bool hasMessage = user_json.contains("message");
	if (hasMessage)
	{
		int messaage=user_json["message"];
		if (messaage==1)
		{
			showMessageIcon(true);
		}
		else
		{
			showMessageIcon(false);
		}
	}


     
}

// into setting
void MainScene::intoSetting(Ref * pSender)
{
	
	json info;
	info["type"] = TYPE_MAIN_SETTING;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif

}

void MainScene::intoBookStore(Ref * pSender)
{
	

	json info;
	info["type"] = TYPE_BOOK_STORE;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif

}

void MainScene::intoMusicHall(Ref * pSender)
{
	
	json info;
	info["type"] = TYPE_MUSIC_HALL;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif

}

void MainScene::intoCinema(Ref * pSender)
{

	json info;
	info["type"] = TYPE_CINEMA;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}

void MainScene::intoPodium(Ref * pSender)
{


	json info;
	info["type"] = TYPE_PODIUM;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}


void MainScene::intoShowList(Ref * pSender)
{

	json info;
	info["type"] = TYPE_MESSAGE_MAIN;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}


void MainScene::intoStudyReport(Ref * pSender)
{

	json info;
	info["type"] = TYPE_STUDY_REPORT;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
}




void MainScene::onGetIcon(string & url)
{

	HttpClient* httpClient = HttpClient::getInstance();
	HttpRequest* httpRequest = new HttpRequest();
	httpRequest->setRequestType(HttpRequest::Type::GET);
	httpRequest->setUrl("");
	httpRequest->setResponseCallback(CC_CALLBACK_2(MainScene::onGetIconFinished, this));
	httpClient->setTimeoutForConnect(30);
	httpClient->send(httpRequest);
	httpRequest->release();//用完之后释放

}

void MainScene::onGetIconFinished(HttpClient * sender, HttpResponse * response)
{
	Scene *scene = Director::getInstance()->getRunningScene();
	if (typeid(*scene) != typeid(MainScene)) {
		return;
	}
	if (!response)
	{
		log("response is null");
		return;
	}
	if (!response->isSucceed())
	{
		log("reponse return false:%s", response->getErrorBuffer());
	}
	if (response->getResponseCode() != 200)
	{
		log("reponse return code:%ld", response->getResponseCode());
		return;
	}
	const char* tag = response->getHttpRequest()->getTag();
	if (0 != strlen(tag)) {
		log("reponse getTag:%s", tag);
	}
	std::vector<char>* buffData = response->getResponseData();
	Image* img = new Image();
	img->initWithImageData((unsigned char*)buffData->data(), buffData->size());
	Texture2D* texture = new Texture2D();
	bool isImage = texture->initWithImage(img);
	img->release();

	//icon
	auto draw = DrawNode::create();
	// draw a circle
	draw->drawSolidCircle(Vec2::ZERO, 110 / scale, CC_DEGREES_TO_RADIANS(90), 50, 1.0f, 1.0f, Color4F(0.0, 1.0, 0.0, 1.0));

	Sprite* iconSprite = Sprite::createWithTexture(texture);
	iconSprite->setContentSize(Size(220, 220) / scale);


	ClippingNode* clippingNode = ClippingNode::create();
	clippingNode->setStencil(draw);
	clippingNode->addChild(iconSprite);
	clippingNode->setPosition(Vec2(123, 128) / scale);
	_infoSprite->addChild(clippingNode);
}



