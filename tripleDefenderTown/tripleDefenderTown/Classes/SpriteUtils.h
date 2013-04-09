#ifndef __SPRITE_UTILS_H_
#define __SPRITE_UTILS_H_
#include "cocos2d.h"

USING_NS_CC;

class SpriteUtils
{
public:
	static void test();
	static CCAnimation* SpriteUtils::animationWithSingleFrames(const char *name);
};
#endif