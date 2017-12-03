
// DdangDdaMuckgiDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "DdangDdaMuckgi.h"
#include "DdangDdaMuckgiDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDdangDdaMuckgiDlg 대화 상자



CDdangDdaMuckgiDlg::CDdangDdaMuckgiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDdangDdaMuckgiDlg::IDD, pParent)
	, x_point1(0)
	, x_point2(0)
	, y_point1(0)
	, y_point2(0)
	, red_score(0)
	, blue_score(0)
	, count(0)
	, team_name(_T("RED"))
	, histo(_T(""))
	, chk(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	int temp = 0;;

	m_view = cvCreateImage(cvSize(700, 700),8,3);

	srand((unsigned int)time(NULL));

	for(int i =0; i<7; i++)
		for(int j =0; j<7; j++)
			map[i][j] = rand()%2;

	for(int i=0; i<700; i++){
		for(int j =0; j<700; j++){

			m_view->imageData[(i*m_view->width+j)*3+2] = (unsigned char)255;
			m_view->imageData[(i*m_view->width+j)*3+1] = (unsigned char)255;
			m_view->imageData[(i*m_view->width+j)*3] = (unsigned char)255;

			if(i%100==0 || j%100==0){
				m_view->imageData[(i*m_view->width+j)*3+2] = (unsigned char)200;
				m_view->imageData[(i*m_view->width+j)*3+1] = (unsigned char)200;
				m_view->imageData[(i*m_view->width+j)*3] = (unsigned char)200;
			}
			else if(i%50==0 && j%50==0)
				if(map[((j-50)/100)][((i-50)/100)] == 1){
					for(int y=-2; y<3; y++)
						for(int x=-2; x<3; x++)
						{
							m_view->imageData[((i+y)*m_view->width+(j+x))*3+2] = (unsigned char)0;
							m_view->imageData[((i+y)*m_view->width+(j+x))*3+1] = (unsigned char)0;
							m_view->imageData[((i+y)*m_view->width+(j+x))*3] = (unsigned char)0;
						}
					temp++;
				}
		}
	}

}

void CDdangDdaMuckgiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEW, m_iView);
	DDX_Text(pDX, IDC_X1, x_point1);
	DDV_MinMaxInt(pDX, x_point1, 1, 7);
	DDX_Text(pDX, IDC_X2, x_point2);
	DDV_MinMaxInt(pDX, x_point2, 1, 7);
	DDX_Text(pDX, IDC_Y1, y_point1);
	DDV_MinMaxInt(pDX, y_point1, 1, 7);
	DDX_Text(pDX, IDC_Y2, y_point2);
	DDV_MinMaxInt(pDX, y_point2, 1, 7);
	DDX_Text(pDX, IDC_RED_SCORE, red_score);
	DDX_Text(pDX, IDC_BLUE_SCORE, blue_score);
	DDX_Text(pDX, IDC_TEAM_NAME, team_name);
	DDX_Text(pDX, IDC_HISTO, histo);
}

BEGIN_MESSAGE_MAP(CDdangDdaMuckgiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_INPUT, &CDdangDdaMuckgiDlg::OnBnClickedInput)
	ON_BN_CLICKED(IDC_RESTART, &CDdangDdaMuckgiDlg::OnBnClickedRestart)
END_MESSAGE_MAP()


// CDdangDdaMuckgiDlg 메시지 처리기

BOOL CDdangDdaMuckgiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	SetTimer(1, (UINT)((1/(double)12)*10),NULL);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDdangDdaMuckgiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDdangDdaMuckgiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_View.CopyOf(m_view);

		m_iView.GetClientRect(&view);
		m_View.DrawToHDC(m_iView.GetDC()->GetSafeHdc(), view);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDdangDdaMuckgiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDdangDdaMuckgiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(1 == nIDEvent){
		
		for(int i=0; i<count; i++){

			if(i%2 == 0)
				cvLine(m_view, cvPoint(line[i][0]*100-50, line[i][1]*100-50), cvPoint(line[i][2]*100-50, line[i][3]*100-50), CV_RGB(255, 0, 0), 5);
			else
				cvLine(m_view, cvPoint(line[i][0]*100-50, line[i][1]*100-50), cvPoint(line[i][2]*100-50, line[i][3]*100-50), CV_RGB(0, 0, 255), 5);

		}

		if(chk == true){
			m_View.CopyOf(m_view);

			m_iView.GetClientRect(&view);
			m_View.DrawToHDC(m_iView.GetDC()->GetSafeHdc(), view);

			chk = false;

		}

	}


	CDialogEx::OnTimer(nIDEvent);
}


void CDdangDdaMuckgiDlg::OnBnClickedInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//그은 선의 각 좌표에 점이 있어야 함. 
	if(map[x_point1-1][y_point1-1] == 1 && map[x_point2-1][y_point2-1] == 1){

		int temp = 0;
		for(int i=0; i<count+1; i++)
		{
			temp =0;

			if(line[i][0] == x_point1) //현재 사용자가 설정한 좌표가 이미 그어져 있는지 확인
				temp++;
			if(line[i][1] == y_point1) //현재 사용자가 설정한 좌표가 이미 그어져 있는지 확인
				temp++;
			if(line[i][2] == x_point2) //현재 사용자가 설정한 좌표가 이미 그어져 있는지 확인
				temp++;
			if(line[i][3] == y_point2) //현재 사용자가 설정한 좌표가 이미 그어져 있는지 확인
				temp++;
		
			if(temp == 4){ //이미 그어진 선이라면 에러를 표시하고, 다시 재입력
				MessageBox(_T("Error.이미 그어진 선입니다.")); 
				break;
			}
		}//for loop closed

		if(temp !=4){ //그어진 선이 아니라면

			bool checkFlag=true;
			//선이 겹치는지 확인
			CMyVector inputV1(x_point1, y_point1);
			CMyVector inputV2(x_point2, y_point2);

			//여리랑 성욱이가 구현한 함수는 map이라는 변수가 필요했기 때문에 map을 매개변수에 넣었스미다.
			if (CMyVector::checkDoublePoint(inputV1, inputV2, map)) {
				//여리 테스트
				MessageBox(_T("Error: 선분에 점이 여러개"));
				checkFlag = false;
			}

			for (int i = 0; i < count + 1; i++) {
				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);
				
 				if (!CMyVector::sementIntersects(inputV1, inputV2, V1, V2)) {//1(true)이면 선을 그릴수 있음
					MessageBox(_T("Error: 교차")); 
					checkFlag = false;
					break;
				}
										
			}//loop for closed

			if (checkFlag == true) {
				line[count][0] = x_point1;
				line[count][1] = y_point1;
				line[count][2] = x_point2;
				line[count++][3] = y_point2; //count에 넣은 다음에 count 인덱스를 하나 증가 시킴.
				MessageBox(_T("선긋기 성공!"));
			}
			
		}
		
		
		
		
		// 
		// i번째 입력된 X1 : line[i][0], Y1 : line[i][1], X2 : line[i][2], Y2 : line[i][3]
		// 현재 입력된 X1 : x_point1, Y1 : y_point1, X2 : x_point2, Y2 : y_point2;
		// map[가로][세로] : 7x7에 대한 매트릭스로 비었을 경우 0, 점일 경우 1
		// count 현재까지 입력된 직선의 수
		// team_name 현재 입력가능한 팀 이름
		// histo 지금까지 입력된 팀에 따른 좌표들
		// red_score red팀 점수
		// blue_score blue팀 점수
		// 

		
		//(상대방의 선이 입력되면),
		//1. (상대방) 점수 계산 (틀리면 실격)
		//2. (수를 읽고) 예측하여 선긋기 
			//성분이 이어지지 않도록 구현 
			//Min, Max를 이용하여 구현
			//먼저 몇수를 보는 것, 넓이 우선 / 깊이 우선은 마음대로
		//3. 본인의 점수 계산

		//규칙
			//1. 선 교차하면 안됨.(예외처리가 안되어 있음)
			//2. 선 사이에 점이 있어도 안됨. (예외처리가 안되어 있음) 
			//3. 있는 선 위에 같은 선 올리면 안됨. (예외처리가 되어 있음)
			
		//계산한 점수는 아래에 설정하면 자동으로 화면에 나타남
		red_score = 2;
		blue_score = 1;

		//화면에 출력
		CString str;
		str.Format(_T("%s : (%d, %d), (%d, %d)\r\n"), team_name, x_point1, y_point1, x_point2, y_point2);
		histo += str;

		//Turn을 정하여 값 설정 가능 (count가 짝수일때 RED 팀, 홀수일때 BLUE팀)
		if(count%2 == 0)
			team_name = _T("RED");
		else
			team_name = _T("BLUE");

		//다음 턴을 위해 0값 설정
		x_point1 = 0;
		y_point1 = 0;
		x_point2 = 0;
		y_point2 = 0;
	
		//인터페이스에 뿌리기. 
		UpdateData(FALSE);	
		chk = true;
	}
	else //점이 없는 지점을 선택한 경우, 에러 출력, 재입력
		MessageBox(_T("Error. 그곳에는 점이 없어요")); 
}



void CDdangDdaMuckgiDlg::OnBnClickedRestart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//처음 시작할때 점을 임의로 생성해주고, 인터페이스 상에 출력
	srand((unsigned int)time(NULL));

	for(int i =0; i<7; i++)
		for(int j =0; j<7; j++)
			map[i][j] = rand()%2;

	for(int i=0; i<700; i++){
		for(int j =0; j<700; j++){

			m_view->imageData[(i*m_view->width+j)*3+2] = (unsigned char)255;
			m_view->imageData[(i*m_view->width+j)*3+1] = (unsigned char)255;
			m_view->imageData[(i*m_view->width+j)*3] = (unsigned char)255;

			if(i%100==0 || j%100==0){
				m_view->imageData[(i*m_view->width+j)*3+2] = (unsigned char)200;
				m_view->imageData[(i*m_view->width+j)*3+1] = (unsigned char)200;
				m_view->imageData[(i*m_view->width+j)*3] = (unsigned char)200;
			}
			else if(i%50==0 && j%50==0)
				if(map[((j-50)/100)][((i-50)/100)] == 1){
					for(int y=-2; y<3; y++)
						for(int x=-2; x<3; x++)
						{
							m_view->imageData[((i+y)*m_view->width+(j+x))*3+2] = (unsigned char)0;
							m_view->imageData[((i+y)*m_view->width+(j+x))*3+1] = (unsigned char)0;
							m_view->imageData[((i+y)*m_view->width+(j+x))*3] = (unsigned char)0;
						}
				}
		}
	}

	//점수 값등 초기화
	red_score = 0;
	blue_score = 0;
	count = 0;
	team_name = _T("RED");
	histo = _T("");
	chk = true;

	UpdateData(FALSE);
}
