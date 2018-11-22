//------------------------------������˵����-----------------------------
// �������ƣ�GDIGameCore1
// 2018��10��Creat by XY
// ������GDI�������λ�ͼʾ������
//-----------------------------------------------------------------------


//------------------------------��ͷ�ļ��������֡�-----------------------
//����������������������ͷ�ļ�
//-----------------------------------------------------------------------
#include <windows.h>
#include <time.h>
#pragma comment(lib,"winmm.lib")		//����ʹ��PlaySound���������winmm.lib���ļ�

//------------------------------���궨�岿�֡�---------------------------
//����������һЩ������
//-----------------------------------------------------------------------
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"������������Ϩ�����Ϸ�������롿������Ŀ��"	//Ϊ���ڱ��ⶨ��ĺ�

//------------------------------��ȫ�ֱ����������֡�---------------------
//������ȫ�ֱ�������
//-----------------------------------------------------------------------
HDC g_hdc = nullptr;	//ȫ���豸�������
HPEN g_hpen[7] = {0};	//���廭�ʾ��������
HBRUSH g_hBrush[7] = {0};	//���廭ˢ���������
int g_iPenStyle[7] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME};	//���廭����ʽ���鲢��ʼ��
int g_iBrushStyle[6] = {HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_BDIAGONAL};	//���廭ˢ��ʽ���鲢��ʼ��

//------------------------------��ȫ�ֺ����������֡�---------------------
//������ȫ�ֺ�����������ֹ��δ�����ı�ʶ��ϵ�д���
//-----------------------------------------------------------------------
LRESULT CALLBACK  WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);	//���ڹ��̺���
BOOL Game_Init(HWND hwnd);		//�ڴ˺����н�����Դ�ĳ�ʼ��
VOID Game_Paint(HWND hwnd);		//�ڴ˺����н��л�ͼ�������д
BOOL Game_CleanUp(HWND hwnd);	//�ڴ˺����н�����Դ������

//------------------------------��WinMain����������-----------------------
//������WindowsӦ�ó������ں��������ǵĳ�������￪ʼ
//------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	//��1�����ڴ����Ĳ���֮һ����ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };	//��WINDCLASSEX����һ��������
	wndClass.cbSize = sizeof(WNDCLASSEX);	//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;		//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;		//������ĸ����ڴ棬ȡ0�Ϳ�����
	wndClass.cbWndExtra = 0;		//���ڵĸ����ڴ棬��Ȼȡ0�Ϳ�����
	wndClass.hInstance = hInstance;	//ָ���������ڹ��̵ĳ����ʵ�����
	wndClass.hIcon = (HICON)::LoadImage(NULL,L"icon.ico",IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);	//���ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//ָ��������Ĺ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); 	//ΪhbrBackground��Աָ��һ����ɫ��ˢ���
	wndClass.lpszMenuName = NULL;	//��һ���Կ���ֹ���ַ�����ָ���˵���Դ������
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";	//��һ���Կ���ֹ���ַ�����ָ������������֡�

	//��2�����ڴ����Ĳ���֮����ע�ᴰ����
	if( !RegisterClassEx(&wndClass))
		return -1;

	//��3�����ڴ����Ĳ���֮������ʽ��������
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop",WINDOW_TITLE,	//�������ں���CreateWindow
		WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,WINDOW_WIDTH,
		WINDOW_HEIGHT,NULL,NULL,hInstance,NULL);

	//��4�����ڴ����Ĳ���֮�ģ����ڵ��ƶ�����ʾ�����
	MoveWindow(hwnd,250,80,WINDOW_WIDTH,WINDOW_HEIGHT,true);	//����������ʾʱ��λ�ã�ʹ�������Ͻ�λ��(250,80)��
	ShowWindow(hwnd,nShowCmd);	//����ShowWindow��������ʾ����
	UpdateWindow(hwnd);	//�Դ��ڽ��и��£������������˷���Ҫװ��һ��

	//��Ϸ��Դ�ĳ�ʼ��������ʼ��ʧ�ܣ�����һ����Ϣ�򣬲�����FALSE
	if(!Game_Init(hwnd))
	{
		MessageBox(hwnd,L"��Դ��ʼ��ʧ��",L"��Ϣ����",0);		//ʹ��MessageBox����������һ����Ϣ����
		return FALSE;
	}

//	PlaySound(L"AIR - ��Ӱ.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP); //ѭ�����ű�������

	//��5����Ϣѭ������
	MSG msg = {0};	//���岢��ʼ��msg
	while(msg.message != WM_QUIT)	//ʹ��whileѭ���������Ϣ����WM_QUIT���ͼ���ѭ��
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))	//�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ
		{
			TranslateMessage(&msg);	//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);	//�ַ�һ����Ϣ�����ڳ���
		}
	}

	//��6���������ע��
	UnregisterClass(L"ForTheDreamOfGameDevelop",wndClass.hInstance);	//����׼��������ע��������
	return 0;
}

//---------------------------------��WndProc()������-------------------------------------
//���������ڹ��̺���WndProc���Դ�����Ϣ���д���
//---------------------------------------------------------------------------------------
LRESULT CALLBACK  WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	PAINTSTRUCT paintStruct;		//����һ��PAINTSTRUCT�ṹ������¼һЩ������Ϣ

	switch(message)	//switch��俪ʼ
	{
	case WM_PAINT:	//���ǿͻ����ػ���Ϣ
		g_hdc = BeginPaint(hwnd, &paintStruct);		//ָ�����ڽ��л�ͼ������׼�������ý��ͻ�ͼ�йص���Ϣ��䵽paintStruct�ṹ���С�
		Game_Paint(hwnd);
		EndPaint(hwnd, &paintStruct);		//EndPaint�������ָ�����ڵĻ滭���̽���

		ValidateRect(hwnd,NULL);	//���¿ͻ�������ʾ
		break;	
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)	//������µļ���ESC
			DestroyWindow(hwnd);	//���ٴ��ڣ�������һ��WM_DESTROY��Ϣ
		break;

	case WM_DESTROY:		//���Ǵ���������Ϣ
		Game_CleanUp(hwnd);		//�����Զ������Դ������Game_CleanUp()�����˳�ǰ����Դ����

		PostQuitMessage(0);	//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;		//������switch���

	default:	//������case������������
		return DefWindowProcW(hwnd,message,wParam,lparam);	//����Ĭ�ϵĴ��ڹ���
	}

	return 0;
}

//---------------------------------��Game_Init()������-------------------------------------
//��������ʼ������������һЩ�򵥵ĳ�ʼ��
//-----------------------------------------------------------------------------------------
BOOL Game_Init(HWND hwnd)
{
	g_hdc = GetDC(hwnd);		//��ȡ�豸�������
	srand((unsigned)time(NULL));	//��ʼ��ʱ������

	//�����ʼ�����ʺͻ�ˢ����ɫֵ
	for(int i = 0;i <= 6; ++i)
	{
		g_hpen[i] = CreatePen(g_iPenStyle[i],1,RGB(rand()%256,rand()%256,rand()%256));

		if(i==6)
			g_hBrush[i] = CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
		else
			g_hBrush[i] = CreateHatchBrush(g_iBrushStyle[i],RGB(rand()%256,rand()%256,rand()%256));
	}
	Game_Paint(hwnd);
	ReleaseDC(hwnd,g_hdc);
	return TRUE;
}

//---------------------------------��Game_Paint()������------------------------------------
//���������ƺ������ڴ˺����н��л��Ʋ���
//-----------------------------------------------------------------------------------------
VOID Game_Paint(HWND hwnd)
{
	//����һ��y����ֵ
	int y=0;

	//һ��forѭ������7�ֲ�ͬ�Ļ��ʻ�������
	for(int i=0; i<=6 ;++i)
	{
		y = (i+1)*70;

		SelectObject(g_hdc,g_hpen[i]);	//����Ӧ�Ļ���ѡ��
		MoveToEx(g_hdc,30,y,nullptr);	//����ꡱ�ƶ�����Ӧ��(30,y)���괦
		LineTo(g_hdc,100,y);			//��(30,y)���괦��(100,y)�����߶�
	}

	//ע�����滭���y=420
	//��������x����ֵ
	int x1 = 120;
	int x2 = 190;

	//��7�в�ͬ�Ļ�ˢ������
	for(int i=0;i<=6;++i)
	{
		SelectObject(g_hdc,g_hBrush[i]);	//ѡ�û�ˢ
		Rectangle(g_hdc,x1,70,x2,y);	
		x1+=90;
		x2+=90;
	}
}

//---------------------------------��Game_CleanUp()������----------------------------------
//��������Դ���������ڴ˺����н����˳�ǰ��Դ��������
//-----------------------------------------------------------------------------------------
BOOL Game_CleanUp(HWND hwnd)
{
	for (int i = 0; i <= 6; ++i)
	{
		DeleteObject(g_hpen[i]);
		DeleteObject(g_hBrush[i]);
	}
	return TRUE;
}