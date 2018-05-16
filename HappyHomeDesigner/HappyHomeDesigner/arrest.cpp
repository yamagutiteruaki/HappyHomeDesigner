//=============================================================================
//
// �G���� [arrest.cpp]
// Author : ��������
//
//=============================================================================
#include "main.h"
#include "arrest.h"
#include "clock.h"
#include "player.h"
#include "field.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "voice.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexArrest(int no);
void SetTextureArrest(int no, int cntPattern);
void SetVertexArrest(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureArrest = NULL;		// �e�N�X�`���ւ̃|���S��

ARREST					arrestWk[ARREST_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitArrest(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = arrestWk;				// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ARREST,				// �t�@�C���̖��O
			&g_pD3DTextureArrest);			// �ǂݍ��ރ������̃|�C���^
	}
	int cnt = 0;
	// �G�l�~�[�̏���������
	for (int i = 0; i < ARREST_MAX; i++, arrest++, cnt++)
	{
		arrest->use = true;										// �g�p
		arrest->pos = D3DXVECTOR3(SCREEN_WIDTH-TEXTURE_ARREST_SIZE_X, 50+100*i, 0.0f);	// ���W�f�[�^��������
		arrest->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		arrest->cnt_frame = 0;									// �t���[���𐔂�����
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ARREST_SIZE_X, TEXTURE_ARREST_SIZE_Y);
		arrest->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		arrest->BaseAngle = atan2f(TEXTURE_ARREST_SIZE_Y, TEXTURE_ARREST_SIZE_X);	// �G�l�~�[�̊p�x��������

		arrest->Texture = g_pD3DTextureArrest;					// �e�N�X�`�����
		MakeVertexArrest(i);										// ���_���̍쐬
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitArrest(void)
{
	if (g_pD3DTextureArrest != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureArrest->Release();
		g_pD3DTextureArrest = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateArrest(void)
{

	ARREST *arrest = arrestWk;				// �G�l�~�[�̃|�C���^�[��������
	VOICE *voice = GetVoice(0);

	for (int i = 0; i < ARREST_MAX; i++, arrest++)
	{
			SetVertexArrest(i);	// �ړ���̍��W�Œ��_��ݒ�
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawArrest(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = arrestWk;				// �G�l�~�[�̃|�C���^�[��������
	VOICE *voice = GetVoice(0);

										// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < voice->count; i++, arrest++)
	{
		if (arrest->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, arrest->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ARREST, arrest->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexArrest(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = &arrestWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexArrest(no);

	// rhw�̐ݒ�
	arrest->vertexWk[0].rhw =
		arrest->vertexWk[1].rhw =
		arrest->vertexWk[2].rhw =
		arrest->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	arrest->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	arrest->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	arrest->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST, 0.0f);
	arrest->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST);
	arrest->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST);

	//arrest->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//arrest->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//arrest->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//arrest->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureArrest(int no, int cntPattern)
{
	ARREST *arrest = &arrestWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ARREST;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ARREST;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST;

	arrest->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	arrest->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	arrest->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	arrest->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexArrest(int no)
{
	ARREST *arrest = &arrestWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	arrest->vertexWk[0].vtx.x = arrest->pos.x - cosf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[0].vtx.y = arrest->pos.y - sinf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[0].vtx.z = 0.0f;

	arrest->vertexWk[1].vtx.x = arrest->pos.x + cosf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[1].vtx.y = arrest->pos.y - sinf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[1].vtx.z = 0.0f;

	arrest->vertexWk[2].vtx.x = arrest->pos.x - cosf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[2].vtx.y = arrest->pos.y + sinf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[2].vtx.z = 0.0f;

	arrest->vertexWk[3].vtx.x = arrest->pos.x + cosf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[3].vtx.y = arrest->pos.y + sinf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ARREST *GetArrest(int no)
{
	return(&arrestWk[no]);
}
