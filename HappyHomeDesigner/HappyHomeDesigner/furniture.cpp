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
#include "input.h"
#include "write_csv.h"
#include "camera.h"
#include "calculate.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int FurnitureColi(void);
void FurnitureGetDAZE(int no);
void FurniturePut(void);
int BagCheck(int func);
bool WeightCheck(int no);

//void FurnitureWt(void);
void FurnitureMove(int no);
void FurnitureRotate(int no);
void FurnitureScaling(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURE_TYPE_MAX];		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshFurniture[FURNITURE_TYPE_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURE_TYPE_MAX];	// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatFurniture[FURNITURE_TYPE_MAX];			// �������̑���
D3DXMATRIX			g_mtxWorldFurniture;							// ���[���h�}�g���b�N�X
FURNITURE			furnitureWk[MAX_FURNITURE];						// �Ƌ�i�[���[�N

int					FurnitureNum;									// ���삷��Ƌ�̔ԍ��w��p

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

	FurnitureNum = 0;

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

	FurnitureColi();
	//FurnitureGetDAZE();
	FurniturePut();

#ifdef _DEBUG
	// �������Ƌ������
	if (GetKeyboardTrigger(DIK_L))
	{
		FurnitureNum++;
		if (FurnitureNum >= GetFurnitureCnt())
		{	// �|�C���^�G���[�h�~
			FurnitureNum--;
		}
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		FurnitureNum--;
		if (FurnitureNum < 0)
		{	// �|�C���^�G���[�h�~
			FurnitureNum = 0;
		}
	}
	// �w�肵���Ƌ���ړ�
	FurnitureMove(FurnitureNum);
	// �w�肵���Ƌ��Y����]
	FurnitureRotate(FurnitureNum);
	// �w�肵���X�P�[���g��E�k��
	FurnitureScaling(FurnitureNum);

	// csv�t�@�C���V�K�쐬
	if (GetKeyboardTrigger(DIK_M))
	{
		WriteCsv(CREATE);
	}
	// csv�t�@�C���ɏ㏑��
	if (GetKeyboardTrigger(DIK_Q))
	{
		WriteCsv(OVERWRITE);
	}

	// �f�o�b�O�t�H���g�\��
	PrintDebugProc("\n\n���݂̉Ɣԍ�:       %d \n", GetStage());
	PrintDebugProc("�ҏW���̉Ƌ�̖��O: %s \n\n", furnitureWk[FurnitureNum].name);
	PrintDebugProc("�Ƌ��pos:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].pos.x,
		furnitureWk[FurnitureNum].pos.y,
		furnitureWk[FurnitureNum].pos.z);
	PrintDebugProc("�Ƌ��rot:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].rot.x,
		furnitureWk[FurnitureNum].rot.y,
		furnitureWk[FurnitureNum].rot.z);
	PrintDebugProc("�Ƌ��scl:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].scl.x,
		furnitureWk[FurnitureNum].scl.y,
		furnitureWk[FurnitureNum].scl.z);
	PrintDebugProc("�Ƌ��id:        [%d]\n", furnitureWk[FurnitureNum].id);
	PrintDebugProc("�Ƌ��use:       [%d]\n", furnitureWk[FurnitureNum].use);
	PrintDebugProc("�Ƌ��type:      [%d]\n", furnitureWk[FurnitureNum].type);
	PrintDebugProc("�Ƌ��house_num: [%d]\n", furnitureWk[FurnitureNum].house_num);
	PrintDebugProc("�Ƌ��weight:    [%f]\n", furnitureWk[FurnitureNum].weight);
	PrintDebugProc("�Ƌ��price:     [%d]\n", furnitureWk[FurnitureNum].price);
	PrintDebugProc("�Ƌ��ratio:     [%d]\n", furnitureWk[FurnitureNum].ratio);
	PrintDebugProc("\n�Ƌ�̑�����@�ꗗ\n");
	PrintDebugProc("�Ƌ��I��:               [K�L�[orL�L�[]\n");
	PrintDebugProc("�Ƌ�̈ړ�:               [�O�ړ�T�L�[], [��ړ�G�L�[], [���ړ�F�L�[], [�E�ړ�H�L�[]\n");
	PrintDebugProc("�Ƌ��Y����]:            [R�L�[orE�L�[]\n");
	PrintDebugProc("�Ƌ�̃X�P�[���g��Ək��: [I�L�[orJ�L�[]\n\n");
	PrintDebugProc("CSV�t�@�C���̏㏑���ۑ�:  [Q�L�[]\n\n");
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
// �Ƌ�w��ԍ��̎擾
//=============================================================================
int GetFurnitureNum(void)
{
	return FurnitureNum;
}
//=============================================================================
// �Ƌ�̓����蔻�菈��
//=============================================================================
int FurnitureColi()
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	int no = -1;
	float dist = 0.0;
	const float distCheck = 32.0f;

	for (int i = 0; i < MAX_FURNITURE; i++, fnt++)
	{
		// ���݂��Ă���̂�
		if (fnt->use == FALSE) continue;
		if (fnt->house_num != GetStage()) continue;

		// �������v�Z
		dist = float(sqrt(pow((fnt->pos.x - ply->Eye.x), 2) + pow((fnt->pos.z - ply->Eye.z), 2)));
		#ifdef _DEBUG
		PrintDebugProc("NO.%d dist = %f\n", fnt->id, dist);
		#endif

		// ����͈͓����Ƃ���
		if (dist <= distCheck)
		{
			// ���b�Z�[�W�\��
			#ifdef _DEBUG
			PrintDebugProc("�擾�\ ");
			#endif

			// �ԍ����擾
			#ifdef _DEBUG
			PrintDebugProc("�Ƌ�ID: %d\n", fnt->id);
			PrintDebugProc("�Ƌ���z: %g\n", fnt->price);

			#endif

			no = i;

			// �{�^������
			if (GetKeyboardTrigger(DIK_E))
			{
				FurnitureGetDAZE(no);
				//fnt = GetFurniture(0);
				//(fnt + no)->use = FALSE;
				
			}

		}
		else
		{
			no = -1;
		}

	}

	return no;
}

//=============================================================================
// �Ƌ�
//=============================================================================
void FurnitureGetDAZE(int no)
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);

	// �������`�F�b�N�A�J�o���̒��ŋ󂢂Ă���ꏊ��T��
	int space = -1;
	space = BagCheck(0);

	if ((space >= 0 && space < HAVE_MAX) &&	// �������`�F�b�N�A�J�o���̒��ŋ󂢂Ă���ꏊ��T��
		WeightCheck(no) == TRUE)			// �����d�ʃ`�F�b�N
	{
		// �J�o���ɓ����
		ply->havenum[space] = (fnt + no)->id;

		// �����d�ʏ���
		ply->weight += (fnt + no)->weight;

		// �t�B�[���h��̃I�u�W�F�N�g���폜
		(fnt + no)->use = FALSE;
	}

}

//=============================================================================
// �����i�`�F�b�N
// �����F0 ��� 1 �����
//=============================================================================
int BagCheck(int func)
{
	PLAYER *ply = GetPlayer(0);
	int no = -1;

	switch (func)
	{
	case 0:
		// �J�o���̒��ŋ󂢂Ă���ꏊ��T��
		for (int i = 0; i < HAVE_MAX; i++)
		{
			if (ply->havenum[i] == -1)
			{
				no = i;
				break;
			}
		}
		break;

	case 1:
		// �J�o���̒��ň�ԏ�̃A�C�e����T��
		for (int i = 0; i < HAVE_MAX; i++)
		{
			if (ply->havenum[i] != -1)
			{
				no = i;
			}
		}
		break;

	}
	
	return no;

}

//=============================================================================
// �����d�ʃ`�F�b�N
//=============================================================================
bool WeightCheck(int no)
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	if (ply->weight + (fnt + no)->weight <= WT_MAX)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

//=============================================================================
// �Ƌ��u��
//=============================================================================
void FurniturePut()
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	int no = -1;
	int id = -1;

	// �{�^������
	if (GetKeyboardTrigger(DIK_B))
	{
		// �u����ꏊ�`�F�b�N�i����Ȃ��j

		// �J�o���̒��g���擾
		no = BagCheck(1);

		// �����i�`�F�b�N
		if (no != -1)
		{
			// �J�o���̒��g���擾
			id = ply->havenum[no];

			// �v���C���[�ʒu���擾�A�v�b�g
			(fnt + id)->pos = ply->Eye;
			(fnt + id)->house_num = GetStage();
			(fnt + id)->use = TRUE;

			//��Q���z���Z
			if (GetStage() == STAGE_MYHOUSE)
			{
				AddPrice((fnt + id)->price);
			}
			// �����i����
			ply->havenum[no] = -1;

			// �����d�ʏ���
			ply->weight -= (fnt + id)->weight;

		}

	}

}

//=============================================================================
// �Ƌ�̈ړ�
//=============================================================================
void FurnitureMove(int no)
{
	FURNITURE *furniture = &furnitureWk[no];
	CAMERA *camera = GetCamera();

	float fDiffRotY;

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_F))
	{
		if (GetKeyboardPress(DIK_T))
		{// ���O�ړ�
			furniture->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_G))
		{// ����ړ�
			furniture->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// ���ړ�
			furniture->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.50f;

		}
	}
	else if (GetKeyboardPress(DIK_H))
	{
		if (GetKeyboardPress(DIK_T))
		{// �E�O�ړ�
			furniture->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_G))
		{// �E��ړ�
			furniture->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// �E�ړ�
			furniture->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(DIK_T))
	{// �O�ړ�
		furniture->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
		furniture->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

		furniture->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(DIK_G))
	{// ��ړ�
		furniture->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
		furniture->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

		furniture->rotDest.y = camera->rotCamera.y;
	}

	// �ړ��ʂɊ�����������
	furniture->move.x += (0.0f - furniture->move.x) * RATE_MOVE_FURNITURE;
	furniture->move.y += (0.0f - furniture->move.y) * RATE_MOVE_FURNITURE;
	furniture->move.z += (0.0f - furniture->move.z) * RATE_MOVE_FURNITURE;

	// �ʒu�ړ�
	furniture->pos.x += furniture->move.x;
	furniture->pos.y += furniture->move.y;
	furniture->pos.z += furniture->move.z;

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = furniture->rotDest.y - furniture->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	furniture->rot.y += fDiffRotY * RATE_ROTATE_FURNITURE;
	if (furniture->rot.y > D3DX_PI)
	{
		furniture->rot.y -= D3DX_PI * 2.0f;
	}
	if (furniture->rot.y < -D3DX_PI)
	{
		furniture->rot.y += D3DX_PI * 2.0f;
	}

	// �p�x���C��
	furniture->rot.y = PiCalculate360(furniture->rot.y);

}
//=============================================================================
// �Ƌ��Y����]
//=============================================================================
void FurnitureRotate(int no)
{
	FURNITURE *furniture = &furnitureWk[no];
	CAMERA *camera = GetCamera();

	float fDiffRotY;

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_E))
	{// ����]
		furniture->rotDest.y -= VALUE_ROTATE_FURNITURE;
		if (furniture->rotDest.y < -D3DX_PI)
		{
			furniture->rotDest.y += D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_R))
	{// �E��]
		furniture->rotDest.y += VALUE_ROTATE_FURNITURE;
		if (furniture->rotDest.y > D3DX_PI)
		{
			furniture->rotDest.y -= D3DX_PI * 2.0f;
		}
	}

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = furniture->rotDest.y - furniture->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	furniture->rot.y += fDiffRotY * RATE_ROTATE_FURNITURE;
	if (furniture->rot.y > D3DX_PI)
	{
		furniture->rot.y -= D3DX_PI * 2.0f;
	}
	if (furniture->rot.y < -D3DX_PI)
	{
		furniture->rot.y += D3DX_PI * 2.0f;
	}

	// �p�x���C��
	furniture->rot.y = PiCalculate360(furniture->rot.y);

}
//=============================================================================
// �Ƌ�̃X�P�[���g��E�k��
//=============================================================================
void FurnitureScaling(int no)
{
	FURNITURE *furniture = &furnitureWk[no];

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_I))
	{// �g��
		furniture->scl.x += VALUE_SCALE_FURNITURE;
		furniture->scl.y += VALUE_SCALE_FURNITURE;
		furniture->scl.z += VALUE_SCALE_FURNITURE;
	}
	if (GetKeyboardPress(DIK_J))
	{// �k��
		furniture->scl.x -= VALUE_SCALE_FURNITURE;
		furniture->scl.y -= VALUE_SCALE_FURNITURE;
		furniture->scl.z -= VALUE_SCALE_FURNITURE;
	}
}
