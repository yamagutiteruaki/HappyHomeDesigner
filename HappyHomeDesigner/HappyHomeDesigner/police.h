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

// �|���X�{�̊֌W
#define	VALUE_MOVE_POLICE		(1.00f)											// �ړ����x�W��
#define	RATE_MOVE_POLICE			(0.20f)										// �ړ������W��
#define	VALUE_ROTATE_POLICE		(D3DX_PI * 0.05f)								// ��]���x
#define	RATE_ROTATE_POLICE		(0.20f)											// ��]�����W��
#define	POLICE_MAX				(1)												// �|���X�̍ő吔 /////�܂������Ή����ĂȂ��̂ł�����Ȃ��ŁI�I/////
#define	POLICE_SIZE_X			(10.0f)											// �|���X�̕�
#define	POLICE_SIZE_Y			(20.0f)											// �|���X�̍���
#define	POLICE_ANIM_MAX			(12)											// �|���X�̃A�j���[�V�����p�^�[����
#define	POLICE_ANIM_SEC			(1)												// �A�j���[�V�����ꏄ�ɂ�����b��
#define	POLICE_SPEED_FREQUENCY	(60*10)											// �|���X�̈ړ����x�̍X�V�p�x(�t���[���~�b��)
#define	POLICE_SPEEDUP			(0.2f)											// �|���X�̈ړ����x�ω���
#define POLICE_SHADOW_SIZE		(53.0f)											// �|���X�̉e�T�C�Y
#define	POLICE_MODEL			"data/MODEL/POLICE/standing_body.x"				// �ǂݍ��ރ��f����
// �|���X�A�[���֌W
#define	POLICE_ARM_TYPE_MAX		(2)												// �|���X�̘r�̎��(�E�r�E���r)
#define	POLICE_ARM_MAX			(POLICE_MAX * 2)								// �|���X�̘r�̍ő吔(���r�̍��v��)
#define	POLICE_ARM_ANIM_FRAME	(1 * 60)										// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
// �|���X�̃��b�O�֌W
#define	POLICE_LEG_TYPE_MAX		(2)												// �|���X�̑��̎��(�E���E����)
#define	POLICE_LEG_MAX			(POLICE_MAX * 2)								// �|���X�̑��̍ő吔(�����̍��v��)
#define	POLICE_LEG_ANIM_FRAME	(1 * 60)										// �A�j���[�V�����ꉝ���ɂ�����t���[����(�b�� * 60�t���[��)
// �`�F�b�N�|�C���g�֌W
#define	CHECK_POINT_X_MAX		(3)												// �������̃`�F�b�N�|�C���g�̍ő吔
#define	CHECK_POINT_Y_MAX		(3)												// �c�����̃`�F�b�N�|�C���g�̍ő吔
#define	CHECK_POINT_MAX			(CHECK_POINT_X_MAX * CHECK_POINT_Y_MAX)			// �`�F�b�N�|�C���g�̍��v
//**************************************
// �ݒ�Ώۂ̍\���̂ւ̃|�C���^���ʔԍ�
//**************************************
enum
{
	TYPE_BODY = 0,		// �{��
	TYPE_ARM,			// �A�[��
	TYPE_LEG,			// ���b�O
	FURNITURETYPE_MAX
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

	float			speed;							// �ړ����x�W��
	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				anim;							// �A�j���[�V�����ԍ�
	int				key;							// �t���[���J�E���g�p

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

	float			speed;							// �ړ����x�W��
	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				anim;							// �A�j���[�V�����ԍ�
	int				key;							// �t���[���J�E���g�p
	int				type;							// �A�[���̎��(�E�r��0�E���r��1)

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

	float			speed;							// �ړ����x�W��
	float			fangleXZ;						// ��]�p�x(XZ)
	float			fangleY;						// ��]�p�x(Y)

	int				anim;							// �A�j���[�V�����ԍ�
	int				key;							// �t���[���J�E���g�p
	int				type;							// �A�[���̎��(�E�r��0�E���r��1)

} POLICE_LEG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);

POLICE *GetPolice(int no);

#endif
