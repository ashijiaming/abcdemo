/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

#include <string>
#include "MainScene.h"

USING_NS_CC;
using namespace ui;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{

	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}


	//into main scene
	auto mainItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::intoMainScene, this));
	mainItem->setPosition(100, 200);


	// testJni
	auto oneItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png", CC_CALLBACK_1(HelloWorld::JNIActivity, this));
	oneItem->setPosition(Vec2(100, 100));

	

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, oneItem, mainItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}



	return true;
}


void HelloWorld::JNITest(Ref* pSender) {
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.utils.JNIProvider";
	JniHelper::callStaticVoidMethod(classPath, "voidMethod1");

	JniHelper::callStaticVoidMethod(classPath, "voidMethod2", "JNI is easy");

	JniHelper::callStaticVoidMethod(classPath, "voidMethod3", int(4), float(2.5), "JNI is really easy");

	bool b1 = JniHelper::callStaticBooleanMethod(classPath, "booleanMethod", int(5));
	CC_ASSERT(b1 == true);
	bool b2 = JniHelper::callStaticBooleanMethod(classPath, "booleanMethod", int(-3));
	CC_ASSERT(b2 == false);

	int i = JniHelper::callStaticIntMethod(classPath, "intMethod", int(10), int(10));
	CC_ASSERT(i == 20);

	float f = JniHelper::callStaticFloatMethod(classPath, "floatMethod", float(2.35), float(7.65));
	CC_ASSERT(f == 10.0);

	double d = JniHelper::callStaticDoubleMethod(classPath, "doubleMethod", double(2.5), int(4));
	CC_ASSERT(d == 10.0);

	std::string str = "ABCDEF";
	std::string s1 = JniHelper::callStaticStringMethod(classPath, "stringMethod", str, true);
	CC_ASSERT(s1 == "FEDCBA");
	std::string s2 = JniHelper::callStaticStringMethod(classPath, "stringMethod", str, false);
	CC_ASSERT(s2 == "ABCDEF");

	const char* cstr = "XYZ";
	std::string s3 = JniHelper::callStaticStringMethod(classPath, "stringMethod", cstr, true);
	CC_ASSERT(s3 == "ZYX");

	// should not crash
	for (int i = 0; i < 10000; i++) {
		JniHelper::callStaticVoidMethod(classPath, "voidMethod4", "ABCDEF");
	}
#endif 
}

void HelloWorld::JNIActivity(cocos2d::Ref *pSender) {
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	const::std::string classPath = "com.neoelite.abc.activity.GameActivity";
	JniHelper::callStaticVoidMethod(classPath, "replaceActivity");
#endif
}

//进入MainScene场景
void HelloWorld::intoMainScene(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::create());
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


