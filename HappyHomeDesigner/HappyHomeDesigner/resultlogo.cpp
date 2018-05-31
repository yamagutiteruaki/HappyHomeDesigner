//=============================================================================
//
// ���U���g��ʏ��� [resultlogo.cpp]
// Author : GP12B295 �K �֌��V��
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "debugproc.h"
#include "stage.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice);
void SetTextureScore(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResult = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo2 = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultLogo2 = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
//LPDIRECT3DTEXTURE9		g_pD3DTextureResultClear = NULL;	// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultClear = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultGameOver = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultGameOver = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultScore = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
VERTEX_2D				g_vertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

D3DXVECTOR3				g_posScore;						// �|���S���̈ړ���

int						g_nScore;						// �X�R�A

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexResultLogo(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT,							// �t�@�C���̖��O
		&g_pD3DTextureResult);					// �ǂݍ��ރ������[

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT_LOGO2,					// �t�@�C���̖��O
		&g_pD3DTextureResultLogo2);				// �ǂݍ��ރ������[

												// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
	//	TEXTURE_RESULT_CLEAR,					// �t�@�C���̖��O
	//	&g_pD3DTextureResultClear);				// �ǂݍ��ރ������[

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT_GAMEOVER,					// �t�@�C���̖��O
		&g_pD3DTextureResultGameOver);				// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SCORE00,				// �t�@�C���̖��O
		&g_pD3DTextureScore);				// �ǂݍ��ރ������̃|�C���^

	g_posScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	g_nScore = 0;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultLogo(void)
{
	if (g_pD3DTextureResult != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureResult->Release();
		g_pD3DTextureResult = NULL;
	}

	if (g_pD3DVtxBuffResult != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResult->Release();
		g_pD3DVtxBuffResult = NULL;
	}

	if (g_pD3DTextureResultLogo2 != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureResultLogo2->Release();
		g_pD3DTextureResultLogo2 = NULL;
	}

	if (g_pD3DVtxBuffResultLogo2 != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultLogo2->Release();
		g_pD3DVtxBuffResultLogo2 = NULL;
	}

	//if (g_pD3DTextureResultClear != NULL)
	//{	// �e�N�X�`���̊J��
	//	g_pD3DTextureResultClear->Release();
	//	g_pD3DTextureResultClear = NULL;
	//}

	//if (g_pD3DVtxBuffResultClear != NULL)
	//{	// ���_�o�b�t�@�̊J��
	//	g_pD3DVtxBuffResultClear->Release();
	//	g_pD3DVtxBuffResultClear = NULL;
	//}

	if (g_pD3DTextureResultGameOver != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureResultGameOver->Release();
		g_pD3DTextureResultGameOver = NULL;
	}

	if (g_pD3DVtxBuffResultGameOver != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultGameOver->Release();
		g_pD3DVtxBuffResultGameOver = NULL;
	}


	if (g_pD3DTextureScore != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}

	if (g_pD3DVtxBuffResultScore != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultScore->Release();
		g_pD3DVtxBuffResultScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultLogo(void)
{

	PrintDebugProc("[�N���A��  �F(%d)]\n", GetGameEnd());

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	//// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	//pDevice->SetStreamSource(0, g_pD3DVtxBuffResultClear, 0, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureResultClear);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultGameOver, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultGameOver);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultLogo2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultLogo2);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore);

	// �X�R�A
	for (i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkScore[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResult,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffResult->Unlock();
	}


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultGameOver,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultGameOver->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT/2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f);

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
		g_pD3DVtxBuffResultGameOver->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultLogo2,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultLogo2->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, RESULT_LOGO2_HEIGHT / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULT_LOGO2_WIDTH, RESULT_LOGO2_HEIGHT / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, RESULT_LOGO2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULT_LOGO2_WIDTH, RESULT_LOGO2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffResultLogo2->Unlock();
	}

	int i;
	float habaX = 16.0f;	// �����̉���

							// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultScore,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 3, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 3, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// ��������������
		for (i = 0; i < SCORE_DIGIT; i++)
		{
			// ���_���W�̐ݒ�
			g_vertexWkScore[i][0].vtx.x = -habaX * i + g_posScore.x;
			g_vertexWkScore[i][0].vtx.y = g_posScore.y;
			g_vertexWkScore[i][0].vtx.z = 0.0f;
			g_vertexWkScore[i][1].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			g_vertexWkScore[i][1].vtx.y = g_posScore.y;
			g_vertexWkScore[i][1].vtx.z = 0.0f;
			g_vertexWkScore[i][2].vtx.x = -habaX * i + g_posScore.x;
			g_vertexWkScore[i][2].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			g_vertexWkScore[i][2].vtx.z = 0.0f;
			g_vertexWkScore[i][3].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			g_vertexWkScore[i][3].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			g_vertexWkScore[i][3].vtx.z = 0.0f;
			//g_vertexWkScore[i][4].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][4].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][4].vtx.z = 0.0f;
			//g_vertexWkScore[i][5].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][5].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][5].vtx.z = 0.0f;
			//g_vertexWkScore[i][6].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][6].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][6].vtx.z = 0.0f;
			//g_vertexWkScore[i][7].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][7].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][7].vtx.z = 0.0f;
			//g_vertexWkScore[i][8].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][8].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][8].vtx.z = 0.0f;
			//g_vertexWkScore[i][9].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][9].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][9].vtx.z = 0.0f;

			// rhw�̐ݒ�
			g_vertexWkScore[i][0].rhw =
				g_vertexWkScore[i][1].rhw =
				g_vertexWkScore[i][2].rhw =
				g_vertexWkScore[i][3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			g_vertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`�����W�̐ݒ�
			g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_vertexWkScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_vertexWkScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
//void SetTextureScore(void)
//{
//	int i;
//	int number = g_nScore;
//
//	for (i = 0; i < SCORE_DIGIT; i++)
//	{
//		// �e�N�X�`�����W�̐ݒ�
//		float x = (float)(number % 10);
//		g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
//		g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
//		g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
//		g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
//		number /= 10;
//	}
//
//
//	return S_OK;
//}

	
