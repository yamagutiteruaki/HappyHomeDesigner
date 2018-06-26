//=============================================================================
//
// �n�ʏ��� [field.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "field.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"
#include "fade.h"
#include "player.h"
#include "collision.h"


/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_LIMIT				(0)
#define HOUSE_LEN				(200.0f)
#define HOUSE_WID				(170.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void AreaHouse(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField[FIELD_MAX];	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField[FIELD_MAX];	// ���_�o�b�t�@�ւ̃|�C���^

FIELD					g_aField[FIELD_MAX];

const char *FileNameField[FIELD_MAX] =
{
	TEXTURE_FIELD,		// ��1
	TEXTURE_FIELD1,		// ��2
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);

	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				FileNameField[i],			// �t�@�C���̖��O
				&g_pD3DTextureField[i]);	// �ǂݍ��ރ������[
		}

		field->Pos.x = 0.0f;	//X���W�̐ݒ�
		field->Pos.y = 0.0f;//Y���W��0�Œ�
		field->Pos.z = 0.0f;	//Z���W�̐ݒ�

		field->Size = D3DXVECTOR3(FIELD_SIZE_X / (i*3 + 1), 0.0f, FIELD_SIZE_Z / (i*3 + 1));
		//field->Size = D3DXVECTOR3(FIELD_SIZE_X/2, 0.0f, FIELD_SIZE_Z/2);

	}
		MakeVertexField(pDevice);




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		//�t�B�[���h
		if (g_pD3DTextureField != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureField[i]->Release();
			g_pD3DTextureField[i] = NULL;
		}

		if (g_pD3DVtxBuffField != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffField[i]->Release();
			g_pD3DVtxBuffField[i] = NULL;
		}
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	AreaHouse();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{
		SetFade(FADE_OUT, STAGE_HOUSE1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F2))
	{
		SetFade(FADE_OUT, STAGE_HOUSE2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F3))
	{
		SetFade(FADE_OUT, STAGE_HOUSE3, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F4))
	{
		SetFade(FADE_OUT, STAGE_MYHOUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F5))
	{
		SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
#endif



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DXMATERIAL matDef;
	int fieldnum;

	if (GetStage() == STAGE_GAME)
	{
		fieldnum = 0;
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE
		|| GetStage() == STAGE_RESULT)
	{
		fieldnum = 1;
	}
	FIELD *field = GetField(fieldnum);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&field->world);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
	D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &field->world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField[fieldnum], 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureField[fieldnum]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{	
	FIELD *field = GetField(0);
	VERTEX_3D *pVtx;
	for (int i = 0; i < FIELD_MAX; i++, field++, pVtx += 4)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffField[i],		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}
		//for (int i = 0; i < FIELD_MAX; i++)
		{//���_�o�b�t�@�̒��g�𖄂߂�

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffField[i]->Lock(0, 0, (void**)&pVtx, 0);



			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[1].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[2].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, -field->Size.z / 2);
				pVtx[3].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, -field->Size.z / 2);

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse =
					pVtx[1].diffuse =
					pVtx[2].diffuse =
					pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			// ���_�f�[�^���A�����b�N����
			g_pD3DVtxBuffField[i]->Unlock();
		}
	}
	return S_OK;
}

FIELD *GetField(int no)
{
	return &g_aField[no];
}


