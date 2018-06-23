//=============================================================================
//
// �n�ʏ��� [field.h]
// Author : ����T��
//
//=============================================================================
#ifndef _HOME_H_
#define _HOME_H_

#include "main.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define HOME_MAX				(4)

#define HOME_DISTANCE  (FIELD_SIZE_X/4-FIELD_SIZE_X/50-10)
//#define HOME_DISTANCE  (1000)
//=============================================================================
// �\���̐錾
//=============================================================================

typedef struct // �z�[���\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;

	float			len;						// ����
	float			wid;						// �L��

}HOME;

typedef struct // �h�A�̍\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
	int				Homeno;
	bool			Use;
}DOOR;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHome(int nType);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);

HOME  *GetHome(int no);
DOOR *GetDoor(int no);

#endif