//------------------------------������˵����-----------------------------
// �������ƣ�GDIdemo7
// 2018��10��Creat by XY
// ��������Ϸ��������֮ ��ʱ��������ʾ ʾ������
//-----------------------------------------------------------------------


//------------------------------��ͷ�ļ��������֡�-----------------------
//����������������������ͷ�ļ�
//-----------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>//ʹ��swprintf_s���������ͷ�ļ�

//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //����PlaySound����������ļ�
#pragma  comment(lib,"Msimg32.lib")  //���ʹ��TransparentBlt��������Ŀ��ļ�

//------------------------------���궨�岿�֡�---------------------------
//����������һЩ������
//-----------------------------------------------------------------------
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"������������Ϩ�����Ϸ�������롿������Ŀ��"	//Ϊ���ڱ��ⶨ��ĺ�

//------------------------------��ȫ�ֱ����������֡�---------------------
//������ȫ�ֱ�������
//-----------------------------------------------------------------------
HDC g_hdc = nullptr,g_mdc = nullptr;	//ȫ���豸���������ȫ���ڴ�DC���
HBITMAP g_hSprite[12];	
DWORD g_tPre = 0, g_tNow= 0;		//����������������¼ʱ��
int g_iNum = 0;		//��¼Ŀǰ��ʾ��ͼ��

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

	//��5����Ϣѭ������
	MSG msg = {0};	//���岢��ʼ��msg
	while(msg.message != WM_QUIT)	//ʹ��whileѭ���������Ϣ����WM_QUIT���ͼ���ѭ��
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))	//�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ
		{
			TranslateMessage(&msg);	//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessageW(&msg);	//�ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			g_tNow = GetTickCount();		//��ȡ��ǰϵͳʱ��
			if(g_tNow-g_tPre >= 100)		//���˴�ѭ���������ϴλ�ͼʱ�����0.1��ʱ�ٽ�Щ�ػ�
				Game_Paint(hwnd);
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
	switch(message)	//switch��俪ʼ
	{

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
	g_hdc = GetDC(hwnd);

	wchar_t filename[20];
	//�����������λͼ
	for(int i = 0; i <12; ++i)
	{
		memset(filename, 0, sizeof(filename));		//filename�ĳ�ʼ��
		swprintf_s(filename, L"%d.bmp",i);			//��װͼƬ����
		g_hSprite[i] = (HBITMAP)LoadImage(nullptr,filename,IMAGE_BITMAP,WINDOW_WIDTH,WINDOW_HEIGHT,LR_LOADFROMFILE);
	}

	//��������DC
	g_mdc = CreateCompatibleDC(g_hdc);		//���������豸�������ڴ�DC

	return TRUE;
}

//---------------------------------��Game_Paint()������------------------------------------
//���������ƺ������ڴ˺����н��л��Ʋ���
//-----------------------------------------------------------------------------------------
VOID Game_Paint(HWND hwnd)
{
	//����ͼ��
	if(g_iNum == 11)
		g_iNum = 0;

	SelectObject(g_mdc,g_hSprite[g_iNum]);		//����ͼ��ѡ���Ӧ��λͼ
	BitBlt(g_hdc,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,g_mdc,0,0,SRCCOPY);

	g_tPre = GetTickCount();		//��¼�˴λ�ͼʱ�䣬���´���Ϸѭ�����ж��Ƿ��Ѿ��ﵽ������²����趨��ʱ������
	g_iNum++;
}

//---------------------------------��Game_CleanUp()������----------------------------------
//��������Դ���������ڴ˺����н����˳�ǰ��Դ��������
//-----------------------------------------------------------------------------------------
BOOL Game_CleanUp(HWND hwnd)
{
	//�ͷ���Դ����
	for (int i =0; i < 12; ++i)
	{
		DeleteObject(g_hSprite[i]);
	}
	DeleteDC(g_mdc);
	ReleaseDC(hwnd,g_hdc);		//�ͷ��豸����

	return TRUE;
}