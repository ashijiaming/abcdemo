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
	float scale = Director::getInstance()->getContentScaleFactor();

	//background
	bgSpriteOne = Sprite::create("bg_center_leaning.png");
	bgSpriteOne->setPosition(_contentSize.width / 2, _contentSize.height / 2);
	bgSpriteOne->setScale(scale);
	//this->addChild(bgSpriteOne);

	//background
	bgSpriteTwo = Sprite::create("bg_center_leaning.png");
	bgSpriteTwo->setPosition(_contentSize.width / 2 + _contentSize.width, _contentSize.height / 2);
	bgSpriteTwo->setScale(scale);
	//this->addChild(bgSpriteTwo);

	//back btn
	Button* backButton = Button::create("ic_back.png", "ic_back.png");
	backButton->setPosition(Vec2(20 + 172 / 2, 922 + 140 / 2));
	backButton->setScale(scale);
	backButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(MainScene::create());
	});
	this->addChild(backButton, 1);

	//up btn
	Button* upButton = Button::create("ic_center_up.png", "ic_center_up.png");
	upButton->setPosition(Vec2(232 + 507 / 2, 922 + 141 / 2));
	upButton->setScale(scale);
	upButton->addClickEventListener([=](Ref* sender) {
		changeLessionUp();
	});
	this->addChild(upButton, 1);


	//level btn
	Button* levelButton = Button::create("ic_center_level.png", "ic_center_level.png");
	levelButton->setPosition(Vec2(1555 + 344 / 2, 922 + 140 / 2));
	levelButton->setScale(scale);
	levelButton->addClickEventListener([=](Ref* sender) {
		changeLessionLevel();
	});
	this->addChild(levelButton, 1);


	//sprite men
	menSprite = Sprite::create("sp_role_men.png");
	menSprite->setPosition(Vec2(200, 220 + 598 / 2));
	menSprite->setScale(scale);

	//list
	ListView* listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	listView->setBounceEnabled(true);
	listView->setContentSize(Size(_contentSize.width, _contentSize.height));
	listView->setBackGroundImage("bg_center_leaning.png");
	listView->addEventListener((ListView::ccListViewCallback)CC_CALLBACK_2(LearningCenterScene::selectedItemEvent, this));
    this->addChild(listView);

	// create model
	Button* default_button = Button::create("ic_tem_center_undone.png", "ic_tem_center_undone.png");
	default_button->setName("ic_tem_center_undone");

	Layout *default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(Size(300, _contentSize.height));
	default_button->setPosition(Vec2(default_item->getContentSize().width / 2, 93 + 168 / 2));
	default_item->addChild(default_button);

	// set model
	listView->setItemModel(default_item);

	// set all items layout gravity
	listView->setGravity(ListView::Gravity::CENTER_VERTICAL);

	int _totalCount = 20;
	int _spawnCount = 4;
	//initial the data
	for (int i = 0; i < _totalCount; ++i) {
		Widget* item = default_item->clone();
		item->setTag(i);
		Button* btnItem = (Button*)item->getChildByName("ic_tem_center_undone");
		btnItem->setTitleText("item" + i);
		listView->pushBackCustomItem(item);
	}

	// set items margin
	float spacing = 4;
	listView->setItemsMargin(spacing);
	float _itemTemplateWidth = default_item->getContentSize().width;
	float _reuseItemOffset = (_itemTemplateWidth + spacing) * _spawnCount;

	//listView->forceDoLayout();
	float totalWidth = _itemTemplateWidth * _totalCount + (_totalCount - 1) * 4;
	listView->getInnerContainer()->setContentSize(Size(totalWidth, listView->getInnerContainerSize().height));

	listView->addChild(menSprite);




	return true;
}

void LearningCenterScene::selectedItemEvent(cocos2d::Ref * sender, cocos2d::ui::ListView::EventType type)
{

	switch (type)
	{
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
		ListView* listView = static_cast<ListView*>(sender);
		auto item = listView->getItem(listView->getCurSelectedIndex());
		log("select child start index = %d", item->getTag());
		break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
		ListView* listView = static_cast<ListView*>(sender);
		int index=listView->getCurSelectedIndex();
		auto item = listView->getItem(index);
		Button* btnItem = (Button*)item->getChildByName("ic_tem_center_undone");
		float btnPosX = btnItem->getPositionX();
		float left = _contentSize.width / 2;
		float right = listView->getInnerContainerSize().width - left;
		float menPosX = menSprite->getPositionX();
		float currentItemPosX=item->getPositionX()+ btnPosX;
		float move = 304;
		log("btnPosX:%f left:%f right:%f", btnPosX, left, right);
		int direction =index - lastIndex;
			menSprite->runAction(MoveTo::create(1, Vec2(currentItemPosX, menSprite->getPosition().y)));
			if (currentItemPosX > left&& currentItemPosX < right&&direction>0)
			{
			
				listView->getInnerContainer()->runAction(MoveBy::create(2, Vec2(-move*direction, 0)));
			}
			else if(currentItemPosX > left&& currentItemPosX < right&&direction<0)
			{
				listView->getInnerContainer()->runAction(MoveBy::create(2, Vec2(-move*direction, 0)));
			}
		

		lastIndex = index;
		log("select child end index = %d", item->getTag());
		break;
	}
	default:
		break;
	}

	}

/*
*选择单元
*/
void LearningCenterScene::changeLessionUp()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticVoidMethod(classPath, "replaceKindActivity", int(5));
#endif
}

/*
* 选择等级
*/
void LearningCenterScene::changeLessionLevel()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticVoidMethod(classPath, "replaceKindActivity", int(6));
#endif
}

void LearningCenterScene::onGetImage()
{

	std::string path = FileUtils::getInstance()->getWritablePath() + "test.png";
	if (FileUtils::getInstance()->isFileExist(path))
	{
		spriteImg = Sprite::create(path);
		spriteImg->setPosition(100, 100);
		this->addChild(spriteImg);
	}
	else
	{
		HttpClient* httpClient = HttpClient::getInstance();
		HttpRequest* httpRequest = new HttpRequest();
		httpRequest->setRequestType(HttpRequest::Type::GET);
		httpRequest->setUrl("http://oss.hkxdjy.com/My%20World/headPic/L6/2.png");
		httpRequest->setResponseCallback(this, callfuncND_selector(LearningCenterScene::onGetFinished));
		httpRequest->setTag("PicGet");
		httpClient->setTimeoutForConnect(30);
		httpClient->send(httpRequest);
		httpRequest->release();//用完之后释放

	}

}

void LearningCenterScene::onGetFinished(Node * node, void * obj)
{
	HttpResponse* response = (HttpResponse*)obj;
	if (!response)
	{
		log("response is null");
		return;
	}
	if (!response->isSucceed())
	{
		log("reponse return false:%s", response->getErrorBuffer());
	}
	if (0 != strlen(response->getHttpRequest()->getTag())) {
		log("reponse getTag:%s", response->getHttpRequest()->getTag());
	}

	std::vector<char>* buffData = response->getResponseData();
	Image* img = new Image();
	img->initWithImageData((unsigned char*)buffData->data(), buffData->size());
	Texture2D* texture = new Texture2D();
	bool isImage = texture->initWithImage(img);
	img->release();
	spriteImg = Sprite::createWithTexture(texture);
	spriteImg->setContentSize(Size(100, 120));
	spriteImg->setPosition(menSprite->getPosition().x, menSprite->getPosition().y + 300);
	this->addChild(spriteImg);


}

