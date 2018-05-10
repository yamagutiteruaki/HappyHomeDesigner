

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


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
void PoliceMove(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPolice;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPolice;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPolice;				// �������̑���

D3DXMATRIX			g_mtxWorldPolice;							// ���[���h�}�g���b�N�X

POLICE				policeWk[POLICE_MAX];							// �|���X�i�[���[�N

D3DXVECTOR3			movePointWk[10];							// �|���X�̕����]���_�i�[���[�N

int					animCnt;									// �A�j���J�E���g
int					key;										// �t���[���J�E���g
int					sp_Update;									// �X�V�p�x�v�Z�p

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
			g_pD3DTexturePolice = NULL;
			g_pD3DXMeshPolice = NULL;
			g_pD3DXBuffMatPolice = NULL;


			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(POLICE_MODEL,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPolice,
				NULL,
				&g_nNumMatPolice,
				&g_pD3DXMeshPolice)))
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

	// �|���X�̏���������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �|���X�̎��_(�ʒu���W)�̏�����
		police->Eye = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
		// �|���X�̒����_�̏�����
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �|���X�̏�����̏�����
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �|���X�̌����̏�����
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �|���X�̈ړ��ʂ̏�����
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �|���X�̃X�P�[���̏�����
		police->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// use�t���O��true�ɐݒ�
		police->use = true;

		// �|���X�̈ړ����x������
		police->speed = VALUE_MOVE_POLICE;

	}



	// �����]���_�̏����ݒ�
	movePointWk[0] = D3DXVECTOR3(-300.0f, 0.0f, 300.0f);	// ����(-300,0,300)
	movePointWk[1] = D3DXVECTOR3(0.0f, 0.0f, 300.0f);		// ���S��(0,0,300)
	movePointWk[2] = D3DXVECTOR3(300.0f, 0.0f, 300.0f);		// �E��(300,0,300)
	movePointWk[3] = D3DXVECTOR3(-300.0f, 0.0f, 0.0f);		// ���S��(-300,0,0)
	movePointWk[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���S(0,0,0)
	movePointWk[5] = D3DXVECTOR3(300.0f, 0.0f, 0.0f);		// ���S�E(300,0,0)
	movePointWk[6] = D3DXVECTOR3(-300.0f, 0.0f, -300.0f);	// ����(-300,0,-300)
	movePointWk[7] = D3DXVECTOR3(-0.0f, 0.0f, -300.0f);		// ���S��(0,0,-300)
	movePointWk[8] = D3DXVECTOR3(300.0f, 0.0f, -300.0f);	// �E��(300,0,-300)

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolice(void)
{
	for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_MAX; nCntPoliceAnim++)
	{
		if (g_pD3DTexturePolice != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePolice->Release();
			g_pD3DTexturePolice = NULL;
		}

		if (g_pD3DXMeshPolice != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshPolice->Release();
			g_pD3DXMeshPolice = NULL;
		}

		if (g_pD3DXBuffMatPolice != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatPolice->Release();
			g_pD3DXBuffMatPolice = NULL;
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
	PLAYER *player = GetPlayer(0);

	//police->At = player->Eye;

	PoliceMove();

	// �f�o�b�O���Ɏ蓮�Ń|���X�ړ�
//#ifdef _DEBUG
//	if (GetKeyboardPress(DIK_A))
//	{
//		if (GetKeyboardPress(DIK_W))
//		{// ���O�ړ�
//			police->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else if (GetKeyboardPress(DIK_S))
//		{// ����ړ�
//			police->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else
//		{// ���ړ�
//			police->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		}
//	}
//	else if (GetKeyboardPress(DIK_D))
//	{
//		if (GetKeyboardPress(DIK_W))
//		{// �E�O�ړ�
//			police->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else if (GetKeyboardPress(DIK_S))
//		{// �E��ړ�
//			police->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else
//		{// �E�ړ�
//			police->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		}
//	}
//	else if (GetKeyboardPress(DIK_W))
//	{// �O�ړ�
//		police->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		police->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//	}
//	else if (GetKeyboardPress(DIK_S))
//	{// ��ړ�
//		police->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		police->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//	}
//
//	
//#endif
//
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
	PrintDebugProc("[�|���X�̒����_  �F(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[�|���X�̌���  �F(%f)]\n", police->rot.y);
	PrintDebugProc("[�|���X�̎g�p���  �F(%d)]\n", police->use);

#endif
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

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, police->Eye.x, police->Eye.y, police->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolice);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPolice->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPolice; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePolice);

				// �`��
				g_pD3DXMeshPolice->DrawSubset(nCntMat);

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
	//D = *pEye - *pAt;
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
// �|���X�̈ړ��֐�
//=============================================================================
void PoliceMove(void)
{
	POLICE *police = &policeWk[0];
	CAMERA *camera = GetCamera();


	if (GetKeyboardPress(DIK_NUMPAD4))
	{// ��������
		//police->rot.y = camera->rotCamera.y - D3DX_PI * 0.50f;

		// �������t�B�[���h���
		police->rot.y = D3DX_PI * 0.50f;

		//if (police->rot.y < -D3DX_PI)
		//{
		//	police->rot.y += D3DX_PI * 2.0f;
		//}

		police->At.x = police->Eye.x - sinf(police->rot.y);
		police->At.z = police->Eye.z - cosf(police->rot.y);


		// �ړ��ʌv�Z
		police->move.x -= cosf(police->rot.y) * VALUE_MOVE_POLICE;
		police->move.z += sinf(police->rot.y) * VALUE_MOVE_POLICE;


	}
	if (GetKeyboardPress(DIK_NUMPAD6))
	{// �E������
		police->rot.y = camera->rotCamera.y + D3DX_PI * 0.50f;


		//if (police->rot.y < -D3DX_PI)
		//{
		//	police->rot.y += D3DX_PI * 2.0f;
		//}

		police->At.x = police->Eye.x - sinf(police->rot.y);
		police->At.z = police->Eye.z - cosf(police->rot.y);

		// �ړ��ʌv�Z
		police->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;

	}
	if (GetKeyboardPress(DIK_NUMPAD8))
	{// �O������
		police->rot.y = D3DX_PI + camera->rotCamera.y;

		//if (police->rot.y < -D3DX_PI)
		//{
		//	police->rot.y += D3DX_PI * 2.0f;
		//}

		police->At.x = police->Eye.x - sinf(police->rot.y);
		police->At.z = police->Eye.z - cosf(police->rot.y);

		// �ړ��ʌv�Z
		police->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;

	}
	if (GetKeyboardPress(DIK_NUMPAD2))
	{// �������
		police->rot.y = camera->rotCamera.y;

		//if (police->rot.y < -D3DX_PI)
		//{
		//	police->rot.y += D3DX_PI * 2.0f;
		//}

		police->At.x = police->Eye.x - sinf(police->rot.y);
		police->At.z = police->Eye.z - cosf(police->rot.y);

		// �ړ��ʌv�Z
		police->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;

	}



}
//=============================================================================
// �|���X�̈ړ��ύX�|�C���g�ݒ�֐�
//=============================================================================
void SetMovePoint(void)
{
	// ����(-300,0,300)
	// ���S��(0,0,300)
	// �E��(300,0,300)
	// ���S��(-300,0,0)
	// ���S(0,0,0)
	// ���S�E(300,0,0)
	// ����(-300,0,-300)
	// ���S��(0,0,-300)
	// �E��(300,0,-300)
}
//=============================================================================
// �|���X�ƈړ��ύX�|�C���g�̓����蔻��
//=============================================================================
void CheckHitPoliceMove(void)
{
	// 9����|�C���g�̂����ꂩ�͈͓̔��Ƀ|���X���N���������𔻒�

	// �O�㍶�E�̂����A�i�s�\�ȕ���������
	// �N�������玟�ɐi�ޕ����������_���Ō���
	// �|���X�̒����_�����̃|�C���g�փZ�b�g����
	// ���̕����ւ̐i�s�x�N�g�������߂�

}