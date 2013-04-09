#ifndef _EQUIPSCENE__H_
#define _EQUIPSCENE__H_
#include "Basic.h"

USING_NS_CC;
class EquipScene : public cocos2d::CCLayer
{
public: 
virtual bool init();    
virtual void onEnter(); 
static  void Show();    
CREATE_FUNC(EquipScene);
};
#endif