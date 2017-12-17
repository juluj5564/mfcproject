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
	//������
	CMyVector(double _x, double _y);
	
	//��������
	double cross(const CMyVector& other) const;

	//������ �����ε��� ���� ���� ������ ������ ����
	CMyVector operator * (double r) const;//������ �Ǽ���
	CMyVector operator + (CMyVector other) const;//������ ����
	CMyVector operator - (CMyVector other) const;//������ ����
	bool operator == (CMyVector other) const;//�� ������ ��
	bool operator < (CMyVector other) const;

	static double ccw(CMyVector a, CMyVector b);//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ
	static double ccw(CMyVector p, CMyVector a, CMyVector b);//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ 
	static bool sementIntersects(CMyVector a, CMyVector b, CMyVector c, CMyVector d);//�� ������ ���� �����ϴ��� ���θ� ��ȯ
	static bool checkException(CMyVector inputA, CMyVector inputB, CMyVector existA, CMyVector existB);
	//static bool paralleSegments(CMyVector a, CMyVector b, CMyVector c, CMyVector d, CMyVector& p); //�� a, b�� �� c, d�� ������ �� ���� �� �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
	static int check(int x1, int y1, int x2, int y2);
	static bool checkbox(int a, int b, int c, int d);
	static bool checkLineCross(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	static bool checkDoublePoint(CMyVector inputA, CMyVector inputB, int(*map)[7]);
};


