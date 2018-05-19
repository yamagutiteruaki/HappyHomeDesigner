//=============================================================================
//
// �|���X���� [enemy.h]
// Author : GP11B243-18-���_��
//
//=============================================================================
#ifndef _POLICE_H_
#define _POLICE_H_

#include "main.h"
#include "field.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �|���X�{�̊֌W
#define	POLICE_SPEED			(1.20f)											// �ړ����x�W��
#define	POLICE_MAX				(3)												// �|���X�̍ő吔
#define	POLICE_MODEL			"data/MODEL/POLICE/standing_body.x"				// �ǂݍ��ރ��f����
#define	POLICE_SCALE_X			(1.0f * 1.2)									// �X�P�[����X����
#define	POLICE_SCALE_Y			(1.0f * 1.2)									// �X�P�[����Y����
#define	POLICE_SCALE_Z			(1.0f * 1.2)									// �X�P�[����Z����
#define	POLICE_ROTBASIS_X		(0.0f)											// ��]��_��X���W
#define	POLICE_ROTBASIS_Y		(60.0f)											// ��]��_��Y���W
#define	POLICE_ROTBASIS_Z		(0.0f)											// ��]��_��Z���W
// �|���X�A�[���֌W
#define	POLICE_ARM_TYPE_MAX		(2)												// �|���X�̘r�̎��(�E�r�E���r)
#define	POLICE_ARM_MAX			(POLICE_MAX * 2)								// �|���X�̘r�̍ő吔(���r�̍��v��)
#define	POLICE_ARM_ANIM_FRAME	(1 * 60 / 4)									// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	POLICE_ARM_ANGLE		(D3DX_PI / 4 / 2)								// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	POLICE_ARM_ROTBASIS_X	(0.0f)											// ��]��_��X���W
#define	POLICE_ARM_ROTBASIS_Y	(30.0f)											// ��]��_��Y���W
#define	POLICE_ARM_ROTBASIS_Z	(0.0f)											// ��]��_��Z���W
// �|���X�̃��b�O�֌W
#define	POLICE_LEG_TYPE_MAX		(2)												// �|���X�̑��̎��(�E���E����)
#define	POLICE_LEG_MAX			(POLICE_MAX * 2)								// �|���X�̑��̍ő吔(�����̍��v��)
#define	POLICE_LEG_ANIM_FRAME	(1 * 60 / 4)									// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
#define	POLICE_LEG_ANGLE		(D3DX_PI / 4 / 2)								// �A�j���[�V�����̉�]�p�x(180�x / �K���Ȋp�x)
#define	POLICE_LEG_ROTBASIS_X	(0.0f)											// ��]��_��X���W
#define	POLICE_LEG_ROTBASIS_Y	(20.0f)											// ��]��_��Y���W
#define	POLICE_LEG_ROTBASIS_Z	(0.0f)											// ��]��_��Z���W
// �`�F�b�N�|�C���g�֌W
#define	CHECK_POINT_X_MAX		(3)												// �������̃`�F�b�N�|�C���g�̍ő吔
#define	CHECK_POINT_Y_MAX		(3)												// �c�����̃`�F�b�N�|�C���g�̍ő吔
#define	CHECK_POINT_MAX			(FIELD_SIZE_X_MAX * CHECK_POINT_Y_MAX)			// �`�F�b�N�|�C���g�̍��v��
#define	CHECK_POINT_X			(FIELD_SIZE_X / 2 - FIELD_SIZE_X / 16)
#define	CHECK_POINT_Z			(FIELD_SIZE_X / 2 - FIELD_SIZE_Z / 16)
//**************************************
// �A�j���[�V�����ݒ�Ώۂ̎��ʔԍ�
//**************************************
enum
{
	TYPE_BODY = 0,		// �{��
	TYPE_ARM,			// �A�[��
	TYPE_LEG,			// ���b�O
	TYPE_MAX
};
//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �|���X�\����
{
	bool			use;							// true:�g�p  false:���g�p
	bool			able_hit;						// true:�����蔻��L��  false:�����蔻�薳��

	D3DXVECTOR3		scl;							// �X�P�[��
	D3DXVECTOR3		Eye;							// �|���X�̎��_(�ʒu���W)
	D3DXVECTOR3		At;								// �|���X�̒����_(�|���X�����Ă�����W)
	D3DXVECTOR3		Up;								// �|���X�̏����
	D3DXVECTOR3		rot;							// �|���X�̌���
	D3DXVECTOR3		move;							// �|���X�̈ړ���
	D3DXVECTOR3		rotBasis;						// �|���X�̉�]�̒��S�_(���_���班���������邽�߁j
	D3DXVECTOR3		axisXZ;							// �|���X�̉�]��(XZ)
	D3DXVECTOR3		axisY;							// �|���X�̉�]��(Y)

	D3DXQUATERNION	qRotateXZ;						// �|���X��XZ����]�N�H�[�^�j�I��
	D3DXQUATERNION	qRotateY;						// �|���X��Y����]�N�H�[�^�j�I��
	D3DXQUATERNION	qAnswer;						// �|���X�̍������]�N�H�[�^�j�I��

	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				key;							// �t���[���J�E���g�p
	int				num;							// �e�q�֌W���ʗp
} POLICE;
typedef struct		// �|���X�A�[���\����
{
	bool			use;							// true:�g�p  false:���g�p
	bool			rotf;							// ��]�����̐؂�ւ��t���O

	D3DXVECTOR3		scl;							// �X�P�[��
	D3DXVECTOR3		Eye;							// �A�[���̎��_(�ʒu���W)
	D3DXVECTOR3		At;								// �A�[���̒����_(�A�[�������Ă�����W)
	D3DXVECTOR3		Up;								// �A�[���̏����
	D3DXVECTOR3		rot;							// �A�[���̌���
	D3DXVECTOR3		move;							// �A�[���̈ړ���
	D3DXVECTOR3		rotBasis;						// �A�[���̉�]�̒��S�_(���_���班���������邽�߁j
	D3DXVECTOR3		axisXZ;							// �A�[���̉�]��(XZ)
	D3DXVECTOR3		axisY;							// �A�[���̉�]��(Y)

	D3DXQUATERNION	qRotateXZ;						// �A�[����XZ����]�N�H�[�^�j�I��
	D3DXQUATERNION	qRotateY;						// �A�[����Y����]�N�H�[�^�j�I��
	D3DXQUATERNION	qAnswer;						// �A�[���̍������]�N�H�[�^�j�I��

	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				key;							// �t���[���J�E���g�p
	int				type;							// �A�[���̎��(�E�r��0�E���r��1)
	int				num;							// �e�q�֌W���ʗp
} POLICE_ARM;
typedef struct		// �|���X���b�O�\����
{
	bool			use;							// true:�g�p  false:���g�p
	bool			rotf;							// ��]�����̐؂�ւ��t���O

	D3DXVECTOR3		scl;							// �X�P�[��
	D3DXVECTOR3		Eye;							// ���b�O�̎��_(�ʒu���W)
	D3DXVECTOR3		At;								// ���b�O�̒����_(���b�O�����Ă�����W)
	D3DXVECTOR3		Up;								// ���b�O�̏����
	D3DXVECTOR3		rot;							// ���b�O�̌���
	D3DXVECTOR3		move;							// ���b�O�̈ړ���
	D3DXVECTOR3		rotBasis;						// ���b�O�̉�]�̒��S�_(���_���班���������邽�߁j
	D3DXVECTOR3		axisXZ;							// ���b�O�̉�]��(XZ)
	D3DXVECTOR3		axisY;							// ���b�O�̉�]��(Y)

	D3DXQUATERNION	qRotateXZ;						// ���b�O��XZ����]�N�H�[�^�j�I��
	D3DXQUATERNION	qRotateY;						// ���b�O��Y����]�N�H�[�^�j�I��
	D3DXQUATERNION	qAnswer;						// ���b�O�̍������]�N�H�[�^�j�I��

	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				key;							// �t���[���J�E���g�p
	int				type;							// �A�[���̎��(�E�r��0�E���r��1)
	int				num;							// �e�q�֌W���ʗp
} POLICE_LEG;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);
POLICE *GetPolice(int no);
void SetAnimation(int pType, float fAngle, int frame,D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY);
void SetParts(void);
#endif
