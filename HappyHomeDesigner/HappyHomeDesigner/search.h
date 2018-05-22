//=============================================================================
//
// ���G�͈͕`�揈�� [search.h]
// Author : GP12A295-19-���_��
//
//=============================================================================
#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSearch(void);
void UninitSearch(void);
void UpdateSearch(void);
void DrawSearch(void);
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SEARCH	"data/TEXTURE/field000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SEARCH_MAX		(1)							// ���G�͈͂̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SEARCH	// �T�[�`�N���X
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
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSearch(int nType);

#endif
