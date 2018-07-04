//=============================================================================
//
// �~�j�}�b�v���� [minimap.cpp]
// Author : GP12A295-19-���_��
//
//=============================================================================
#include "main.h"
#include "minimap.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMinimap(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapField = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapField = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
MINIMAP					minimapWk[MINIMAP_MAX];					// �~�j�}�b�v�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMinimap(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINIMAP *minimap = &minimapWk[0];												// �~�j�}�b�v�̃|�C���^�[��������
	
	// �~�j�}�b�v�̏���������
	if (type == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�̃|�C���^
			TEXTURE_MINIMAP_FIELD,													// �t�@�C���̖��O
			&g_pD3DTextureMinimapField);											// �ǂݍ��ރ������̃|�C���^
		// �t�B�[���h
		for (int i = 0; i < MINIMAP_MAX; i++, minimap++)
		{
			minimap->use = true;													// �g�p
			minimap->pos = D3DXVECTOR3(MINIMAP_POS_X, MINIMAP_POS_Y, 0.0f);			// ���W�f�[�^��������
			minimap->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ��]�f�[�^��������
			MakeVertexMinimap();													// ���_���̍쐬
		}

	}


	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitMinimap(void)
{
	if (g_pD3DTextureMinimapField != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMinimapField->Release();
		g_pD3DTextureMinimapField = NULL;
	}
	if (g_pD3DVtxBuffMinimapField != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffMinimapField->Release();
		g_pD3DVtxBuffMinimapField = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMinimap(void)
{
	MINIMAP *minimap = &minimapWk[0];				// �~�j�}�b�v�̃|�C���^�[��������

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINIMAP *minimap = &minimapWk[0];				// �~�j�}�b�v�̃|�C���^�[��������

	for (int i = 0; i < MINIMAP_MAX; i++, minimap++)
	{
		if (minimap->use == true)					// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapField, 0, sizeof(VERTEX_2D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureMinimapField);
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MINIMAP, minimap->vertexWk, sizeof(VERTEX_2D));
		}
	}
	

}
//=============================================================================
// �~�j�}�b�v�擾�֐�
//=============================================================================
MINIMAP *GetMinimap(int no)
{
	return(&minimapWk[no]);
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �~�j�}�b�v�t�B�[���h�`��
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffMinimapField,											// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffMinimapField->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(MINIMAP_POS_X - MINIMAP_WIDTH, MINIMAP_POS_Y - MINIMAP_HEIGHT, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(MINIMAP_POS_X + MINIMAP_WIDTH, MINIMAP_POS_Y - MINIMAP_HEIGHT, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(MINIMAP_POS_X - MINIMAP_WIDTH, MINIMAP_POS_Y + MINIMAP_HEIGHT, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(MINIMAP_POS_X + MINIMAP_WIDTH, MINIMAP_POS_Y + MINIMAP_HEIGHT, 0.0f);
	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;
	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffMinimapField->Unlock();


	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerPoint(int no)
{
	PLAYER *player = GetPlayer(0);
	MINIMAP *minimap = &minimapWk[0];				// �~�j�}�b�v�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	//player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[0].vtx.z = 0.0f;

	//player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[1].vtx.z = 0.0f;

	//player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[2].vtx.z = 0.0f;

	//player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[3].vtx.z = 0.0f;
}
