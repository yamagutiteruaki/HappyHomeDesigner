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
// �v���C���[�{�̊֌W
#define	PLAYER_MAX					(1)										// �v���C���[�̍ő吔
#define	PLAYER_WID					(10.0f)									// �v���C���[�̕�
#define	PLAYER_HEI					(20.0f)									// �v���C���[�̍���
#define HAVE_MAX					(5)										// �Ƌ�����Ă�ő吔
#define WT_MAX						(5)										// �����d�ʐ���
#define PLAYER_SHADOW_SIZE			(23.0f)									// �v���C���[�̉e�T�C�Y
#define	PLAYER_MODEL				"data/MODEL/PLAYER/standingman.x"		// �ǂݍ��ރ��f����
#define	PLAYER_SCALE_X				(1.0f * 1.2)							// �X�P�[����X����
#define	PLAYER_SCALE_Y				(1.0f * 1.2)							// �X�P�[����Y����
#define	PLAYER_SCALE_Z				(1.0f * 1.2)							// �X�P�[����Z����
// �|���X�E�A�[���֌W
#define	PLAYER_R_ARM_MAX			(PLAYER_MAX)							// �|���X�̘r�̍ő吔(���r�̍��v��)
#define	PLAYER_R_ARM_ANIM_FRAME		(1 * 60 / 4)							// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	PLAYER_R_ARM_ANGLE			(D3DX_PI / 4 / 2)						// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	PLAYER_R_ARM_ROTBASIS_X		(0.0f)									// ��]��_��X���W
#define	PLAYER_R_ARM_ROTBASIS_Y		(30.0f)									// ��]��_��Y���W
#define	PLAYER_R_ARM_ROTBASIS_Z		(0.0f)									// ��]��_��Z���W
#define	PLAYER_R_ARM_MODEL			"data/MODEL/PLAYER/player_R_hand.x"		// �ǂݍ��ރ��f��
// �|���X���A�[���֌W
#define	PLAYER_L_ARM_MAX			(PLAYER_MAX)							// �|���X�̘r�̍ő吔(���r�̍��v��)
#define	PLAYER_L_ARM_ANIM_FRAME		(1 * 60 / 4)							// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	PLAYER_L_ARM_ANGLE			(D3DX_PI / 4 / 2)						// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	PLAYER_L_ARM_ROTBASIS_X		(0.0f)									// ��]��_��X���W
#define	PLAYER_L_ARM_ROTBASIS_Y		(30.0f)									// ��]��_��Y���W
#define	PLAYER_L_ARM_ROTBASIS_Z		(0.0f)									// ��]��_��Z���W
#define	PLAYER_L_ARM_MODEL			"data/MODEL/PLAYER/player_L_hand.x"		// �ǂݍ��ރ��f����
// �|���X�̉E���b�O�֌W
#define	PLAYER_R_LEG_TYPE_MAX		(2)										// �|���X�̑��̎��(�E���E����)
#define	PLAYER_R_LEG_MAX			(PLAYER_MAX)							// �|���X�̑��̍ő吔(�����̍��v��)
#define	PLAYER_R_LEG_ANIM_FRAME		(1 * 60 / 4)							// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	PLAYER_R_LEG_ANGLE			(D3DX_PI / 4 / 2)						// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	PLAYER_R_LEG_ROTBASIS_X		(0.0f)									// ��]��_��X���W
#define	PLAYER_R_LEG_ROTBASIS_Y		(20.0f)									// ��]��_��Y���W
#define	PLAYER_R_LEG_ROTBASIS_Z		(0.0f)									// ��]��_��Z���W
#define	PLAYER_R_LEG_MODEL			"data/MODEL/PLAYER/player_R_leg.x"		// �ǂݍ��ރ��f����
// �|���X�̍����b�O�֌W
#define	PLAYER_L_LEG_TYPE_MAX		(2)										// �|���X�̑��̎��(�E���E����)
#define	PLAYER_L_LEG_MAX			(PLAYER_MAX)							// �|���X�̑��̍ő吔(�����̍��v��)
#define	PLAYER_L_LEG_ANIM_FRAME		(1 * 60 / 4)							// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	PLAYER_L_LEG_ANGLE			(D3DX_PI / 4 / 2)						// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	PLAYER_L_LEG_ROTBASIS_X		(0.0f)									// ��]��_��X���W
#define	PLAYER_L_LEG_ROTBASIS_Y		(20.0f)									// ��]��_��Y���W
#define	PLAYER_L_LEG_ROTBASIS_Z		(0.0f)									// ��]��_��Z���W
#define	PLAYER_L_LEG_MODEL			"data/MODEL/PLAYER/player_L_leg.x"		// �ǂݍ��ރ��f����

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
//class PLAYER										// �v���C���[�N���X
//{
//public:
//	bool			use;							// true:�g�p  false:���g�p
//	bool			bShadow;
//	D3DXVECTOR3		scl;							// �X�P�[��
//	D3DXVECTOR3		Eye;							// �v���C���[�̎��_(�ʒu���W)
//	D3DXVECTOR3		At;								// �v���C���[�̒����_(�v���C���[�����Ă�����W)
//	D3DXVECTOR3		Up;								// �v���C���[�̏����
//	D3DXVECTOR3		rot;							// �v���C���[�̌���
//	D3DXVECTOR3		rotDest;						// �v���C���[�̖ړI�̌���
//	D3DXVECTOR3		move;							// �v���C���[�̈ړ���
//	D3DXVECTOR3		rotBasis;						// �v���C���[�̉�]�̒��S�_(���_���班���������邽�߁j
//	D3DXVECTOR3		axisXZ;							// �v���C���[�̉�]��(XZ)
//	D3DXVECTOR3		axisY;							// �v���C���[�̉�]��(Y)
//	D3DXQUATERNION	qRotateXZ;						// �v���C���[��XZ����]�N�H�[�^�j�I��
//	D3DXQUATERNION	qRotateY;						// �v���C���[��Y����]�N�H�[�^�j�I��
//	D3DXQUATERNION	qAnswer;						// �v���C���[�̍������]�N�H�[�^�j�I��
//	D3DXVECTOR3		posTmp;							// �v���C���[�̎��_�i�ꎞ�ۑ��j
//	float			fangleXZ;						// ��]�p�x(XZ)
//	float			fangleY;						// ��]�p�x(Y)
//	float			speed;							// �ړ����x�W��
//	int				key;							// �t���[���J�E���g�p
//	int				key2;							// �ړ��t���O�؂�ւ��J�E���g�p
//	int				num;							// �e�q�֌W���ʗp
//	int				weight;
//	int				havenum[HAVE_MAX];
//	int				nIdxShadow;
//	float			fSizeShadow;
//	D3DXCOLOR		colShadow;
//};
//class PLAYER_R_ARM :public PLAYER					// �v���C���[�E�A�[���N���X
//{
//public:
//	bool			rotf;							// ��]�����̐؂�ւ��t���O
//};
//class PLAYER_L_ARM :public PLAYER					// �v���C���[���A�[���N���X
//{
//public:
//	bool			rotf;							// ��]�����̐؂�ւ��t���O
//};
//class PLAYER_R_LEG :public PLAYER					// �v���C���[�E���b�O�N���X
//{
//public:
//	bool			rotf;							// ��]�����̐؂�ւ��t���O
//};
//class PLAYER_L_LEG :public PLAYER					// �v���C���[�����b�O�N���X
//{
//public:
//	bool			rotf;							// ��]�����̐؂�ւ��t���O
//};
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
