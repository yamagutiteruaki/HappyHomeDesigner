//=============================================================================
//
// �~�j�}�b�v���� [miniField.cpp]
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
HRESULT SetVertexPlayerPoint(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
// �~�j�}�b�v�t���[���p
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapFrame = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapFrame = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
MINI_FRAME				miniFrameWk[MINIMAP_FRAME_MAX];			// �~�j�}�b�v�t�B�[���h�\���̔z��
// �~�j�}�b�v�t�B�[���h�p
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapField = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapField = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
MINI_FIELD				miniFieldWk[MINIMAP_FIELD_MAX];			// �~�j�}�b�v�t�B�[���h�\���̔z��
// �~�j�}�b�v�v���C���[���W�p
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapPlayer = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapPlayer = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
MINI_PLAYER				miniPlayerWk[MINIMAP_PLAYER_MAX];		// �~�j�}�b�v�v���C���[�\���̔z��
// ���̑�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMinimap(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINI_FRAME *miniFrame = &miniFrameWk[0];										// �~�j�}�b�v�t���[���̃|�C���^�[������
	MINI_FIELD *miniField = &miniFieldWk[0];										// �~�j�}�b�v�t�B�[���h�̃|�C���^�[������
	MINI_PLAYER *miniPlayer = &miniPlayerWk[0];										// �~�j�}�b�v�v���C���[�̃|�C���^�[������

	if (type == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		// �~�j�}�b�v�t���[��
		D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�̃|�C���^
			TEXTURE_MINIMAP_FRAME,													// �t�@�C���̖��O
			&g_pD3DTextureMinimapFrame);											// �ǂݍ��ރ������̃|�C���^
		// �~�j�}�b�v�t�B�[���h
		D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�̃|�C���^
			TEXTURE_MINIMAP_FIELD,													// �t�@�C���̖��O
			&g_pD3DTextureMinimapField);											// �ǂݍ��ރ������̃|�C���^
		// �~�j�}�b�v�v���C���[���W
		D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�̃|�C���^
			TEXTURE_MINIMAP_PLAYER,													// �t�@�C���̖��O
			&g_pD3DTextureMinimapPlayer);											// �ǂݍ��ރ������̃|�C���^
	}
	// �~�j�}�b�v�t���[���̏���������
	for (int i = 0; i < MINIMAP_FRAME_MAX; i++, miniFrame++)
	{
		miniFrame->use = true;														// �g�p
	}
	// �~�j�}�b�v�t�B�[���h�̏���������
	for (int i = 0; i < MINIMAP_FIELD_MAX; i++, miniField++)
	{
		miniField->use = true;														// �g�p
	}
	// �~�j�}�b�v�v���C���[�̏���������
	for (int i = 0; i < MINIMAP_PLAYER_MAX; i++, miniPlayer++)
	{
		miniPlayer->use = true;														// �g�p
		miniPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �~�j�}�b�v�v���C���[���W�̏�����
		miniPlayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �~�j�}�b�v�v���C���[��]�̏�����
	}

	MakeVertexMinimap();															// ���_���̍쐬

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitMinimap(void)
{
	// �~�j�}�b�v�t���[��
	if (g_pD3DTextureMinimapFrame != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMinimapFrame->Release();
		g_pD3DTextureMinimapFrame = NULL;
	}
	if (g_pD3DVtxBuffMinimapFrame != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffMinimapFrame->Release();
		g_pD3DVtxBuffMinimapFrame = NULL;
	}
	// �~�j�}�b�v�t�B�[���h
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
	// �~�j�}�b�v�v���C���[���W
	if (g_pD3DTextureMinimapPlayer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureMinimapPlayer->Release();
		g_pD3DTextureMinimapPlayer = NULL;
	}
	if (g_pD3DVtxBuffMinimapPlayer != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffMinimapPlayer->Release();
		g_pD3DVtxBuffMinimapPlayer = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMinimap(void)
{
	MINI_FIELD *miniField = &miniFieldWk[0];				// �~�j�}�b�v�̃|�C���^�[��������

	SetVertexPlayerPoint(0);								// �~�j�}�b�v�v���C���̍��W�X�V



}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINI_FRAME *miniFrame = &miniFrameWk[0];				// �~�j�}�b�v�t���[���̃|�C���^�[������
	MINI_FIELD *miniField = &miniFieldWk[0];				// �~�j�}�b�v�̃|�C���^�[��������
	MINI_PLAYER *miniPlayer = &miniPlayerWk[0];				// �~�j�}�b�v�v���C���[�̃|�C���^�[������

	// �~�j�}�b�v�t���[���`��
	for (int i = 0; i < MINIMAP_FRAME_MAX; i++, miniFrame++)
	{
		if (miniFrame->use == true)					// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapFrame, 0, sizeof(VERTEX_2D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureMinimapFrame);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		}
	}
	// �~�j�}�b�v�t�B�[���h�`��
	for (int i = 0; i < MINIMAP_FIELD_MAX; i++, miniField++)
	{
		if (miniField->use == true)					// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapField, 0, sizeof(VERTEX_2D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureMinimapField);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		}
	}
	// �~�j�}�b�v�v���C���`��
	for (int i = 0; i < MINIMAP_PLAYER_MAX; i++, miniPlayer++)
	{
		if (miniPlayer->use == true)					// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapPlayer, 0, sizeof(VERTEX_2D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureMinimapPlayer);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}
//=============================================================================
// �~�j�}�b�v�t�B�[���h�擾�֐�
//=============================================================================
MINI_FIELD *GetMiniField(int no)
{
	return(&miniFieldWk[no]);
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �~�j�}�b�v�t���[��
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffMinimapFrame,											// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	{
		VERTEX_2D *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffMinimapFrame->Lock(0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X - TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y - TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X + TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y - TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X - TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y + TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X + TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y + TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
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
		g_pD3DVtxBuffMinimapFrame->Unlock();
	}
	// �~�j�}�b�v�t�B�[���h
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
	{
		VERTEX_2D *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffMinimapField->Lock(0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X - TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y - TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X + TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y - TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X - TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y + TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X + TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y + TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
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
	}
	// �~�j�}�b�v�v���C���[���W
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffMinimapPlayer,											// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	{
		VERTEX_2D *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffMinimapPlayer->Lock(0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X - TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y - TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X + TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y - TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X - TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y + TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X + TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y + TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
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
		g_pD3DVtxBuffMinimapPlayer->Unlock();
	}

	return S_OK;
}
//=============================================================================
// �~�j�}�b�v���v���C���[���_���W�̐ݒ�
//=============================================================================
HRESULT SetVertexPlayerPoint(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer(0);

	// �~�j�}�b�v�v���C���[���W
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffMinimapPlayer,											// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffMinimapPlayer->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W�̐ݒ�
	pVtx[0].vtx.x = (player->Eye.x * MAP_RATIO) - TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[0].vtx.y = (-player->Eye.z * MAP_RATIO) - TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y ;
	pVtx[0].vtx.z = 0.0f;

	pVtx[1].vtx.x = (player->Eye.x * MAP_RATIO) + TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[1].vtx.y = (-player->Eye.z * MAP_RATIO) - TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y ;
	pVtx[1].vtx.z = 0.0f;

	pVtx[2].vtx.x = (player->Eye.x * MAP_RATIO) - TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[2].vtx.y = (-player->Eye.z * MAP_RATIO) + TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y ;
	pVtx[2].vtx.z = 0.0f;

	pVtx[3].vtx.x = (player->Eye.x * MAP_RATIO) + TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[3].vtx.y = (-player->Eye.z * MAP_RATIO) + TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y ;
	pVtx[3].vtx.z = 0.0f;



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
	g_pD3DVtxBuffMinimapPlayer->Unlock();

#ifdef _DEBUG
	PrintDebugProc("[�~�j�}�b�v�v���C�����_���W0 �F(%f : %f : %f)]\n", pVtx[0].vtx.x, pVtx[0].vtx.y, pVtx[0].vtx.z);
	PrintDebugProc("[�~�j�}�b�v�v���C�����_���W1 �F(%f : %f : %f)]\n", pVtx[1].vtx.x, pVtx[1].vtx.y, pVtx[1].vtx.z);
	PrintDebugProc("[�~�j�}�b�v�v���C�����_���W2 �F(%f : %f : %f)]\n", pVtx[2].vtx.x, pVtx[2].vtx.y, pVtx[2].vtx.z);
	PrintDebugProc("[�~�j�}�b�v�v���C�����_���W3 �F(%f : %f : %f)]\n", pVtx[3].vtx.x, pVtx[3].vtx.y, pVtx[3].vtx.z);
#endif
	return S_OK;
}