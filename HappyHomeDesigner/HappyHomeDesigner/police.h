//=============================================================================
//
// �|���X���� [police.h]
// Author : GP12A295-19-���_��
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
#define	POLICE_COLLISION_FRAME	(5 * 60)										// �����蔻��̖�����Ԃ̉����ɂ�����t���[����(�b�� * 60�t���[��)
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
#define	CHECK_POINT_X			(FIELD_SIZE_X / 2 - FIELD_SIZE_X / 16)			// �`�F�b�N�|�C���g��X���W
#define	CHECK_POINT_Z			(FIELD_SIZE_Z / 2 - FIELD_SIZE_Z / 16)			// �`�F�b�N�|�C���g��Z���W
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class POLICE						// �|���X�N���X
{
public:
	bool			use;							// true:�g�p  false:���g�p
	bool			able_hit;						// true:�����蔻��L��  false:�����蔻�薳��
	bool			rotf;							// ��]�����̐؂�ւ��t���O(���͎g��Ȃ��̂�NULL)
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
	int				type;							// �{�̂̎��(���͎g��Ȃ��̂�NULL)
};
class POLICE_ARM :public POLICE		// �|���X�A�[���N���X
{
};
class POLICE_LEG :public POLICE		// �|���X���b�O�N���X
{
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);
POLICE *GetPolice(int no);
void SetParts(void);
template <typename CLASS> void SetAnimation(CLASS *pIn, float fAngle, int frame, D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY);
void Animation(void);
#endif