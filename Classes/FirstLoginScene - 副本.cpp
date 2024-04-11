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
	spine::SkeletonAnimation*  skeletonNode = spine::SkeletonAnimation::createWithJsonFile("AnimLoginFirst.json", "AnimLoginFirst.atlas");
	skeletonNode->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	skeletonNode->setScale(scale);
	this->addChild(skeletonNode);
	skeletonNode->setAnimation(0, "animation", false);
	skeletonNode->setAnimation(0, "animation", true);
    
	//login frame
	_frameSprite = Sprite::create("ic_login_frame.png");
	_frameSprite->setPosition(Vec2(862/2+237,515/2+232));
	_frameSprite->setScale(scale);
	this->addChild(_frameSprite);

	//请输入手机号
    //textFieldName = TextField::create("请输入手机号", "Arial", 40);
	_textFieldName = TextField::create("name", "fonts/arial.ttf", 45);
	_textFieldName->setPosition(Vec2(450, (_textFieldName->getContentSize().height / 2+373))/scale);
	_textFieldName->setColor(Color3B(22,22,22));
	_textFieldName->addEventListener(CC_CALLBACK_2(FirstLoginScene::textFieldEvent, this));
	_frameSprite->addChild(_textFieldName);

	//请输入密码
    //textFieldPassword = TextField::create("请输入密码", "Arial", 40);
	_textFieldPassword = TextField::create("password", "fonts/arial.ttf", 45);
	_textFieldPassword->setPasswordEnabled(true);
	_textFieldPassword->setPasswordStyleText("* ");
	_textFieldPassword->setPosition(Vec2(450, (_textFieldPassword->getContentSize().height / 2 + 230))/scale);
	_textFieldPassword->setColor(Color3B(22,22,22));
	_textFieldPassword->addEventListener(CC_CALLBACK_2(FirstLoginScene::textFieldEvent, this));
	_frameSprite->addChild(_textFieldPassword);

	//first login btn
	Button* loginButton = Button::create("ic_login_confirm.png");
	loginButton->setPosition(Vec2((509 / 2 + 178), (152 / 2 + 26))/scale);
	loginButton->addClickEventListener([=](Ref* sender) {
		loginFirst();
	});
	_frameSprite->addChild(loginButton);


	//second start btn
	_startButton = Button::create("ic_enter_main.png");
	_startButton->setPosition(Vec2(236 / 2 + 846, 236 / 2 + 172));
	_startButton->setScale(scale);
	_startButton->setVisible(false);
	_startButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(MainScene::create());
	});
	this->addChild(_startButton);

	getLoginState();
	return true;
}

void FirstLoginScene::textFieldEvent(cocos2d::Ref * pSender, cocos2d::ui::TextField::EventType type)
{

	switch (type)
	{
	case TextField::EventType::ATTACH_WITH_IME:
	{
		//TextField* textField = dynamic_cast<TextField*>(pSender);
		//Size screenSize = Director::getInstance()->getWinSize();
		//textField->runAction(MoveTo::create(0.225f,
		//	Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));


	}
	break;

	case TextField::EventType::DETACH_WITH_IME:
	{
		//TextField* textField = dynamic_cast<TextField*>(pSender);
		//Size screenSize = Director::getInstance()->getWinSize();
		//textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
		//_displayValueLabel->setString(StringUtils::format("detach with IME password"));

	}
	break;

	case TextField::EventType::INSERT_TEXT:
		//_displayValueLabel->setString(StringUtils::format("insert words password"));
		//_textFieldName->setPositionX(_textFieldName->getContentSize().width / 2 + 192);
		//_textFieldPassword->setPositionX(_textFieldPassword->getContentSize().width / 2 + 192);
		break;

	case TextField::EventType::DELETE_BACKWARD:
		//_displayValueLabel->setString(StringUtils::format("delete word password"));
		break;

	default:
		break;
	}
}

//点击登录
void FirstLoginScene::loginFirst()
{
	const char* name=_textFieldName->getString().c_str();

	const char* password= _textFieldPassword->getString().c_str();
	json data;
	data["name"] = name;
	data["password"] = password;
	json info;
	info["type"] = TYPE_LOGIN;
	info["data"] = data;

	string param = info.dump();

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif

}

//获取登录状态从原生拿数据 result ={"isLogin":false,"username":"jm","password":"123"}
void FirstLoginScene::getLoginState()
{
    std::string result;

    json info;
    info["type"] = TYPE_LOGIN_STATE;
	info["data"] = {};

	string param = info.dump();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	result=JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
	changeViewForData(result);
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    result=CCBridgeToOCManager::dealEventFromGame(param);
	changeViewForData(result);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	loginSuccess();
#endif



	



}

//通过登录状态决定设置数据还是二次登录
void FirstLoginScene::changeViewForData(std::string &result)
{
	json info_json = json::parse(result);
	bool isLogin = info_json["isLogin"];

	if (isLogin) {
		loginSuccess();
	}
	else {
		std::string username = info_json["username"];
		std::string password = info_json["password"];
		_textFieldName->setString(username);
		_textFieldPassword->setString(password);

	}
}


void FirstLoginScene::loginSuccess()
{
	_frameSprite->setVisible(false);
	_startButton->setVisible(true);
}

void FirstLoginScene::loginOut()
{
	_frameSprite->setVisible(true);
	_startButton->setVisible(false);
}
