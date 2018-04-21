//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "stage.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFade(void);
void SetColor(D3DCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_p3DTextureFade = NULL;		// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				g_vertexWkFade[NUM_VERTEX];		// ���_���i�[���[�N

D3DXCOLOR				g_color;		// �t�F�[�h�J���[
FADE					g_eFade;		// �t�F�[�h���
int						g_nState;		// ���ɔ�ԗ\��̃X�e�[�g

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_eFade = FADE_IN;
	g_nState = STAGE_TITLE;			// ���ɔ�ԗ\��̃X�e�[�g

	// ���_���̐ݒ�
	MakeVertexFade();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	if(g_p3DTextureFade != NULL)
	{// �e�N�X�`���̊J��
		g_p3DTextureFade->Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	if(g_eFade != FADE_NONE)
	{// �t�F�[�h������
		if(g_eFade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			g_color.a += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
			if(g_color.a >= 1.0f)
			{
				// ��Ԃ�؂�ւ�
				SetStage(g_nState);
				InitStageEach(STAGE_INIT_LOOP);

				// �t�F�[�h�C�������ɐ؂�ւ�
				g_color.a = 1.0f;
				SetFade(FADE_IN, STAGE_MAX);
			}

			// �F��ݒ�
			SetColor(g_color);
		}
		else if (g_eFade == FADE_OUT_HALF)
		{	// �t�F�[�h�n�[�t�A�E�g����
			g_color.a += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
			if (g_color.a >= FADE_HALF)
			{
				// �t�F�[�h�C�������ɐ؂�ւ�
				g_color.a = FADE_HALF;
			}

			// �F��ݒ�
			SetColor(g_color);
		}
		else if(g_eFade == FADE_IN)
		{// �t�F�[�h�C������
			g_color.a -= FADE_RATE;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if(g_color.a <= 0.0f)
			{
				// �t�F�[�h�����I��
				g_color.a = 0.0f;
				SetFade(FADE_NONE, STAGE_MAX);
			}

			// �F��ݒ�
			SetColor(g_color);
		}
	}
}

//=============================================================================
// �t�F�[�h���
//=============================================================================
void DrawFade()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkFade, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkFade[0].rhw =
	g_vertexWkFade[1].rhw =
	g_vertexWkFade[2].rhw =
	g_vertexWkFade[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_color = D3DXCOLOR(FADE_COLOR_R, FADE_COLOR_G, FADE_COLOR_B, 1.0f);
	g_vertexWkFade[0].diffuse = g_color;
	g_vertexWkFade[1].diffuse = g_color;
	g_vertexWkFade[2].diffuse = g_color;
	g_vertexWkFade[3].diffuse = g_color;

	// ���_���W�̐ݒ�
	g_vertexWkFade[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vertexWkFade[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	g_vertexWkFade[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	g_vertexWkFade[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkFade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkFade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkFade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkFade[3].tex = D3DXVECTOR2(1.0f, 1.0f);	

	return S_OK;
}

//=============================================================================
// �F��ݒ�
//=============================================================================
void SetColor(D3DCOLOR col)
{
	// ���ˌ��̐ݒ�
	g_vertexWkFade[0].diffuse = col;
	g_vertexWkFade[1].diffuse = col;
	g_vertexWkFade[2].diffuse = col;
	g_vertexWkFade[3].diffuse = col;
}

//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void SetFade(FADE fade, int next )
{
	switch (fade)
	{
	case FADE_OUT:
		g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	case FADE_OUT_HALF:
		g_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	}
	g_eFade = fade;
	g_nState = next;
}

//=============================================================================
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
FADE GetFade(void)
{
	return g_eFade;
}
