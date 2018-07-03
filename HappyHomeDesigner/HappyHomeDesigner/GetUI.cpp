//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : 
//
//=============================================================================
#include "GetUI.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debugproc.h"
#include "stage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGetUI(LPDIRECT3DDEVICE9 pDevice);
void SetVertexGetUI(float alpha);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGetUI = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffGetUI = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldGetUI;			// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posGetUI;					// �ʒu
D3DXVECTOR3				g_sclGetUI;					// �X�P�[��
D3DXVECTOR3				g_moveGetUI;				// �ړ���
bool					g_bUse;
float					g_fUIalpha;



//=============================================================================
// ����������
//=============================================================================
HRESULT InitGetUI(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexGetUI(pDevice);

	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BILLBOARD,			// �t�@�C���̖��O
			&g_pD3DTextureGetUI);	// �ǂݍ��ރ������[
	}
	g_posGetUI = D3DXVECTOR3(0.0f, 18.0f, 0.0f);
	g_sclGetUI = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_moveGetUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bUse = false;
	g_fUIalpha = 1.0f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGetUI(void)
{
	if (g_pD3DTextureGetUI != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGetUI->Release();
		g_pD3DTextureGetUI = NULL;
	}

	if (g_pD3DVtxBuffGetUI != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffGetUI->Release();
		g_pD3DVtxBuffGetUI = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGetUI(void)
{
	if (g_bUse == true)
	{
		g_posGetUI.y += 0.3f;
		g_fUIalpha -= 0.01f;

		if (g_fUIalpha <= 0.0f)
		{
			g_bUse = false;
			g_fUIalpha = 1.0f;
		}
	}
	SetVertexGetUI(g_fUIalpha);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	if (g_bUse == true)
	{
		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X���擾
		mtxView = GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldGetUI);

		// �|���S���𐳖ʂɌ�����
		D3DXMatrixInverse(&g_mtxWorldGetUI, NULL, &mtxView);
		g_mtxWorldGetUI._41 = 0.0f;
		g_mtxWorldGetUI._42 = 0.0f;
		g_mtxWorldGetUI._43 = 0.0f;
		

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, g_sclGetUI.x,
			g_sclGetUI.y,
			g_sclGetUI.z);
		D3DXMatrixMultiply(&g_mtxWorldGetUI,
			&g_mtxWorldGetUI, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_posGetUI.x,
			g_posGetUI.y,
			g_posGetUI.z);
		D3DXMatrixMultiply(&g_mtxWorldGetUI,
			&g_mtxWorldGetUI, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGetUI);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffGetUI, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureGetUI);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexGetUI(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffGetUI,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffGetUI->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffGetUI->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexGetUI(float alpha)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffGetUI->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffGetUI->Unlock();
	}
}

void SetGetUI(D3DXVECTOR3 pos)
{
	g_bUse = true;
	g_posGetUI = D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z);
	g_fUIalpha = 1.0f;
}