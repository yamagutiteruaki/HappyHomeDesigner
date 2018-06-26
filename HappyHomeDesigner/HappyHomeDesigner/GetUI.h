//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : 
//
//=============================================================================
#ifndef _GETUI_H_
#define _GETUI_H_

#include "main.h"


#define	TEXTURE_BILLBOARD		"data/TEXTURE/itemget.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BILLBOARD_SIZE_X		(30.0f)							// �r���{�[�h�̕�
#define	BILLBOARD_SIZE_Y		(20.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGetUI(int nType);
void UninitGetUI(void);
void UpdateGetUI(void);
void DrawGetUI(void);
void SetGetUI(D3DXVECTOR3 pos);

#endif
