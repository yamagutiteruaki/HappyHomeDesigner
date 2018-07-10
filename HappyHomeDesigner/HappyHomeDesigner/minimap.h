//=============================================================================
//
// �~�j�}�b�v���� [minimap.h]
// Author : GP12A295-19-���_��
//
//=============================================================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �~�j�}�b�v�t���[��
#define TEXTURE_MINIMAP_FRAME				("data/TEXTURE/�X�}�z�g.png")	// �~�j�}�b�v�摜
#define MINIMAP_FRAME_POS_X					(TEXTURE_MINIMAP_FRAME_SIZE_X)
#define MINIMAP_FRAME_POS_Y					(SCREEN_HEIGHT - TEXTURE_MINIMAP_FRAME_SIZE_Y + 50.0f)
#define TEXTURE_MINIMAP_FRAME_SIZE_X		(250 / 2 * SCREEN_SCALE)			// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_FRAME_SIZE_Y		(375 / 2 * SCREEN_SCALE)			// ����
#define MINIMAP_FRAME_MAX					(1)								// �~�j�}�b�v�ő吔

// �~�j�}�b�v�t�B�[���h
#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/�X�}�z�g1.png")// �~�j�}�b�v�摜
#define MINIMAP_FIELD_POS_X					(TEXTURE_MINIMAP_FIELD_SIZE_X)
#define MINIMAP_FIELD_POS_Y					(SCREEN_HEIGHT - TEXTURE_MINIMAP_FIELD_SIZE_Y + 50.0f)
#define TEXTURE_MINIMAP_FIELD_SIZE_X		(250 / 2 * SCREEN_SCALE)			// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(375 / 2 * SCREEN_SCALE)			// ����
#define MINIMAP_FIELD_SCALE					((float)(TEXTURE_MINIMAP_FIELD_SIZE_X - 20)/(FIELD_SIZE_X / 2))		// �~�j�}�b�v�̏k��
#define MINIMAP_FIELD_MAX					(1)								// �~�j�}�b�v�ő吔

// �~�j�}�b�v�v���C���[
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/�v���C���~�j�}�b�v.png")		// �v���C���[�摜
#define MINIMAP_PLAYER_POS_X				(TEXTURE_MINIMAP_PLAYER_SIZE_X)
#define MINIMAP_PLAYER_POS_Y				(SCREEN_HEIGHT - TEXTURE_MINIMAP_PLAYER_SIZE_Y)
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(15 / 2*SCREEN_SCALE)			// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(15 / 2*SCREEN_SCALE)			// ����
#define MINIMAP_PLAYER_MAX					(1)								// �~�j�}�b�v�v���C���[�ő吔
#define MINIMAP_PLAYER_RANGE				(15.0f)							// �~�j�}�b�v�v���C���[�̈ʒu����(�X�}�z�̘g����͂ݏo�Ȃ��悤��)

// �~�j�}�b�v�|���X
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/�X�}�z�g.png")	// �|���X�摜
#define MINIMAP_POLICE_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_POLICE_POS_Y				(60)
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100 / 2*SCREEN_SCALE)			// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100 / 2*SCREEN_SCALE)			// ����
#define MINIMAP_POLICE_MAX					(1)								// �~�j�}�b�v�|���X�ő吔

// ���̑�
#define	NUM_MINIMAP							(2)								// �|���S����

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
class MINI_FRAME							// �~�j�}�b�v�t�B�[���h�N���X
{
public:
	bool			use;					// true:�g�p  false:���g�p
};
class MINI_FIELD :public MINI_FRAME			// �~�j�}�b�v�t�B�[���h�N���X
{
};
class MINI_PLAYER :public MINI_FRAME		// �~�j�}�b�v�v���C���[�N���X
{
public:
	D3DXVECTOR3		pos;					// �ʒu���W
	D3DXVECTOR3		rot;					// ��]
};
class MINI_POLICE :public MINI_FRAME		// �~�j�}�b�v�|���X�N���X
{
public:
	D3DXVECTOR3		pos;					// �ʒu���W
	D3DXVECTOR3		rot;					// ��]
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMinimap(int type);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
MINI_FIELD *GetMiniField(int no);

#endif
