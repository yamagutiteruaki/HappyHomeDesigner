#pragma once
//=============================================================================
//
// �n�ʏ��� [field.h]
// Author : ����T��
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/field_glass.jpg"								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_HOME	"data/TEXTURE/field001.jpg"							// �ǂݍ��ރe�N�X�`���t�@�C����

#define	FIELD_SIZE_X			(600.0f)										// �n�ʂ̃T�C�Y(X����)
#define	FIELD_SIZE_Z			(600.0f)										// �n�ʂ̃T�C�Y(Z����)

#define HOME_SIZE_X		(100.0f)										//�Ƃ̏��̃T�C�Y(X����)
#define HOME_SIZE_Z		(100.0f)										//�Ƃ̏��̃T�C�Y(Y����)

#define FIELD_MAX				(1)
#define HOME_MAX				(4)

//=============================================================================
// �\���̐錾
//=============================================================================

typedef struct // �t�B�[���h�\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W

}FIELD;

typedef struct // �t�B�[���h�\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W

}HOME;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

FIELD *GetField(int no);
HOME  *GetHome(int no);
#endif