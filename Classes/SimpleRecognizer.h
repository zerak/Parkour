#ifndef __SIMPLERECOGNIZER_H__
#define __SIMPLERECOGNIZER_H__
#include <limits>
#include <iostream>
#include "GeometricRecognizerTypes.h"
#include "GestureTemplate.h"
#include "SampleGestures.h"

using namespace std;

typedef enum {
	SimpleGesturesRight,//
	SimpleGesturesLeft,//开始游戏
	SimpleGesturesUp,//游戏结束
	SimpleGesturesDown,//
	SimpleGesturesError,//
	SimpleGesturesNotSupport

} SimpleGestures;

// same as dollar library
//定义与dallar库一样的Point。这使得项目可以很简单的使用这两个库
namespace Parkour{
class Point
{
public:
	//--- Wobbrock used doubles for these, not ints
	//int x, y;
	double x, y;
	Point() 
	{
		this->x=0; 
		this->y=0;
	}
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
};
}

class SimpleRecognizer
{
protected:
	//--- These are variables because C++ doesn't (easily) allow
	//---  constants to be floating point numbers
	double X;
	double Y;
	SimpleGestures result;
	std::vector<Parkour::Point> points;

public:
	SimpleRecognizer();

	void beginPoint(double x, double y);
	void movePoint(double x, double y);
	SimpleGestures endPoint();

	std::vector<Parkour::Point>& getPoints();
};

#endif // __SIMPLERECOGNIZER_H__
