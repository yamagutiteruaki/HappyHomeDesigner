//=============================================================================
//
// �G���� [button.h]
// Author : 
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_



// �}�N����`
#define	NUM_BUTTON				(2)			// �|���S����

#define TEXTURE_GAME_BUTTON_0		("data/TEXTURE/����.png")	// �摜
#define TEXTURE_GAME_BUTTON_1		("data/TEXTURE/�u��.png")	// �摜
#define TEXTURE_GAME_BUTTON_2		("data/TEXTURE/�͂�.png")	// �摜

#define TEXTURE_BUTTON_SIZE_X	(1000/6*SCREEN_SCALE)		// �e�N�X�`���T�C�Y
#define TEXTURE_BUTTON_SIZE_Y	(300/6*SCREEN_SCALE)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_BUTTON	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BUTTON	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BUTTON			(TEXTURE_PATTERN_DIVIDE_X_BUTTON*TEXTURE_PATTERN_DIVIDE_Y_BUTTON)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BUTTON			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BUTTON_MAX						(1) // �������ő吔
#define BUTTON_SPEED						(300) //���̃X�s�[�h
//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				kind;					// ���
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} BUTTON;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitButton(int type);
void UninitButton(void);
void UpdateButton(void);
void DrawButton(void);
BUTTON *GetButton(int no);
bool Button(void);


#endif
