//=============================================================================
//
// �~�j�}�b�v���� [minimap.h]
// Author : GP12A295-19-���_��
//
//=============================================================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �~�j�}�b�v�t�B�[���h
#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/�X�}�z�g.png")	// �~�j�}�b�v�摜
#define MINIMAP_FIELD_POS_X					(SCREEN_CENTER_X)
#define MINIMAP_FIELD_POS_Y					(60)
#define	MINIMAP_FIELD_WIDTH					(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�t�B�[���h�̕�
#define	MINIMAP_FIELD_HEIGHT				(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�t�B�[���h�̍���
#define TEXTURE_MINIMAP_FIELD_SIZE_X		(100/2)							// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(100/2)							// ����
#define MINIMAP_FIELD_MAX					(1)								// �~�j�}�b�v�ő吔

// �~�j�}�b�v�v���C���[
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/�X�}�z�g.png")		// �v���C���[�摜
#define MINIMAP_PLAYER_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_PLAYER_POS_Y				(160)
#define	MINIMAP_PLAYER_WIDTH				(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�v���C���[�̕�
#define	MINIMAP_PLAYER_HEIGHT				(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�v���C���[�̍���
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(100/2)							// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(100/2)							// ����
#define MINIMAP_PLAYER_MAX					(1)								// �~�j�}�b�v�v���C���[�ő吔

// �~�j�}�b�v�|���X
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/�X�}�z�g.png")		// �|���X�摜
#define MINIMAP_POLICE_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_POLICE_POS_Y				(60)
#define	MINIMAP_POLICE_WIDTH				(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�|���X�̕�
#define	MINIMAP_POLICE_HEIGHT				(100 / 2*SCREEN_SCALE)			// �~�j�}�b�v�|���X�̍���
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100/2)							// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100/2)							// ����
#define MINIMAP_POLICE_MAX					(1)								// �~�j�}�b�v�|���X�ő吔

// ���̑�
#define	NUM_MINIMAP							(2)								// �|���S����

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
class MINI_FIELD							// �~�j�}�b�v�t�B�[���h�N���X
{
public:
	bool			use;					// true:�g�p  false:���g�p
	VERTEX_2D		vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
};
class MINI_PLAYER :public MINI_FIELD		// �~�j�}�b�v�v���C���[�N���X
{
public:
	D3DXVECTOR3		pos;					// �ʒu���W
	D3DXVECTOR3		rot;					// ��]
};
class MINI_POLICE :public MINI_FIELD		// �~�j�}�b�v�|���X�N���X
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
