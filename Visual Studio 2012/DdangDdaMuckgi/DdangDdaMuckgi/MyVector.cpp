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
		all 0�� ���
		a<b,c<d�� ���� abcd�� �������� ���� ���
		�μ����� ��ġġ �ʱ� ���ؼ���
		b<c �Ǵ� d<a���� ���� �̿�
		*/
		if (b < a) swap(a, b);//ũ������� �� ���г��� ���� ����
		if (d < c) swap(c, d);
		return (b< c || d <a || b == c || d == a);//�ϳ��� ���̸� true

	}
	return (ab*xy) >= 0 && (cd*zw) >= 0; //�Ѵ� ���̿��� true
}

bool CMyVector::checkException(CMyVector inputA, CMyVector inputB, CMyVector existA, CMyVector existB)
{
	//���� ���� ����ó�� ������
	
	/*
		1�������� ������ �ٸ� ���� ������ �ȵǴ� �� ����ó�� �߰�
		
	*/
	
	bool answer;

	answer = sementIntersects(inputA, inputB, existA, existB);//���� �׸��� �ִ°�? �׸��� ������ TRUE
	return answer;
	/*

	//vector2 a(1, 1), b(2, 2), c(2, 2), d(1, 1);//ANSWER=0//1�ƿ� ���� ������ ���0k//all0
	//vector2 a(1, 1), b(3, 1), c(2, 1), d(3, 1);//ANSWER=0//2������ ���ԵǴ� ���0k//all0
	//vector2 a(1, 1), b(3, 3), c(2, 2), d(4, 4);//ANSWER=0//3������ �κа�ħ�Ǵ� ���//all0
	//vector2 a(1, 1), b(2, 2), c(4, 4), d(3, 3);//ANSWER=1//4������ �и��Ǵ� ��� all0
	//vector2 a(1, 1), b(2, 2), c(2, 2), d(3, 3);//ANSWER=1//5������ ���������� ���������� ������ ��� all0
	
	//vector2 a(1, 2), b(2, 3), c(2, 1), d(3, 2);//ANSWER=1//6������ �����ϴ� ���ok//���� ������ȣ==6

	//vector2 a(1, 1), b(2, 2), c(2, 2), d(3, 1);//ANSWER=1//7������ ���ϴ� ���ok//0��2��
	//vector2 a(1, 1), b(2, 2), c(2,1), d(1, 2);//ANSWER=0//8������ �ƿ� �����ϴ� ���ok//���� �ݴ��ȣ
	//vector2 a(1, 2), b(2, 3), c(2,2), d(3, 2);//ANSWER=1//9������ �ƿ� ����x���ok//���� ������ȣ==4
	
	*/
	
	
}
bool CMyVector::checkDoublePoint(CMyVector inputA, CMyVector inputB, int (*map)[7]) {

	double m_slop;   //���� �׸����� ������ ����
	double m_y;      //y����
	if (inputA.x != inputB.x)
	{
		//����
		m_slop = (double)(inputB.y - inputA.y) / (inputB.x - inputA.x);
		m_y = m_slop * inputA.x - inputA.y;
	}
	else
	{
		m_slop = 100;   //���Ⱑ ������ ���� ǥ��, x=n
		m_y = inputA.x;      //���Ⱑ �����϶� y�� x�� ����.
	}
	int max, min;
	int max_y, min_y;
	bool same = false;   //���Ⱑ ������ ���θ� �˷��ִ� ����

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
			if ((inputA.x == i && inputA.y == j) || (inputB.x == i && inputB.y == j))   //x,y�� ���� ��� skip!
				continue;
			else
			{
				if (map[i - 1][j - 1] == 1) {   //���� ���� ���� �ִ� �������� ����.

					if (inputB.x - i == 0) {   //���Ѵ��� ��� skip�ؾ���.
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
