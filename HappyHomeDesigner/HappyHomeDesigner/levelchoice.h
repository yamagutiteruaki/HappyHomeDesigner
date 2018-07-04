//=============================================================================
//
// �G���� [voice.h]
// Author : 
//
//=============================================================================
#ifndef _VOICE_H_
#define _VOICE_H_


// �}�N����`
#define	NUM_VOICE				(2)			// �|���S����

#define TEXTURE_GAME_VOICE		("data/TEXTURE/wait.png")	// �摜
#define TEXTURE_VOICE_SIZE_X	(900/2*SCREEN_SCALE)		// �e�N�X�`���T�C�Y
#define TEXTURE_VOICE_SIZE_Y	(550/2*SCREEN_SCALE)		// ����

#define TEXTURE_PATTERN_DIVIDE_X_VOICE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_VOICE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_VOICE			(TEXTURE_PATTERN_DIVIDE_X_VOICE*TEXTURE_PATTERN_DIVIDE_Y_VOICE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_VOICE			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define VOICE_MAX						(1) // ���̍ő吔
#define VOICE_SPEED						(300) //���̃X�s�[�h
//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				cnt_frame;					// �J�E���g
	int				count;						// ��
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x

} VOICE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitVoice(int type);
void UninitVoice(void);
void UpdateVoice(void);
void DrawVoice(void);
VOICE *GetVoice(int no);


#endif
