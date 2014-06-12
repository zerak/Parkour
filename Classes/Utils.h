/*
    文件名：    Utils.h
    描　述：    游戏中定义的一些公共函数
    创建人：    郝萌主 (博客：http://blog.csdn.net/haomengzhu)

    创建日期：   2013.12.09
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"

//全局变量
#define  g_groundHight  50 
#define g_runnerStartX  100

// collision type for chipmunk
enum SpriteTag{
	SpriteTagRunner,
	SpriteTagCoin,
	SpriteTagRock,
};

#endif // __UTILS_H__
