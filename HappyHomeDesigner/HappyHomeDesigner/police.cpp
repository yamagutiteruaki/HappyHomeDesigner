

//=============================================================================
//
// �|���X���� [police.cpp]
// Author : GP11B243-18-���_��
//
//=============================================================================
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
//#include "shadow.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetPoliceAnimation(int sec);
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
void SetPoliceHoming(int no, int frequency, float speedup);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice[POLICE_ANIM_MAX];			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPolice[POLICE_ANIM_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPolice[POLICE_ANIM_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPolice[POLICE_ANIM_MAX];				// �������̑���

D3DXMATRIX			g_mtxWorldPolice;							// ���[���h�}�g���b�N�X

float				g_fSizeShadowE;								// �e�̃T�C�Y
D3DXCOLOR			g_colShadowE;								// �e�̐F

POLICE				policeWk[POLICE_MAX];							// �|���X�i�[���[�N

int					animCnt;									// �A�j���J�E���g
int					key;										// �t���[���J�E���g
int					sp_Update;									// �X�V�p�x�v�Z�p


const char *FileNamePolice[POLICE_ANIM_MAX] =
{
	"data/MODEL/POLICE/police_a00.x",		// ����
	"data/MODEL/POLICE/police_a01.x",		// �����O�P
	"data/MODEL/POLICE/police_a02.x",		// �����O�Q
	"data/MODEL/POLICE/police_a03.x",		// �����O�R
	"data/MODEL/POLICE/police_a02.x",		// �����O�Q
	"data/MODEL/POLICE/police_a01.x",		// �����O�P
	"data/MODEL/POLICE/police_a00.x",		// ����
	"data/MODEL/POLICE/police_a11.x",		// �E���O�P
	"data/MODEL/POLICE/police_a12.x",		// �E���O�Q
	"data/MODEL/POLICE/police_a13.x",		// �E���O�R
	"data/MODEL/POLICE/police_a12.x",		// �E���O�Q
	"data/MODEL/POLICE/police_a11.x"		// �E���O�P

};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolice(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POLICE *police = &policeWk[0];
	FIELD *field = GetField(0);

	if (nType == STAGE_INIT_FAST)
	{
		for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_ANIM_MAX; nCntPoliceAnim++)
		{
			g_pD3DTexturePolice[nCntPoliceAnim] = NULL;
			g_pD3DXMeshPolice[nCntPoliceAnim] = NULL;
			g_pD3DXBuffMatPolice[nCntPoliceAnim] = NULL;


			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNamePolice[nCntPoliceAnim],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPolice[nCntPoliceAnim],
				NULL,
				&g_nNumMatPolice[nCntPoliceAnim],
				&g_pD3DXMeshPolice[nCntPoliceAnim])))
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif

		}

	}

	// �|���X�̏���������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		//PANEL *panel = GetPanel(GetPanelNumber(1, 8));
		// �|���X�̎��_�̏�����
		police->Eye = field->Pos;
		// �|���X�̒����_�̏�����
		police->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �|���X�̏�����̏�����
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �|���X�̌����̏�����
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �|���X�̈ړ��ʂ̏�����
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �|���X�̃X�P�[���̏�����
		police->scl = D3DXVECTOR3(0.9f, 0.9f, 0.9f);

		// use�t���O��true�ɐݒ�
		police->use = true;

		// �|���X�̈ړ����x������
		police->speed = VALUE_MOVE_POLICE;

		// �A�j���[�V�����ԍ�������
		// �ŏ��͒�����Ԃɐݒ�
		police->anim = 0;

		// �A�j���[�V�����J�E���g������
		animCnt = 0;

		// �X�V�p�x������
		sp_Update = 0;

		// �ǔ��v���C���[�ԍ�������
		key = 0;
		// �����_���ōŏ��ɒǔ�����v���C���[��I��
		//key = rand() % PLAYER_MAX;

		// �V���h�E�p
		police->nIdxShadow = 0;
		police->fSizeShadow = 0.0f;
		police->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		police->bShadow = false;
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolice(void)
{
	for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_ANIM_MAX; nCntPoliceAnim++)
	{
		if (g_pD3DTexturePolice[nCntPoliceAnim] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePolice[nCntPoliceAnim]->Release();
			g_pD3DTexturePolice[nCntPoliceAnim] = NULL;
		}

		if (g_pD3DXMeshPolice[nCntPoliceAnim] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshPolice[nCntPoliceAnim]->Release();
			g_pD3DXMeshPolice[nCntPoliceAnim] = NULL;
		}

		if (g_pD3DXBuffMatPolice[nCntPoliceAnim] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatPolice[nCntPoliceAnim]->Release();
			g_pD3DXBuffMatPolice[nCntPoliceAnim] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolice(void)
{
	POLICE *police = &policeWk[0];
	CAMERA *camera = GetCamera();
	//PANEL *panel = GetPanel(0);
	//PLAYER *player = GetPlayer(0);

	// �A�j���[�V����
	SetPoliceAnimation(POLICE_ANIM_SEC);


	// �{�^���Œǔ��Ώې؂�ւ���
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_1))
	{
		key = 0;
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		key = 1;
	}
#endif


	// �Q�[�W�̏��Ȃ��ق���ǔ�
	//if (player[0].item < player[1].item)
	//{	// 1P�̂ق����Q�[�W�����Ȃ��ꍇ

	//	// 1P��ǔ�
	//	key = 0;
	//}
	//if (player[0].item > player[1].item)
	//{	// 2P�̂ق����Q�[�W�����Ȃ��ꍇ

	//	// 2P��ǔ�
	//	key = 1;
	//}
	// �ǔ����Z�b�g
	SetPoliceHoming(key, POLICE_SPEED_FREQUENCY, POLICE_SPEEDUP);


	// �f�o�b�O���Ɏ蓮�Ń|���X�ړ�
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			police->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// ����ړ�
			police->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else
		{// ���ړ�
			police->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			police->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			police->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else
		{// �E�ړ�
			police->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		police->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		police->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
	}




#endif

	// �|���X�ړ�����

	// �ړ��ʂɊ�����������
	police->move.x += (0.0f - police->move.x) * RATE_MOVE_POLICE;
	police->move.y += (0.0f - police->move.y) * RATE_MOVE_POLICE;
	police->move.z += (0.0f - police->move.z) * RATE_MOVE_POLICE;

	/// �ʒu�ړ�
	police->Eye.x += police->move.x;
	police->Eye.y += police->move.y;
	//if (police->Eye.y < 5.0f)
	//{
	//	police->Eye.y = 5.0f;
	//}
	//if (police->Eye.y > 75.0f)
	//{
	//	police->Eye.y = 75.0f;
	//}
	police->Eye.z += police->move.z;


	// �|���X�̈ړ������i��O�ɍs���Ȃ��悤�ɂ���j
	// Z���W�̃}�b�N�X��X���W�̃}�b�N�X�Ő���������
	//panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));		// �E��
	//if (police->Eye.x > panel->Pos.x)
	//{
	//	police->Eye.x = panel->Pos.x;
	//}
	//if (police->Eye.z > panel->Pos.z)
	//{
	//	police->Eye.z = panel->Pos.z;
	//}

	// Z���W�̃~�j�}����X���W�̃~�j�}���Ő���������
	//panel = GetPanel(GetPanelNumber(1, 1));							// ����
	//if (police->Eye.x < -panel->Pos.x)
	//{
	//	police->Eye.x = -panel->Pos.x;
	//}
	//if (police->Eye.z < -panel->Pos.z)
	//{
	//	police->Eye.z = -panel->Pos.z;
	//}


	police = &policeWk[0];
#ifdef _DEBUG
	PrintDebugProc("[�|���X�̈ʒu  �F(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	//PrintDebugProc("\n");
#endif

	// �V���h�E
	//if (!police->bShadow)
	//{	// �V���h�E�ݒu
	//	police->nIdxShadow = CreateShadow(police->Eye, 25.0f, 25.0f);
	//	police->fSizeShadow = POLICE_SHADOW_SIZE;
	//	police->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
	//	police->bShadow = true;
	//}
	//else
	//{
	//	// �V���h�E�Ǘ�
	//	SetPositionShadow(police->nIdxShadow, D3DXVECTOR3(police->Eye.x, 0.2f, police->Eye.z));
	//	SetVertexShadow(police->nIdxShadow, police->fSizeShadow, police->fSizeShadow);
	//	SetColorShadow(police->nIdxShadow, police->colShadow);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (police->use == true)	// �g�p��ԂȂ�`�悷��
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPolice);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, police->scl.x,
				police->scl.y,
				police->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice,
				&g_mtxWorldPolice, &mtxScale);


			// ��]�𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, police->rot.y, police->rot.x, police->rot.z);
			//D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxRot);
			PoliceLookAtMatrix(&mtxRot, &police->Eye, &police->At, &police->Up);

			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxRot);

			//// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, police->Eye.x, police->Eye.y, police->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolice);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			// ���͒�����ݒ肵�Ă�O
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPolice[police->anim]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPolice[police->anim]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePolice[police->anim]);

				// �`��
				g_pD3DXMeshPolice[police->anim]->DrawSubset(nCntMat);

			}

			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		}

	}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}

}
//=============================================================================
// �|���X�擾�֐�
//=============================================================================
POLICE *GetPolice(int no)
{
	return(&policeWk[no]);
}
//=============================================================================
// �|���X�̉�]�s��Z�o�֐�
//=============================================================================
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pAt - *pEye;
	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));


	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

	return pout;
}
//=============================================================================
// �|���X�A�j���[�V�����ݒ�֐�
// �����F�A�j���[�V�����ꏄ�ɂ�����b���j
//=============================================================================
void SetPoliceAnimation(int sec)
{
	POLICE *police = &policeWk[0];

	// �A�j���[�V�����J�E���g
	animCnt++;

	// �b���̐�Βl�����߂�
	sec = abs(sec);

	// �A�j���[�V������؂�ւ���t���[���������߂�
	sec = (60 * sec) / POLICE_ANIM_MAX;

	if (animCnt % sec == 0)
	{	// �A�j���[�V������؂�ւ���
		police->anim++;
		if (police->anim >= POLICE_ANIM_MAX)
		{	// �ꏄ������ŏ��ɖ߂�
			police->anim = 0;
		}
	}

}
//=============================================================================
// �|���X�ǔ��ݒ�֐�
// �����P�F�ǔ��������v���C���[�ԍ�
// �����Q�F�ړ����x�̍X�V�p�x�i�Ƃ�܃t���[�����n���j
// �����R�F�X�V��񓖂���̈ړ����x�̕ω���
//=============================================================================
void SetPoliceHoming(int no, int frequency, float speedup)
{
	POLICE *police = &policeWk[0];

	// �ړ����x�X�V�p�x�J�E���g
	sp_Update++;

	// �ǔ��ΏۂɃ|���X�̒����_���Z�b�g
	//police->At = GetPosPlayer(no);

	// �ǔ��Ώۂւ̈ړ��x�N�g�������߂�
	//police->move = GetPosPlayer(no) - police->Eye;

	// �ړ��x�N�g���𐳋K��
	D3DXVec3Normalize(&police->move, &police->move);

	// �|���X�̑��x����

	// ���x�����Ԋu�ōX�V
	if (sp_Update % frequency == 0)
	{	// ���xup
		police->speed += speedup;
		// �ړ����x�X�V�p�x�J�E���g���[���ɖ߂�
		sp_Update = 0;
	}

	// ���x�ݒ�
	police->move *= police->speed;

}