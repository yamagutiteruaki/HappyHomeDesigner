//=============================================================================
//
// �|���X���� [police.cpp]
// Author : GP12A295-19-���_��
//
//=============================================================================
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
#include "collision.h"
#include "calculate.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InvalidCollision(int frame);
void PoliceCollision(void);
void SetPoliceMove(POLICE *police, int y, int x);
void PoliceMove(void);
void PoliceEachCollision(void);
void PoliceMoveControl(int frame);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
// �|���X�{�̊֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice;									// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPolice;										// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPolice;									// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPolice;										// �������̑���
D3DXMATRIX			g_mtxWorldPolice;										// ���[���h�}�g���b�N�X
POLICE				policeWk[POLICE_MAX];									// �|���X�i�[���[�N
// �|���X�A�[���֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePoliceArm[POLICE_ARM_TYPE_MAX];			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPoliceArm[POLICE_ARM_TYPE_MAX];				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPoliceArm[POLICE_ARM_TYPE_MAX];			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPoliceArm[POLICE_ARM_TYPE_MAX];				// �������̑���
D3DXMATRIX			g_mtxWorldPoliceArm;									// ���[���h�}�g���b�N�X
POLICE_ARM			policeArmWk[POLICE_ARM_MAX];							// �|���X�A�[���i�[���[�N
const char *FileNamePoliceArm[POLICE_ARM_TYPE_MAX] =
{	// �ǂݍ��ރ��f��
	"data/MODEL/POLICE/standing_R_hand.x",		// �E�r
	"data/MODEL/POLICE/standing_L_hand.x",		// ���r
};
// �|���X�̃��b�O�֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePoliceLeg[POLICE_LEG_TYPE_MAX];			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPoliceLeg[POLICE_LEG_TYPE_MAX];				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPoliceLeg[POLICE_LEG_TYPE_MAX];			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPoliceLeg[POLICE_LEG_TYPE_MAX];				// �������̑���
D3DXMATRIX			g_mtxWorldPoliceLeg;									// ���[���h�}�g���b�N�X
POLICE_LEG			policeLegWk[POLICE_LEG_MAX];							// �|���X���b�O�i�[���[�N
const char *FileNamePoliceLeg[POLICE_LEG_TYPE_MAX] =
{
	"data/MODEL/POLICE/standing_R_leg.x",		// �E��
	"data/MODEL/POLICE/standing_L_leg.x",		// ����
};
// �`�F�b�N�|�C���g�֌W
D3DXVECTOR3			CheckPointWk[CHECK_POINT_Y_MAX][CHECK_POINT_X_MAX];		// �`�F�b�N�|�C���g�i�[���[�N
// ���̑�
int					animCnt;												// �A�j���J�E���g
int					sp_Update;												// �X�V�p�x�v�Z�p
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolice(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];
	FIELD *field = GetField(0);

	// �|���X�{�̂̃��f���ǂݍ���
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
		//D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		//	TEXTURE_FILENAME,		// �t�@�C���̖��O
		//	&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif
		// �A�[���̃��f���ǂݍ���
		for (int i = 0; i < POLICE_ARM_TYPE_MAX; i++)
		{
			g_pD3DTexturePoliceArm[i] = NULL;
			g_pD3DXMeshPoliceArm[i] = NULL;
			g_pD3DXBuffMatPoliceArm[i] = NULL;

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNamePoliceArm[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPoliceArm[i],
				NULL,
				&g_nNumMatPoliceArm[i],
				&g_pD3DXMeshPoliceArm[i])))
			{
				return E_FAIL;
			}
#if 0
			// �e�N�X�`���̓ǂݍ���
			//D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			//	TEXTURE_FILENAME,		// �t�@�C���̖��O
			//	&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif
		}
		// ���b�O�̃��f���ǂݍ���
		for (int i = 0; i < POLICE_LEG_TYPE_MAX; i++)
		{
			g_pD3DTexturePoliceLeg[i] = NULL;
			g_pD3DXMeshPoliceLeg[i] = NULL;
			g_pD3DXBuffMatPoliceLeg[i] = NULL;

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNamePoliceLeg[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPoliceLeg[i],
				NULL,
				&g_nNumMatPoliceLeg[i],
				&g_pD3DXMeshPoliceLeg[i])))
			{
				return E_FAIL;
			}
#if 0
			// �e�N�X�`���̓ǂݍ���
			//D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			//	TEXTURE_FILENAME,		// �t�@�C���̖��O
			//	&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif
		}
	}

	// �`�F�b�N�|�C���g�̏����ݒ�
	CheckPointWk[0][0] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, CHECK_POINT_Z);		// ����
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, CHECK_POINT_Z);				// ���S��
	CheckPointWk[2][0] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, CHECK_POINT_Z);		// �E��
	CheckPointWk[0][1] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, 0.0f);				// ���S��
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ���S
	CheckPointWk[2][1] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, 0.0f);				// ���S�E
	CheckPointWk[0][2] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, -CHECK_POINT_Z);		// ����
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -CHECK_POINT_Z);				// ���S��
	CheckPointWk[2][2] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, -CHECK_POINT_Z);		// �E��

	// �|���X�{�̂̏���������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �|���X�̎��_(�ʒu���W)�̏�����
		//police->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		police->Eye = CheckPointWk[i][i];
		// �|���X�̒����_�̏�����
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �|���X�̏�����̏�����
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �|���X�̌����̏�����
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �|���X�̈ړ��ʂ̏�����
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		police->rotBasis = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		// �|���X�̃X�P�[���̏�����
		police->scl = D3DXVECTOR3(POLICE_SCALE_X, POLICE_SCALE_Y, POLICE_SCALE_Z);
		// �|���X�̉�]���̏�����
		police->axisXZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		police->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �|���X�̉�]�p�x�̏�����
		police->fangleXZ = 0.0f;
		police->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		police->use = true;
		// �����蔻��L���t���O��true�ɐݒ�
		police->able_hit = true;
		// �|���X�̃t���[���J�E���g������
		police->key = 0;
		// �e�q�֌W���ʔԍ��̏����ݒ�(�ԍ���1����)
		police->num = i + 1;
		// ��]�؂�ւ��t���O��NULL��
		police->rotf = NULL;
		// �{�̂̃^�C�v��NULL��
		police->type = NULL;
		// �ړ��t���O�̏�����
		police->movef = true;
		// �ړ��؂�ւ��p�J�E���^�̏�����
		police->key2 = 0;
	}
	// �A�[���̏���������
	police = &policeWk[0];
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		// �A�[���̎��_(�ʒu���W)�̏�����
		//policeArm->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		policeArm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// �A�[���̒����_�̏�����
		policeArm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �A�[���̏�����̏�����
		policeArm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̌����̏�����
		policeArm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �A�[���̈ړ��ʂ̏�����
		policeArm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		policeArm->rotBasis = D3DXVECTOR3(POLICE_ARM_ROTBASIS_X * POLICE_SCALE_X, POLICE_ARM_ROTBASIS_Y * POLICE_SCALE_Y, POLICE_ARM_ROTBASIS_Z * POLICE_SCALE_Z);
		// �A�[���̃X�P�[���̏�����
		//policeArm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		policeArm->scl = police->scl;
		// �A�[���̉�]���̏�����
		policeArm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeArm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̉�]�p�x�̏�����
		policeArm->fangleXZ = 0.0f;
		policeArm->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		policeArm->use = false;
		// �A�[���̃t���[���J�E���g������
		policeArm->key = 0;
		// �A�[���̃^�C�v�̏�����(�E�r��0�E���r��1)
		if (i < POLICE_MAX)
		{	// �E�r���|���X�̐l�����p��
			policeArm->type = 0;
		}
		if (i >= POLICE_MAX)
		{	// ���r���|���X�̐l�����p��
			policeArm->type = 1;
		}
		// ��]�؂�ւ��t���O��true�ɐݒ�
		policeArm->rotf = true;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		policeArm->num = 0;
	}
	// ���b�O�̏���������
	police = &policeWk[0];
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		// ���b�O�̎��_(�ʒu���W)�̏�����
		//policeLeg->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		policeLeg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// ���b�O�̒����_�̏�����
		policeLeg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// ���b�O�̏�����̏�����
		policeLeg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���b�O�̌����̏�����
		policeLeg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ���b�O�̈ړ��ʂ̏�����
		policeLeg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		policeLeg->rotBasis = D3DXVECTOR3(POLICE_LEG_ROTBASIS_X * POLICE_SCALE_X, POLICE_LEG_ROTBASIS_Y * POLICE_SCALE_Y, POLICE_LEG_ROTBASIS_Z * POLICE_SCALE_Z);
		// ���b�O�̃X�P�[���̏�����
		policeLeg->scl = police->scl;
		// ���b�O�̉�]���̏�����
		policeLeg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeLeg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���b�O�̉�]�p�x�̏�����
		policeLeg->fangleXZ = 0.0f;
		policeLeg->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		policeLeg->use = false;
		// ���b�O�̃t���[���J�E���g������
		policeLeg->key = 0;
		// ���b�O�̃^�C�v�̏�����(�E����0�E������1)
		if (i < POLICE_MAX)
		{	// �E�����|���X�̐l�����p��
			policeLeg->type = 0;
		}
		if (i >= POLICE_MAX)
		{	// �������|���X�̐l�����p��
			policeLeg->type = 1;
		}
		// ��]�؂�ւ��t���O��false�ɐݒ�
		policeLeg->rotf = false;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		policeLeg->num = 0;
	}

	// �e�q�֌W�ݒ菈��
	SetParts();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPolice(void)
{
	// �{��
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
	// �A�[��
	for (int i = 0; i < POLICE_ARM_TYPE_MAX; i++)
	{
		if (g_pD3DTexturePoliceArm[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePoliceArm[i]->Release();
			g_pD3DTexturePoliceArm[i] = NULL;
		}
		if (g_pD3DXMeshPoliceArm[i] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshPoliceArm[i]->Release();
			g_pD3DXMeshPoliceArm[i] = NULL;
		}
		if (g_pD3DXBuffMatPoliceArm[i] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatPoliceArm[i]->Release();
			g_pD3DXBuffMatPoliceArm[i] = NULL;
		}
	}
	// ���b�O
	for (int i = 0; i < POLICE_LEG_TYPE_MAX; i++)
	{
		if (g_pD3DTexturePoliceLeg[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePoliceLeg[i]->Release();
			g_pD3DTexturePoliceLeg[i] = NULL;
		}
		if (g_pD3DXMeshPoliceLeg[i] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshPoliceLeg[i]->Release();
			g_pD3DXMeshPoliceLeg[i] = NULL;
		}
		if (g_pD3DXBuffMatPoliceLeg[i] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatPoliceLeg[i]->Release();
			g_pD3DXBuffMatPoliceLeg[i] = NULL;
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolice(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// �ړ������؂�ւ�����
	PoliceMoveControl(3 * 60);
	// �����蔻��̈�莞�Ԗ�������
	InvalidCollision(POLICE_COLLISION_FRAME);
	// �|���X�̓����蔻�菈��
	PoliceCollision();
	// �|���X���m�̓����蔻�菈��
	PoliceEachCollision();
	// �|���X�ړ�����
	PoliceMove();
	// �A�j���[�V��������
	Animation();

#ifdef _DEBUG
	police = &policeWk[0];
	PrintDebugProc("[�|���X�̈ʒu  �F(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[�|���X�̒����_  �F(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[�|���X�̈ړ��x�N�g��  �F(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	//PrintDebugProc("[�|���X�̌���  �F(%f)]\n", police->rot);
	PrintDebugProc("[�|���X�̎g�p���  �F(%d)]\n", police->use);
	//PrintDebugProc("[�E�r�̉�]�p�x  �F(%f)]\n", policeArm->fangleXZ);
	PrintDebugProc("[�|���X�̓����蔻��L�����  �F(%d)]\n", police->able_hit);
#endif

	police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (GetStage() == STAGE_GAME)
		{
			// �V���h�E
			if (!police->bShadow)
			{	// �V���h�E�ݒu
				police->nIdxShadow = CreateShadow(police->Eye, 25.0f, 25.0f);
				police->fSizeShadow = PLAYER_SHADOW_SIZE;
				police->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
				police->bShadow = true;
			}
			else
			{
				// �V���h�E�Ǘ�
				SetPositionShadow(police->nIdxShadow, D3DXVECTOR3(police->Eye.x, 0.2f, police->Eye.z));
				SetVertexShadow(police->nIdxShadow, police->fSizeShadow, police->fSizeShadow);
				SetColorShadow(police->nIdxShadow, police->colShadow);
			}
		}
		
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// �|���X�{�̂̕`�揈��
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (police->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPolice);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPolice, NULL, NULL, &police->scl, &police->rotBasis, &police->qAnswer, &police->Eye);
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
	// �|���X�̃A�[���̕`��
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		if (policeArm->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPoliceArm);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPoliceArm, NULL, NULL, &policeArm->scl, &policeArm->rotBasis, &policeArm->qAnswer, &policeArm->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPoliceArm);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPoliceArm[policeArm->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPoliceArm[policeArm->type]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePoliceArm[policeArm->type]);
				// �`��
				g_pD3DXMeshPoliceArm[policeArm->type]->DrawSubset(nCntMat);

			}
			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// �|���X�̃��b�O�̕`��
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		if (policeLeg->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPoliceLeg);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPoliceLeg, NULL, NULL, &policeLeg->scl, &policeLeg->rotBasis, &policeLeg->qAnswer, &policeLeg->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPoliceLeg);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPoliceLeg[policeLeg->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPoliceLeg[policeLeg->type]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePoliceLeg[policeLeg->type]);
				// �`��
				g_pD3DXMeshPoliceLeg[policeLeg->type]->DrawSubset(nCntMat);
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
// �����蔻�薳�������֐�(�����F�����蔻�薳�������������܂ł̃t���[����)
//=============================================================================
void InvalidCollision(int frame)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (!police->able_hit) police->key++;
		// �����蔻�薳�����Ԃ̉���
		if (police->key % frame == 0)
		{
			police->key = 0;
			police->able_hit = true;
		}
	}
}
//=============================================================================
// �����蔻�菈���֐�
//=============================================================================
void PoliceCollision(void)
{
	POLICE *police = &policeWk[0];

	for (int k = 0; k < POLICE_MAX; k++, police++)
	{	// �����蔻�肪�L���ȃ|���X�̂݃`�F�b�N
		if (!police->able_hit) continue;
		for (int j = 0; j < CHECK_POINT_Y_MAX; j++)
		{	// �z��Y�v�f�ɂ��ă`�F�b�N
			for (int i = 0; i < CHECK_POINT_X_MAX; i++)
			{	// �z��X�v�f�ɂ��ă`�F�b�N
				if (CollisionBC(police->Eye, CheckPointWk[j][i], POLICE_RADIUS, CHECK_POINT_RADIUS))
				{	// �`�F�b�N�|�C���g�ɐN��������|���X�̈ړ��ݒ�
					SetPoliceMove(police, j, i);
					// �����蔻��L���t���O��false��
					police->able_hit = false;
					break;
				}
			}
		}
	}
}
//=============================================================================
// �p�[�c�e�q�֌W�ݒ�֐�
//=============================================================================
void SetParts(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// �{�̂ɘr�p�[�c���֘A�t����
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �g�p��Ԃ̃|���X�ɂ̂݃p�[�c���Z�b�g
		if (!police->use) continue;
		// ���g�p�̉E�r�p�[�c���Z�b�g
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{	// ���g�p���E�r�ł��邱�Ƃ̃`�F�b�N
			if ((policeArm->use) || (policeArm->type == 1)) continue;
			// �{�̂Ɠ����ԍ����Z�b�g
			policeArm->num = police->num;
			// �g�p��Ԃɂ���
			policeArm->use = true;
			break;
		}
		// ���g�p�̍��r�p�[�c���Z�b�g
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{	// ���g�p�����r�ł��邱�Ƃ̃`�F�b�N
			if ((policeArm->use) || (policeArm->type == 0)) continue;
			// �{�̂Ɠ����ԍ����Z�b�g
			policeArm->num = police->num;
			// �g�p��Ԃɂ���
			policeArm->use = true;
			break;
		}
	}
	// �{�̂ɑ��p�[�c���֘A�t����
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �g�p��Ԃ̃|���X�ɂ̂݃p�[�c���Z�b�g
		if (!police->use) continue;
		// ���g�p�̉E���p�[�c���Z�b�g
		policeLeg = &policeLegWk[0];
		for (int j = 0; j < POLICE_LEG_MAX; j++, policeLeg++)
		{	// ���g�p���E���ł��邱�Ƃ̃`�F�b�N
			if ((policeLeg->use) || (policeLeg->type == 1)) continue;
			// �{�̂Ɠ����ԍ����Z�b�g
			policeLeg->num = police->num;
			// �g�p��Ԃɂ���
			policeLeg->use = true;
			break;
		}
		// ���g�p�̍����p�[�c���Z�b�g
		policeLeg = &policeLegWk[0];
		for (int j = 0; j < POLICE_LEG_MAX; j++, policeLeg++)
		{	// ���g�p�������ł��邱�Ƃ̃`�F�b�N
			if ((policeLeg->use) || (policeLeg->type == 0)) continue;
			// �{�̂Ɠ����ԍ����Z�b�g
			policeLeg->num = police->num;
			// �g�p��Ԃɂ���
			policeLeg->use = true;
			break;
		}
	}
}
//=============================================================================
// �|���X�̈ړ��ݒ�֐�(����1:�|���X�\���̂ւ̃|�C���^,����2:�񎟌��z���Y�v�f,����3:�񎟌��z���X�v�f)
//=============================================================================
void SetPoliceMove(POLICE *police, int y, int x)
{
	int n = 0;
	int m = 0;

	// �|���X�����_������ړ�����
	while (1)
	{	// �����_���Ŏ��̖ڕW�|�C���g������
		n = rand() % CHECK_POINT_Y_MAX;		// �z���Y�v�f�ԍ��������_���ŋ��߂�
		m = rand() % CHECK_POINT_X_MAX;		// �z���X�v�f�ԍ��������_���ŋ��߂�
											// �㉺���E�Ȃ狖��
		if (n == y && m == x + 1 || n == y && m == x - 1 || m == x && n == y + 1 || m == x && n == y - 1) break;
	}
	// �����_�����̖ڕW�|�C���g�ɃZ�b�g
	police->At = CheckPointWk[n][m];
	// �����_���������߂�Y����]�p�x�����߂�
	D3DXVECTOR3 vec = police->Eye - police->At;		// �����_�ւ̃x�N�g�������߂�
	police->fangleY = (atan2f(vec.x, vec.z));		// ��]�p�x�����߂�
													// ���݂̃|���X�̍��W���玟�̖ڕW�|�C���g�ւ̈ړ��x�N�g�������߂�
	police->move = CheckPointWk[n][m] - police->Eye;
	// �ړ��x�N�g���𐳋K��
	D3DXVec3Normalize(&police->move, &police->move);
	// �ړ����x����
	police->move = police->move * POLICE_SPEED;
}
//=============================================================================
// �|���X�̈ړ��֐�
//=============================================================================
void PoliceMove(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// �|���X�{�̂̈ړ�
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{	// �ړ��t���O��true�̎��݈̂ړ�
		if (!police->movef) continue;
		police->Eye.x += police->move.x;
		police->Eye.y += police->move.y;
		police->Eye.z += police->move.z;
	}
	// �{�̂Ɛe�q�֌W�̃p�[�c���ړ�
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �A�[���̈ړ�
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{
			if (!policeArm->use) continue;
			if (policeArm->num == police->num)
			{	// �{�̂̍��W�ƈ�v������
				policeArm->Eye = police->Eye;
				policeArm->At = police->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				policeArm->fangleY = police->fangleY;
			}
		}
		// ���b�O�̈ړ�
		policeLeg = &policeLegWk[0];
		for (int k = 0; k < POLICE_LEG_MAX; k++, policeLeg++)
		{	// �{�̂̍��W�ƈ�v������
			if (!policeLeg->use) continue;
			if (policeLeg->num == police->num)
			{
				policeLeg->Eye = police->Eye;
				policeLeg->At = police->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				policeLeg->fangleY = police->fangleY;
			}
		}
	}
}
//=============================================================================
// �A�j���[�V�����ݒ�֐�
// (����1:�ݒ�Ώۂ̃N���X�ւ̃|�C���^,
//  ����2:XZ����]�p�x,
//  ����3:�ꉝ���ɂ�����t���[����,
//  ����4:��]��XZ,
//  ����5:��]��Y)
//=============================================================================
template <typename CLASS> void SetAnimation(CLASS *pIn, float fAngle, int frame, D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY)		// ����:typename��class�Ə����Ă��悢
{
	if (pIn->use)
	{	// �g�p�����g�p���`�F�b�N
		// ��]��XZ�̐ݒ�
		pIn->axisXZ = AxisXZ;
		// ��]��Y�̐ݒ�
		pIn->axisY = AxisY;
		// XZ����]�p�x�̐ݒ�
		if (pIn->type == 0)
		{	// �E�p�[�c�̏ꍇ
			if (pIn->fangleXZ >= fAngle)
			{	// ���p�x�܂Ńp�[�c�オ������t���O�؂�ւ�
				pIn->rotf = false;
			}
			if (pIn->fangleXZ <= -fAngle)
			{	// ���p�x�܂Ńp�[�c�オ������t���O�؂�ւ�
				pIn->rotf = true;
			}
			if (pIn->rotf == true)
			{	// ���̉�]
				pIn->fangleXZ += fAngle / frame;
				if (pIn->fangleXZ > D3DX_PI)
				{
					pIn->fangleXZ -= D3DX_PI * 2.0f;
				}
			}
			if (pIn->rotf == false)
			{	// ���̉�]
				pIn->fangleXZ -= fAngle / frame;
				if (pIn->fangleXZ < -D3DX_PI)
				{
					pIn->fangleXZ += D3DX_PI * 2.0f;
				}
			}
		}
		if (pIn->type == 1)
		{	// ���p�[�c�̏ꍇ
			if (pIn->fangleXZ >= fAngle)
			{	// ���p�x�܂Ńp�[�c�オ������t���O�؂�ւ�
				pIn->rotf = true;
			}
			if (pIn->fangleXZ <= -fAngle)
			{	// ���p�x�܂Ńp�[�c�オ������t���O�؂�ւ�
				pIn->rotf = false;
			}
			if (pIn->rotf == true)
			{	// ���̉�]
				pIn->fangleXZ -= fAngle / frame;
				if (pIn->fangleXZ < -D3DX_PI)
				{
					pIn->fangleXZ += D3DX_PI * 2.0f;
				}
			}
			if (pIn->rotf == false)
			{	// ���̉�]
				pIn->fangleXZ += fAngle / frame;
				if (pIn->fangleXZ > D3DX_PI)
				{
					pIn->fangleXZ -= D3DX_PI * 2.0f;
				}
			}
		}
		// XZ��]���x�N�g����0�̏ꍇ�̃G���[����
		if (pIn->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{	// ��]�p�x��0�ɂ���
			pIn->fangleXZ = 0.0f;
		}
		// Y��]���x�N�g����0�̏ꍇ�̃G���[����
		if (pIn->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{	// ��]�p�x��0�ɂ���
			pIn->fangleY = 0.0f;
		}
		// ��]�N�H�[�^�j�I���𐶐�
		D3DXQuaternionRotationAxis(&pIn->qRotateXZ, &pIn->axisXZ, pIn->fangleXZ);	// XZ����]�N�H�[�^�j�I������
		D3DXQuaternionRotationAxis(&pIn->qRotateY, &pIn->axisY, pIn->fangleY);		// Y����]�N�H�[�^�j�I������(At�Ɍ�������)
		D3DXQuaternionMultiply(&pIn->qAnswer, &pIn->qRotateXZ, &pIn->qRotateY);		// ��]�N�H�[�^�j�I��������
	}
}
//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void Animation(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// �|���X�{�̃A�j���[�V��������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		SetAnimation(police, NULL, NULL,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// �A�[���A�j���[�V��������
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		SetAnimation(policeArm, POLICE_ARM_ANGLE, POLICE_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// ���b�O�A�j���[�V��������
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		SetAnimation(policeLeg, POLICE_LEG_ANGLE, POLICE_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
}
//=============================================================================
// �|���X���m�̓����蔻�菈���֐�
//=============================================================================
void PoliceEachCollision(void)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++)
	{	// �g�p��Ԃ̃|���X�̂݃`�F�b�N
		if (!policeWk[i].use) continue;
		for (int j = i + 1; j < POLICE_MAX; j++)
		{	// �g�p��Ԃ̃|���X�̂݃`�F�b�N
			if (!policeWk[j].use) continue;
			if (CollisionBC(policeWk[i].Eye, policeWk[j].Eye, POLICE_RADIUS + POLICE_RADIUS_VALUE, POLICE_RADIUS + POLICE_RADIUS_VALUE))
			{	// �|���X���m���Ԃ�������
				// ���݂���move�x�N�g���𔽓]
				police[i].move = -police[i].move;
				police[j].move = -police[j].move;
				// ���������](�V����Y����]�p�x�����߂�)
				police[i].fangleY = police[i].fangleY + D3DX_PI;
				police[j].fangleY = police[j].fangleY + D3DX_PI;
				// �`�F�b�N�|�C���g�Ƃ̓����蔻��L���t���O��true��
				police[i].able_hit = true;
				police[j].able_hit = true;
			}
		}
	}
}
//=============================================================================
// �ړ����������֐�(�����F�ړ����������������܂ł̃t���[����)
//=============================================================================
void PoliceMoveControl(int frame)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (!police->movef) police->key2++;
		// �ړ��������Ԃ̉���
		if (police->key2 % frame == 0)
		{
			police->key2 = 0;
			police->movef = true;
		}
	}
}
