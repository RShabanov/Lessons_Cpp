#pragma once
#ifndef _SEARCH_H
#define _SEARCH_H
#include "geometry.h"
void searchLargestTriangles(const Point* pointArray, int pointNum, Triangle* trArray, int maxTrNum);
void findAndInsert(Triangle* trArray, int length, const Triangle& triangle);
void clearPoint(Point& p);
void clearTriangle(Triangle& tr);
#endif