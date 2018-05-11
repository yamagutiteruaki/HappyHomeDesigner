//=============================================================================
//
// �^�C�}�[���� [clock.cpp]
// Author : GP12B295 �K �֌��V��
//
//=============================================================================
#include "main.h"
#include "clock.h"
#include "input.h"
#include "fade.h"
#include "stage.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexClock(int no);
void SetVertexClockHand(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureClock = NULL;				// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClock = NULL;				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureClockHand = NULL;			// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClockHand = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


CLOCK					clockWk[CLOCK_MAX];				// �^�C�}�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitClock(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// �^�C�}�[�̃|�C���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_CLOCK,				// �t�@�C���̖��O
		&g_pD3DTextureClock);			// �ǂݍ��ރ������̃|�C���^


	// �^�C�}�[�̏���������
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_CLOCKHAND,				// �t�@�C���̖��O
			&g_pD3DTextureClockHand);			// �ǂݍ��ރ������̃|�C���^
	}

	// �j�̏���������
	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		clock->use = true;										// �g�p
		clock->pos = D3DXVECTOR3(CLOCK_POS_X, CLOCK_POS_Y, 0.0f);			// ���W�f�[�^��������
		clock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ��]�f�[�^��������
		clock->PatternAnim = 0;												// �A�j���p�^�[���ԍ��������_���ŏ�����
		clock->CountAnim = 0;												// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_CLOCKHAND_SIZE_X, TEXTURE_CLOCKHAND_SIZE_Y);
		clock->Radius = D3DXVec2Length(&temp);					// �j�̔��a��������
		clock->BaseAngle = atan2f(TEXTURE_CLOCKHAND_SIZE_Y, TEXTURE_CLOCKHAND_SIZE_X);	// �j�̊p�x��������

		clock->Texture = g_pD3DTextureClockHand;					// �e�N�X�`�����
		MakeVertexClock(i);											// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitClock(void)
{
	if (g_pD3DTextureClock != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureClock->Release();
		g_pD3DTextureClock = NULL;
	}

	if (g_pD3DVtxBuffClock != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffClock->Release();
		g_pD3DVtxBuffClock = NULL;
	}


	if (g_pD3DTextureClockHand != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureClockHand->Release();
		g_pD3DTextureClockHand = NULL;
	}

	if (g_pD3DVtxBuffClockHand != NULL)
	{	// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffClockHand->Release();
		g_pD3DVtxBuffClockHand = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateClock(void)
{
	CLOCK *clock = clockWk;				// �^�C�}�[�̃|�C���^�[��������

	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			
			clock->rot.z += 0.01f;
			
			SetVertexClockHand(i);		// �ړ���̍��W�Œ��_��ݒ�

		}
		//if (clock->rot.z > D3DX_PI * 2)
		//{
		//	SetFade(FADE_OUT, STAGE_RESULT);
		//}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawClock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// �^�C�}�[�̃|�C���^�[��������

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffClock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureClock);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffClockHand, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, clock->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLOCK, clock->vertexWk, sizeof(VERTEX_2D));
		
		

		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexClock(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = &clockWk[no];			// �^�C�}�[�̃|�C���^�[��������

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffClock,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffClock->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(CLOCK_POS_X - CLOCK_WIDTH, CLOCK_POS_Y - CLOCK_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(CLOCK_POS_X + CLOCK_WIDTH, CLOCK_POS_Y - CLOCK_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(CLOCK_POS_X - CLOCK_WIDTH, CLOCK_POS_Y + CLOCK_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(CLOCK_POS_X + CLOCK_WIDTH, CLOCK_POS_Y + CLOCK_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffClock->Unlock();
	}


	// ���_���W�̐ݒ�
	SetVertexClockHand(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	clock->vertexWk[0].rhw =
	clock->vertexWk[1].rhw =
	clock->vertexWk[2].rhw =
	clock->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	clock->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	clock->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	clock->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	clock->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	clock->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexClockHand(int no)
{
	CLOCK *clock = &clockWk[no];			// �^�C�}�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	clock->vertexWk[0].vtx.x = clock->pos.x - cosf(clock->BaseAngle+clock->rot.z) * clock->Radius;
	clock->vertexWk[0].vtx.y = clock->pos.y - sinf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[0].vtx.z = 0.0f;

	clock->vertexWk[1].vtx.x = clock->pos.x + cosf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[1].vtx.y = clock->pos.y - sinf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[1].vtx.z = 0.0f;

	clock->vertexWk[2].vtx.x = clock->pos.x - cosf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[2].vtx.y = clock->pos.y + sinf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[2].vtx.z = 0.0f;

	clock->vertexWk[3].vtx.x = clock->pos.x + cosf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[3].vtx.y = clock->pos.y + sinf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�}�[�擾�֐�
//=============================================================================
CLOCK *GetClock(int no)
{
	return(&clockWk[no]);
}


