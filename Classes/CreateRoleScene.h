#pragma once
#include "Global.h"

class CreateRoleScene :public Scene
{
public:
	CreateRoleScene();
	~CreateRoleScene();

	CREATE_FUNC(CreateRoleScene);
	
	virtual bool init();

	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);

	void onIntoPickName();
	void onBackPickName(const std::string &data);

	void onIntoPickBirthday();
	void onBackPickBirthday(const std::string &data);


private:
	Text* nameText;

	Text* birthdayText;

	spine::SkeletonAnimation* _menSprite;
	spine::SkeletonAnimation* _womenSprite;

	ImageView* _manImage;
	ImageView* _womanImage;
	int _gender; //1 男 2女

	EventListenerTouchOneByOne* _listener;


};

