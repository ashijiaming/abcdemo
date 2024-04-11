#pragma once
#include <cocos2d.h>
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

#include "Global.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;
USING_NS_CC;

class LearningCenterScene :public Scene
{
public:
	LearningCenterScene();
	~LearningCenterScene();

	CREATE_FUNC(LearningCenterScene);
	virtual bool init();
	

	void onGetNodeInfo();
	void callBackNodeInfo(const std::string &nodeList,const std::string &level,int sort);
	
	void changeLessonUp();
	void moveToTarget(int position,int time);

	void callChangeLessonUp(int position);
	void changeLessonLevel();
	void onIntoLessonUp(int position,int status);

	void onChangeVisible(int position,bool visible);
	
	void onChangeNodeStatus(int position);

	void onGetImage(int position);

	void onGetFinished(HttpClient *sender, HttpResponse *response);//回调函数，这里有参数Node和void Finish(void* obj);

	

private:
	enum MoveEnum
	{
		left=1001,
		right
	};
	int _move;
	Button* _nextButton;
	Button* _levelButton;
	Button* _upButton;
	spine::SkeletonAnimation*   _menSprite;
	Sprite* _spriteImg;
	Sprite* _bgLevelSprite;
	ScrollView* _scrollView;

	Layout* _layoutContainer;

	std::vector<Button*>   _layoutImageArray;
	std::vector<Button*>   _layoutNodeArray;


	float centerX;
	int _lastIndex;
	bool _isAction;
	float _innerWidth;
	int _sort;

    struct NodeInfo{
		string	id;
		string  img;
		int     status;
		int 	sort;
		string  title;
		int	    sign;
	};

	std::vector<NodeInfo> _nodelist;
};

