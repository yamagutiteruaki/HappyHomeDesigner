//=============================================================================
//
// �G���� [voice.cpp]
// Author : ��������
//
//=============================================================================
#include "main.h"
#include "voice.h"
#include "clock.h"
#include "player.h"
#include "field.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "arrest.h"
#include <time.h>
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexVoice(int no);
void SetTextureVoice(int no, int cntPattern);
void SetVertexVoice(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureVoice = NULL;		// �e�N�X�`���ւ̃|���S��

VOICE					voiceWk[VOICE_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitVoice(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = voiceWk;				// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_VOICE,				// �t�@�C���̖��O
			&g_pD3DTextureVoice);			// �ǂݍ��ރ������̃|�C���^
	}
	int cnt = 0;
	// �G�l�~�[�̏���������
	for (int i = 0; i < VOICE_MAX; i++, voice++, cnt++)
	{
		voice->use = false;										// �g�p
		voice->pos = D3DXVECTOR3(SCREEN_WIDTH*2, 350.0f, 0.0f);	// ���W�f�[�^��������
		voice->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		voice->cnt_frame = 0;									// �t���[���𐔂�����
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_VOICE_SIZE_X, TEXTURE_VOICE_SIZE_Y);
		voice->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		voice->BaseAngle = atan2f(TEXTURE_VOICE_SIZE_Y, TEXTURE_VOICE_SIZE_X);	// �G�l�~�[�̊p�x��������
		voice->count = 0;

		voice->Texture = g_pD3DTextureVoice;					// �e�N�X�`�����
		MakeVertexVoice(i);										// ���_���̍쐬
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitVoice(void)
{
	if (g_pD3DTextureVoice != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureVoice->Release();
		g_pD3DTextureVoice = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateVoice(void)
{

	VOICE *voice = voiceWk;				// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer(0);
	FIELD *field = GetField(0);
	CAMERA *camera = GetCamera();


	for (int i = 0; i < VOICE_MAX; i++, voice++)
	{

		if (GetKeyboardTrigger(DIK_V))
		{
			voice->use = voice->use ? false : true;
		}
		if (voice->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			voice->cnt_frame++;
			if (voice->cnt_frame >= 60)
			{
				if (voice->count == ARREST_MAX)
				{
					SetFade(FADE_OUT, STAGE_RESULT);
				}
				else
				{
					SetFade(FADE_OUT, STAGE_GAME);
				}

				if (GetFade() == FADE_IN)
				{
					player->Eye = field->Pos;
					player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					camera->rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					voice->use = false;
					voice->count++;
				}
			}
			if (voice->pos.x > SCREEN_CENTER_X)
			{
				voice->pos.x -= VOICE_SPEED;
			}
			if (voice->pos.x < SCREEN_CENTER_X)
			{
				voice->pos.x += VOICE_SPEED/5;
			}
		

			SetVertexVoice(i);	// �ړ���̍��W�Œ��_��ݒ�
		}
		else
		{
			voice->pos = D3DXVECTOR3(SCREEN_WIDTH * 2, 350.0f, 0.0f);
			voice->cnt_frame = 0;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawVoice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = voiceWk;				// �G�l�~�[�̃|�C���^�[��������

										// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < VOICE_MAX; i++, voice++)
	{
		if (voice->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, voice->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_VOICE, voice->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexVoice(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = &voiceWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexVoice(no);

	// rhw�̐ݒ�
	voice->vertexWk[0].rhw =
		voice->vertexWk[1].rhw =
		voice->vertexWk[2].rhw =
		voice->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	voice->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);

	// �e�N�X�`�����W�̐ݒ�
	voice->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	voice->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE, 0.0f);
	voice->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE);
	voice->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE);

	//voice->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//voice->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//voice->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//voice->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureVoice(int no, int cntPattern)
{
	VOICE *voice = &voiceWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_VOICE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_VOICE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE;

	voice->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	voice->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	voice->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	voice->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexVoice(int no)
{
	VOICE *voice = &voiceWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	voice->vertexWk[0].vtx.x = voice->pos.x - cosf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[0].vtx.y = voice->pos.y - sinf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[0].vtx.z = 0.0f;

	voice->vertexWk[1].vtx.x = voice->pos.x + cosf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[1].vtx.y = voice->pos.y - sinf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[1].vtx.z = 0.0f;

	voice->vertexWk[2].vtx.x = voice->pos.x - cosf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[2].vtx.y = voice->pos.y + sinf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[2].vtx.z = 0.0f;

	voice->vertexWk[3].vtx.x = voice->pos.x + cosf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[3].vtx.y = voice->pos.y + sinf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
VOICE *GetVoice(int no)
{
	return(&voiceWk[no]);
}
