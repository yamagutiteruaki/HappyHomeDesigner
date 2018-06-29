//=============================================================================
//
// �X�R�A���� [rankscore.cpp]
// Author : 
//
//=============================================================================
#include "rankscore.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "input.h"
#include "ranking.h"
#include "rankpaper.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRankscore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureRankscore(int idx, int number);
void SetVertexRankScore(int no);


//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRankscore = {NULL};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankscore = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

RANKSCORE			rankscoreWk[RANKSCORE_MAX];

bool				g_bCheckScore;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRankscore(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKSCORE *rankscore = &rankscoreWk[0];

	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RANKSCORE,			// �t�@�C���̖��O
			&g_pD3DTextureRankscore);	// �ǂݍ��ރ������[
	}

	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		// �X�R�A�̏�����
		rankscore->rankscore = 0;
		rankscore->maxrankscore = 0;

		rankscore->pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	}

	g_bCheckScore=false;

	// ���_���̍쐬
	MakeVertexRankscore(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankscore(void)
{
	RANKSCORE *rankscore = &rankscoreWk[0];

	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		if (g_pD3DTextureRankscore != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureRankscore->Release();
			g_pD3DTextureRankscore = NULL;
		}

		if (g_pD3DVtxBuffRankscore != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffRankscore->Release();
			g_pD3DVtxBuffRankscore = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankscore(void)
{
	RANKSCORE *ras = &rankscoreWk[0];
	RANKING *rank = GetRanking(0);

	if (g_bCheckScore == false)
	{
		Ranking();
		g_bCheckScore = true;
	}

	for (int i = 0; i < RANKSCORE_MAX; i++, ras++,rank++)
	{
		ras->rankscore = rank->score;
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			int number;

			number = (ras->rankscore % (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));

			nCntPlace += NUM_PLACE*i;
			SetTextureRankscore(nCntPlace, number);
			nCntPlace -= NUM_PLACE*i;

		}
		SetVertexRankScore(i);

		PrintDebugProc("[�X�R�A %d�ʁF(%g)]\n",i+1,ras->rankscore );
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKSCORE *rankscore = &rankscoreWk[0];


	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffRankscore, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);


		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureRankscore);

		// �|���S���̕`��
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4+(i*4* NUM_PLACE)), NUM_POLYGON);
		}

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureRankscore);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_PLACE*4 * RANKSCORE_MAX, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRankscore(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE*RANKSCORE_MAX ),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRankscore,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankscore->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < RANKSCORE_MAX; i++)
		{
			RANKSCORE *ras = &rankscoreWk[i];
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);

				// rhw�̐ݒ�
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse =
					pVtx[1].diffuse =
					pVtx[2].diffuse =
					pVtx[3].diffuse = SetColorPallet(COLOR_PALLET_BROWN);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
			}
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankscore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRankscore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffRankscore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffRankscore->Unlock();
}



void SetVertexRankScore(int no)
{


	RANKSCORE *ras = &rankscoreWk[no];
	RANKPAPER *paper = GetRankPaper(no);

	ras->pos.x = paper->pos.x + RANKSCORE_POS_X;
	ras->pos.y = paper->pos.y + RANKSCORE_POS_Y;

	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffRankscore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4*11);

	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankscore->Unlock();

	}

	PrintDebugProc("[�X�R�A���W %d�ʁFX(%f) Y(%f) Z(%f)]\n", no+1, ras->pos.x,ras->pos.y,ras->pos.z);

}