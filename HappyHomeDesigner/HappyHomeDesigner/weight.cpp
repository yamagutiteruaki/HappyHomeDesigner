//=============================================================================
//
// �^�C�}�[���� [weight.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "weight.h"
#include "input.h"
#include "clock.h"
#include "player.h"
#include "stage.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexWeight(LPDIRECT3DDEVICE9 pDevice); 

void SetVertexWeight(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureWeight = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWeight = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureWeightMeter = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWeightMeter = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
float					Power;
float					PowerDest;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitWeight(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//use = true;										// �g�p
	Power = 0.0f;
	PowerDest = 0.0f;
	MakeVertexWeight(pDevice);										// ���_���̍쐬

	if (type == STAGE_INIT_FAST)
	{
		// �e�N�X�`���[�̏��������s��
// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_WEIGHT,				// �t�@�C���̖��O
			&g_pD3DTextureWeight);			// �ǂݍ��ރ������̃|�C���^

												// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_WEIGHT2,				// �t�@�C���̖��O
			&g_pD3DTextureWeightMeter);			// �ǂݍ��ރ������̃|�C���^
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWeight(void)
{
	if (g_pD3DTextureWeight != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureWeight->Release();
		g_pD3DTextureWeight = NULL;
	}

	if (g_pD3DVtxBuffWeight != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffWeight->Release();
		g_pD3DVtxBuffWeight = NULL;
	}

	if (g_pD3DTextureWeightMeter != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureWeightMeter->Release();
		g_pD3DTextureWeightMeter = NULL;
	}

	if (g_pD3DVtxBuffWeightMeter != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffWeightMeter->Release();
		g_pD3DVtxBuffWeightMeter = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWeight(void)
{
	PLAYER *player = GetPlayer(0);

	PowerDest = ((float)player->weight/WT_MAX)-Power;

	Power += (float)(PowerDest / 30);


	//if (GetKeyboardPress(DIK_P))
	//{
	//	if (Power < 1.0)
	//	{
	//		Power = Power + 0.01f;
	//	}
	//	else
	//	{
	//		Power = 0.0f;
	//	}
	//}
	SetVertexWeight();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWeight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffWeight, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureWeight);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_WEIGHT);


		//���[�^�[
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffWeightMeter, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureWeightMeter);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_WEIGHT);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexWeight(LPDIRECT3DDEVICE9 pDevice)
{

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffWeight,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffWeight->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3( 0.0f , 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( TEXTURE_WEIGHT_SIZE_X, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3( 0.0f , TEXTURE_WEIGHT_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( TEXTURE_WEIGHT_SIZE_X, TEXTURE_WEIGHT_SIZE_Y, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffWeight->Unlock();
	}


	//�Ԃ̎�
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffWeightMeter,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffWeightMeter->Lock(0, 0, (void**)&pVtx, 0);

		//// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f , TEXTURE_WEIGHT_SIZE_Y/2+Power, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f + TEXTURE_WEIGHT_SIZE_X , TEXTURE_WEIGHT_SIZE_Y/2+Power, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f , TEXTURE_WEIGHT_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f + TEXTURE_WEIGHT_SIZE_X , TEXTURE_WEIGHT_SIZE_Y, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffWeightMeter->Unlock();
	}

	return S_OK;

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetVertexWeight(void)
{

	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffWeightMeter->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(0.0f, TEXTURE_WEIGHT_SIZE_Y-(Power*TEXTURE_WEIGHT_X), 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(0.0f + TEXTURE_WEIGHT_SIZE_X, TEXTURE_WEIGHT_SIZE_Y - (Power * TEXTURE_WEIGHT_Y), 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, TEXTURE_WEIGHT_SIZE_Y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(0.0f + TEXTURE_WEIGHT_SIZE_X, TEXTURE_WEIGHT_SIZE_Y, 0.0f);


	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - Power);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - Power);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f );
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f );


	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffWeightMeter->Unlock();

}

