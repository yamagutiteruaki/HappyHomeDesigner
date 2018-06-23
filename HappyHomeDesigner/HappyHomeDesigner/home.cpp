//=============================================================================
//
// �n�ʏ��� [field.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "home.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"
#include "fade.h"
#include "player.h"
#include "collision.h"


/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_LIMIT				(0)
#define HOUSE_LEN				(200.0f)
#define HOUSE_WID				(170.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void AreaHouse(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pD3DTextureHome[HOME_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome[HOME_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureDoor[HOME_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffDoor[HOME_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

HOME					g_aHome[HOME_MAX];
DOOR					g_aDoor[HOME_MAX];

LPD3DXMESH			g_pD3DXMeshHome[HOME_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatHome[HOME_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatHome[HOME_MAX];				// �������̑���

LPD3DXMESH			g_pD3DXMeshDoor[HOME_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatDoor[HOME_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatDoor[HOME_MAX];				// �������̑���

const char *FileNameHome[HOME_MAX] =
{
	"data/MODEL/HOUSE/house_nobi.x",		// ��1
	"data/MODEL/HOUSE/house_nobi.x",		// ��2
	"data/MODEL/HOUSE/house_nobi.x",		// ��3
	"data/MODEL/HOUSE/house03.x",		// ����
};

const char *FileNameDoor[HOME_MAX] =
{
	"data/MODEL/ITEM/doa.x",		// �h�A1
	"data/MODEL/ITEM/doa.x",		// �h�A2
	"data/MODEL/ITEM/doa.x",		// �h�A3
	"data/MODEL/ITEM/doa.x",		// �h�A4
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitHome(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOME  *home = GetHome(0);


	//�Ƃ̐ݒ�
	for (int i = 0; i < HOME_MAX; i++, home++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNameHome[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatHome[i],
				NULL,
				&g_nNumMatHome[i],
				&g_pD3DXMeshHome[i])))
			{
				return E_FAIL;
			}
		}

		home->Pos.x = -(HOME_DISTANCE)+i % 2 * (HOME_DISTANCE * 2);	//X���W�̐ݒ�
		home->Pos.y = 0.0f;//Y���W�̐ݒ�
		home->Pos.z = HOME_DISTANCE + i / 2 * (-HOME_DISTANCE * 2);	//Z���W�̐ݒ�

		home->Rot.y = D3DX_PI / 2;

		home->Scl.x = 1.0f;
		home->Scl.y = 1.0f;
		home->Scl.z = 1.0f;

		home->len = HOUSE_LEN;
		home->wid = HOUSE_WID;

	}

	home = GetHome(0);
	DOOR *door = GetDoor(0);
	//�h�A�̐ݒ�
	for (int i = 0; i < HOME_MAX; i++, door++, home++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNameDoor[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatDoor[i],
				NULL,
				&g_nNumMatDoor[i],
				&g_pD3DXMeshDoor[i])))
			{
				return E_FAIL;
			}
		}
		door->Pos.x = home->Pos.x + 70.0f*home->Scl.x;	//X���W�̐ݒ�
		door->Pos.y = home->Pos.y;		//Y���W�̐ݒ�
		door->Pos.z = home->Pos.z - 75.0f*home->Scl.z;	//Z���W�̐ݒ�


		door->Rot.y = 0.0f;

		door->Scl.x = 2.0f;
		door->Scl.y = 2.0f;
		door->Scl.z = 1.0f;

		door->Homeno = STAGE_HOUSE1 + i;
		door->Use = true;


	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHome(void)
{

	//��
	for (int i = 0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureHome[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureHome[i]->Release();
			g_pD3DTextureHome[i] = NULL;
		}

		if (g_pD3DXMeshHome[i] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshHome[i]->Release();
			g_pD3DXMeshHome[i] = NULL;
		}

		if (g_pD3DXBuffMatHome[i] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatHome[i]->Release();
			g_pD3DXBuffMatHome[i] = NULL;
		}

	}

	//�h�A
	for (int i = 0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureDoor[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureDoor[i]->Release();
			g_pD3DTextureDoor[i] = NULL;
		}

		if (g_pD3DXMeshDoor[i] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshDoor[i]->Release();
			g_pD3DXMeshDoor[i] = NULL;
		}

		if (g_pD3DXBuffMatDoor[i] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatDoor[i]->Release();
			g_pD3DXBuffMatDoor[i] = NULL;
		}

	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHome(void)
{
	AreaHouse();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{
		SetFade(FADE_OUT, STAGE_HOUSE1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F2))
	{
		SetFade(FADE_OUT, STAGE_HOUSE2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F3))
	{
		SetFade(FADE_OUT, STAGE_HOUSE3, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F4))
	{
		SetFade(FADE_OUT, STAGE_MYHOUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F5))
	{
		SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
#endif


	DOOR *door = GetDoor(0);
	HOME *home = GetHome(0);
	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++, door++)
		{
			door->Pos.x = home->Pos.x + 70.0f*home->Scl.x;	//X���W�̐ݒ�
			door->Pos.y = home->Pos.y;		//Y���W�̐ݒ�
			door->Pos.z = home->Pos.z - 75.0f*home->Scl.z;	//Z���W�̐ݒ�
			door->Use = true;
		}
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		for (int i = 0; i < HOME_MAX; i++, door++)
		{
			door->Pos = D3DXVECTOR3(90.0f, 0.0f, -125.0f);
			door->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (GetStage() == i + 4)
			{
				door->Use = true;
				PrintDebugProc("DOORNO: %d\n", door->Homeno);

			}
			else
			{
				door->Use = false;
			}
		}
	}
	//HOME *House = GetHome(0);
	//PrintDebugProc("House 0: %f, %f\n", (House + 0)->Pos.x, (House + 0)->Pos.z);
	//PrintDebugProc("House 1: %f, %f\n", (House + 1)->Pos.x, (House + 1)->Pos.z);
	//PrintDebugProc("House 2: %f, %f\n", (House + 2)->Pos.x, (House + 2)->Pos.z);
	//PrintDebugProc("House 3: %f, %f\n", (House + 3)->Pos.x, (House + 3)->Pos.z);
	//PrintDebugProc("\n");


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DXMATERIAL matDef;
	int fieldnum;

	if (GetStage() == STAGE_GAME)
	{
		fieldnum = 0;
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		fieldnum = 1;
	}

	HOME *home = GetHome(0);

	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++)
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&home->world);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, home->Scl.x,
				home->Scl.y,
				home->Scl.z);
			D3DXMatrixMultiply(&home->world,
				&home->world, &mtxScale);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, home->Rot.y, home->Rot.x, home->Rot.z);
			D3DXMatrixMultiply(&home->world, &home->world, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, home->Pos.x, home->Pos.y, home->Pos.z);
			D3DXMatrixMultiply(&home->world, &home->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &home->world);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef.MatD3D);



			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatHome[i]->GetBufferPointer();

			for (int j = 0; j < (int)g_nNumMatHome[i]; j++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureHome[i]);

				// �`��
				g_pD3DXMeshHome[i]->DrawSubset(j);
			}

			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


			//D3DXMATERIAL mat;
			//
			//mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			//mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef.MatD3D);
		}
	}

	DOOR *door = GetDoor(0);
	for (int i = 0; i < HOME_MAX; i++, home++, door++)
	{
		if (door->Use == true)
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&door->world);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, door->Scl.x,
				door->Scl.y,
				door->Scl.z);
			D3DXMatrixMultiply(&door->world,
				&door->world, &mtxScale);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, door->Rot.y, door->Rot.x, door->Rot.z);
			D3DXMatrixMultiply(&door->world, &door->world, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, door->Pos.x, door->Pos.y, door->Pos.z);
			D3DXMatrixMultiply(&door->world, &door->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &door->world);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef.MatD3D);



			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatDoor[i]->GetBufferPointer();

			for (int j = 0; j < (int)g_nNumMatDoor[i]; j++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureDoor[i]);

				// �`��
				g_pD3DXMeshDoor[i]->DrawSubset(j);
			}

			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


			//D3DXMATERIAL mat;
			//
			//mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			//mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef.MatD3D);
		}
	}
}



HOME *GetHome(int no)
{
	return &g_aHome[no];
}
DOOR *GetDoor(int no)
{
	return &g_aDoor[no];
}

//=============================================================================
// ��
//=============================================================================
void AreaHouse()
{
	PLAYER *player = GetPlayer(0);
	HOME *house = GetHome(0);

	for (int i = 0; i < HOME_MAX; i++, house++)
	{
		if (CollisionBoxToPos(house->Pos, player->Eye, D3DXVECTOR2((house->len / 2), (house->wid / 2))) == TRUE)
		{

			//player->Eye = player->tmpPos;

			//PlyColiObj(house->Pos, (house->len / 2), (house->wid / 2));

			CBTP_resetPos(
				&(player->Eye),
				player->posTmp,
				house->Pos,
				(house->len / 2),
				(house->wid / 2)
			);
		}

	}

}