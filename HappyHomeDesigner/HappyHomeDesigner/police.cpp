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
#include "collision.h"
#include "calculate.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
D3DXMATRIX* FixedPostureLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
D3DXMATRIX* VariablePostureLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);

void PoliceMove(POLICE *police, int y, int x);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice;									// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPolice;										// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPolice;									// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPolice;										// �������̑���

D3DXMATRIX			g_mtxWorldPolice;										// ���[���h�}�g���b�N�X

POLICE				policeWk[POLICE_MAX];									// �|���X�i�[���[�N

D3DXVECTOR3			CheckPointWk[CHECK_POINT_Y_MAX][CHECK_POINT_X_MAX];		// �`�F�b�N�|�C���g�i�[���[�N

int					animCnt;												// �A�j���J�E���g
int					sp_Update;												// �X�V�p�x�v�Z�p


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

	// �����]���_�̏����ݒ�
	CheckPointWk[0][0] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);		// ����(-300,0,300)
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, FIELD_SIZE_Z / 2);						// ���S��(0,0,300)
	CheckPointWk[2][0] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);			// �E��(300,0,300)
	CheckPointWk[0][1] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, 0.0f);					// ���S��(-300,0,0)
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// ���S(0,0,0)
	CheckPointWk[2][1] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, 0.0f);						// ���S�E(300,0,0)
	CheckPointWk[0][2] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// ����(-300,0,-300)
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -FIELD_SIZE_Z / 2);					// ���S��(0,0,-300)
	CheckPointWk[2][2] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// �E��(300,0,-300)


	// �|���X�̏���������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �|���X�̎��_(�ʒu���W)�̏�����
		//police->Eye = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
		police->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

		// �|���X�̒����_�̏�����
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �|���X�̏�����̏�����
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �|���X�̌����̏�����
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//police->rot = 0.0f;

		// �|���X�̈ړ��ʂ̏�����
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//police->move = CheckPointWk[0][0] - CheckPointWk[0][1];
		//D3DXVec3Normalize(&police->move, &police->move);

		//police->move = CheckPointWk[1][1] - CheckPointWk[0][0];
		//D3DXVec3Normalize(&police->move, &police->move);

		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		police->rotBasis = D3DXVECTOR3(0.0f, 60.0f, 0.0f);

		// �|���X�̃X�P�[���̏�����
		police->scl = D3DXVECTOR3(1.0f * 2, 1.0f * 2, 1.0f * 2);

		// �|���X�̉�]���̏�����
		police->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		police->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �|���X�̉�]�p�x�̏�����
		police->fangleXZ = 0.0f;
		police->fangleY = 0.0f;
		
		// use�t���O��true�ɐݒ�
		police->use = true;

		// �����蔻��L���t���O��true�ɐݒ�
		police->able_hit = true;

		// �|���X�̈ړ����x������
		police->speed = VALUE_MOVE_POLICE;

		// �|���X�̃t���[���J�E���g������
		police->key = 0;
	}




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

	// �����蔻��̈�莞�Ԗ�������
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		police->key++;
		// �����蔻�薳�����Ԃ̉���
		if (police->key % 120 == 0)
		{
			police->key = 0;
			police->able_hit = true;
		}
	}
	// �|���X�̓����蔻�菈��
	police = &policeWk[0];
	for (int k = 0; k < POLICE_MAX; k++, police++)
	{	// �|���X�ɂ��ă`�F�b�N
		if (police->able_hit)
		{	// �����蔻�肪�L���ȃ|���X�̂݃`�F�b�N
			for (int j = 0; j < CHECK_POINT_Y_MAX; j++)
			{	// �z��Y�v�f�ɂ��ă`�F�b�N
				for (int i = 0; i < CHECK_POINT_X_MAX; i++)
				{	// �z��X�v�f�ɂ��ă`�F�b�N
					if (CollisionBC(police->Eye, CheckPointWk[j][i], 70.0f, 70.0f))
					{	// �`�F�b�N�|�C���g�ɐN������������]�����A�ړ��x�N�g���Z�o
						PoliceMove(police, j, i);
						// �����蔻��L���t���O��false��
						police->able_hit = false;
						break;
					}
				}
			}
		}
	}
	// �|���X�ړ�����
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �ʒu�ړ�
		police->Eye.x += police->move.x;
		police->Eye.y += police->move.y;
		police->Eye.z += police->move.z;
	}

	// �|���X��]����
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// �N�H�[�^�j�I���ɂ���]��XZ����]�������߂�
		// ������̃x�N�g���Ɛi�s�����̃x�N�g���̊O�ς���]��
		//D3DXVec3Cross(&police->axis, D3DXVec3Normalize(&police->rotBasis, &police->rotBasis), D3DXVec3Normalize(&police->move, &police->move));
		D3DXVec3Normalize(&police->axisXZ, &police->axisXZ);
		D3DXVec3Normalize(&police->axisY, &police->axisY);

		// ��]�p�x�̐ݒ�
		police->fangleXZ += VALUE_ROTATE_CAMERA / 1.0f;
		if (police->fangleXZ > D3DX_PI)
		{
			police->fangleXZ -= D3DX_PI * 2.0f;
		}
		// XZ��]���x�N�g����0�̏ꍇ�̃G���[����
		if (police->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{	// ��]�p�x��0�ɂ���
			police->fangleXZ = 0.0f;
		}
		// Y��]���x�N�g����0�̏ꍇ�̃G���[����
		if (police->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{	// ��]�p�x��0�ɂ���
			police->fangleY = 0.0f;
		}
		// ��]�N�H�[�^�j�I���𐶐�
		D3DXQuaternionRotationAxis(&police->qRotateXZ, &police->axisXZ, police->fangleXZ);		// XZ����]�N�H�[�^�j�I������
		D3DXQuaternionRotationAxis(&police->qRotateY, &police->axisY, police->fangleY);			// Y����]�N�H�[�^�j�I������(At�Ɍ�������)
		D3DXQuaternionMultiply(&police->qAnswer, &police->qRotateXZ, &police->qRotateY);		// ��]�N�H�[�^�j�I��������
	}

	police = &policeWk[0];
#ifdef _DEBUG
	PrintDebugProc("[�|���X�̈ʒu  �F(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[�|���X�̒����_  �F(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[�|���X�̈ړ��x�N�g��  �F(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	PrintDebugProc("[�|���X�̌���  �F(%f)]\n", police->rot);
	PrintDebugProc("[�|���X�̎g�p���  �F(%d)]\n", police->use);

#endif
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
// �|���X�̈ړ������֐�(����1:�|���X�̃|�C���^,����2:�񎟌��z���Y�v�f,����3:�񎟌��z���X�v�f)
//=============================================================================
void PoliceMove(POLICE *police, int y, int x)
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
	police->move = police->move * VALUE_MOVE_POLICE;
}
