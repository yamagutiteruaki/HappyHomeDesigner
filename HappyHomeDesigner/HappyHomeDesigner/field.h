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

#define	TEXTURE_FIELD	"data/TEXTURE/field_stone.jpg"								// �ǂݍ��ރe�N�X�`���t�@�C����



#define	FIELD_SIZE_X			(1000.0f)										// �n�ʂ̃T�C�Y(X����)
#define	FIELD_SIZE_Z			(1000.0f)										// �n�ʂ̃T�C�Y(Z����)

#define HOME_SIZE_X		(100.0f)										//�Ƃ̏��̃T�C�Y(X����)
#define HOME_SIZE_Z		(100.0f)										//�Ƃ̏��̃T�C�Y(Y����)

#define	DOOR_SIZE_X			(1000.0f)										// �h�A�̃T�C�Y(X����)
#define	DOOR_SIZE_Z			(1000.0f)										// �h�A�̃T�C�Y(Z����)

#define FIELD_MAX				(1)
#define HOME_MAX				(4)

#define HOME_DISTANCE  (FIELD_SIZE_X/4-FIELD_SIZE_X/50)
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
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
}HOME;

typedef struct // �h�A�̍\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
}DOOR;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

FIELD *GetField(int no);
HOME  *GetHome(int no);
DOOR *GetDoor(int no);

#endif