//=============================================================================
//
// �G���� [button.cpp]
// Author : ��������
//
//=============================================================================
#include "main.h"
#include "button.h"
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
HRESULT MakeVertexButton(int no);
void SetVertexButton(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureButton[BUTTON_MAX] = { NULL ,NULL,NULL };		// �e�N�X�`���ւ̃|���S��

BUTTON					buttonWk[BUTTON_MAX];				// �G�l�~�[�\����

const char *FileNameButton[BUTTON_MAX] =
{
	TEXTURE_GAME_BUTTON_0,
	TEXTURE_GAME_BUTTON_3,
	TEXTURE_GAME_BUTTON_1,
	TEXTURE_GAME_BUTTON_2,
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitButton(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// �G�l�~�[�̃|�C���^�[��������


	if (type == STAGE_INIT_FAST)
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
				FileNameButton[i],				// �t�@�C���̖��O
				&g_pD3DTextureButton[i]);			// �ǂݍ��ރ������̃|�C���^

		}
	}										// �G�l�~�[�̏���������
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
		button->use = false;										// �g�p
		button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// ���W�f�[�^��������
		button->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		button->kind = 0;									// �t���[���𐔂�����
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BUTTON_SIZE_X, TEXTURE_BUTTON_SIZE_Y);
		button->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		button->BaseAngle = atan2f(TEXTURE_BUTTON_SIZE_Y, TEXTURE_BUTTON_SIZE_X);	// �G�l�~�[�̊p�x��������

		button->Texture = g_pD3DTextureButton[i];					// �e�N�X�`�����
		
		button->rate = D3DXVECTOR2(10,10);

																	// �e�N�X�`���̓ǂݍ���


		MakeVertexButton(i);										// ���_���̍쐬
	}






	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitButton(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (g_pD3DTextureButton != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureButton[i]->Release();
			g_pD3DTextureButton[i] = NULL;
		}
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateButton(void)
{

	BUTTON *button = buttonWk;				// �G�l�~�[�̃|�C���^�[��������
	VOICE *voice = GetVoice(0);
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{

		if (button->use == true)
		{
			if (button->rate.x > 0)
			{
				button->rate.x -= 0.5f;
			}
			if (button->pos.x < SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X;
				button->rate.x = 0;
			}
			else
			{
				button->pos.x -= 5 * button->rate.x;
			}

		}
		else
		{
			if (button->rate.x < 10)
			{
				button->rate.x += 0.5f;
			}
			if (button->pos.x > SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X;
				button->rate.x = 10;
				button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// ���W�f�[�^��������
			}
			else
			{
				button->pos.x += 5 * button->rate.x;
			}


		}
		SetVertexButton(i);	// �ړ���̍��W�Œ��_��ݒ�
	}


	if (buttonWk[ENTER_BUTTON].use == true || buttonWk[GET_BUTTON].use == true|| buttonWk[EXIT_BUTTON].use == true)
	{
		if (buttonWk[PUT_BUTTON].rate.y > 0)
		{
			buttonWk[PUT_BUTTON].rate.y -= 0.5f;
		}
		if (buttonWk[PUT_BUTTON].pos.y < SCREEN_HEIGHT - (3 * TEXTURE_BUTTON_SIZE_Y))
		{
			buttonWk[PUT_BUTTON].pos.y = SCREEN_HEIGHT - (3 * TEXTURE_BUTTON_SIZE_Y);
			buttonWk[PUT_BUTTON].rate.y = 0;
		}
		else
		{
			buttonWk[PUT_BUTTON].pos.y -= 5 * buttonWk[PUT_BUTTON].rate.y;
		}

	}
	else if (buttonWk[ENTER_BUTTON].use == false && buttonWk[GET_BUTTON].use == false)
	{
		if (buttonWk[PUT_BUTTON].rate.y < 10)
		{
			buttonWk[PUT_BUTTON].rate.y += 0.5f;
		}
		if (buttonWk[PUT_BUTTON].pos.y >= SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y)
		{
			buttonWk[PUT_BUTTON].pos.y = SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y;
			buttonWk[PUT_BUTTON].rate.y = 10;
		}
		else
		{
			buttonWk[PUT_BUTTON].pos.y += 5 * buttonWk[PUT_BUTTON].rate.y;
		}


	}
	SetVertexButton(PUT_BUTTON);	// �ړ���̍��W�Œ��_��ݒ�

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// �G�l�~�[�̃|�C���^�[��������
	VOICE *voice = GetVoice(0);


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, button->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BUTTON, button->vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexButton(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = &buttonWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexButton(no);

	// rhw�̐ݒ�
	button->vertexWk[0].rhw =
		button->vertexWk[1].rhw =
		button->vertexWk[2].rhw =
		button->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	button->vertexWk[0].diffuse =
		button->vertexWk[1].diffuse =
		button->vertexWk[2].diffuse =
		button->vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	button->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	button->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexButton(int no)
{
	BUTTON *button = &buttonWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	button->vertexWk[0].vtx.x = button->pos.x - cosf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[0].vtx.y = button->pos.y - sinf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[0].vtx.z = 0.0f;

	button->vertexWk[1].vtx.x = button->pos.x + cosf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[1].vtx.y = button->pos.y - sinf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[1].vtx.z = 0.0f;

	button->vertexWk[2].vtx.x = button->pos.x - cosf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[2].vtx.y = button->pos.y + sinf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[2].vtx.z = 0.0f;

	button->vertexWk[3].vtx.x = button->pos.x + cosf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[3].vtx.y = button->pos.y + sinf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BUTTON *GetButton(int no)
{
	return(&buttonWk[no]);
}

//========================================================
// �{�^���̕\���@false�Ȃ�true���Atrue�Ȃ�false���B
//========================================================
void Button(bool flag,int no)
{
	BUTTON *button = &buttonWk[no];				// �G�l�~�[�̃|�C���^�[��������

	button->use = flag;
}
