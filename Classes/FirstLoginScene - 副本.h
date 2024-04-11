#pragma once
#include"Global.h"
class FirstLoginScene:public Scene
{

protected:
	 TextField* _textFieldName;
	 TextField* _textFieldPassword;
	 Sprite* _frameSprite;
	 Button* _startButton;


public:
	FirstLoginScene();
	~FirstLoginScene();

	CREATE_FUNC(FirstLoginScene);
	virtual bool init();
	
	void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
	void loginFirst();
	void getLoginState();

	void changeViewForData(std::string &result);

	void loginSuccess();
	void loginOut();
};

