////***********************************************************
////			levelchoice.cpp
////			����T��
////
////***********************************************************
////#include "main.h"
////#include "levelchoice.h"
////#include "input.h"
////#include "fade.h"
////#include "stage.h"
////#include "sound.h"
////#include "inputCtrl.h"
//
//
////***********************************************************
//// �v���g�^�C�v�錾
////***********************************************************
//HRESULT MakeVertexMode(LPDIRECT3DDEVICE9 pDevice);
//
////***********************************************************
////�O���[�o���錾
////***********************************************************
//
//
////***********************************************************
//// ����������
////***********************************************************
//HRESULT InitMode(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//	MakeVertexMode(pDevice);							//���_���̍쐬
//
//#include "main.h"
//
//															// �e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
//		TEXTURE_MODE,				// �t�@�C���̖��O
//		&g_pD3DTextureMode);		// �ǂݍ��ރ������[
//
//
//	return S_OK;
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void UninitMode(void)
//{
//	if (g_pD3DTextureMode != NULL)
//	{// �e�N�X�`���̊J��
//		g_pD3DTextureMode->Release();
//		g_pD3DTextureMode = NULL;
//	}
//
//	if (g_pD3DVtxBuffMode != NULL)
//	{// ���_�o�b�t�@�̊J��
//		g_pD3DVtxBuffMode->Release();
//		g_pD3DVtxBuffMode = NULL;
//	}
//
//
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateTitleMode(void)
//{
//	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
//	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);
//
//#if 0
//	if (g_nCountAppearStart >= COUNT_APPERA_START)
//	{
//		g_nConutDemo++;
//		if (g_nConutDemo > COUNT_WAIT_DEMO)
//		{
//			SetFade(FADE_OUT, MODE_TITLE);
//		}
//	}
//#endif
//
//
//	if (GetKeyboardTrigger(DIK_START))//�X�^���v���@T=�����Ă�@F=�����ĂȂ�
//	{
//		
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawTitleMode(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
//	pDevice->SetStreamSource(0, g_pD3DVtxBuffTitle, 0, sizeof(VERTEX_2D));
//
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pD3DTextureMode);
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
//
//}
//
////=============================================================================
//// ���_�̍쐬
////=============================================================================
//HRESULT MakeVertexTitleMode(LPDIRECT3DDEVICE9 pDevice)
//{
//	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
//	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
//		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
//		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
//		&g_pD3DVtxBuffTitle,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
//		NULL)))						// NULL�ɐݒ�
//	{
//		return E_FAIL;
//	}
//
//	{//���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_2D *pVtx;
//
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		g_pD3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
//
//		// ���_���W�̐ݒ�
//		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
//		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
//		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
//
//		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
//		pVtx[0].rhw =
//			pVtx[1].rhw =
//			pVtx[2].rhw =
//			pVtx[3].rhw = 1.0f;
//
//		// ���ˌ��̐ݒ�
//		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// �e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		// ���_�f�[�^���A�����b�N����
//		g_pD3DVtxBuffTitle->Unlock();
//	}
//
//	return S_OK;
//}
//
//
