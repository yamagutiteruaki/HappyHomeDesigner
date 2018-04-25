//=============================================================================
//
// �Ƌ�� [furniture.h]
// Author : GP11B243-18-���_��
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_FURNITURE				(128)						// �A�C�e���ő吔
#define	MAX_FURNITURE_POP			(5)							// �A�C�e���������݉\��
#define	NUM_POP					(2)							// SetFurniture�֐��ň�񓖂���|�b�v�����鐔
#define	FURNITURE_LIFE				(300)						// �A�C�e���̎���
#define	VALUE_MOVE_FURNITURE			(0.5f)						// �A�C�e���̈ړ����x
#define	FURNITURE_SIZE_X				(10.0f)						// �A�C�e���̕�
#define	FURNITURE_SIZE_Y				(40.0f)						// �A�C�e���̍���
#define	FURNITURE_POP_FREQUENCY		(60*3)						// �A�C�e���̃|�b�v�p�x(�t���[���~�b��)
#define FURNITURE_SHADOW_SIZE		(35.0f)						// �A�C�e���̉e�T�C�Y
#define FURNITURE_SHADOW_REREASE		(-20.0f)					// �A�C�e���̉e���폜���鍂��

//**************************************
// ���
//**************************************
enum
{
	FURNITURETYPE_COIN = 0,		// �R�C��
	FURNITURETYPE_LIFE,			// ���C�t
	FURNITURETYPE_TIMER,			// �^�C�}�[
	FURNITURETYPE_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;				// ���݂̈ʒu
	D3DXVECTOR3	rot;				// ���݂̌���
	D3DXVECTOR3	scl;				// �X�P�[��

	float		fRadius;			// ���a
	int			nType;				// ���
	int			life;				// ����
	int			no;					// �|�b�v���Ă���p�l���ԍ�
	bool		use;				// �g�p���Ă��邩�ǂ���

									// �V���h�E�p
	int				nIdxShadow;
	float			fSizeShadow;
	D3DXCOLOR		colShadow;
	bool			bShadow;
} FURNITURE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);

void SetFurniture(D3DXVECTOR3 pos, int nType, int life);
FURNITURE *GetFurniture(int no);
int GetExistFurnitureNum(void);

#endif
