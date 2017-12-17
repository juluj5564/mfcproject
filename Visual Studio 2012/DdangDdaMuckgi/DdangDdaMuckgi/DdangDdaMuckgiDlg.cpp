
// DdangDdaMuckgiDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DdangDdaMuckgi.h"
#include "DdangDdaMuckgiDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CDdangDdaMuckgiDlg ��ȭ ����



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


// CDdangDdaMuckgiDlg �޽��� ó����

BOOL CDdangDdaMuckgiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDdangDdaMuckgiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDdangDdaMuckgiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDdangDdaMuckgiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	//���� ���� �� ��ǥ�� ���� �־�� ��. 
	if(map[x_point1-1][y_point1-1] == 1 && map[x_point2-1][y_point2-1] == 1){

		int temp = 0;
		for(int i=0; i<count+1; i++)
		{
			temp =0;

			if(line[i][0] == x_point1) //���� ����ڰ� ������ ��ǥ�� �̹� �׾��� �ִ��� Ȯ��
				temp++;
			if(line[i][1] == y_point1) //���� ����ڰ� ������ ��ǥ�� �̹� �׾��� �ִ��� Ȯ��
				temp++;
			if(line[i][2] == x_point2) //���� ����ڰ� ������ ��ǥ�� �̹� �׾��� �ִ��� Ȯ��
				temp++;
			if(line[i][3] == y_point2) //���� ����ڰ� ������ ��ǥ�� �̹� �׾��� �ִ��� Ȯ��
				temp++;
		
			if(temp == 4){ //�̹� �׾��� ���̶�� ������ ǥ���ϰ�, �ٽ� ���Է�
				MessageBox(_T("Error.�̹� �׾��� ���Դϴ�.")); 
				break;
			}
		}//for loop closed

		//�� ����ó��
		if(temp !=4){ //�׾��� ���� �ƴ϶��

			bool checkFlag=true;
			//���� ��ġ���� Ȯ��
			CMyVector inputV1(x_point1, y_point1);
			CMyVector inputV2(x_point2, y_point2);

			//����ó�� 1 : ������ ���� ������ �����ϴ� ���
			if (CMyVector::checkDoublePoint(inputV1, inputV2, map)) {
				//���� �׽�Ʈ
				MessageBox(_T("Error: ���п� ���� ������"));
				checkFlag = false;
			}

			//����ó�� : ����������
			for (int i = 0; i < count + 1; i++) {
				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);
				if (inputV1 == V1&&inputV2 == V2 || inputV1 == V2&&inputV2 == V1) {
					MessageBox(_T("��ġ�� �ٲ۰�� ���� ������ �ֽ��ϴ�."));
					checkFlag = false;
				}
			}
			//����ó�� 2 : ������ �����ϴ� ���
			for (int i = 0; i < count + 1; i++) {
				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);
	
 				if (!CMyVector::checkException(inputV1, inputV2, V1, V2)) {//1(true)�̸� ���� �׸��� ����
					MessageBox(_T("Error: ����")); 
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

			//������ �׸� �� �ִ� ��� ������ �ߴ´�.
			if (checkFlag == true) {
				line[count][0] = x_point1;
				line[count][1] = y_point1;
				line[count][2] = x_point2;
				line[count++][3] = y_point2; //count�� ���� ������ count �ε����� �ϳ� ���� ��Ŵ.
				map[x_point1][y_point1] = 3;	//���� ������ ���� �� ���� ��쿡�� 3�� �ִ´�.
				map[x_point2][y_point2] = 3;	//���� ������ ���� �� ���� ��쿡�� 3�� �ִ´�.
				MessageBox(_T("���߱� ����!"));
			}
			
		}
		
		
		
		
		// 
		// i��° �Էµ� X1 : line[i][0], Y1 : line[i][1], X2 : line[i][2], Y2 : line[i][3]
		// ���� �Էµ� X1 : x_point1, Y1 : y_point1, X2 : x_point2, Y2 : y_point2;
		// map[����][����] : 7x7�� ���� ��Ʈ������ ����� ��� 0, ���� ��� 1
		// count ������� �Էµ� ������ ��
		// team_name ���� �Է°����� �� �̸�
		// histo ���ݱ��� �Էµ� ���� ���� ��ǥ��
		// red_score red�� ����
		// blue_score blue�� ����
		// 

		
		//(������ ���� �ԷµǸ�),
		//1. (����) ���� ��� (Ʋ���� �ǰ�)
		//2. (���� �а�) �����Ͽ� ���߱� 
			//������ �̾����� �ʵ��� ���� 
			//Min, Max�� �̿��Ͽ� ����
			//���� ����� ���� ��, ���� �켱 / ���� �켱�� �������
		//3. ������ ���� ���

		//��Ģ
			//1. �� �����ϸ� �ȵ�.(����ó���� �ȵǾ� ����)
			//2. �� ���̿� ���� �־ �ȵ�. (����ó���� �ȵǾ� ����) 
			//3. �ִ� �� ���� ���� �� �ø��� �ȵ�. (����ó���� �Ǿ� ����)
			
		//����� ������ �Ʒ��� �����ϸ� �ڵ����� ȭ�鿡 ��Ÿ��
		red_score = 0;
		blue_score = 0;

		//ȭ�鿡 ���
		CString str;
		str.Format(_T("%s : (%d, %d), (%d, %d)\r\n"), team_name, x_point1, y_point1, x_point2, y_point2);
		histo += str;

		//Turn�� ���Ͽ� �� ���� ���� (count�� ¦���϶� RED ��, Ȧ���϶� BLUE��)
		if(count%2 == 0)
			team_name = _T("RED");
		else
			team_name = _T("BLUE");

		//���� ���� ���� 0�� ����
		x_point1 = 0;
		y_point1 = 0;
		x_point2 = 0;
		y_point2 = 0;
	
		//�������̽��� �Ѹ���. 
		UpdateData(FALSE);	
		chk = true;
	}
	else //���� ���� ������ ������ ���, ���� ���, ���Է�
		MessageBox(_T("Error. �װ����� ���� �����")); 
}



void CDdangDdaMuckgiDlg::OnBnClickedRestart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//ó�� �����Ҷ� ���� ���Ƿ� �������ְ�, �������̽� �� ���
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

	//���� ���� �ʱ�ȭ
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
	//���� 15�� ������ �� ������ ������ ���� �Լ�

	//������ ������ �� Ƚ���� ���� ������ ����� ���� �޶�����.
	//���� 15���� �Ŵϱ� �迭�� 15����������.
	int notYet[15][3];	//���� ������ ����

	int x = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++) {
			if (map[i][j] != 3) {
				notYet[x][0] = i;
				notYet[x][1] = j;
				//���� ������ �׾����� ���� ��ǥ�� ���� ã�´�.
				x++;
			}
		}
	}

	//����ó���� �̿��ؼ� ���� �� �ִ� ������ �����.
	/*
		����Լ��� ���ؼ� ���� �� �ִ� �ִ�, �ּ��� ������ ���Ѵ�.
		�� ���� �׾��� �� �ٸ� �������� �� ���� ������ ���� �� �ִ°��� �˾Ƴ��� ���̴�.
		�� ��, �ִ밹���� �ּҰ��� �� �� ��θ� ���Ѵ�.
		�� ������ �� �����غ���.

		�� ����Լ� ���� �������� �غ���..
		A���� B�� �ߴ� ��� ���� C,D,E ���� ������ �ٸ� ���а� �������� �ʴ� �ٴ� ���ǿ��� �� ���� ���� �� ����.

		1) �� ���� ��ġ�� ������ �������� �˰� �Ѵ�.

		2) ���� ���� ���� ���ִ� �� �ƴ϶� �и� ����� ���� ��. �̶�, ���� ��� �� ���ΰ�.
			=>����ó���� �̿��ؼ� ���� �ϴ� ��� ��츦 �����Ѵ�.(�׷��ϱ� ������ ������ ���ؾ���.)
				-> ���� ��� A���� B�� ���п� ���ļ� �ƿ� �׸� �� ����. �׷��� A-B ������ �����Ѵ�.

				-��� ������ ����� �ٰǵ�? 15���� ����� �����.. �����ž� ����
				-���� ������ �ִµ� ��� 15���� �Ƴ�. 6����� �����ϰ� �ϴ�¥����.


		3) ������ ��ȿ�� ������ ������ �� �� ���� �� �ִ� ���� �˰� �Ѵ�.
			=>�ٵ� �̶�, �ִ� �ּҴ� ��� �˰ԵǴ°ž�..?
				-> A���� B, A���� C, A���� D, A���� E �� ��� ������ �׾ �� �ִ�, �ּҸ� ���Ѵ�.(�̶�, ��� ������ �׸� �� �ִٴ� ���� �����Ѵ�, 2���� �� �ɸ�)

		*������ ������ ��� �Ұž�,.. �� �̰Ŵ� �ѹ��� ������ �����ʳ�? ��ü ���� ������ �������� �ʾ�?
		5���϶�����.
	*/
	
	bool lineError = false;

	for (int i = 0; i < x; i++) {

		CMyVector inputV1(notYet[i][0], notYet[i][0]);

		for (int j = i + 1; j < x; j++) {

			/*
				���� �ϳ��� �׾��� �� �ֺ��� ���� ���� �� �ִ� ������ ������ ����.
				x�� ��ŭ(������ ���� �� �ִ� ���� ����) �ߴ´�. �̶�, ������ ��������
				1. �̹� �׾��� ������� �����ϸ� �ȵ�(�������� �Ǿ� ����.)
				2. ���� �ִ� ���е��� �����鼭 �̰� ���� �� �ִ� ��������. Ȥ�� ���������� �ʴ���.���� �˻�
					->�� ��� min �Ǵ� max�� ���� ��ȭ�� x
				3. �� ���п��� ���� �� �ִ� ������ ������ �������� ����.

			*/

			CMyVector inputV2(notYet[j][0], notYet[j][1]);

			for (int k = 0; k < count + 1; i++) {

				CMyVector V1(line[i][0], line[i][1]);
				CMyVector V2(line[i][2], line[i][3]);

				if (!CMyVector::sementIntersects(inputV1, inputV2, V1, V2)) {//1(true)�̸� ���� �׸��� ����
					lineError = true;
					break;
				}

			}//loop for closed
			if (lineError) {	//���ǿ� �ɸ��� ��� continue
				//���� ��͸� �������� ������.
				/*
					��͸� ������ �� �ʹ� ������ ���ڸ� �� �ٰž�
					1. �� ������ line�� ���� ���� �����ϰ� ���� ���� �� �ִ� �ֵ��� ã�ƾ��� (�ּ�)
					2. �� �ٵ� �ּҸ� ��� ����..
					��Ͱ� ������ �ϰ� �Ұž�?
					1) �츮�� ������ ������ �׾��� �� �� ���� �׸� �� �ִ� �������� ��ȯ��ų�ž�
					2) �׷��� �� �ִ�� ���ʴ� �� �Լ����� �ϴ� �ž� �׷���? ��
					��� ���ڰ� �׷���..
					���̹��� ������� ������ x,y
					���׷��� ������ ������ �ִ� �迭
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

							if (!CMyVector::sementIntersects(inputV3, inputV4, V1, V2)) {//1(true)�̸� ���� �׸��� ����
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
			
				//notYet[i][3]�� �ִ� ���� ���� �� �ִ� ������ ������ ���� �� ���̴�. �̸� min, max�� ������ ��
				//�߿�

				
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
