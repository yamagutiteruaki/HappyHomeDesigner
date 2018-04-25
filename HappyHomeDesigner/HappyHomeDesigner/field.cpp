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

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void SetDiffuseField(int nField, D3DXCOLOR col);
void SetDiffuseHitPanel(int HitPanel, D3DXCOLOR col);
void SetVertexHitPanel(int no);



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PANEL					g_aPanel[PANEL_MAX];

LPDIRECT3DTEXTURE9		g_pD3DTextureHitPanel = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHitPanel = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

HIT_PANEL				g_aHitPanel[PANEL_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PANEL *panel = GetPanel(0);
	HIT_PANEL *hitpanel = GetHitPanel(0);

	if (nType == STAGE_INIT_FAST)
	{
		MakeVertexField(pDevice);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PANEL,			// �t�@�C���̖��O
			&g_pD3DTextureField);	// �ǂݍ��ރ������[
									// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PANEL,			// �t�@�C���̖��O
			&g_pD3DTextureHitPanel);// �ǂݍ��ރ������[

	}


	for (int i = 0; i < PANEL_MAX; i++, panel++, hitpanel++)
	{
		panel->Pos.x = i % PANEL_NUM_X * PANEL_SIZE_X;	//X���W�̐ݒ�
		panel->Pos.y = 0.0f;							//Y���W��0�Œ�
		panel->Pos.z = i / PANEL_NUM_X * PANEL_SIZE_Z;	//Z���W�̐ݒ�
		panel->PanelType = PANEL_NORMAL;				//�p�l���^�C�v�@��{�̓m�[�}��
		panel->PanelCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�p�l���J���[ ��{�͔�
		panel->ItemSet = false;
		panel->HitFlag = PANEL_NORMAL;

		hitpanel->Pos.x = panel->Pos.x;
		hitpanel->Pos.y = panel->Pos.y + 0.1f;
		hitpanel->Pos.z = panel->Pos.z;

		hitpanel->Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		hitpanel->HitCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		hitpanel->Use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	//�p�l��
	if (g_pD3DTextureField != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}

	//�q�b�g�G�t�F�N�g
	if (g_pD3DTextureHitPanel != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureHitPanel->Release();
		g_pD3DTextureHitPanel = NULL;
	}

	if (g_pD3DVtxBuffHitPanel != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffHitPanel->Release();
		g_pD3DVtxBuffHitPanel = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PANEL *panel;
	HIT_PANEL *hitpanel;


#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_L))
	{
		{
			int p = rand() % 105;
			int num = rand() % 2;
			SetHitPanel(p, num);
		}
	}
#endif

	panel = GetPanel(0);
	hitpanel = GetHitPanel(0);

	for (int i = 0; i < PANEL_MAX; i++, panel++, hitpanel++)
	{
#ifdef _DEBUG
		PrintDebugProc("%d", panel->PanelType);
#endif
		if (hitpanel->Use == true)//�q�b�g�p�l����on�̎�
		{
			hitpanel->Size.x++;//�q�b�g�p�l���̃T�C�Y���������傫��
			hitpanel->Size.z++;

			//�q�b�g�p�l���̐F��ݒ�
			if (panel->HitFlag == 1)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_RED);
			}
			else if (panel->HitFlag == 2)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_BLUE);
			}
			else if (panel->HitFlag == 0)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_WHITE);
			}

		}
		if (hitpanel->Size.x >= PANEL_SIZE_X)//�q�b�g�p�l�����p�l���Ɠ��T�C�Y�ɂȂ�����
		{
			hitpanel->Size.x = 0.0f;			//�T�C�Y��0�ɖ߂�
			hitpanel->Size.z = 0.0f;
			panel->PanelType = panel->HitFlag;	//�p�l���^�C�v��ύX��
			panel->HitFlag = 0;					//�p�l���^�C�v�����Z�b�g
			hitpanel->Use = false;				//�q�b�g�p�l����off

		}
		SetVertexHitPanel(i);
		SetDiffuseHitPanel(i, hitpanel->HitCol);

	}



	panel = GetPanel(0);
	hitpanel = GetHitPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		if (panel->PanelType == PANEL_1P)	//�p�l���^�C�v��1P�ɕς������
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_RED);	//�p�l���J���[��Ԃ�
		}
		else if (panel->PanelType == PANEL_2P)	//�p�l���^�C�v��2P�ɂȂ�����
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_BLUE);//�p�l���J���[���
		}
		else if (panel->PanelType == PANEL_NORMAL)	//�p�l���^�C�v��2P�ɂȂ�����
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_WHITE);//�p�l���J���[���
		}

		SetDiffuseField(i, panel->PanelCol);
	}


#ifdef _DEBUG
	//�p�l���ʒu�m�F�p
	//PANEL *panelcheck1 = GetPanel(GetPanelNumber(1, 1));
	//PANEL *panelcheck2 = GetPanel(GetPanelNumber(1, 15));
	//PANEL *panelcheck3 = GetPanel(GetPanelNumber(7, 1));
	//PANEL *panelcheck4 = GetPanel(GetPanelNumber(7, 15));
	//PrintDebugProc("�p�l��[ 1][ 1] : (%f,%f,%f)\n", panelcheck1->Pos.x, panelcheck1->Pos.y, panelcheck1->Pos.z);
	//PrintDebugProc("�p�l��[ 1][15] : (%f,%f,%f)\n", panelcheck2->Pos.x, panelcheck2->Pos.y, panelcheck2->Pos.z);
	//PrintDebugProc("�p�l��[ 7][ 1] : (%f,%f,%f)\n", panelcheck3->Pos.x, panelcheck3->Pos.y, panelcheck3->Pos.z);
	//PrintDebugProc("�p�l��[ 7][15] : (%f,%f,%f)\n", panelcheck4->Pos.x, panelcheck4->Pos.y, panelcheck4->Pos.z);

	/*GetPanel(1)->PanelCol = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);*/

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	PANEL *panel = GetPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&panel->mtxWorldField);


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, panel->Pos.x, panel->Pos.y, panel->Pos.z);
		D3DXMatrixMultiply(&panel->mtxWorldField, &panel->mtxWorldField, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &panel->mtxWorldField);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureField);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	HIT_PANEL *hitpanel = GetHitPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, hitpanel++)
	{
		if (hitpanel->Use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&hitpanel->mtxWorldHitPanel);


			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, hitpanel->Pos.x, hitpanel->Pos.y, hitpanel->Pos.z);
			D3DXMatrixMultiply(&hitpanel->mtxWorldHitPanel, &hitpanel->mtxWorldHitPanel, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &hitpanel->mtxWorldHitPanel);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffHitPanel, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureHitPanel);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
		}
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//for (int i = 0; i < PANEL_MAX; i++)
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < PANEL_MAX; i++, pVtx += 4)

		{

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, PANEL_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(PANEL_SIZE_X / 2, 0.0f, PANEL_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, -PANEL_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(PANEL_SIZE_X / 2, 0.0f, -PANEL_SIZE_Z / 2);

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
		g_pD3DVtxBuffField->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffHitPanel,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//for (int i = 0; i < PANEL_MAX; i++)
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
		HIT_PANEL *hitpanel = GetHitPanel(0);

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < PANEL_MAX; i++, hitpanel++, pVtx += 4)

		{

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
			pVtx[1].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);
			pVtx[3].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);

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
		g_pD3DVtxBuffHitPanel->Unlock();
	}

	return S_OK;
}

//============================================================================= 
// ���ˌ��̐ݒ�֐� 
//============================================================================= 
void SetDiffuseField(int nField, D3DXCOLOR col)
{
	{// ���_�o�b�t�@�̒��g�𖄂߂� 
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾 
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nField * 4);

		// ���_���W�̐ݒ� 
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;


		// ���_�f�[�^���A�����b�N���� 
		g_pD3DVtxBuffField->Unlock();
	}
}
//============================================================================= 
// ���ˌ��̐ݒ�֐� 
//============================================================================= 
void SetDiffuseHitPanel(int HitPanel, D3DXCOLOR col)
{
	{// ���_�o�b�t�@�̒��g�𖄂߂� 
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾 
		g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (HitPanel * 4);

		// ���_���W�̐ݒ� 
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;


		// ���_�f�[�^���A�����b�N���� 
		g_pD3DVtxBuffHitPanel->Unlock();
	}
}

//=============================================================================
//���_���W
//=============================================================================
void SetVertexHitPanel(int no)
{
	HIT_PANEL *hitpanel = GetHitPanel(no);
	// ���_�o�b�t�@�̒��g�𖄂߂� 
	VERTEX_3D *pVtx;


	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += (no * 4);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
	pVtx[1].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
	pVtx[2].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);
	pVtx[3].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffHitPanel->Unlock();

}
//===========================================================
//�p�l���̎擾
//===========================================================
PANEL *GetPanel(int no)
{
	return &g_aPanel[no];
}

//===========================================================
//�q�b�g�p�l���̎擾
//===========================================================
HIT_PANEL *GetHitPanel(int no)
{
	return &g_aHitPanel[no];
}

//===========================================================
//�p�l���ԍ��̌v�Z
//height(�����P)	��(��O)���琔���ĉ��Ԗڂ̃p�l����
//width(�����Q)		�����琔���ĉ��Ԗڂ̃p�l����
//===========================================================
int GetPanelNumber(int height, int width)
{
	return (height - 1)*PANEL_NUM_X + (width - 1);
}

//==========================================================
//�p�l���ύX�̏���
//no(�����P)		�ς������p�l���̔ԍ�
//playernum(����2)	�ς��悤�Ƃ��Ă���v���C���[�̔ԍ�
//==========================================================
void SetHitPanel(int no, int playernum)
{
	PANEL *panel = GetPanel(no);
	HIT_PANEL *hitpanel = GetHitPanel(no);

	if (hitpanel->Use == false && panel->PanelType == PANEL_NORMAL)//�q�b�g�p�l�����g���ĂȂ��@���@�p�l���^�C�v��0�̎�
	{
		panel->HitFlag = playernum + 1;	//�v���C���[�i���o�[��1�������t���O�i���o�[�𗧂Ă�
										//�� 0�Ԃ��m�[�}���p�l���̂��߁@1�ԕ��̂��ꂪ�o�Ă���

		hitpanel->Use = true;//�q�b�g�p�l�����g�p��Ԃ�
	}
}