//=============================================================================
//
// �e���� [shadow.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SHADOW_SIZE_X		(50.0f)							// �e�̕�
#define	SHADOW_SIZE_Z		(50.0f)							// �e�̍���

#define SHADOW_POS_Y		(0.2f)							// �V���h�E�̍������Œ�

#define	MAX_SHADOW			(20)							// �e�ő吔

#define SHADOW_ALPHA		(1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	bool bUse;				// �g�p���Ă��邩�ǂ���
	bool bDraw;				// �`��̗L��
} SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitShadow(int nType);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);
LPDIRECT3DVERTEXBUFFER9 DebugShadow(void);
#endif
