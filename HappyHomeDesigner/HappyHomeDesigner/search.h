//=============================================================================
//
// ���G�͈͕`�揈�� [search.h]
// Author : GP12A295-19-���_��
//
//=============================================================================
#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "main.h"
#include "police.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SEARCH	"data/TEXTURE/white.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SEARCH_MAX		(POLICE_MAX)				// ���G�͈͂̍ő吔
#define	SEARCH_LENGTH	(100.0f)					// ���G����
#define	SEARCH_ANGLE	(D3DX_PI / 2.0f)			// ���G����p
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SEARCH :public POLICE		// �T�[�`�N���X
{
public:
	float	cos;				// �R�T�C��
	float	sita;				// ���G�p�x
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSearch(int nType);
void UninitSearch(void);
void UpdateSearch(void);
void DrawSearch(void);
#endif
