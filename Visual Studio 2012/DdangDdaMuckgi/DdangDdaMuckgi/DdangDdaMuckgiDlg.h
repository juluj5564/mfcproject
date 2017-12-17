
// DdangDdaMuckgiDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "ml.h"
#include "MyVector.h"


// CDdangDdaMuckgiDlg 대화 상자
class CDdangDdaMuckgiDlg : public CDialogEx
{
// 생성입니다.
public:
	CDdangDdaMuckgiDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CRect view;
	IplImage *m_view;
	CvvImage m_View;

	int map[7][7];
	int line[160][4]; //160개, 각 팀별로 약 80턴을 수행할 수 있음
	int count;
	CvPoint start_point, end_point;
	bool chk;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DDANGDDAMUCKGI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_iView;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int x_point1;
	int x_point2;
	int y_point1;
	int y_point2;
	int red_score;
	int blue_score;
	afx_msg void OnBnClickedInput();
	CString team_name;
	CString histo;
	afx_msg void OnBnClickedRestart();

	//함수 추가
	CMyVector vec;
	void strategy1();//1번 전략 :  선을 그을 수 있을 때까지 긋는다
	//void strategt2();//2번 전략 : 
	
};

