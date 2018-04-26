//=============================================================================
//
// ���U���g��ʏ��� [resultlogo.cpp]
// Author : GP12B295 �K �֌��V��
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultlogo(LPDIRECT3DDEVICE9 pDevice);
void SetColorResultlogoLogo(void);
void SetTextureResultlogologo(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogoLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogoLogo = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogologo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogologo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


int						g_nCountAppearResultlogo = 0;		// �o���܂ł̑҂�����
int						g_nCountWaitResultlogo = 0;			// �҂�����
float					g_fAlphaResultlogo = 0.0f;			// ���U���g���S�̃��l
bool					g_bResultFade;



//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultlogo(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResultlogo = 0;
	g_nCountWaitResultlogo = 0;
	g_fAlphaResultlogo = 0.0f;
	g_bResultFade = false;



	// ���_���̍쐬
	MakeVertexResultlogo(pDevice);


	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO,				// �t�@�C���̖��O
			&g_pD3DTextureResultlogo);		// �ǂݍ��ރ������[

											// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO_LOGO,		// �t�@�C���̖��O
			&g_pD3DTextureResultlogoLogo);	// �ǂݍ��ރ������[

											// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO_LOGO2		// �ǂݍ��ރ������[
			,		// �t�@�C���̖��O
			&g_pD3DTextureResultlogologo);	// �ǂݍ��ރ������[


	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultlogo(void)
{
	if (g_pD3DTextureResultlogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultlogo->Release();
		g_pD3DTextureResultlogo = NULL;
	}

	if (g_pD3DVtxBuffResultlogo != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultlogo->Release();
		g_pD3DVtxBuffResultlogo = NULL;
	}

	if (g_pD3DTextureResultlogoLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultlogoLogo->Release();
		g_pD3DTextureResultlogoLogo = NULL;
	}

	if (g_pD3DVtxBuffResultlogoLogo != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultlogoLogo->Release();
		g_pD3DVtxBuffResultlogoLogo = NULL;
	}

	if (g_pD3DTextureResultlogologo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultlogologo->Release();
		g_pD3DTextureResultlogologo = NULL;
	}

	if (g_pD3DVtxBuffResultlogologo != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultlogologo->Release();
		g_pD3DVtxBuffResultlogologo = NULL;
	}



}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultlogo(void)
{
	g_nCountAppearResultlogo++;
	if (g_nCountAppearResultlogo >= COUNT_APPERA_RESULTLOGO)
	{
		if (g_fAlphaResultlogo < 1.0f)
		{
			g_fAlphaResultlogo += 0.05f;
			if (g_fAlphaResultlogo >= 1.0f)
			{
				g_fAlphaResultlogo = 1.0f;
			}

			SetColorResultlogoLogo();
		}
	}


	//SetTextureResultlogologo(GetStageWinPlayer());
	//SetTextureResultlogologo(1);


	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(1, BUTTON_C) || IsButtonTriggered(0, BUTTON_C))
	{// Enter��������A�t�F�[�h�A�E�g���ă��[�h��؂�ւ�����
		if (!g_bResultFade)
		{
			g_bResultFade = true;
			SetSe(SE_BUTTON, E_DS8_FLAG_NONE, CONTINUITY_ON);
			SetFade(FADE_OUT, STAGE_TITLE);
		}
	}

	g_nCountWaitResultlogo++;
	if (g_nCountWaitResultlogo == LIMIT_COUNT_WAIT)
	{
		if (!g_bResultFade)
		{
			g_bResultFade = true;
			SetFade(FADE_OUT, STAGE_TITLE);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultlogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogoLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultlogoLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogologo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultlogologo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);




}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultlogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultlogo,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogo->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffResultlogo->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultlogoLogo,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogoLogo->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X - RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y - RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X + RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y - RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X - RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y + RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X + RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y + RESULTLOGO_LOGO_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogoLogo->Unlock();
	}


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultlogologo,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogologo->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X - RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y - RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X + RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y - RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X - RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y + RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X + RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y + RESULTLOGO_LOGO2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffResultlogologo->Unlock();
	}



	return S_OK;
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorResultlogoLogo(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogoLogo->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogoLogo->Unlock();
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureResultlogologo(int no)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogologo->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((no - 1)*0.5, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((no - 1)*0.5 + 0.5, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((no - 1)*0.5, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((no - 1)*0.5 + 0.5, 1.0f);


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogologo->Unlock();
	}



}

