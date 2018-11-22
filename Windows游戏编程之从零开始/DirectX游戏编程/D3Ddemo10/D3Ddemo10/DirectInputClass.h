//=============================================================================
// Name: DirectInputClass.h
//	Des: ��װ��DirectInput�������봦�����ͷ�ļ�
// 2018�� 11��  Create by XY
//=============================================================================

#pragma once		//ֻҪ��ͷ�ļ����ʼ����������ע�����ܹ���֤ͷ�ļ�ֻ������һ�Ρ�
#include "D3DUtil.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//DInputClass�ඨ�忪ʼ
class DInputClass
{
private:
	IDirectInput8	*m_pDirectInput;		//IDirectInput8�ӿڶ���
	IDirectInputDevice8		*m_KeyboardDevice;		//�����豸�ӿڶ���
	char			m_keyBuffer[256];		//���ڼ��̼�ֵ�洢������

	IDirectInputDevice8		*m_MouseDevice;	//����豸�ӿڶ���
	DIMOUSESTATE	m_MouseState;			//��������ֵ�洢��һ���ṹ��

public:
	DInputClass(void);						//���캯��
	~DInputClass(void);						//��������
public:
	//��ʼ��DirectInput���̼���������豸
	HRESULT Init(HWND hWnd,HINSTANCE hInstance,DWORD keyboardCoopFlags,DWORD mouseCoopFlags);
	void GetInput();	
	bool IsKeyDown(int iKey);
	bool IsMouseButtonDown(int button);		
	
	float MouseDX();		//
	float MouseDY();		//
	float MouseDZ();		//��������Z������ֵ
};