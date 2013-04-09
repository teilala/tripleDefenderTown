#ifndef _MENUSCENE__H_
#define _MENUSCENE__H_
#include "Basic.h"

USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public: 
virtual bool init();    
virtual void onEnter(); 
static  void Show();    
void MenuScene::menuCallbackStart(CCObject* sender);
void MenuScene::menuCallbackExit(CCObject* sender);
CREATE_FUNC(MenuScene);
};
#endif