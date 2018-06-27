//=============================================================================
//
// �v���C���[���� [run.h]
// Author : 
//
//=============================================================================
#ifndef _RUN_H_
#define _RUN_H_
#include <time.h>
#include "main.h"


// �}�N����`
#define	NUM_RUN		(2)					// �|���S����

#define TEXTURE_GAME_RUN	("data/TEXTURE/runningman002.png")	// �摜
#define TEXTURE_RUN_SIZE_X	(900) // �e�N�X�`���T�C�Y
#define TEXTURE_RUN_SIZE_Y	(900) // ����

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(2)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define RUN_MAX					(1) // �v���C���[�̍ő吔


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} RUN;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRun(int type);
void UninitRun(void);
void UpdateRun(void);
void DrawRun(void);
RUN *GetRun(int no);


#endif
