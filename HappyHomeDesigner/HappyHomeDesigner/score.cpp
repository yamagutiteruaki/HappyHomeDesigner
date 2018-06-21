//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "input.h"
#include "ranking.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureScore(int idx, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				g_posScore;						// �ʒu
D3DXVECTOR3				g_rotScore;						// ����

long long			g_score;						// �\���X�R�A
long long			g_maxscore;						//�擾�X�R�A

int slotTimer ;									//�X���b�g�^�C�}�[
int slotCount ;									//�X���b�g����
bool slotStart;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�R�A�̏�����
	g_score = 0;
	g_maxscore = 0;

	slotTimer = 0;
	slotCount = 0;
	slotStart = false;

	// ���_���̍쐬
	MakeVertexScore(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,			// �t�@�C���̖��O
		&g_pD3DTextureScore[0]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if (g_pD3DTextureScore[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureScore[0]->Release();
		g_pD3DTextureScore[0] = NULL;
	}
	if (g_pD3DTextureScore[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureScore[1]->Release();
		g_pD3DTextureScore[1] = NULL;
	}

	if (g_pD3DVtxBuffScore != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffScore->Release();
		g_pD3DVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{

	g_maxscore = GetPrice();	//��Q���z�̎擾

	long long slotadd=0;		//�X���b�g���Z��

	slotTimer++;				//�^�C�}�[���Z
	
	if(slotTimer>60)
	{
		slotStart = true;
		slotTimer = 0;
	}
	if (slotStart == true)
	{
		for (int i = 0; i < NUM_PLACE - slotCount; i++)
		{

			slotadd = (long long)(powf(10.0f, (float)(NUM_PLACE - i - 1)));//���Z���o
			g_score += slotadd;

			if (GetKeyboardTrigger(DIK_LSHIFT))//���o�X�L�b�v
			{
				g_score = g_maxscore;
				slotCount = NUM_PLACE;
			}

		}

		int number;
		int number2;

		number = (g_score % (long long)(powf(10.0f, (float)(slotCount + 1)))) / (long long)(powf(10.0f, (float)(slotCount)));	//�w�茅�m�F
		number2 = (g_maxscore % (long long)(powf(10.0f, (float)(slotCount + 1)))) / (long long)(powf(10.0f, (float)(slotCount)));//�w�茅�m�F

		if (slotTimer > SLOT_INTERVAL && number == number2)//���o�X�g�b�v����
		{
			slotCount++;
			slotTimer = 0;
		}
		else if (slotTimer == NUM_PLACE)
		{
			g_score = g_maxscore;
		}

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			int number;

			number = (g_score % (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
			SetTextureScore(nCntPlace, number);
		}
	}
	PrintDebugProc("[�X�R�A �F(%g)]\n", g_score);
	PrintDebugProc("[��Q���z �F(%g)]\n", g_maxscore);

	if (GetKeyboardTrigger(DIK_4))
	{
		// �����L���Ocsv�X�V
		Ranking();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// �|���S���̕`��
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffScore,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = 
			pVtx[1].diffuse = 
			pVtx[2].diffuse = 
			pVtx[3].diffuse = SetColorPallet(COLOR_PALLET_CYAN);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffScore->Unlock();
}

