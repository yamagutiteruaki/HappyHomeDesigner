//=============================================================================
//
// �^�C�}�[���� [clock.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "clock.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexClock(int no);
void SetVertexClock(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureClock = NULL;		// �e�N�X�`���ւ̃|���S��
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClock = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


CLOCK					clockWk[CLOCK_MAX];				// �^�C�}�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitClock(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// �^�C�}�[�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s��
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_CLOCK,				// �t�@�C���̖��O
			&g_pD3DTextureClock);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�}�[�̏���������
	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		clock->use = true;										// �g�p
		clock->pos = D3DXVECTOR3(150.0f, 100.0f, 0.0f);			// ���W�f�[�^��������
		clock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		clock->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		clock->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_CLOCK_SIZE_X, TEXTURE_CLOCK_SIZE_Y);
		clock->Radius = D3DXVec2Length(&temp);					// �^�C�}�[�̔��a��������
		clock->BaseAngle =1.0f* D3DX_PI;	// �^�C�}�[�̊p�x��������

		clock->Texture = g_pD3DTextureClock;					// �e�N�X�`�����
		MakeVertexClock(i);										// ���_���̍쐬
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
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffClock->Release();
		g_pD3DVtxBuffClock = NULL;
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
			
				clock->rot.z -= 1.0f;
			
			SetVertexClock(i);	// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawClock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// �^�C�}�[�̃|�C���^�[��������

	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffClock, 0, sizeof(VERTEX_2D));

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

	// ���_���W�̐ݒ�
	SetVertexClock(no);

	// rhw�̐ݒ�
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
void SetVertexClock(int no)
{
	CLOCK *clock = &clockWk[no];			// �^�C�}�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	clock->vertexWk[0].vtx.x = clock->pos.x - cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[0].vtx.y = clock->pos.y - sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[0].vtx.z = 0.0f;

	clock->vertexWk[1].vtx.x = clock->pos.x + cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[1].vtx.y = clock->pos.y - sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[1].vtx.z = 0.0f;

	clock->vertexWk[2].vtx.x = clock->pos.x - cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[2].vtx.y = clock->pos.y + sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[2].vtx.z = 0.0f;

	clock->vertexWk[3].vtx.x = clock->pos.x + cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[3].vtx.y = clock->pos.y + sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�}�[�擾�֐�
//=============================================================================
CLOCK *GetClock(int no)
{
	return(&clockWk[no]);
}


