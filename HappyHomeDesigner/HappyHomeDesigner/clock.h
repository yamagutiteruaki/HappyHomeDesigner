//=============================================================================
//
// �^�C�}�[���� [clock.h]
// Author : GP12B295 �K �֌��V��
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_CLOCK				(2)			// �|���S����

#define TEXTURE_GAME_CLOCK			("data/TEXTURE/clock.png")				// �^�C�}�[�摜
#define TEXTURE_GAME_CLOCKHAND		("data/TEXTURE/clockhand01.png")		// �j�摜

#define CLOCK_POS_X				(SCREEN_CENTER_X)
#define CLOCK_POS_Y				(60)

#define	CLOCK_WIDTH		(100 / 2*SCREEN_SCALE)				// �^�C�}�[�̕�
#define	CLOCK_HEIGHT	(100 / 2*SCREEN_SCALE)				// �^�C�}�[�̍���

#define TEXTURE_CLOCK_SIZE_X		(100/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_CLOCK_SIZE_Y		(100/2)		// ����
#define TEXTURE_CLOCKHAND_SIZE_X	(100/2)		// ����
#define TEXTURE_CLOCKHAND_SIZE_Y	(100/2)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_CLOCKHAND	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOCKHAND	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_CLOCKHAND			(TEXTURE_PATTERN_DIVIDE_X_CLOCK*TEXTURE_PATTERN_DIVIDE_Y_CLOCK)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_CLOCKHAND			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define CLOCK_MAX						(1) 

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �j�\����
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
//CLOCK *StopClock(void);


#endif
