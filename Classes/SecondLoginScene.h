#pragma once
#include <cocos2d.h>
USING_NS_CC;

class SecondLoginScene :public Scene
{
public:
	SecondLoginScene();
	~SecondLoginScene();
	
	CREATE_FUNC(SecondLoginScene);
	virtual bool init();

	void saveLoginInfo(const std::string &normalImage);

};

