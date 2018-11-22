//=============================================================================
// Desc: D3DUtil.hͷ�ļ������ڹ���������Ķ���
// 2018�� 11��  Create by XY
//=============================================================================

#pragma once	//ֻҪ��ͷ�ļ����ʼ����������ע�����ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

#ifndef HR		//�Ȳ���x�Ƿ񱻺궨���,���xû�б��궨���������x��������
#define HR(x) hr = x; {if(FAILED(hr)) {return hr;}}	//�Զ���һ��HR�꣬����ִ�д���ķ���
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p) {delete(p);	(p)=NULL; }}	//�Զ���һ��SAFE_RELEASE()��,����ָ����Դ���ͷ�
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p)=NULL;}}	//�Զ���һ��SAFE_RELEASE()��,����COM��Դ���ͷ�
#endif

