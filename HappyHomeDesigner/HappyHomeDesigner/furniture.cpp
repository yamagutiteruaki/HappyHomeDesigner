//=============================================================================
//
// �Ƌ�� [furniture.cpp]
// Author : GP12A295-19-���_��
//
//=============================================================================
#include "furniture.h"
#include "field.h"
#include "main.h"
#include "debugproc.h"
#include "stage.h"
//#include "shadow.h"

//#include "stdlib.h"
//#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE_FURNITURE		(D3DX_PI * 0.025f)		// ��]���x
#define	FURNITURE_RADIUS				(10.0f)					// ���a

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURETYPE_MAX];	// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshFurniture[FURNITURETYPE_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURETYPE_MAX];	// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatFurniture[FURNITURETYPE_MAX];		// �������̑���

D3DXMATRIX			g_mtxWorldFurniture;						// ���[���h�}�g���b�N�X

FURNITURE				furnitureWk[MAX_FURNITURE];					// �A�C�e�����[�N

int					poptime;							// �|�b�v����Ԋu

const char *FileNameFurniture[FURNITURETYPE_MAX] =
{
	"data/MODEL/FURNITURE/furniture.x",			// �R�C��
	"data/MODEL/FURNITURE/furniture001.x",		// ���C�t
	"data/MODEL/FURNITURE/furniture002.x"			// �^�C�}�[
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFurniture(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FURNITURE *furniture = &furnitureWk[0];
	int one = 0;

	if (nType == STAGE_INIT_FAST)
	{
		for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURETYPE_MAX; nCntFurnitureType++)
		{
			g_pD3DTextureFurniture[nCntFurnitureType] = NULL;
			g_pMeshFurniture[nCntFurnitureType] = NULL;
			g_pD3DXMatBuffFurniture[nCntFurnitureType] = NULL;

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNameFurniture[nCntFurnitureType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXMatBuffFurniture[nCntFurnitureType],
				NULL,
				&g_aNumMatFurniture[nCntFurnitureType],
				&g_pMeshFurniture[nCntFurnitureType])))
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,									// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,						// �t�@�C���̖��O
				&g_pD3DTextureModelFurniture[nCntFurnitureType]);	// �ǂݍ��ރ������[
#endif
		}
	}

	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{
		furniture->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->fRadius = 0.0f;
		furniture->nIdxShadow = -1;
		furniture->nType = FURNITURETYPE_COIN;
		furniture->life = 0;
		furniture->no = 0;
		furniture->use = false;

		// �V���h�E�p
		furniture->nIdxShadow = 0;
		furniture->fSizeShadow = 0.0f;
		furniture->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		furniture->bShadow = false;
	}

	poptime = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFurniture(void)
{
	for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURETYPE_MAX; nCntFurnitureType++)
	{
		if (g_pD3DTextureFurniture[nCntFurnitureType] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureFurniture[nCntFurnitureType]->Release();
			g_pD3DTextureFurniture[nCntFurnitureType] = NULL;
		}

		if (g_pMeshFurniture[nCntFurnitureType] != NULL)
		{// ���b�V���̊J��
			g_pMeshFurniture[nCntFurnitureType]->Release();
			g_pMeshFurniture[nCntFurnitureType] = NULL;
		}

		if (g_pD3DXMatBuffFurniture[nCntFurnitureType] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXMatBuffFurniture[nCntFurnitureType]->Release();
			g_pD3DXMatBuffFurniture[nCntFurnitureType] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFurniture(void)
{
	FURNITURE *furniture = &furnitureWk[0];
	//PANEL *panel = GetPanel(0);


	// �A�C�e�������Ԋu�Ń|�b�v������
	if (poptime % FURNITURE_POP_FREQUENCY == 0)
	{
		SetFurniture(D3DXVECTOR3(0.0f, 10.0f, 0.0f), FURNITURETYPE_COIN, FURNITURE_LIFE);
		poptime = 0;
	}
	poptime++;

	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{
		if (furniture->use)
		{
			// �A�C�e������]������
			furniture->rot.y += VALUE_ROTATE_FURNITURE;
			if (furniture->rot.y > D3DX_PI)
			{
				furniture->rot.y -= D3DX_PI * 2.0f;
			}

			// �X�P�[���������Âg��
			furniture->scl.x += 0.05f;
			furniture->scl.y += 0.05f;
			furniture->scl.z += 0.05f;

			// �A�C�e�������S�Ƀ|�b�v������i�X�P�[�����ő�܂Ŋg�傳�ꂽ��j
			if (furniture->scl.x >= 1.0f)
			{
				// �X�P�[��������ȏ�傫���Ȃ�Ȃ��悤�ɂ���
				furniture->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

				// �A�C�e���̎��������炷
				furniture->life--;

			}


			if (furniture->life <= 0)
			{	// �A�C�e�������X�ɉ������Ɉړ�
				furniture->pos.y -= VALUE_MOVE_FURNITURE;
			}


			//if (furniture->life <= 0)
			//{	// �������s�����A�C�e��������
			//	furniture->use = false;
			//}

			// �V���h�E
			//if (!furniture->bShadow)
			//{	// �V���h�E�ݒu
			//	furniture->nIdxShadow = CreateShadow(furniture->pos, 25.0f, 25.0f);
			//	furniture->fSizeShadow = FURNITURE_SHADOW_SIZE;
			//	furniture->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.7f);
			//	furniture->bShadow = true;
			//}
			//else
			//{
			//	// �V���h�E�Ǘ�
			//	SetPositionShadow(furniture->nIdxShadow, D3DXVECTOR3(furniture->pos.x, 0.2f, furniture->pos.z));
			//	SetVertexShadow(furniture->nIdxShadow, furniture->fSizeShadow, furniture->fSizeShadow);
			//	SetColorShadow(furniture->nIdxShadow, furniture->colShadow);
			//}

			//if (furniture->pos.y < FURNITURE_SHADOW_REREASE && furniture->bShadow)
			//{
			//	// �A�C�e���̉e���폜
			//	ReleaseShadow(furniture->nIdxShadow);
			//	furniture->bShadow = false;
			//}
			// ���S�Ƀt�B�[���h�̉��ɍs���������
			if (furniture->pos.y < -FURNITURE_SIZE_Y)
			{
				// �A�C�e��������
				furniture->use = false;
				// �p�l�����Z�b�g��Ԃ��������Ă�����
				//panel[furniture->no].FurnitureSet = false;

			}

			// �e�̈ʒu�ݒ�
			//SetPositionShadow(furniture->nIdxShadow, D3DXVECTOR3(furniture->pos.x, 0.1f, furniture->pos.z));

			float fSizeX = 20.0f + (furniture->pos.y - 10.0f) * 0.05f;
			if (fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (furniture->pos.y - 10.0f) * 0.05f;
			if (fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			//SetVertexShadow(furniture->nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (furniture->pos.y - 10.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			//SetColorShadow(furniture->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


#ifdef _DEBUG
	PrintDebugProc("[�A�C�e���̐�����]  �F(%d)]\n", GetExistFurnitureNum());
	PrintDebugProc("\n");
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFurniture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	FURNITURE *furniture = &furnitureWk[0];


	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{
		if (furniture->use)
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldFurniture);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, furniture->scl.x,
				furniture->scl.y,
				furniture->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture,
				&g_mtxWorldFurniture, &mtxScale);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, furniture->rot.y, furniture->rot.x, furniture->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture, &g_mtxWorldFurniture, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, furniture->pos.x, furniture->pos.y, furniture->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture, &g_mtxWorldFurniture, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldFurniture);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffFurniture[furniture->nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatFurniture[furniture->nType]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureFurniture[furniture->nType]);

				// �`��
				g_pMeshFurniture[furniture->nType]->DrawSubset(nCntMat);
			}

			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		}
	}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
// �����P�F�|�b�v��������W�����p
// �����Q�F�A�C�e���̎��
// �����R�F�A�C�e�����|�b�v���Ă��������܂ł̎���
//=============================================================================
void SetFurniture(D3DXVECTOR3 pos, int nType, int life)
{
	FURNITURE *furniture = &furnitureWk[0];
	//PANEL *panel = GetPanel(0);
	int no = 0;		// �p�l���ԍ��i�[

	for (int i = 0; i < NUM_POP; i++)
	{	// �A�C�e�����|�b�v�����镪�������[�v

		furniture = &furnitureWk[0];

		//while (1)
		//{
		//	no = rand() % PANEL_MAX;

		//	panel = GetPanel(no);

		//	// �I�΂ꂽ�p�l�����g�p�����ǂ����̃`�F�b�N
		//	if (!panel->FurnitureSet)
		//	{	// ���g�p�Ȃ��

		//		// �A�C�e���Z�b�g��Ԃɂ���
		//		panel->FurnitureSet = true;


		//		break;
		//	}

		//}

		for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
		{
			if (!furniture->use)
			{
				// �A�C�e�����Z�b�g�����p�l���̔ԍ���ۑ�
				furniture->no = no;

				// �A�C�e���̃X�P�[�����[���ɂ���
				furniture->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �|�b�v�ʒu�̐ݒ�
				//furniture->pos = panel->Pos;		// �����_���őI�񂾃p�l���̍��W�ɃZ�b�g
											// �|�b�v�ʒu�������
				furniture->pos.x += pos.x;
				furniture->pos.y += pos.y;
				furniture->pos.z += pos.z;

				furniture->fRadius = FURNITURE_RADIUS;
				furniture->nType = nType;
				furniture->life = life;
				furniture->use = true;

				// �e�̐ݒ�
				//furniture->nIdxShadow = SetShadow(furniture->pos, furniture->fRadius * 2.0f, furniture->fRadius * 2.0f);

				break;
			}
		}

		// �A�C�e���̐�������MAX�ɂȂ����甲����
		if (GetExistFurnitureNum() >= MAX_FURNITURE_POP) break;

	}
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
FURNITURE *GetFurniture(int no)
{
	return &furnitureWk[no];
}
//=============================================================================
// �A�C�e���̐������擾
//=============================================================================
int GetExistFurnitureNum(void)
{
	FURNITURE *furniture = &furnitureWk[0];
	int Cnt = 0;

	for (int i = 0; i < MAX_FURNITURE; i++, furniture++)
	{
		if (furniture->use)
		{
			Cnt++;
		}
	}

	return Cnt;
}