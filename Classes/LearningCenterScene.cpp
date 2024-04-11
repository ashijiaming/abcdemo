#include "LearningCenterScene.h"
#include "MainScene.h"

LearningCenterScene::LearningCenterScene()
{
}


LearningCenterScene::~LearningCenterScene()
{
}

bool LearningCenterScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//back btn
	Button* backButton = Button::create("ic_back.png");
	backButton->setPosition(Vec2(20 + 172 / 2, 922 + 140 / 2));
	backButton->setScale(scale);
	backButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(MainScene::create());
	});
	this->addChild(backButton,1);

	//up btn
	_upButton = Button::create("ic_center_up.png");
	_upButton->setPosition(Vec2(232 + 507 / 2, 922 + 141 / 2));
	_upButton->setScale(scale);
	_upButton->setTitleFontSize(50);
	_upButton->addClickEventListener([=](Ref* sender) {
		if (_isAction)return;
		changeLessonUp();
	});
	this->addChild(_upButton, 1);

	//level btn
	_levelButton = Button::create("ic_center_level.png");
	_levelButton->setPosition(Vec2(_contentSize.width - (344 / 2+20), 922 +  140/ 2));
	_levelButton->setScale(scale);
	_levelButton->setTitleFontSize(50);
	_levelButton->addClickEventListener([=](Ref* sender) {
		changeLessonLevel();
	});
	this->addChild(_levelButton, 1);
	
	//sprite men idle  idle2 walk 
	_menSprite = spine::SkeletonAnimation::createWithJsonFile("anim/anim_boy.json", "anim/anim_boy.atlas");
	_menSprite->setPosition(Vec2(200, 220));
	_menSprite->setContentSize(Size(176, 274));
	_menSprite->setAnimation(0, "idle2", false);
	_menSprite->setAnimation(0, "idle2", true);

	_scrollView = ui::ScrollView::create();
	_scrollView->setContentSize(Size(_contentSize.width, _contentSize.height));
	_scrollView->setScrollBarEnabled(false);
	//_scrollView->setScrollBarWidth(4);
	//_scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
	//_scrollView->setScrollBarColor(Color3B::WHITE);
	_scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	this->addChild(_scrollView);

	_scrollView->addChild(_menSprite, 1);

	_layoutContainer = Layout::create();

	char str_bg[30];
	if (extern_level_num < 0) {
		sprintf(str_bg, "bg_level_%d.png", 9);
	}
	else
	{
		sprintf(str_bg, "bg_level_%d.png", extern_level_num);
	}
	
	Sprite* bgLevelSprite = Sprite::create(str_bg);
	bgLevelSprite->setAnchorPoint(Vec2::ZERO);
	bgLevelSprite->setScale(scale);
   _layoutContainer->addChild(bgLevelSprite);

	_scrollView->addChild(_layoutContainer);

	onGetNodeInfo();
	
	return true;
}

/*
*获取节点数据
*/
void LearningCenterScene::onGetNodeInfo()
{
	
	json info;
	info["type"] = TYPE_NODE_INFO;
	info["data"] = {};

	string param = info.dump();

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	string result = "[{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":2,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":3,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":0,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":1,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b553eee\",\"img\":\"\",\"sign\":1,\"sort\":0,\"status\":0,\"title\":\"测试节点\"},{\"id\":\"7f843b0a19f82aedaa8076cdde07965e\",\"img\":\"\",\"sign\":1,\"sort\":0,\"status\":1,\"title\":\"qwe\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":2,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":3,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":0,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b55391\",\"img\":\"\",\"sign\":2,\"sort\":0,\"status\":1,\"title\":\"课程节点\"},{\"id\":\"5a79fe00cfd22debb961da7624b553eee\",\"img\":\"\",\"sign\":1,\"sort\":0,\"status\":0,\"title\":\"测试节点\"},{\"id\":\"7f843b0a19f82aedaa8076cdde07965e\",\"img\":\"\",\"sign\":1,\"sort\":0,\"status\":1,\"title\":\"qwe\"}]";
	//string result = "[]";
	string level = "LEVEL 1";
	int sort = 1;
	callBackNodeInfo(result, level, sort);
#endif 



}

/*
节点数据获取成功返回
*/
void LearningCenterScene::callBackNodeInfo(const std::string & result, const std::string &level,int sort)
{
	log("nodeInfo:%s", result.c_str());
	_sort = sort;
	_menSprite->setPosition(Vec2(200, 220));
	_menSprite->setRotationSkewY(0);
	_menSprite->setAnimation(0, "idle2", false);
	_menSprite->setAnimation(0, "idle2", true);
	_menSprite->stopActionByTag(1);
	_scrollView->getInnerContainer()->setPositionX(0);
	_scrollView->getInnerContainer()->stopActionByTag(2);
	

	_lastIndex = 0;
	
	_nodelist.clear();
	_layoutImageArray.clear();
    _layoutNodeArray.clear();
	_layoutContainer->removeAllChildren();

	char str_bg[30];
	if (sort < 0) {
		sprintf(str_bg, "bg_level_%d.png", 9);
	}
	else
	{
		sprintf(str_bg, "bg_level_%d.png", sort);
	}
	Sprite* bgSprite = Sprite::create(str_bg);
	bgSprite->setAnchorPoint(Vec2(0,0));
	bgSprite->setScale(scale);
	_layoutContainer->addChild(bgSprite);

	json nodeList = json::parse(result);
	if(nodeList.size()<=0){
		_upButton->setTitleText("暂无数据");
		_levelButton->setTitleText(level);
		return;
	}

	for (size_t i = 0; i < nodeList.size(); i++)
	{
		json node=nodeList[i];
		string img=(node["img"] == nullptr)?"":node["img"];
		string title = (node["title"] == nullptr) ? "" : node["title"];
		NodeInfo nodeInfo = {node["id"],img,node["status"],node["sort"],title,node["sign"]};
		_nodelist.push_back(nodeInfo);
	}

	// Create the scrollview by vertical
	float innerHeight = _scrollView->getContentSize().height / 3;
	int num =_nodelist.size();
	float space = (400 + 216) / 2;
	_innerWidth = space + num * space;
	if (_innerWidth<_contentSize.width)
	{
		_innerWidth = _contentSize.width;
	}
	_scrollView->setInnerContainerSize(Size(_innerWidth, innerHeight));

	int number = _innerWidth / 3500;
	log("number=%d innerWidth=%f", number, _innerWidth);

	for (int i = 0; i < number; i++)
	{
		Sprite* bgSprite = Sprite::create(str_bg);
		bgSprite->setScale(scale);
		bgSprite->setAnchorPoint(Vec2::ZERO);
		bgSprite->setPositionX(3500 * (i+1));
		_layoutContainer->addChild(bgSprite);
	}

	centerX = _contentSize.width / 2;
	_lastIndex = 0;
	for (size_t i = 0; i < num; i++)
	{

		Button* nodeBgSprite = Button::create("ic_center_node_bg.png");
		nodeBgSprite->setPosition(Vec2(300 + i * space, 500 + 301 / 2));
		nodeBgSprite->setScale(scale);
		nodeBgSprite->setVisible(false);


		unsigned status=_nodelist[i].status;
		log("item is status%d", status);
		int isLock = (status & 2)==2;//第二位代表未锁0和锁1
		log("item is lock%d", isLock);
		if (isLock)
		{
			Sprite* lockSprite = Sprite::create("ic_level_lock.png");
			lockSprite->setPosition(Vec2(nodeBgSprite->getContentSize().width / 2, nodeBgSprite->getContentSize().height / 2 + 20));
			nodeBgSprite->addChild(lockSprite, 1);
		}

		int isMessage=(status & 4) == 4;
		if (isMessage)
		{
			Sprite* tipSprite = Sprite::create("ic_tip_message.png");
			tipSprite->setPosition(Vec2(177 + i * space, 230 + 168 / 2));
			tipSprite->setScale(scale);
			_layoutContainer->addChild(tipSprite);
			auto actionUp = JumpBy::create(2, Vec2(0, 0), 30, 4);
			tipSprite->runAction(RepeatForever::create(actionUp));
		}
		int isComplete = (status & 8) == 8;
		if (isComplete)
		{
			Sprite* lockSprite = Sprite::create("ic_level_lock.png");
			lockSprite->setPosition(Vec2(nodeBgSprite->getContentSize().width / 2, nodeBgSprite->getContentSize().height / 2 + 20));
			nodeBgSprite->addChild(lockSprite, 1);
		}
		

		nodeBgSprite->addClickEventListener([=](Ref* sender) {
			onIntoLessonUp(i, status);
		});
        _layoutContainer->addChild(nodeBgSprite);
		_layoutImageArray.push_back(nodeBgSprite);

		bool isDone= (status & 1)||(status&8);

		string item = "ic_item_center_undone.png";
		if (isDone)
		{
			item = "ic_item_center_done.png";
		}
		Button* btnItem = Button::create(item, item);
		btnItem->setPosition(Vec2(177 + i * space, 93 + 168 / 2));
		btnItem->setTitleFontSize(45);
		btnItem->setScale(scale);
		btnItem->setTag(i);
		btnItem->setTitleText("\r\n"+_nodelist[i].title);
		_layoutNodeArray.push_back(btnItem);

		_isAction = false;
		btnItem->addClickEventListener([=](Ref* sender) {
			int tag = btnItem->getTag();
			moveToTarget(tag,1);
		});
        _layoutContainer->addChild(btnItem);

	}

	onChangeVisible(0, true);
	onGetImage(0);
	_upButton->setTitleText(_nodelist[0].title);
	_levelButton->setTitleText(level);

	//调到上次保存的那个节点
	int lastLevelSort = UserDefault::getInstance()->getIntegerForKey("lastLevelSort", -1);
	if (lastLevelSort == sort)
	{
		int lastNodeSort = UserDefault::getInstance()->getIntegerForKey("lastNodeSort", 0);
		callChangeLessonUp(lastNodeSort);
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey("lastLevelSort", sort);
		UserDefault::getInstance()->setIntegerForKey("lastNodeSort", 0);
	}
}




/*
*选择单元
*/
void LearningCenterScene::changeLessonUp()
{

	json info;
	info["type"] = TYPE_LESSON_CHANGE_UP;
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

void LearningCenterScene::moveToTarget(int position, int type)
{

	if (position>=_layoutImageArray.size())
	{
		log("not have this node");
		return;
	}
	UserDefault::getInstance()->setIntegerForKey("lastNodeSort", position);

	int tempSort = _sort;
	int move = position - _lastIndex;
	if (_isAction || move == 0)
	{
		log("ignore onclick");
		return;
	}
	
	centerX = _contentSize.width / 2 - _scrollView->getInnerContainerPosition().x;
	Button* btnItem = _layoutNodeArray[position];
	Vec2 btnPos = btnItem->getPosition();
	int time=0;
	if (type==1)
	{
		time = abs(move);
		if (move > 7)
		{
			float menX = centerX - _contentSize.width / 2;
			_menSprite->setPositionX(menX);
			time = (btnPos.x - menX) / 200;
		}
		if (move < -7)
		{
			float menX = centerX + _contentSize.width / 2;
			_menSprite->setPositionX(menX);
			time = (menX - btnPos.x) / 200;
		}
	}
	Vec2 menPos = _menSprite->getPosition();

	log("move=%d lastIndex=%d index=%d centerX:%f", move, _lastIndex, position, centerX);


	int bg_time = time * 1.5;
	int men_time = time * 1;

	_isAction = true;
	onChangeVisible(_lastIndex, false);
	
	CallFuncN* func = CallFuncN::create([=](Ref* sender) {
		if (tempSort==_sort)
		{
			onChangeVisible(position, true);
			onGetImage(position);
		}
		_isAction = false;
		_menSprite->setAnimation(0, "idle2", false);
		_menSprite->setAnimation(0, "idle2", true);
	});
	Sequence* sequenceMen = Sequence::create(MoveTo::create(men_time, Vec2(btnPos.x, menPos.y)), func, nullptr);
	sequenceMen->setTag(1);
	_menSprite->runAction(sequenceMen);
	_menSprite->setAnimation(0, "walk", false);
	_menSprite->setAnimation(0, "walk", true);
	if (move > 0)
	{
		_menSprite->setRotationSkewY(0);
		//float moveX = 200 * move;
		float moveX = btnPos.x - menPos.x;
		float marginRight = _innerWidth - centerX - _contentSize.width / 2;

		log("move right marginRight %f:", marginRight);

		if (centerX - btnPos.x < 0)
		{
			log(" layout move left");
			if (marginRight > moveX)
			{
				MoveBy* action= MoveBy::create(bg_time, Vec2(-moveX, 0));
				action->setTag(2);
				_scrollView->getInnerContainer()->runAction(action);
			}
			else
			{
				MoveBy* action = MoveBy::create(bg_time, Vec2(-marginRight, 0));
				action->setTag(2);
				_scrollView->getInnerContainer()->runAction(action);
			}

		}

	}
	else if (move < 0)
	{
		_menSprite->setRotationSkewY(180);
		//float moveX = -200 * move;
		float moveX =menPos.x- btnPos.x;
		float marginLeft = centerX - _contentSize.width / 2;

		log("move left centerX:%f,marginLeft %f:", centerX, marginLeft);

		if (centerX - btnPos.x > 0)
		{
			log(" layout move right");
			if (marginLeft > moveX)
			{
				MoveBy* action = MoveBy::create(bg_time, Vec2(moveX, 0));
				action->setTag(2);
				_scrollView->getInnerContainer()->runAction(action);
			}
			else
			{
				MoveBy* action = MoveBy::create(bg_time, Vec2(marginLeft, 0));
				action->setTag(2);
				_scrollView->getInnerContainer()->runAction(action);
			}

		}
	}
	_lastIndex = btnItem->getTag();
}

/*
*切换节点信息调用
*/
void LearningCenterScene::callChangeLessonUp(int position)
{
	moveToTarget(position, 0);
	_upButton->setTitleText(_nodelist[position].title);
}

/*
* 选择等级
*/
void LearningCenterScene::changeLessonLevel()
{
	
	json info;
	info["type"] = TYPE_LESSON_CHANGE_LEVEL;
	info["data"] = {};

	string param = info.dump();

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticStringMethod(classPath, "dealEventFromGame", param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	CCBridgeToOCManager::dealEventFromGame(param);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	string result = "[]";
	string level = "level2";
	int sort = 2;
	callBackNodeInfo(result, level, sort);
#endif 


}

/*
* 进入课程节点详细
*/
void LearningCenterScene::onIntoLessonUp(int position,int status)
{
	string nodeId=_nodelist[position].id;
	int nodeSign =_nodelist[position].sign;
	string title = _nodelist[position].title;
	json data;
	data["nodeId"] = nodeId;
	data["nodeSign"] = nodeSign;
	data["nodeTitle"] = title;
	data["position"] = position;
	data["status"] = status;
	json info;
	info["type"] = TYPE_LESSON_UP;
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

/*
* 改变布局的显示状态
*/
void LearningCenterScene::onChangeVisible(int position,bool visiable)
{
	_upButton->setTitleText(_nodelist[position].title);
	_layoutImageArray[position]->setVisible(visiable);

}

/*
*如果节点完成则(弃用)
*/
void LearningCenterScene::onChangeNodeStatus(int position)
{
	_layoutNodeArray[position]->loadTextureNormal("ic_item_center_done.png");
	_layoutNodeArray[position]->loadTexturePressed("ic_item_center_done.png");
}

/*
*  通过url获取图片
*/
void LearningCenterScene::onGetImage(int position)
{

	std::string path = FileUtils::getInstance()->getWritablePath() + "test.png";
	if (FileUtils::getInstance()->isFileExist(path))
	{
		_spriteImg = Sprite::create(path);
		_spriteImg->setPosition(100, 100);
		this->addChild(_spriteImg);
	}
	else
	{
		HttpClient* httpClient = HttpClient::getInstance();
		HttpRequest* httpRequest = new HttpRequest();
		httpRequest->setRequestType(HttpRequest::Type::GET);
		httpRequest->setUrl(_nodelist[position].img);
		httpRequest->setResponseCallback(CC_CALLBACK_2(LearningCenterScene::onGetFinished,this));
		char str[8];
		sprintf(str,"%d",position);
		httpRequest->setTag(str);
		httpClient->setTimeoutForConnect(30);
		httpClient->send(httpRequest);
		httpRequest->release();//用完之后释放

	}

}

void LearningCenterScene::onGetFinished(HttpClient *sender, HttpResponse *response)
{
	Scene *scene = Director::getInstance()->getRunningScene();
	if (typeid(*scene) != typeid(LearningCenterScene)) {
		return;
	}
	if (!response)
	{
		log("response is null");
		return;
	}
	if (!response->isSucceed())
	{
		log("reponse return false:%s",response->getErrorBuffer());
	}
	if (response->getResponseCode() != 200)
	{
		log("reponse return code:%ld", response->getResponseCode());
		return;
	}
	const char* tag=response->getHttpRequest()->getTag();
	if (0 != strlen(tag)){
		log("reponse getTag:%s", tag);
	}
	int index=atoi(tag);

	log("response index=%d", index);
	if (_layoutImageArray.size() <= 0)
	{
		return;
	}
	std::vector<char>* buffData = response->getResponseData();
	Image* img = new Image();
	img->initWithImageData((unsigned char*)buffData->data(), buffData->size());
	Texture2D* texture = new Texture2D();
	bool isImage = texture->initWithImage(img);
	img->release();
	Button* nodeLayout = _layoutImageArray[index];
	_spriteImg = Sprite::createWithTexture(texture);
	texture->release();
	_spriteImg->setContentSize(nodeLayout->getContentSize()*0.7);
	_spriteImg->setPosition(Vec2(nodeLayout->getContentSize().width/2, nodeLayout->getContentSize().height / 2+20));
	nodeLayout->addChild(_spriteImg);
	


}



