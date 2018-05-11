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

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureHome [HOME_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome [HOME_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

FIELD					g_aField[FIELD_MAX];
HOME					g_aHome[HOME_MAX];

LPD3DXMESH			g_pD3DXMeshHome[HOME_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatHome[HOME_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatHome[HOME_MAX];				// �������̑���

const char *FileNameHome[HOME_MAX] =
{
	"data/MODEL/HOUSE/house00.x",		// ��1
	"data/MODEL/HOUSE/house00.x",		// ��2
	"data/MODEL/HOUSE/house00.x",		// ��3
	"data/MODEL/HOUSE/house00.x",		// ����
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);
	HOME  *home = GetHome(0);
	{
		MakeVertexField(pDevice);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FIELD,			// �t�@�C���̖��O
			&g_pD3DTextureField);	// �ǂݍ��ރ������[
									// �e�N�X�`���̓ǂݍ���

									// �e�N�X�`���̓ǂݍ���

	}


	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		field->Pos.x =0.0f;	//X���W�̐ݒ�
		field->Pos.y = 0.0f;//Y���W��0�Œ�
		field->Pos.z =0.0f;	//Z���W�̐ݒ�

	}

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

		home->Pos.x = -120.0f+i%2*240;	//X���W�̐ݒ�
		home->Pos.y = 0.0f;//Y���W�̐ݒ�
		home->Pos.z = 150.0f + i / 2 * (-240);	//Z���W�̐ݒ�

		home->Rot.y = D3DX_PI / 2 ;
	;

	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{

	//�t�B�[���h
	if (g_pD3DTextureField != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
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

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{

	//HOME  *home = GetHome(0);

	//for (int i = 0; i < HOME_MAX; i++, home++)
	//{
	//	home->Rot.x +=i* 0.1f;
	//	home->Rot.y +=i* 0.01f;
	//	home->Rot.z +=i* 0.001f;

	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DXMATERIAL matDef;

	FIELD *field = GetField(0);
	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&field->world);


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &field->world);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureField);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	HOME *home = GetHome(0);
	for (int i = 0; i < HOME_MAX; i++, home++)
	{
		// ���C�g��on
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&home->world);

		//// �X�P�[���𔽉f
		//D3DXMatrixScaling(&mtxScale, enemy->scl.x,
		//	enemy->scl.y,
		//	enemy->scl.z);
		//D3DXMatrixMultiply(&g_mtxWorldEnemy,
		//	&g_mtxWorldEnemy, &mtxScale);


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

		for (int j = 0; j < (int) g_nNumMatHome[i]; j++ )
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

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//for (int i = 0; i < FIELD_MAX; i++)
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < FIELD_MAX; i++, pVtx += 4)

		{

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);

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
		g_pD3DVtxBuffField->Unlock();
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