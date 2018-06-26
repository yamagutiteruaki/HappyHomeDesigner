
//***********************************************************
//timeeffect.cpp
// 
//
//***********************************************************
#include "main.h"
#include "timeeffect.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "clock.h"
#include "sound.h"

//***********************************************************
// �v���g�^�C�v�錾
//***********************************************************
HRESULT MakeVertexTimeeffect(LPDIRECT3DDEVICE9 pDevice);

//***********************************************************
//�O���[�o���錾
//***********************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimeeff = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimeeff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

void SetColor(void);

float					g_fAlpha;
bool					g_bAlpha;
bool					g_bUseEffect;

//***********************************************************
// ����������
//***********************************************************
HRESULT InitTimeeffect(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	MakeVertexTimeeffect(pDevice);							//���_���̍쐬

	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TIME_EFF,				// �t�@�C���̖��O
			&g_pD3DTextureTimeeff);		// �ǂݍ��ރ������[
	}
	g_fAlpha = 0.0f;
	g_bAlpha = false;
	g_bUseEffect = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimeeffect(void)
{
	if (g_pD3DTextureTimeeff != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTimeeff->Release();
		g_pD3DTextureTimeeff = NULL;
	}

	if (g_pD3DVtxBuffTimeeff!= NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffTimeeff->Release();
		g_pD3DVtxBuffTimeeff = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimeeffect(void)
{
	CLOCK *clock = GetClock(0);

	if (clock->rot.z > WARNING_TIME
		&& g_bUseEffect ==false)
	{
		g_bUseEffect = true;
		g_bAlpha = true;

	}
	else if (clock->rot.z <= WARNING_TIME)
	{
		g_bUseEffect = false;
		g_bAlpha = false;
		g_fAlpha = 0.0f;
	}
	
	if (g_bUseEffect == true)
	{
		if (g_bAlpha == true)
		{
			g_fAlpha += ALPHA_RATE;
			if (g_fAlpha >= ALPHA_MAX)
			{
				g_bAlpha = false;
			}
		}
		else if (g_bAlpha == false)
		{
			g_fAlpha -= ALPHA_RATE;
			if (g_fAlpha <= 0.0f)
			{
				g_bAlpha = true;
			}
		}

		SetSe(SE_CHIME, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}

	SetColor();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimeeffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_bUseEffect==true)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffTimeeff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureTimeeff);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTimeeffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffTimeeff,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTimeeff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTimeeff->Unlock();
	}
	return S_OK;
}

//===========================================================================
//�F�Z�b�g
//===========================================================================
void SetColor(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTimeeff->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fAlpha);



		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTimeeff->Unlock();
	}


}