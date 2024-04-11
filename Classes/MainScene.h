#pragma once
#include "Global.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;

class MainScene :public Scene
{
protected:
	Text* _nameText;
	Text* _levelText;
	Text* _goldText;
	Sprite* _infoSprite;
	Button* _messageSprite;

	spine::SkeletonAnimation* _bookSprite;
	spine::SkeletonAnimation* _musicSprite;
	spine::SkeletonAnimation* _learningSprite;
	spine::SkeletonAnimation* _cinemaSprite;
	spine::SkeletonAnimation* _pouidmSprite;
	

	EventListenerTouchOneByOne* _listener;


public:
	MainScene();
	~MainScene();

	CREATE_FUNC(MainScene);
	virtual bool init();

	void getUserInfo();
	void changeViewForData(std::string &result);

	void intoSetting(Ref* pSender);
	void intoBookStore(Ref* pSender);

	void intoMusicHall(Ref* pSender);

	void intoCinema(Ref* pSender);

	void intoPodium(Ref* pSender);

	void intoStudyReport(Ref* pSender);

	void onGetIcon(string &url);

	void onGetIconFinished(HttpClient *sender, HttpResponse *response);//回调函数，这里有参数Node和void Finish(void* obj);

	bool onTouchBegan(Touch* touch, Event  *event);

	void onTouchEnded(Touch* touch, Event  *event);

	void showMessageIcon(bool isShow);
	void intoShowList(Ref* pSender);
	void setGoldCount(const std::string &result);

};

