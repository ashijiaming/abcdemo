#pragma once
#include<string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "nlohmann/json.hpp"
#include "spine/spine-cocos2dx.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "CCBridgeToOCManager.h"
#endif

using namespace std;
USING_NS_CC;

using namespace cocos2d::ui;

using json = nlohmann::json;

extern int extern_level_num;
extern int extern_sex;
extern float scale;

enum ROUTER_TYPE {
	TYPE_LOGIN = 1,
	TYPE_PICK_NAME,
	TYPE_PICK_BIRTHDAY,
	TYPE_BOOK_STORE,
	TYPE_MUSIC_HALL,
	TYPE_CINEMA,
	TYPE_PODIUM,
	TYPE_LESSON_UP,
	TYPE_LESSON_CHANGE_UP,
	TYPE_LESSON_CHANGE_LEVEL,
	TYPE_MAIN_SETTING,
	TYPE_LOGIN_OUT,
	TYPE_LOGIN_STATE,
	TYPE_USER_INFO,
	TYPE_NODE_INFO,
	TYPE_CHANGE_NODE_STATUS,
	TYPE_INTO_MAIN,
	TYPE_MESSAGE_MAIN,
	TYPE_UPDATE_MAIN_DATA,
	TYPE_STUDY_REPORT
};

namespace Global {


}