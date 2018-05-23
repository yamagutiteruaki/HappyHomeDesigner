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
void SetTextureButton(int no, int cntPattern);
void SetVertexButton(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureButton = NULL;		// �e�N�X�`���ւ̃|���S��

BUTTON					buttonWk[BUTTON_MAX];				// �G�l�~�[�\����
float rate;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitButton(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`���[�̏��������s���H
	if (button->kind == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BUTTON_0,				// �t�@�C���̖��O
			&g_pD3DTextureButton);			// �ǂݍ��ރ������̃|�C���^
	}
	if (button->kind == 1)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BUTTON_1,				// �t�@�C���̖��O
			&g_pD3DTextureButton);			// �ǂݍ��ރ������̃|�C���^
	}
	if (button->kind == 2)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BUTTON_2,				// �t�@�C���̖��O
			&g_pD3DTextureButton);			// �ǂݍ��ރ������̃|�C���^
	}

	rate = 10;

	// �G�l�~�[�̏���������
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
		button->use = false;										// �g�p
		button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X,SCREEN_HEIGHT-TEXTURE_BUTTON_SIZE_Y, 0.0f);	// ���W�f�[�^��������
		button->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		button->kind = 0;									// �t���[���𐔂�����
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BUTTON_SIZE_X, TEXTURE_BUTTON_SIZE_Y);
		button->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		button->BaseAngle = atan2f(TEXTURE_BUTTON_SIZE_Y, TEXTURE_BUTTON_SIZE_X);	// �G�l�~�[�̊p�x��������

		button->Texture = g_pD3DTextureButton;					// �e�N�X�`�����
		MakeVertexButton(i);										// ���_���̍쐬
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitButton(void)
{
	if (g_pD3DTextureButton != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureButton->Release();
		g_pD3DTextureButton = NULL;
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
		if (GetKeyboardTrigger(DIK_Q))
		{
			SetFade(FADE_OUT, STAGE_HOUSE2);
		}
#ifdef DEBUG
		if (GetKeyboardTrigger(DIK_B))
		{
			Button();
		}
#endif

		if (button->use == true)
		{
			if (rate > 0)
			{
				rate -= 0.5f;
			}
			if (button->pos.x < SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X;
				rate = 0;
			}
			else
			{
				button->pos.x -= 5 * rate;
			}

		}
		else
		{

			button->use = false;
			rate = 10;

			button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// ���W�f�[�^��������
		}
		SetVertexButton(i);	// �ړ���̍��W�Œ��_��ݒ�
	}

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
	button->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	button->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON, 0.0f);
	button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON);
	button->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON);

	//button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//button->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//button->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureButton(int no, int cntPattern)
{
	BUTTON *button = &buttonWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON;

	button->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	button->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	button->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	button->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
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
bool Button(void)
{
	BUTTON *button = buttonWk;				// �G�l�~�[�̃|�C���^�[��������

	return button->use = button->use ? false : true;
	//return button->use = true;

}
