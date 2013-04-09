#include "controller.h"

void Controller::CreateTestScene(int nIdx)
{
    CCDirector::sharedDirector()->purgeCachedData();

    TestScene* pScene = NULL;

    switch (nIdx)
    {
    case MENU_SCENE:
         MenuScene::Show(); break;
    case GAME_SCENE:
		 GameScene::Show(); break;
     case EQUIP_SCENE:
		 EquipScene::Show(); break;
    default:
        break;
    }
}

void Controller::menuCallbackTest2(CCObject *sender)
{
	CCLog("ok");
}
