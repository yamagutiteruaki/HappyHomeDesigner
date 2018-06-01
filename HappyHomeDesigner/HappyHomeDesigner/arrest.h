//=============================================================================
//
// �G���� [arrest.h]
// Author : 
//
//=============================================================================
#ifndef _ARREST_H_
#define _ARREST_H_


// �}�N����`
#define	NUM_ARREST				(2)			// �|���S����

#define TEXTURE_GAME_ARREST		("data/TEXTURE/police.png")	// �摜
#define TEXTURE_ARREST_SIZE_X	(150/2*SCREEN_SCALE)		// �e�N�X�`���T�C�Y
#define TEXTURE_ARREST_SIZE_Y	(150/2*SCREEN_SCALE)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_ARREST	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ARREST	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ARREST			(TEXTURE_PATTERN_DIVIDE_X_ARREST*TEXTURE_PATTERN_DIVIDE_Y_ARREST)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ARREST			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define ARREST_MAX						(10) // �������ő吔
#define ARREST_SPEED						(300) //���̃X�s�[�h
//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				cnt_frame;					// �J�E���g
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} ARREST;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitArrest(int type);
void UninitArrest(void);
void UpdateArrest(void);
void DrawArrest(void);
ARREST *GetArrest(int no);


#endif
