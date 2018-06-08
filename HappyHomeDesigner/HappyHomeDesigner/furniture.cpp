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
#include "load_csv.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void FurnitureColi(void);
void FurnitureWt(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURE_TYPE_MAX];		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshFurniture[FURNITURE_TYPE_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURE_TYPE_MAX];	// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatFurniture[FURNITURE_TYPE_MAX];			// �������̑���
D3DXMATRIX			g_mtxWorldFurniture;							// ���[���h�}�g���b�N�X
FURNITURE			furnitureWk[MAX_FURNITURE];						// �Ƌ�i�[���[�N

const char *FileNameFurniture[FURNITURE_TYPE_MAX] =
{
	"data/MODEL/FURNITURE/kabin.x",		// �ԕr
	"data/MODEL/FURNITURE/isu.x",		// �֎q
	"data/MODEL/FURNITURE/pig.x",		// �؂̒�����
	"data/MODEL/FURNITURE/yubiwa.x",	// �w��
	"data/MODEL/FURNITURE/toilet.x",	// �g�C��
	"data/MODEL/FURNITURE/desk.x",		// ��
	"data/MODEL/FURNITURE/tv.x",		// �e���r
	"data/MODEL/FURNITURE/kinko.x",		// ����
	"data/MODEL/FURNITURE/tansu.x",		// �^���X
	"data/MODEL/FURNITURE/bed.x"		// �x�b�h
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitFurniture(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FURNITURE *furniture = &furnitureWk[0];

	if (type == STAGE_INIT_FAST)
	{
		for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURE_TYPE_MAX; nCntFurnitureType++)
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

	// �Ƌ�̏���������
	//for (int i = 0; i <MAX_FURNITURE; i++, furniture++)
	//{

	//}


	LoadCsv();			// CSV�t�@�C���ǂݍ���
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFurniture(void)
{
	for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURE_TYPE_MAX; nCntFurnitureType++)
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
	{	// �g�p��Ԃ̉Ƌ�̂ݕ`��

		if (!furniture->use) continue;
		if (furniture->house_num == GetStage())// �X�e�[�W�ԍ��Ɠ����Ɣԍ��̉Ƌ�̂ݕ`��
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

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffFurniture[furniture->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatFurniture[furniture->type]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureFurniture[furniture->type]);

				// �`��
				g_pMeshFurniture[furniture->type]->DrawSubset(nCntMat);
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
// �Ƌ�̎擾
//=============================================================================
FURNITURE *GetFurniture(int no)
{
	return &furnitureWk[no];
}

//=============================================================================
// �Ƌ�̓����蔻�菈��
//=============================================================================
void FurnitureColi()
{
	// ���݂��Ă��邩�Ƃ���

	// �͈͓����Ƃ���

	// �{�^������

	// �������`�F�b�N

	// �����d�ʃ`�F�b�N

	// �J�o���̋󂢂Ă���ꏊ��T��

	// �J�o���ɓ����

	// �����d�ʏ���

}

//=============================================================================
// �Ƌ�̏d�ʂ̏���
//=============================================================================
void FurnitureWt()
{
	PLAYER *player = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);

	player->weight = 0;

	for (int i = 0; i < HAVE_MAX; i++)
	{
		if (player->havenum[i] != -1) continue;
		
		int type_tem = player->havenum[i];

		player->weight += (fnt + type_tem)->weight;

		//for (int j = 0; j < FURNITURE_TYPE_MAX; j++)
		//{
		//	if (player->havenum[i] == (fnt + j)->type)
		//	{
		//		player->weight += (fnt + j)->weight;
		//	}

		//}

	}

}