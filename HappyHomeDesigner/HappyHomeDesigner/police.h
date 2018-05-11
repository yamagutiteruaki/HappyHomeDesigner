//=============================================================================
//
// �|���X���� [enemy.h]
// Author : GP11B243-18-���_��
//
//=============================================================================
#ifndef _POLICE_H_
#define _POLICE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE_POLICE		(0.50f)							// �ړ����x�W��
#define	RATE_MOVE_POLICE			(0.20f)							// �ړ������W��
#define	VALUE_ROTATE_POLICE		(D3DX_PI * 0.05f)				// ��]���x
#define	RATE_ROTATE_POLICE		(0.20f)							// ��]�����W��

#define	POLICE_AT_LENGTH		(50.0f)

#define	POLICE_MAX				(1)								// �|���X�̍ő吔

#define	POLICE_SIZE_X			(10.0f)							// �|���X�̕�
#define	POLICE_SIZE_Y			(20.0f)							// �|���X�̍���

#define	POLICE_ANIM_MAX			(12)							// �|���X�̃A�j���[�V�����p�^�[����
#define	POLICE_ANIM_SEC			(1)								// �A�j���[�V�����ꏄ�ɂ�����b��

#define	POLICE_SPEED_FREQUENCY	(60*10)							// �|���X�̈ړ����x�̍X�V�p�x(�t���[���~�b��)
#define	POLICE_SPEEDUP			(0.2f)							// �|���X�̈ړ����x�ω���
#define POLICE_SHADOW_SIZE		(53.0f)							// �|���X�̉e�T�C�Y

#define	POLICE_MODEL			"data/MODEL/POLICE/standingman.x"	// �ǂݍ��ރ��f����

#define	CHECK_POINT_X_MAX			(3)								// �������̃`�F�b�N�|�C���g�̍ő吔
#define	CHECK_POINT_Y_MAX			(3)								// �c�����̃`�F�b�N�|�C���g�̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct		// �|���X�\����
{
	bool			use;							// true:�g�p  false:���g�p

	D3DXVECTOR3		scl;							// �X�P�[��

	D3DXVECTOR3		Eye;							// �|���X�̎��_(�ʒu���W)
	D3DXVECTOR3		At;								// �|���X�̒����_(�|���X�����Ă�����W)
	D3DXVECTOR3		Up;								// �|���X�̏����
	D3DXVECTOR3		rot;							// �|���X�̌���
	D3DXVECTOR3		move;							// �|���X�̈ړ���

	VERTEX_2D		vertexWk[NUM_VERTEX];			// ���_���i�[���[�N

	int				anim;							// �A�j���[�V�����ԍ�

	float			speed;							// �ړ����x�W��

} POLICE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);

POLICE *GetPolice(int no);

#endif
