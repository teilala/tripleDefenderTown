#include "MenuScene.h"
using namespace cocos2d;
bool MenuScene::init()
{    
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		 CCLabelTTF* pStartLabel = CCLabelTTF::create("Start", "Arial", 24);
         CCMenuItemLabel* item1 = CCMenuItemLabel::create(pStartLabel, this, menu_selector(MenuScene::menuCallbackStart) );
         item1->setDisabledColor( ccc3(32,32,64) );
         item1->setColor( ccc3(200,200,255) );

		 CCLabelTTF* pExitLabel = CCLabelTTF::create("Exit", "Arial", 24);
         CCMenuItemLabel* item2 = CCMenuItemLabel::create(pExitLabel, this, menu_selector(MenuScene::menuCallbackExit) );
         item2->setDisabledColor( ccc3(32,32,64) );
         item2->setColor( ccc3(200,200,255) );
		 CCMenu* menu = CCMenu::create(item1,item2, NULL);
		  menu->alignItemsVertically();
		  addChild(menu);
		  menu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
		  bRet = true;
    } while (0);
    return bRet;
}
 
void MenuScene::onEnter()
{    
    // do something    
	CCLog("first");
    CCLayer::onEnter();
}
 
void MenuScene::Show()
{    
	CCDirector::sharedDirector()->purgeCachedData();
    cocos2d::CCScene *pNewScene = CCScene::create();    
	MenuScene *pLayer = MenuScene::create();    
    pNewScene->addChild(pLayer);    
    cocos2d::CCScene *pCurScene = cocos2d::CCDirector::sharedDirector()->getRunningScene();    
    if(NULL == pCurScene)    
        cocos2d::CCDirector::sharedDirector()->runWithScene(pNewScene);    
    else   
        cocos2d::CCDirector::sharedDirector()->replaceScene(pNewScene);    
}

void MenuScene::menuCallbackStart(CCObject* sender) 
{
	Controller::CreateTestScene(GAME_SCENE);
}

void MenuScene::menuCallbackExit(CCObject* sender) 
{
    CCDirector::sharedDirector()->end();
}