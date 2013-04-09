#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Scene.h"
#include "cocos2d.h"
USING_NS_CC;

class Controller
{
public:
	static void CreateTestScene(int nIdx);
	void menuCallbackTest2(CCObject *sender);
};

#endif
