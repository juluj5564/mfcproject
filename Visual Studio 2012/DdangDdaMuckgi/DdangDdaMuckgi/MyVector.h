#pragma once
#include<stdio.h>
#include<iostream>
using namespace std;
#define ma2(x,y) (x>y?x:y)
#define mi2(x,y) (x<y?x:y)
#define EPSILON 0.0001

class CMyVector
{
public:
	double x, y;
	CMyVector();
	~CMyVector();
	//생성자
	CMyVector(double _x, double _y);
	
	//외적연산
	double cross(const CMyVector& other) const;

	//연산자 오버로딩을 통해 실제 벡터의 연산을 구현
	CMyVector operator * (double r) const;//벡터의 실수배
	CMyVector operator + (CMyVector other) const;//벡터의 덧셈
	CMyVector operator - (CMyVector other) const;//벡터의 뺄셈
	bool operator == (CMyVector other) const;//두 벡터의 비교
	bool operator < (CMyVector other) const;

	static double ccw(CMyVector a, CMyVector b);//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
	static double ccw(CMyVector p, CMyVector a, CMyVector b);//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 
	static bool sementIntersects(CMyVector a, CMyVector b, CMyVector c, CMyVector d);//두 선분이 서로 접촉하는지 여부를 반환
	static bool checkException(CMyVector inputA, CMyVector inputB, CMyVector existA, CMyVector existB);
	//static bool paralleSegments(CMyVector a, CMyVector b, CMyVector c, CMyVector d, CMyVector& p); //점 a, b와 점 c, d가 평행한 두 선분 일 때 이들이 한 점에서 겹치는지 확인한다.
	//static bool checkLineCross(CMyVector inputA, CMyVector inputB, CMyVector existA, CMyVector existB);
	static bool checkDoublePoint(CMyVector inputA, CMyVector inputB, int(*map)[7]);
};


