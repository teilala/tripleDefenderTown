#ifndef _GAMESCENE__H_
#define _GAMESCENE__H_
#define NOTIFY_MAP_TOUCH "notify_map_touch"
#define NOTIFY_MAP_MOVE "notify_map_move"
#define NOTIFY_MAP_END "notify_map_end"
#define NOTIFY_MAP_CANCEL "notify_map_cancel"
#define MAP_GRID_WIDTH 30
#define MAP_GRID_HEIGHT 30
#include "Basic.h"
#include "Defender.h"
#include "Map.h"
class GameScene : public cocos2d::CCLayer
{
public: 
virtual bool init();    
virtual void onEnter(); 
static  void Show();
private:
Defender *moveDefender;
void menuCallbackTest(CCObject *sender);
void onClickTest(CCObject* obj);
void onMapTouch(CCObject* obj);
void onMapMove(CCObject* obj);
void onMapEnd(CCObject* obj);
void onMapCancel(CCObject* obj);
void setMoveDefenderPosition(float px,float py);
CREATE_FUNC(GameScene);
};

#endif
