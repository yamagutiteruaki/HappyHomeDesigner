//=============================================================================
//
// �^�C�}�[���� [clock.h]
// Author : 
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_


// �}�N����`
#define	NUM_CLOCK				(2)			// �|���S����

#define TEXTURE_GAME_CLOCK		("data/TEXTURE/bullet_R1.png")	// �摜
#define TEXTURE_CLOCK_SIZE_X	(50/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_CLOCK_SIZE_Y	(50/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_CLOCK	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOCK	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_CLOCK			(TEXTURE_PATTERN_DIVIDE_X_CLOCK*TEXTURE_PATTERN_DIVIDE_Y_CLOCK)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_CLOCK			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define CLOCK_MAX						(1) // �G�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} CLOCK;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitClock(int type);
void UninitClock(void);
void UpdateClock(void);
void DrawClock(void);
CLOCK *GetClock(int no);


#endif
