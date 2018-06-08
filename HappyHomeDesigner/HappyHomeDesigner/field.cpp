//=============================================================================
//
// �n�ʏ��� [field.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "field.h"
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
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void AreaHouse(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField[FIELD_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField[FIELD_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureHome [HOME_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome [HOME_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureDoor[HOME_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffDoor[HOME_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

FIELD					g_aField[FIELD_MAX];
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
const char *FileNameField[FIELD_MAX] =
{
	TEXTURE_FIELD,		// ��1
	TEXTURE_FIELD1,		// ��2
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);
	HOME  *home = GetHome(0);

	for (int i = 0; i < FIELD_MAX; i++, field++)
	{

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			FileNameField[i],			// �t�@�C���̖��O
			&g_pD3DTextureField[i]);	// �ǂݍ��ރ������[


		field->Pos.x = 0.0f;	//X���W�̐ݒ�
		field->Pos.y = 0.0f;//Y���W��0�Œ�
		field->Pos.z = 0.0f;	//Z���W�̐ݒ�

		field->Size = D3DXVECTOR3(FIELD_SIZE_X / (i*3 + 1), 0.0f, FIELD_SIZE_Z / (i*3 + 1));
		//field->Size = D3DXVECTOR3(FIELD_SIZE_X/2, 0.0f, FIELD_SIZE_Z/2);

	}
		MakeVertexField(pDevice);

	//�Ƃ̐ݒ�
	for (int i = 0; i < HOME_MAX; i++, home++)
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

		home->Pos.x = -(HOME_DISTANCE) + i % 2 * (HOME_DISTANCE*2);	//X���W�̐ݒ�
		home->Pos.y = 0.0f;//Y���W�̐ݒ�
		home->Pos.z = HOME_DISTANCE + i / 2 * (-HOME_DISTANCE *2);	//Z���W�̐ݒ�

		home->Rot.y = D3DX_PI / 2 ;

		home->Scl.x = 1.0f;
		home->Scl.y = 1.0f;
		home->Scl.z = 1.0f;

		home->len = HOUSE_LEN;
		home->wid = HOUSE_WID;

	}

	home = GetHome(0);
	DOOR *door = GetDoor(0);
	//�h�A�̐ݒ�
	for (int i = 0; i < HOME_MAX; i++, door++ ,home++)
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

		door->Pos.x = home->Pos.x+70.0f*home->Scl.x;	//X���W�̐ݒ�
		door->Pos.y = home->Pos.y;		//Y���W�̐ݒ�
		door->Pos.z = home->Pos.z -75.0f*home->Scl.z;	//Z���W�̐ݒ�


		door->Rot.y = 0.0f;
		
		door->Scl.x = 2.0f;
		door->Scl.y = 2.0f;
		door->Scl.z = 1.0f;

		door->Homeno = STAGE_HOUSE1 + i;


	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		//�t�B�[���h
		if (g_pD3DTextureField != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureField[i]->Release();
			g_pD3DTextureField[i] = NULL;
		}

		if (g_pD3DVtxBuffField != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffField[i]->Release();
			g_pD3DVtxBuffField[i] = NULL;
		}
	}

	//��
	for ( int i=0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureHome[i]!= NULL)
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
void UpdateField(void)
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

	//HOME *House = GetHome(0);
	//PrintDebugProc("House 0: %f, %f\n", (House + 0)->Pos.x, (House + 0)->Pos.z);
	//PrintDebugProc("House 1: %f, %f\n", (House + 1)->Pos.x, (House + 1)->Pos.z);
	//PrintDebugProc("House 2: %f, %f\n", (House + 2)->Pos.x, (House + 2)->Pos.z);
	//PrintDebugProc("House 3: %f, %f\n", (House + 3)->Pos.x, (House + 3)->Pos.z);
	//PrintDebugProc("\n");

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
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
	FIELD *field = GetField(fieldnum);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&field->world);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
	D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &field->world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField[fieldnum], 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureField[fieldnum]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	HOME *home = GetHome(0);

	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++)
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

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


		DOOR *door = GetDoor(0);
		for (int i = 0; i < HOME_MAX; i++, home++, door++)
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

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{	
	FIELD *field = GetField(0);
	VERTEX_3D *pVtx;
	for (int i = 0; i < FIELD_MAX; i++, field++, pVtx += 4)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffField[i],		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}
		//for (int i = 0; i < FIELD_MAX; i++)
		{//���_�o�b�t�@�̒��g�𖄂߂�

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffField[i]->Lock(0, 0, (void**)&pVtx, 0);



			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[1].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[2].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, -field->Size.z / 2);
				pVtx[3].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, -field->Size.z / 2);

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse =
					pVtx[1].diffuse =
					pVtx[2].diffuse =
					pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			// ���_�f�[�^���A�����b�N����
			g_pD3DVtxBuffField[i]->Unlock();
		}
	}
	return S_OK;
}

FIELD *GetField(int no)
{
	return &g_aField[no];
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