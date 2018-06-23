//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PLAYER_MAX			(1)			// �|���X�̍ő吔

#define	PLAYER_WID			(10.0f)		// �|���X�̕�
#define	PLAYER_HEI			(20.0f)		// �|���X�̍���

#define HAVE_MAX			(5)			// �Ƌ�����Ă�ő吔
#define WT_MAX				(5)			// �����d�ʐ���

#define PLAYER_SHADOW_SIZE	(23.0f)			// �v���C���[�̉e�T�C�Y

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �v���C���[�\����
{
	bool			use;							// true:�g�p  false:���g�p

	int				hp;								// HP

	D3DXVECTOR3		scl;							// �X�P�[��

	D3DXVECTOR3		Eye;							// �v���C���[�̎��_
	D3DXVECTOR3		At;								// �v���C���[�̒����_
	D3DXVECTOR3		Up;								// �v���C���[�̏����
	D3DXVECTOR3		rot;							// �v���C���[�̌���
	D3DXVECTOR3		rotDest;						// �v���C���[�̖ړI�̌���
	D3DXVECTOR3		move;							// �v���C���[�̈ړ���

	D3DXVECTOR3		posTmp;							// �v���C���[�̎��_�i�ꎞ�ۑ��j


	VERTEX_2D		vertexWk[NUM_VERTEX];			// ���_���i�[���[�N

	int				anim;							// �A�j���[�V�����ԍ�

	float			speed;							// �ړ����x�W��

	int				weight;

	int				havenum[HAVE_MAX];	

	int				nIdxShadow;
	float			fSizeShadow;
	D3DXCOLOR		colShadow;
	bool			bShadow;

} PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int nType);
void UninitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);

PLAYER *GetPlayer(int no);
void SetResetno(int no);


#endif
