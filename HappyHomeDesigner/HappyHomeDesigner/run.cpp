//=============================================================================
//
// �v���C���[���� [run.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "run.h"
#include "input.h"
#include "stage.h"
#include "rankpaper.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRun(int no);
void SetTextureRun(int no, int cntPattern);
void SetVertexRun(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRun = NULL;		// �e�N�X�`���ւ̃|���S��

RUN					runWk[RUN_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitRun(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RUN,				// �t�@�C���̖��O
			&g_pD3DTextureRun);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏���������
	for (int i = 0; i < RUN_MAX; i++, run++)
	{
		run->use = true;									// �g�p
		run->pos = D3DXVECTOR3(SCREEN_WIDTH+TEXTURE_RUN_SIZE_X, 900.0f, 0.0f);	// ���W�f�[�^��������
		run->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		run->PatternAnim = rand() % ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		run->CountAnim = 0;								// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_RUN_SIZE_X, TEXTURE_RUN_SIZE_Y);
		run->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		run->BaseAngle = atan2f(TEXTURE_RUN_SIZE_Y, TEXTURE_RUN_SIZE_X);	// �v���C���[�̊p�x��������

		run->Texture = g_pD3DTextureRun;				// �e�N�X�`�����
		MakeVertexRun(i);								// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRun(void)
{
	if (g_pD3DTextureRun != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureRun->Release();
		g_pD3DTextureRun = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRun(void)
{
	D3DXVECTOR3 Bgpos = GetRankBackPos();

	if (Bgpos.y >= 0)
	{
		RUN *run = &runWk[0];

		for (int i = 0; i < RUN_MAX; i++, run++)
		{
			if (run->use == true)			// �g�p���Ă����ԂȂ�X�V����
			{
				run->pos.x -= 20;
				// �A�j���[�V����
				run->CountAnim++;
				if ((run->CountAnim % TIME_ANIMATION) == 0)
				{
					// �p�^�[���̐؂�ւ�
					run->PatternAnim = (run->PatternAnim + 1) % ANIM_PATTERN_NUM;

					// �e�N�X�`�����W��ݒ�
					SetTextureRun(i, run->PatternAnim);
				}
				// �ړ���̍��W�Œ��_��ݒ�
				SetVertexRun(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[0];

	//// ���e�X�g��L����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RUN_MAX; i++, run++)
	{
		if (run->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, run->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RUN, run->vertexWk, sizeof(VERTEX_2D));
		}
	}

	//// ���e�X�g�𖳌���
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRun(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[no];

	// ���_���W�̐ݒ�
	SetVertexRun(no);

	// rhw�̐ݒ�
	run->vertexWk[0].rhw =
		run->vertexWk[1].rhw =
		run->vertexWk[2].rhw =
		run->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	run->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	run->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	run->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	run->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// �e�N�X�`�����W�̐ݒ�
	run->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	run->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	run->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);
	run->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRun(int no, int cntPattern)
{
	RUN *run = &runWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	run->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	run->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	run->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	run->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexRun(int no)
{
	RUN *run = &runWk[no];

	// ���_���W�̐ݒ�
	run->vertexWk[0].vtx.x = run->pos.x - cosf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[0].vtx.y = run->pos.y - sinf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[0].vtx.z = 0.0f;

	run->vertexWk[1].vtx.x = run->pos.x + cosf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[1].vtx.y = run->pos.y - sinf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[1].vtx.z = 0.0f;

	run->vertexWk[2].vtx.x = run->pos.x - cosf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[2].vtx.y = run->pos.y + sinf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[2].vtx.z = 0.0f;

	run->vertexWk[3].vtx.x = run->pos.x + cosf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[3].vtx.y = run->pos.y + sinf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
RUN *GetRun(int no)
{
	return(&runWk[no]);
}

