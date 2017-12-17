
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

		//선 예외처리
		if(temp !=4){ //그어진 선이 아니라면

			bool checkFlag=true;
			//선이 겹치는지 확인
			CMyVector inputV1(x_point1, y_point1);
			CMyVector inputV2(x_point2, y_point2);

			//예외처리 1 : 선분이 점을 여러개 포함하는 경우
			if (CMyVector::checkDoublePoint(inputV1, inputV2, map)) {
				//여리 테스트
				MessageBox(_T("Error: 선분에 점이 여러개"));
				checkFlag = false;
			}

			//예외처리 : 같은선분임
			for (int i = 0; i < count + 1; i++) {
				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);
				if (inputV1 == V1&&inputV2 == V2 || inputV1 == V2&&inputV2 == V1) {
					MessageBox(_T("위치를 바꾼경우 같은 선분이 있습니다."));
					checkFlag = false;
				}
			}
			//예외처리 2 : 선분이 교차하는 경우
			for (int i = 0; i < count + 1; i++) {
				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);
	
 				if (!CMyVector::checkException(inputV1, inputV2, V1, V2)) {//1(true)이면 선을 그릴수 있음
					MessageBox(_T("Error: 교차")); 
					checkFlag = false;
					break;
				}	

				float den, ua, ub;
				for (int i = 0; i < count + 1; i++) {
					den = (y_point2 - y_point1) * (line[i][2] - line[i][0])
						- (x_point2 - x_point1) * (line[i][3] - line[i][1]);

					if (den != 0) {
						ua = ((x_point2 - x_point1) * (line[i][1] - y_point1)
							- (y_point2 - y_point1) * (line[i][0] - x_point1)) / den;
						ub = ((line[i][2] - line[i][0]) * (line[i][1] - y_point1)
							- (line[i][3] - line[i][1]) * (line[i][0] - x_point1)) / den;

						if (ua > 0 && ua < 1 && ub>0 && ub < 1) {
							checkFlag = false;
							MessageBox(_T("Error."));
							break;
						}
					}
				}
			}//for loop closed

			//선분을 그릴 수 있는 경우 선분을 긋는다.
			if (checkFlag == true) {
				line[count][0] = x_point1;
				line[count][1] = y_point1;
				line[count][2] = x_point2;
				line[count++][3] = y_point2; //count에 넣은 다음에 count 인덱스를 하나 증가 시킴.
				map[x_point1][y_point1] = 3;	//점이 라인이 그을 때 쓰는 경우에는 3을 넣는다.
				map[x_point2][y_point2] = 3;	//점이 라인이 그을 때 쓰는 경우에는 3을 넣는다.
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
		red_score = 0;
		blue_score = 0;

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
<<<<<<< HEAD
void CDdangDdaMuckgiDlg::lineCheck() {
	//점이 15개 남았을 때 선분의 갯수를 세는 함수

	//선분의 갯수는 한 횟수가 지날 때마다 경우의 수가 달라진다.
	//점이 15개일 거니까 배열은 15개까지센다.
	int notYet[15][3];	//그을 점들의 갯수

	int x = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++) {
			if (map[i][j] != 3) {
				notYet[x][0] = i;
				notYet[x][1] = j;
				//아직 선분이 그어지지 않은 좌표의 수를 찾는다.
				x++;
			}
		}
	}

	//예외처리를 이용해서 그을 수 있는 선분을 지운다.
	/*
		재귀함수를 통해서 그을 수 있는 최대, 최소의 갯수를 구한다.
		이 선을 그었을 때 다른 점에서는 몇 개의 선분을 그을 수 있는가를 알아내는 것이다.
		이 때, 최대갯수와 최소갯수 두 개 모두를 구한다.
		자 여리야 잘 생각해보자.

		음 재귀함수 말고 포문으로 해볼까..
		A에서 B를 긋는 경우 남은 C,D,E 점을 가지고 다른 선분과 교차하지 않는 다는 조건에서 두 개를 그을 수 있음.

		1) 이 점의 위치는 ↑위의 포문에서 알게 한다.

		2) 점이 여러 개가 모여있는 게 아니라 분명 흩어져 있을 것. 이때, 경계는 어떻게 알 것인가.
			=>예외처리를 이용해서 교차 하는 모든 경우를 제외한다.(그러니까 가능한 조합을 구해야함.)
				-> 예를 들면 A에서 B는 선분에 걸쳐서 아예 그릴 수 없음. 그러면 A-B 조합은 제외한다.

				-어떻게 조합을 만들어 줄건데? 15개를 만들긴 힘들어.. 터질거야 벡퍼
				-점의 갯수를 주는데 적어도 15개는 아냐. 6개라고 생각하고 일단짜보자.


		3) 점에서 유효한 갯수의 선분을 몇 개 그을 수 있는 지를 알게 한다.
			=>근데 이때, 최대 최소는 어떻게 알게되는거야..?
				-> A에서 B, A에서 C, A에서 D, A에서 E 로 모든 선분을 그어본 뒤 최대, 최소를 구한다.(이때, 모든 조합은 그릴 수 있다는 것을 가정한다, 2번에 안 걸림)

		*여리야 조합은 어떻게 할거야,.. 아 이거는 한번에 돌려야 하지않나? 전체 점의 갯수를 봐야하지 않아?
		5개일때보자.
	*/
	
	bool lineError = false;

	for (int i = 0; i < x; i++) {

		CMyVector inputV1(notYet[i][0], notYet[i][0]);

		for (int j = i + 1; j < x; j++) {

			/*
				선분 하나를 그었을 때 주변의 점에 그을 수 있는 선분의 갯수를 본다.
				x개 만큼(선분을 그을 수 있는 점의 집합) 긋는다. 이때, 봐야할 문제점들
				1. 이미 그어진 선들과는 교차하면 안됨(↑위에서 되어 있음.)
				2. 남아 있는 선분들을 돌리면서 이게 그을 수 있는 선분인지. 혹여 교차되지는 않는지.등을 검사
					->이 경우 min 또는 max의 값은 변화가 x
				3. 한 선분에서 그을 수 있는 점들의 갯수가 여러개를 센다.

			*/

			CMyVector inputV2(notYet[j][0], notYet[j][1]);

			for (int k = 0; k < count + 1; i++) {

				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);

				if (!CMyVector::sementIntersects(inputV1, inputV2, V1, V2)) {//1(true)이면 선을 그릴수 있음
					lineError = true;
					break;
				}

			}//loop for closed
			if (lineError) {	//조건에 걸리는 경우 continue
				//이제 재귀를 돌려야지 여리야.
				/*
					재귀를 돌리는 건 너무 좋은데 인자를 뭘 줄거야
					1. ▲ 위에서 line을 만든 점을 제외하고 이제 만들 수 있는 애들을 찾아야지 (최소)
					2. 아 근데 최소를 어떻게 구해..
					재귀가 무엇을 하게 할거야?
					1) 우리가 가상의 선분을 그었을 때 그 때의 그릴 수 있는 갯수들을 반환시킬거야
					2) 그러면 이 최대랑 최초는 이 함수에서 하는 거야 그렇지? 응
					재귀 인자가 그러면..
					㉠이번에 만들어질 라인의 x,y
					㉡그려질 점들을 가지고 있는 배열
				*/
				for (int k = 0; k < x; k++) {
					
					bool nolineerror = false;

					if ((notYet[k][0] == inputV1.x&&notYet[k][1] == inputV1.y) ||
						(notYet[k][0] == inputV2.x&&notYet[k][1] == inputV2.y)) {
						
						CMyVector inputV3(notYet[k][0], notYet[k][1]);
						if (k + 1 == x)
							break;
						CMyVector inputV4(notYet[k + 1][0], notYet[k + 1][1]);
						
						for (int l = 0; l < count + 1; l++) {

							CMyVector V1(line[i][0], line[i][1]);
							CMyVector V2(line[i][2], line[i][3]);

							if (!CMyVector::sementIntersects(inputV3, inputV4, V1, V2)) {//1(true)이면 선을 그릴수 있음
								if (!CMyVector::sementIntersects(inputV3, inputV4, inputV1, inputV2))
									nolineerror = true;
									break;
							}							
						}//loop for closed
						if (nolineerror) {
							notYet[i][3]++;
						}
					}
				}
			
				//notYet[i][3]에 있는 것은 그을 수 있는 선분의 갯수를 세어 논 것이다. 이를 min, max로 정렬할 것
				//추워

				
			}
		}
	}

	int minLine = 9999, maxLine = 0;
	int minX = 0, minY = 0; 

	maxLine = notYet[0][3];
	for (int k = 0; k < x; k++) {
		if (minLine > notYet[k][3]) {
	
			minLine = notYet[k][3];
			minX = notYet[k][0];
			minY = notYet[k][1];
			
		}
		if (maxLine < notYet[k][3]) {
			maxLine = notYet[k][3];
		}
	}
	
}

int CDdangDdaMuckgiDlg::recursive(int nCount)
{


	return 0;
}
=======

>>>>>>> 2f947fb90071097fc30fe2cbbd5120963e1fe844
