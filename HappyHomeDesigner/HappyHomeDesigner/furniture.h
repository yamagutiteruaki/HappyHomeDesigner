//=============================================================================
//
// �Ƌ�� [furniture.h]
// Author : GP12A295-19-���_��
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_FURNITURE				(128)						// �Ƌ�ő吔
#define	VALUE_MOVE_FURNITURE		(1.00f)						// �ړ����x�W��
#define	RATE_MOVE_FURNITURE			(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_FURNITURE		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_FURNITURE		(0.20f)						// ��]�����W��
#define	VALUE_SCALE_FURNITURE		(0.05f)						// �X�P�[���g��E�k�����x
//**************************************
// ���
//**************************************
enum
{
	kabin = 0,			// �ԕr
	isu,				// �֎q
	buta,				// �؂̒�����
	yubiwa,				// �w��
	toire,				// �g�C��
	tukue,				// ��
	terebi,				// �e���r
	kinko,				// ����
	tansu,				// �^���X
	bed,				// �x�b�h
	FURNITURE_TYPE_MAX	// �Ƌ�̎�ނ̍ő吔
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FURNITURE
{
public:
	bool		use;				// �g�p���Ă��邩�ǂ���
	bool		own;				// �v���C���[�ɏ��L����Ă��邩�ǂ���(true:���L����Ă���,false:���L����Ă��Ȃ�)

	D3DXVECTOR3	pos;				// ���݂̈ʒu
	D3DXVECTOR3	rot;				// ���݂̌���
	D3DXVECTOR3	rotDest;			// �ړI�̌���
	D3DXVECTOR3	scl;				// �X�P�[��
	D3DXVECTOR3	move;				// �ړ���

	int			type;				// ���
	int			house_num;			// �������Ă���Ƃ̔ԍ�
	int			weight;				// �d��
	int			price;				// ���z
	int			ratio;				// �m��

	char		name[64];			// CSV�t�@�C���̉Ƌ�̖��O
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);
FURNITURE *GetFurniture(int no);
int GetFurnitureNum(void);

#endif
