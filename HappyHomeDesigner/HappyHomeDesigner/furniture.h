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
#define	MAX_FURNITURE				(32)						// �Ƌ�ő吔

//**************************************
// ���
//**************************************
enum
{
	FURNITURETYPE_COIN = 0,		// �R�C��
	FURNITURETYPE_LIFE,			// ���C�t
	FURNITURETYPE_TIMER,		// �^�C�}�[
	FURNITURETYPE_MAX
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FURNITURE
{
public:
	bool		use;				// �g�p���Ă��邩�ǂ���

	D3DXVECTOR3	pos;				// ���݂̈ʒu
	D3DXVECTOR3	rot;				// ���݂̌���
	D3DXVECTOR3	rotDest;			// �ړI�̌���
	D3DXVECTOR3	scl;				// �X�P�[��

	int			type;				// ���
	int			num;				// �ԍ�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);

void SetFurniture(D3DXVECTOR3 pos, int nType, int life);
FURNITURE *GetFurniture(int no);

#endif
