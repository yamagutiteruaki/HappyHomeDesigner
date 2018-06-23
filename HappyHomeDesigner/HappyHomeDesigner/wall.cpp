//=============================================================================
//
// �n�ʏ��� [wall.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "wall.h"
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

HRESULT MakeVertexWall(LPDIRECT3DDEVICE9 pDevice,int no);



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureWall[WALL_MAX*WALL_KIND];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWall[WALL_MAX*WALL_KIND];	// ���_�o�b�t�@�ւ̃|�C���^

WALL					g_aWall[WALL_MAX*WALL_KIND];

const char *FileNameWall[WALL_KIND] =
{
	TEXTURE_WALL,		// ��1
	TEXTURE_WALL1,		// ��2
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWall(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WALL *wall = GetWall(0);


	for (int i = 0; i < WALL_KIND*WALL_MAX; i++, wall++)
	{
		FIELD *field = GetField(i/4);

		wall->Pos.x = 0.0f;	//X���W�̐ݒ�
		wall->Pos.y = -(field->Size.x) / 2;//Y���W��0�Œ�
		wall->Pos.z = WALL_SIZE_Z/((i/4)+1);//Z���W�̐ݒ�

		wall->Rot.x = -D3DX_PI / 2;
		wall->Rot.y = (D3DX_PI / 2)*i ;

		wall->Size.x = field->Size.x;
		wall->Size.y = 0.0f;
		wall->Size.z = wall->Pos.z*2;

	}

	if (nType == STAGE_INIT_FAST)
	{
		for (int i = 0; i < WALL_KIND*WALL_MAX; i++)
		{

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				FileNameWall[i / 4],			// �t�@�C���̖��O
				&g_pD3DTextureWall[i]);	// �ǂݍ��ރ������[

			MakeVertexWall(pDevice, i);

		}
	}
		return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	for (int i = 0; i < WALL_KIND*WALL_MAX; i++)
	{
		//�t�B�[���h
		if (g_pD3DTextureWall != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureWall[i]->Release();
			g_pD3DTextureWall[i] = NULL;
		}

		if (g_pD3DVtxBuffWall != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffWall[i]->Release();
			g_pD3DVtxBuffWall[i] = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;


	int no;
	if (GetStage() == STAGE_GAME)
	{
		no = 0;
	}
	else
	{
		no = 4;
	}
		WALL *wall = GetWall(no);
for (int i=no; i < no+4; i++, wall++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&wall->world);


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, wall->Pos.x, wall->Pos.y, wall->Pos.z);
		D3DXMatrixMultiply(&wall->world, &wall->world, &mtxTranslate);

		//��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, wall->Rot.y, wall->Rot.x, wall->Rot.z);
		D3DXMatrixMultiply(&wall->world, &wall->world, &mtxRot);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &wall->world);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffWall[i], 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureWall[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexWall(LPDIRECT3DDEVICE9 pDevice,int no)
{

	WALL *wall = GetWall(no);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* WALL_MAX*WALL_KIND,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffWall[no],		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffWall[no]->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < WALL_MAX*WALL_KIND; i++, pVtx += 4)

		{

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-wall->Size.x /2, 0.0f, wall->Size.z /2);
			pVtx[1].vtx = D3DXVECTOR3(wall->Size.x /2, 0.0f, wall->Size.z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-wall->Size.x / 2, 0.0f, -wall->Size.z / 2);
			pVtx[3].vtx = D3DXVECTOR3(wall->Size.x / 2, 0.0f, -wall->Size.z / 2);

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
		g_pD3DVtxBuffWall[no]->Unlock();
	}

	return S_OK;
}

WALL *GetWall(int no)
{
	return &g_aWall[no];
}
