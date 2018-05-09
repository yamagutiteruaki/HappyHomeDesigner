//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �v�F��
//
//=============================================================================
#include "debugproc.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "stage.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(1.00f)						// �ړ����x�W��
#define	RATE_MOVE_PLAYER		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_PLAYER		(0.20f)						// ��]�����W��

#define	PLAYER_ANIM_MAX			(1)							// �v���C���[�̃A�j���[�V�����p�^�[����
#define	PLAYER_ANIM_SEC			(1)							// �A�j���[�V�����ꏄ�ɂ�����b��

#define PLAYER_HP				(1)							// �c�@

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerMove(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer[PLAYER_ANIM_MAX];		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer[PLAYER_ANIM_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer[PLAYER_ANIM_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer[PLAYER_ANIM_MAX];			// �������̑���

D3DXMATRIX			g_mtxWorldPlayer;							// ���[���h�}�g���b�N�X

PLAYER				playerWk[PLAYER_MAX];						// �v���C���[�i�[���[�N

const char *FileNamePlayer[PLAYER_ANIM_MAX] =					// ���f���ǂݍ���
{
	"data/MODEL/PLAYER/player01.x",

};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];
	FIELD *field = GetField(0);

	if (nType == STAGE_INIT_FAST)
	{
		for (int i = 0; i < PLAYER_ANIM_MAX; i++)
		{
			g_pD3DTexturePlayer[i] = NULL;
			g_pD3DXMeshPlayer[i] = NULL;
			g_pD3DXBuffMatPlayer[i] = NULL;


			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(FileNamePlayer[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPlayer[i],
				NULL,
				&g_nNumMatPlayer[i],
				&g_pD3DXMeshPlayer[i])))
			{
				return E_FAIL;
			}

		}

	}

	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// �v���C���[�̎��_�̏�����
		player->Eye = field->Pos;
		// �v���C���[�̒����_�̏�����
		player->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �v���C���[�̏�����̏�����
		player->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �v���C���[�̌����̏�����
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �v���C���[�̖ړI�̌����̏�����
		player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �v���C���[�̈ړ��ʂ̏�����
		player->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �v���C���[�̃X�P�[���̏�����
		player->scl = D3DXVECTOR3(0.9f, 0.9f, 0.9f);

		// use�t���O��true�ɐݒ�
		player->use = true;

		// �v���C���[��HP
		player->hp = PLAYER_HP;

		// �v���C���[�̈ړ����x������
		player->speed = VALUE_MOVE_PLAYER;

		// �A�j���[�V�����ԍ�������
		// �ŏ��͒�����Ԃɐݒ�
		player->anim = 0;

	}

	return S_OK;

}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		if (g_pD3DTexturePlayer[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePlayer[i]->Release();
			g_pD3DTexturePlayer[i] = NULL;
		}

		if (g_pD3DXMeshPlayer[i] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshPlayer[i]->Release();
			g_pD3DXMeshPlayer[i] = NULL;
		}

		if (g_pD3DXBuffMatPlayer[i] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatPlayer[i]->Release();
			g_pD3DXBuffMatPlayer[i] = NULL;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER *player = &playerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)	// �g�p��ԂȂ�`�悷��
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, player->scl.x,
				player->scl.y,
				player->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer,
				&g_mtxWorldPlayer, &mtxScale);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

			//// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, player->Eye.x, player->Eye.y, player->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer[player->anim]->GetBufferPointer();

			for (int i = 0; i < (int)g_nNumMatPlayer[player->anim]; i++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer[player->anim]);

				// �`��
				g_pD3DXMeshPlayer[player->anim]->DrawSubset(i);

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
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PlayerMove();

#ifdef _DEBUG
	//PLAYER *player = &playerWk[0];
	//CAMERA *camera = GetCamera();

	//PrintDebugProc("player rot: %f\n", player->rotDest.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rot: %f\n", camera->rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera length: %f\n", camera->fLength);
	// PrintDebugProc("\n");
	
#endif

}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

//=============================================================================
// �v���C���[�̈ړ�
//=============================================================================
void PlayerMove(void)
{
	PLAYER *player = &playerWk[0];
	CAMERA *camera = GetCamera();

	float fDiffRotY;

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			player->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// ����ړ�
			player->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// ���ړ�
			player->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.50f;

		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			player->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			player->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// �E�ړ�
			player->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		player->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		player->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = camera->rotCamera.y;
	}

	// �ړ��ʂɊ�����������
	player->move.x += (0.0f - player->move.x) * RATE_MOVE_PLAYER;
	player->move.y += (0.0f - player->move.y) * RATE_MOVE_PLAYER;
	player->move.z += (0.0f - player->move.z) * RATE_MOVE_PLAYER;

	// �ʒu�ړ�
	player->Eye.x += player->move.x;
	player->Eye.y += player->move.y;
	player->Eye.z += player->move.z;

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = player->rotDest.y - player->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	player->rot.y += fDiffRotY * RATE_ROTATE_PLAYER;
	if (player->rot.y > D3DX_PI)
	{
		player->rot.y -= D3DX_PI * 2.0f;
	}
	if (player->rot.y < -D3DX_PI)
	{
		player->rot.y += D3DX_PI * 2.0f;
	}

}