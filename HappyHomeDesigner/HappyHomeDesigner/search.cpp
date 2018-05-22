//=============================================================================
//
// ���G�͈͕`�揈�� [search.cpp]
// Author : GP12A295-19-���_��
//
//=============================================================================
#include "search.h"
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
#include "collision.h"
#include "calculate.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSearch(D3DXVECTOR3 pos);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSearch = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSearch = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldSearch;			// ���[���h�}�g���b�N�X
SEARCH					searchWk[SEARCH_MAX];		// �T�[�`�i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSearch(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	SEARCH *search = &searchWk[0];

	if (nType == STAGE_INIT_FAST)
	{

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SEARCH,			// �t�@�C���̖��O
			&g_pD3DTextureSearch);	// �ǂݍ��ރ������[
	}
		// �ʒu�A�����̏����ݒ�
		search->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		search->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->rotBasis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		search->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSearch(void)
{
	if(g_pD3DTextureSearch != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSearch->Release();
		g_pD3DTextureSearch = NULL;
	}

	if(g_pD3DVtxBuffSearch != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffSearch->Release();
		g_pD3DVtxBuffSearch = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSearch(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	search->Eye.x = police->Eye.x;
	search->Eye.y = police->Eye.y + 0.1f;
	search->Eye.z = police->Eye.z;


	// ���_�̍쐬
	MakeVertexSearch(police->Eye);

	// Y����]�p�x���|���X�ƈ�v������
	search->fangleY = police->fangleY;

	// ��]�N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationAxis(&search->qRotateY, &search->axisY, search->fangleY);		// Y����]�N�H�[�^�j�I������(At�Ɍ�������)


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	D3DXMATRIX mtxRot, mtxTranslate;
	SEARCH *search = &searchWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldSearch);
	// ���[���h�}�g���b�N�X�쐬
	D3DXMatrixTransformation(&g_mtxWorldSearch, NULL, NULL, &search->scl, &search->rotBasis, &search->qRotateY, &search->Eye);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSearch);
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffSearch, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureSearch);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSearch(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffSearch,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSearch->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].vtx = D3DXVECTOR3(10.0f,  0.0f, 10.0f);
		pVtx[2].vtx = D3DXVECTOR3(-50.0f, 0.0f, -100.0f);
		pVtx[3].vtx = D3DXVECTOR3(50.0f,  0.0f, -100.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = 
		pVtx[1].diffuse = 
		pVtx[2].diffuse = 
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSearch->Unlock();
	}
	return S_OK;
}

