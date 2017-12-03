#include "stdafx.h"
#include "MyVector.h"


CMyVector::CMyVector(double _x, double _y)
{
	x = _x, y = _y;
}

double CMyVector::cross(const CMyVector & other) const
{
	return x*other.y - y*other.x;
}

CMyVector CMyVector::operator*(double r) const
{
	return CMyVector(x*r, y*r);
}

CMyVector CMyVector::operator+(CMyVector other) const
{
	return CMyVector(x + other.x, y + other.y);
}

CMyVector CMyVector::operator-(CMyVector other) const
{
	return CMyVector(x - other.x, y - other.y);
}

bool CMyVector::operator==(CMyVector other) const
{
	return x == other.x && y == other.y;
}

bool CMyVector::operator<(CMyVector other) const
{
	return x < other.x && y < other.y;
}

double CMyVector::ccw(CMyVector a, CMyVector b)
{
	return a.cross(b);
}

double CMyVector::ccw(CMyVector p, CMyVector a, CMyVector b)
{
	return ccw(a - p, b - p);
}

bool CMyVector::sementIntersects(CMyVector a, CMyVector b, CMyVector c, CMyVector d)
{
	double ab = ccw(a, b, c);
	double xy = ccw(a, b, d);

	double cd = ccw(c, d, a);
	double zw = ccw(c, d, b);

	if (ab == 0 && cd == 0&& xy==0 && zw==0) {
		/*
		all 0의 경우
		a<b,c<d인 네점 abcd가 일직선상에 있을 경우
		두선분이 겹치치 않기 위해서는
		b<c 또는 d<a여야 함을 이용
		*/
		if (b < a) swap(a, b);//크기순으로 한 선분내의 점을 정렬
		if (d < c) swap(c, d);
		return (b< c || d <a || b == c || d == a);//하나라도 참이면 true

	}
	return (ab*xy) >= 0 && (cd*zw) >= 0; //둘다 참이여야 true
}

bool CMyVector::checkException(CMyVector inputA, CMyVector inputB, CMyVector existA, CMyVector existB)
{
	//직선 교차 예외처리 보스몹
	
	/*
		1차적으로 직선상에 다른 점이 있으면 안되는 것 예외처리 추가
		
	*/
	
	bool answer;

	answer = sementIntersects(inputA, inputB, existA, existB);//선을 그릴수 있는가? 그릴수 있으면 TRUE
	return answer;
	/*

	//vector2 a(1, 1), b(2, 2), c(2, 2), d(1, 1);//ANSWER=0//1아예 같은 선분인 경우0k//all0
	//vector2 a(1, 1), b(3, 1), c(2, 1), d(3, 1);//ANSWER=0//2선분이 포함되는 경우0k//all0
	//vector2 a(1, 1), b(3, 3), c(2, 2), d(4, 4);//ANSWER=0//3선분이 부분겹침되는 경우//all0
	//vector2 a(1, 1), b(2, 2), c(4, 4), d(3, 3);//ANSWER=1//4선분이 분리되는 경우 all0
	//vector2 a(1, 1), b(2, 2), c(2, 2), d(3, 3);//ANSWER=1//5선분이 일직선상위 한점에서만 만나는 경우 all0
	
	//vector2 a(1, 2), b(2, 3), c(2, 1), d(3, 2);//ANSWER=1//6선분이 평행하는 경우ok//둘이 같은부호==6

	//vector2 a(1, 1), b(2, 2), c(2, 2), d(3, 1);//ANSWER=1//7선분이 접하는 경우ok//0이2개
	//vector2 a(1, 1), b(2, 2), c(2,1), d(1, 2);//ANSWER=0//8선분이 아예 교차하는 경우ok//둘이 반대부호
	//vector2 a(1, 2), b(2, 3), c(2,2), d(3, 2);//ANSWER=1//9선분이 아예 교차x경우ok//둘이 같은부호==4
	
	*/
	
	
}
bool CMyVector::checkDoublePoint(CMyVector inputA, CMyVector inputB, int (*map)[7]) {

	double m_slop;   //현재 그리려는 직선의 기울기
	double m_y;      //y절편
	if (inputA.x != inputB.x)
	{
		//기울기
		m_slop = (double)(inputB.y - inputA.y) / (inputB.x - inputA.x);
		m_y = m_slop * inputA.x - inputA.y;
	}
	else
	{
		m_slop = 100;   //기울기가 무한인 것을 표현, x=n
		m_y = inputA.x;      //기울기가 무한일때 y에 x값 저장.
	}
	int max, min;
	int max_y, min_y;
	bool same = false;   //기울기가 같은지 여부를 알려주는 변수

	if (inputA.x > inputB.x)
	{
		max = inputA.x;
		min = inputB.x;
	}
	else
	{
		max = inputB.x;
		min = inputA.x;
	}
	if (inputA.y > inputB.y)
	{
		max_y = inputA.y;
		min_y = inputB.y;
	}
	else
	{
		max_y = inputB.y;
		min_y = inputA.y;
	}
	double m = 0;

	for (int i = min; i < max + 1; i++)
	{
		for (int j = min_y; j < max_y + 1; j++) {
			if ((inputA.x == i && inputA.y == j) || (inputB.x == i && inputB.y == j))   //x,y가 같을 경우 skip!
				continue;
			else
			{
				if (map[i - 1][j - 1] == 1) {   //현재 선분 위에 있는 점인지를 구분.

					if (inputB.x - i == 0) {   //무한대인 경우 skip해야함.
						m = 100;
					}
					else
						m = (double)(inputB.y - j) / (inputB.x - i);

					if (m_slop == m) {
						same = true;
						//   MessageBox(_T("Error."));
						return same;
					}
				}
			}
		}
	
	}
	return false;

}
CMyVector::CMyVector()
{
}


CMyVector::~CMyVector()
{
}
