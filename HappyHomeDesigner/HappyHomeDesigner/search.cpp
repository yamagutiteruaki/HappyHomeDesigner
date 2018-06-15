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
#include "voice.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSearch(void);
void SetSearchParts(void);
void SearchMove(void);
void SearchRotation(void);
void SearchCollision(void);
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

	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{
		// �ʒu�A�����̏����ݒ�
		search->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->rotBasis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->scl = D3DXVECTOR3(1.0f * 1, 1.0f * 1, 1.0f * 1);
		search->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		search->use = false;

		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		search->num = 0;

		search->cos = 0.0f;
		search->sita = 0.0f;

	}
	// �e�q�֌W�̐ݒ�
	SetSearchParts();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitSearch(void)
{
	if (g_pD3DTextureSearch != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSearch->Release();
		g_pD3DTextureSearch = NULL;
	}
	if (g_pD3DVtxBuffSearch != NULL)
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
	// ���G�͈͂̈ړ�
	SearchMove();
	// ���G�͈͂̉�]
	SearchRotation();
	// ���G����
	SearchCollision();
	// ���_�̍쐬
	MakeVertexSearch();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SEARCH *search = &searchWk[0];

	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{
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
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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
		pVtx[0].vtx = D3DXVECTOR3(-7.0f, 0.0f, -10.0f);
		pVtx[1].vtx = D3DXVECTOR3(7.0f, 0.0f, -10.0f);
		pVtx[2].vtx = D3DXVECTOR3(-(SEARCH_LENGTH * sinf(SEARCH_ANGLE / 2.0f)), 0.0f, -SEARCH_LENGTH);		// ANGLE��LENGTH
		pVtx[3].vtx = D3DXVECTOR3(SEARCH_LENGTH * sinf(SEARCH_ANGLE / 2.0f), 0.0f, -SEARCH_LENGTH);			// �ɂ���Ď����I�Ɍ`�ς��

																											// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);

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
//=============================================================================
// ���G�͈͐e�q�֌W�ݒ�֐�
//=============================================================================
void SetSearchParts(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	// �{�̂ɍ��G�͈͂��֘A�t����
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{	// �g�p��Ԃ̃|���X�ɂ̂ݍ��G�͈͂��Z�b�g
		if (!police->use) continue;
		// ���g�p�̍��G�͈͂��Z�b�g
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{	// ���g�p�̃`�F�b�N
			if (search->use) continue;
			// �{�̂Ɠ����ԍ����Z�b�g
			search->num = police->num;
			// �g�p��Ԃɂ���
			search->use = true;
			break;
		}
	}
}
//=============================================================================
// ���G�͈͂̈ړ��֐�
//=============================================================================
void SearchMove(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	// �{�̂Ɛe�q�֌W�̍��G�͈͂��ړ�
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// ���G�͈͂̈ړ�
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{
			if (!search->use) continue;
			if (search->num == police->num)
			{	// �{�̂̍��W�̂ق�̏�����ɃZ�b�g
				search->Eye.x = police->Eye.x;
				search->Eye.y = police->Eye.y + 0.1f;
				search->Eye.z = police->Eye.z;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				search->fangleY = police->fangleY;
				// �{�̂Ɠ����i�s�x�N�g�����擾
				search->move = police->move;
				break;
			}
		}
	}
}
//=============================================================================
// ���G�͈͂̉�]�֐�
//=============================================================================
void SearchRotation(void)
{
	SEARCH *search = &searchWk[0];

	// ��]�N�H�[�^�j�I���𐶐�
	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{	// Y����](�|���X�Ɠ��������Ɍ�������)
		D3DXQuaternionRotationAxis(&search->qRotateY, &search->axisY, search->fangleY);
	}
}
//=============================================================================
// ���G�����֐�
//=============================================================================
void SearchCollision(void)
{
	SEARCH *search = &searchWk[0];
	PLAYER *player = GetPlayer(0);
	VOICE *voice = GetVoice(0);
	POLICE *police = GetPolice(0);

	// ������O����
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// �g�p��Ԃ̃v���C���[�̂ݔ���
		if (!player->use) continue;
		// �|�C���^������
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{	// �g�p��Ԃ̍��G�͈͂̂ݔ���
			if (!search->use) continue;
			// �|���X�̐i�s�x�N�g��(���ʂ̃x�N�g��)���擾
			D3DXVECTOR3 vecA = search->move;
			// �|���X����v���C���[�ւ̃x�N�g�������߂�
			D3DXVECTOR3 vecB = (player->Eye - search->Eye);
			// ���ꂼ��̃x�N�g���̒��������߂�
			float lenA = D3DXVec3Length(&vecA);
			float lenB = D3DXVec3Length(&vecB);
			// �����I�ɔ͈͓��̉\�������邩�𔻒�
			if (!(lenB < SEARCH_LENGTH)) continue;
			// ���ςƃx�N�g���̒�������cos�����߂�
			search->cos = D3DXVec3Dot(&vecA, &vecB) / (lenA*lenB);
			// �v���C���[�ƃ|���X�̑O��̈ʒu�֌W���`�F�b�N(�v���C���[���|���X�̌��Ȃ��̏����X�L�b�v)
			if (search->cos < 0) continue;
			// cos����i�s�x�N�g���ƃv���C���[�ւ̃x�N�g���̂Ȃ��p�����߂�
			search->sita = acosf(search->cos);
			// �Ȃ��p���|���X���G����p�̓񕪂̈�ȉ��Ȃ王����ɂ���
			if (search->sita < (SEARCH_ANGLE / 2.0f))
			{	// ������Ƀv���C���[�������ꍇ�̏���
				// �v���C���[������
				//player->use = false;
				// �����N�̃A���`��
				voice->use = true;

				// �|���X�̓������~�߂�
				police = GetPolice(0);
				for (int k = 0; k < POLICE_MAX; k++, police++)
				{	// �|���X�̈ړ��t���O��false��
					//police->movef = false;
				}
			}
		}
	}
}