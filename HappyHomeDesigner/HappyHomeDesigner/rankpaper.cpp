
//***********************************************************
//
// �^�C�g�������͏��������̒S���ł��B
//
//***********************************************************
#include "main.h"
#include "rankpaper.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "debugproc.h"

//***********************************************************
// �v���g�^�C�v�錾
//***********************************************************
HRESULT MakeVertexRankpaper(LPDIRECT3DDEVICE9 pDevice);
void SetColorRankpaper(void);

void SetVertexRankPaper(int no);
void SetVertexRank(int no);
void SetPaperPos(int no);
void SetRankPos(int no);
void SetVertexBg(void);





//***********************************************************
//�O���[�o���錾
//***********************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper0 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper0 = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper1 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper1 = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper2 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper2 = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper_back = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper_back = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureFirst = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFirst = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureSecond = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSecond = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureThird = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffThird = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


RANKPAPER				rankpaperWk[RANKPAPER_MAX];
RANKINGNO				rankingnoWk[RANK_NO_MAX];


D3DXVECTOR3				rankbackpos;

//***********************************************************
// ����������
//***********************************************************
HRESULT InitRankpaper(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKPAPER_BACK,				// �t�@�C���̖��O
		&g_pD3DTextureRankpaper_back);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKPAPER0,			// �t�@�C���̖��O
		&g_pD3DTextureRankpaper0);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKPAPER1,			// �t�@�C���̖��O
		&g_pD3DTextureRankpaper1);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKPAPER2,			// �t�@�C���̖��O
		&g_pD3DTextureRankpaper2);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FIRST,			// �t�@�C���̖��O
		&g_pD3DTextureFirst);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SECOND,			// �t�@�C���̖��O
		&g_pD3DTextureSecond);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_THIRD,			// �t�@�C���̖��O
		&g_pD3DTextureThird);		// �ǂݍ��ރ������[


	rankbackpos = D3DXVECTOR3(RANKPAPERBACK_POS_X, RANKPAPERBACK_POS_Y,0.0f);

	RANKPAPER *rankpaper = GetRankPaper(0);
	RANKINGNO *rankno = GetRankingNo(0);
	
	for (int i = 0; i < RANKPAPER_MAX; i++, rankpaper++, rankno++)
	{
		rankpaper->pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		rankno->pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	MakeVertexRankpaper(pDevice);							//���_���̍쐬


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankpaper(void)
{
	if (g_pD3DTextureRankpaper0 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRankpaper0->Release();
		g_pD3DTextureRankpaper0 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper0 != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffRankpaper0->Release();
		g_pD3DVtxBuffRankpaper0 = NULL;
	}

	if (g_pD3DTextureRankpaper1 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRankpaper1->Release();
		g_pD3DTextureRankpaper1 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper1 != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffRankpaper1->Release();
		g_pD3DVtxBuffRankpaper1 = NULL;
	}

	if (g_pD3DTextureRankpaper2 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRankpaper2->Release();
		g_pD3DTextureRankpaper2 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper2 != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffRankpaper2->Release();
		g_pD3DVtxBuffRankpaper2 = NULL;
	}

	if (g_pD3DTextureRankpaper_back != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRankpaper_back->Release();
		g_pD3DTextureRankpaper_back = NULL;
	}

	if (g_pD3DVtxBuffRankpaper_back != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffRankpaper_back->Release();
		g_pD3DVtxBuffRankpaper_back = NULL;
	}

	if (g_pD3DTextureFirst != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureFirst->Release();
		g_pD3DTextureFirst = NULL;
	}

	if (g_pD3DVtxBuffFirst != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffFirst->Release();
		g_pD3DVtxBuffFirst = NULL;
	}

	if (g_pD3DTextureSecond != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSecond->Release();
		g_pD3DTextureSecond = NULL;
	}

	if (g_pD3DVtxBuffSecond != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffSecond->Release();
		g_pD3DVtxBuffSecond = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankpaper(void)
{

	if (rankbackpos.y >= 0)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_C))
		{
			SetFade(FADE_OUT, STAGE_TITLE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}

	rankbackpos.y+=10.0f;

	if (rankbackpos.y >= 0)
	{
		rankbackpos.y = 0;
	}

	for (int i = 0; i < RANKPAPER_MAX; i++)
	{
		SetPaperPos(i);
		SetRankPos(i);
		
		SetVertexRankPaper(i);
		SetVertexRank(i);


	}
	SetVertexBg();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankpaper(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ��� */


	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper_back, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRankpaper_back);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/* ��z��0 */
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper0, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRankpaper0);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	/* ��z��1 */
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper1, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRankpaper1);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/* ��z��2 */
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRankpaper2);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffFirst, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureFirst);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffSecond, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureSecond);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffThird, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureThird);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRankpaper(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRankpaper_back,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper_back->Unlock();
	}
	//��z��==========================================

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRankpaper0,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper0->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER0_POS_X, RANKPAPER0_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER0_POS_X + RANKPAPER0_WIDTH, RANKPAPER0_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER0_POS_X, RANKPAPER0_POS_Y + RANKPAPER0_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER0_POS_X + RANKPAPER0_WIDTH, RANKPAPER0_POS_Y + RANKPAPER0_HEIGHT, 0.0f);

		
		
		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper0->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRankpaper1,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper1->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER1_POS_X, RANKPAPER1_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER1_POS_X + RANKPAPER1_WIDTH, RANKPAPER1_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER1_POS_X, RANKPAPER1_POS_Y + RANKPAPER1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER1_POS_X + RANKPAPER1_WIDTH, RANKPAPER1_POS_Y + RANKPAPER1_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper1->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRankpaper2,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper2->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER2_POS_X, RANKPAPER2_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER2_POS_X + RANKPAPER2_WIDTH, RANKPAPER2_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER2_POS_X, RANKPAPER2_POS_Y + RANKPAPER2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER2_POS_X + RANKPAPER2_WIDTH, RANKPAPER2_POS_Y + RANKPAPER2_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper2->Unlock();
	}

	//1��===========================================

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffFirst,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffFirst->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X, RANKPAPER_FIRST_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X + RANKPAPER_FIRST_WIDTH, RANKPAPER_FIRST_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X, RANKPAPER_FIRST_POS_Y + RANKPAPER_FIRST_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X + RANKPAPER_FIRST_WIDTH, RANKPAPER_FIRST_POS_Y + RANKPAPER_FIRST_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffFirst->Unlock();
	}

	// �Z�J���h==============================

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffSecond,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSecond->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X, RANKPAPER_SECOND_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X + RANKPAPER_SECOND_WIDTH, RANKPAPER_SECOND_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X, RANKPAPER_SECOND_POS_Y + RANKPAPER_SECOND_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X + RANKPAPER_SECOND_WIDTH, RANKPAPER_SECOND_POS_Y + RANKPAPER_SECOND_HEIGHT, 0.0f);


		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSecond->Unlock();
	}


	// �T�[�h==============================

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffThird,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffThird->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X, RANKPAPER_THIRD_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X + RANKPAPER_THIRD_WIDTH, RANKPAPER_THIRD_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X, RANKPAPER_THIRD_POS_Y + RANKPAPER_THIRD_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X + RANKPAPER_THIRD_WIDTH, RANKPAPER_THIRD_POS_Y + RANKPAPER_THIRD_HEIGHT, 0.0f);


		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSecond->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�  ����z��
//=============================================================================
void SetVertexRankPaper(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	VERTEX_2D *pVtx;

	switch (no)
	{
	case 0:


		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper0->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER0_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER0_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER0_WIDTH / 2, rankpaper->pos.y + RANKPAPER0_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER0_WIDTH / 2, rankpaper->pos.y + RANKPAPER0_HEIGHT, 0.0f);


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper0->Unlock();


		break;

	case 1:

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper1->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER1_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER1_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER1_WIDTH / 2, rankpaper->pos.y + RANKPAPER1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER1_WIDTH / 2, rankpaper->pos.y + RANKPAPER1_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper1->Unlock();
		break;


	case 2:

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper2->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER2_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER2_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER2_WIDTH / 2, rankpaper->pos.y + RANKPAPER2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER2_WIDTH / 2, rankpaper->pos.y + RANKPAPER2_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper2->Unlock();
		break;


	}
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�@�@����z��
//=============================================================================
void SetPaperPos(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	D3DXVECTOR3 BGpos = GetRankBackPos();

	switch (no)
	{
	case 0:
		rankpaper->pos.x = BGpos.x + RANKPAPER0_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER0_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	case 1:
		rankpaper->pos.x = BGpos.x + RANKPAPER1_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER1_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	case 2:
		rankpaper->pos.x = BGpos.x + RANKPAPER2_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER2_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	}
	PrintDebugProc("[��z�����W%d �FX(%f) Y(%f) Z(%f)]\n", no, rankpaper->pos.x, rankpaper->pos.y, rankpaper->pos.z);


}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�@�@������
//=============================================================================
void SetVertexRank(int no)
{
	VERTEX_2D *pVtx;

	RANKINGNO *rankingno = GetRankingNo(no);

	switch (no)
	{
	case 0:
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffFirst->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y + RANKPAPER_FIRST_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y + RANKPAPER_FIRST_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffFirst->Unlock();
		break;

	case 1:
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSecond->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y + RANKPAPER_SECOND_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y + RANKPAPER_SECOND_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSecond->Unlock();
		break;


	case 2:
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffThird->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y + RANKPAPER_THIRD_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y + RANKPAPER_THIRD_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffThird->Unlock();
		break;


	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetRankPos(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	RANKINGNO *rankingno = GetRankingNo(no);

	switch (no)
	{
	case 0:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_FIRST_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	case 1:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_SECOND_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	case 2:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_THIRD_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	}
	PrintDebugProc("[���ʍ��W%d �FX(%f) Y(%f) Z(%f)]\n", no, rankingno->pos.x, rankingno->pos.y, rankingno->pos.z);

}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetVertexBg(void)
{
	VERTEX_2D *pVtx;

	D3DXVECTOR3 rankbackpos = GetRankBackPos();


		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(rankbackpos.x , rankbackpos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankbackpos.x + RANKPAPERBACK_WIDTH , rankbackpos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankbackpos.x , rankbackpos.y + RANKPAPERBACK_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankbackpos.x + RANKPAPERBACK_WIDTH , rankbackpos.y + RANKPAPERBACK_HEIGHT, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper_back->Unlock();
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetColorRankpaper(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);



		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRankpaper_back->Unlock();
	}

}

//==================================================================================
//��z�����擾�֐�
//==================================================================================
RANKPAPER *GetRankPaper(int no)
{
	return &rankpaperWk[no];
}

//==================================================================================
//���ʃe�N�X�`�����擾�֐�
//==================================================================================
RANKINGNO *GetRankingNo(int no)
{
	return &rankingnoWk[no];
}


//==================================================================================
//BG���擾�֐�
//==================================================================================
D3DXVECTOR3 GetRankBackPos(void)
{
	return rankbackpos;
}