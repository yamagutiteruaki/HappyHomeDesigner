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
#define	NUM_MINIMAP							(2)										// �|���S����

#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/clock.png")				// �~�j�}�b�v�摜
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/clock.png")				// �v���C���[�摜
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/clock.png")				// �|���X�摜

#define MINIMAP_POS_X						(SCREEN_CENTER_X)
#define MINIMAP_POS_Y						(60)

#define	MINIMAP_WIDTH						(100 / 2*SCREEN_SCALE)					// �^�C�}�[�̕�
#define	MINIMAP_HEIGHT						(100 / 2*SCREEN_SCALE)					// �^�C�}�[�̍���

#define TEXTURE_MINIMAP_FIELD_SIZE_X		(100/2)									// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(100/2)									// ����
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(100/2)									// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(100/2)									// ����
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100/2)									// �e�N�X�`���T�C�Y
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100/2)									// ����

#define MINIMAP_MAX							(1) 

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~�j�}�b�v�\����
{
	bool			use;					// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;					// �|���S���̈ړ���
	D3DXVECTOR3		rot;					// �|���S���̉�]��
	VERTEX_2D		vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

} MINIMAP;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMinimap(int type);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
MINIMAP *GetMinimap(int no);


#endif
