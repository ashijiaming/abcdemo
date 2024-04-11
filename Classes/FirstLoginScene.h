#pragma once
#include"Global.h"
class FirstLoginScene:public Scene
{

protected:

public:
	FirstLoginScene();
	~FirstLoginScene();

	CREATE_FUNC(FirstLoginScene);
	virtual bool init();

};

