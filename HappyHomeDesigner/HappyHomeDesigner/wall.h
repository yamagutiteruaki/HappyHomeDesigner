//=============================================================================
//
// �n�ʏ��� [wall.h]
// Author : ����T��
	//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_WALL	"data/TEXTURE/wall005_a.jpg"								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_WALL1	"data/TEXTURE/Floor_wall.jpg"								// �ǂݍ��ރe�N�X�`���t�@�C����

#define	WALL_SIZE_X			(FIELD_SIZE_X)										// �n�ʂ̃T�C�Y(X����)
#define	WALL_SIZE_Z			(200.0f)										// �n�ʂ̃T�C�Y(Z����)

#define WALL_MAX				(4)
#define WALL_KIND				(2)

//=============================================================================
// �\���̐錾
//=============================================================================

typedef struct // �t�B�[���h�\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		Pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3		Rot;						// �|���S���\���ʒu�̉�]���W
	D3DXVECTOR3		Size;

}WALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitWall(int nType);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

WALL *GetWall(int no);
#endif