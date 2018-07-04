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
#include "home.h"
#include "calculate.h"
#include "collision.h"
#include "fade.h"
#include "button.h"
#include "shadow.h"
#include "inputCtrl.h"
#include "police.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(1.00f)						// �ړ����x�W��
#define	RATE_MOVE_PLAYER		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_PLAYER		(0.20f)						// ��]�����W��
#define MOVE_LIMIT				(10)
#define PLAYER_POS_ADJ			(20.0f)						// �����ʒu�����l
#define PLAYER_WT_ADJ			(0.08f)						// �ړ����x�����l
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerMove(void);
void PlayerMoveWt(void);
void PlayerBorder(void);
void PlayerEntrance(void);
void PlayerPosReset(void);

void PlayerPartsMove(void);
void PlayerAnimation(void);
void SetPlayerParts(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
// �v���C���[�{�̊֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;				// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer;					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer;				// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer;					// �������̑���
D3DXMATRIX			g_mtxWorldPlayer;					// ���[���h�}�g���b�N�X
PLAYER				playerWk[PLAYER_MAX];				// �v���C���[�i�[���[�N
// �v���C���[�E�A�[���֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_R_Arm;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer_R_Arm;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_R_Arm;			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer_R_Arm;				// �������̑���
D3DXMATRIX			g_mtxWorldPlayer_R_Arm;				// ���[���h�}�g���b�N�X
PLAYER_R_ARM		player_R_ArmWk[PLAYER_R_ARM_MAX];	// �v���C���[�E�A�[���i�[���[�N
// �v���C���[���A�[���֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_L_Arm;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer_L_Arm;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_L_Arm;			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer_L_Arm;				// �������̑���
D3DXMATRIX			g_mtxWorldPlayer_L_Arm;				// ���[���h�}�g���b�N�X
PLAYER_L_ARM		player_L_ArmWk[PLAYER_L_ARM_MAX];	// �v���C���[���A�[���i�[���[�N
// �v���C���[�̉E���b�O�֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_R_Leg;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer_R_Leg;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_R_Leg;			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer_R_Leg;				// �������̑���
D3DXMATRIX			g_mtxWorldPlayer_R_Leg;				// ���[���h�}�g���b�N�X
PLAYER_R_LEG		player_R_LegWk[PLAYER_R_LEG_MAX];	// �v���C���[�E���b�O�i�[���[�N
// �v���C���[�̍����b�O�֌W
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_L_Leg;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshPlayer_L_Leg;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_L_Leg;			// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer_L_Leg;				// �������̑���
D3DXMATRIX			g_mtxWorldPlayer_L_Leg;				// ���[���h�}�g���b�N�X
PLAYER_L_LEG		player_L_LegWk[PLAYER_L_LEG_MAX];	// �v���C���[�����b�O�i�[���[�N
// ���̑�
bool dash = FALSE;
int dashTimer = 0;
float vel = 0.0f;
const float velRate = 0.4f;
int resetno;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// �v���C���[�E�A�[���|�C���^������
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// �v���C���[���A�[���|�C���^������
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// �v���C���[�E���b�O�|�C���^������
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// �v���C���[�����b�O�|�C���^������
	FIELD *field = GetField(0);

	if (nType == STAGE_INIT_FAST)
	{
		// �v���C���[�{�̂̃��f���ǂݍ���
		g_pD3DTexturePlayer = NULL;
		g_pD3DXMeshPlayer = NULL;
		g_pD3DXBuffMatPlayer = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer,
			NULL,
			&g_nNumMatPlayer,
			&g_pD3DXMeshPlayer)))
		{
			return E_FAIL;
		}
		// �E�A�[���̃��f���ǂݍ���
		g_pD3DTexturePlayer_R_Arm = NULL;
		g_pD3DXMeshPlayer_R_Arm = NULL;
		g_pD3DXBuffMatPlayer_R_Arm = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_R_ARM_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_R_Arm,
			NULL,
			&g_nNumMatPlayer_R_Arm,
			&g_pD3DXMeshPlayer_R_Arm)))
		{
			return E_FAIL;
		}
		// ���A�[���̃��f���ǂݍ���
		g_pD3DTexturePlayer_L_Arm = NULL;
		g_pD3DXMeshPlayer_L_Arm = NULL;
		g_pD3DXBuffMatPlayer_L_Arm = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_L_ARM_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_L_Arm,
			NULL,
			&g_nNumMatPlayer_L_Arm,
			&g_pD3DXMeshPlayer_L_Arm)))
		{
			return E_FAIL;
		}
		// �E���b�O�̃��f���ǂݍ���
		g_pD3DTexturePlayer_R_Leg = NULL;
		g_pD3DXMeshPlayer_R_Leg = NULL;
		g_pD3DXBuffMatPlayer_R_Leg = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_R_LEG_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_R_Leg,
			NULL,
			&g_nNumMatPlayer_R_Leg,
			&g_pD3DXMeshPlayer_R_Leg)))
		{
			return E_FAIL;
		}
		// �����b�O�̃��f���ǂݍ���
		g_pD3DTexturePlayer_L_Leg = NULL;
		g_pD3DXMeshPlayer_L_Leg = NULL;
		g_pD3DXBuffMatPlayer_L_Leg = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_L_LEG_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_L_Leg,
			NULL,
			&g_nNumMatPlayer_L_Leg,
			&g_pD3DXMeshPlayer_L_Leg)))
		{
			return E_FAIL;
		}
	}
	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// �v���C���[�̎��_�̏�����
		player->Eye = D3DXVECTOR3(275.0f, 0.0f, -330.0f);
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
		// �v���C���[�̎��_�i�ꎞ�ۑ��j�̏�����
		player->posTmp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		// use�t���O��true�ɐݒ�
		player->use = true;
		// �v���C���[�̈ړ����x������
		player->speed = VALUE_MOVE_PLAYER;
		// �������̑��d��
		player->weight = 0;
		// �v���C���[�̎�����
		for (int j = 0; j < HAVE_MAX; j++)
		{
			player->havenum[j] = -1;
		}
		// �e
		player->nIdxShadow = -1;
		player->fSizeShadow= PLAYER_SHADOW_SIZE;
		player->colShadow= D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
		player->bShadow=false;

		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		player->rotBasis = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		// �v���C���[�̉�]���̏�����
		player->axisXZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �v���C���[�̉�]�p�x�̏�����
		player->fangleXZ = 0.0f;
		player->fangleY = 0.0f;
		// �v���C���[�̃t���[���J�E���g������
		player->key = 0;
		// �e�q�֌W���ʔԍ��̏����ݒ�(�ԍ���1����)
		player->num = i + 1;
	}
	// �E�A�[���̏���������
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		// �A�[���̎��_(�ʒu���W)�̏�����
		player_R_Arm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// �A�[���̒����_�̏�����
		player_R_Arm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �A�[���̏�����̏�����
		player_R_Arm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̌����̏�����
		player_R_Arm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �A�[���̈ړ��ʂ̏�����
		player_R_Arm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		player_R_Arm->rotBasis = 
			D3DXVECTOR3(PLAYER_R_ARM_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_R_ARM_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_R_ARM_ROTBASIS_Z * PLAYER_SCALE_Z);
		// �A�[���̃X�P�[���̏�����
		//player_R_Arm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_R_Arm->scl = player->scl;
		// �A�[���̉�]���̏�����
		player_R_Arm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_R_Arm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̉�]�p�x�̏�����
		player_R_Arm->fangleXZ = 0.0f;
		player_R_Arm->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		player_R_Arm->use = false;
		// �A�[���̃t���[���J�E���g������
		player_R_Arm->key = 0;
		// ��]�؂�ւ��t���O��true�ɐݒ�
		player_R_Arm->rotf = true;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		player_R_Arm->num = 0;
	}
	// ���A�[���̏���������
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		// �A�[���̎��_(�ʒu���W)�̏�����
		player_L_Arm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// �A�[���̒����_�̏�����
		player_L_Arm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �A�[���̏�����̏�����
		player_L_Arm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̌����̏�����
		player_L_Arm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �A�[���̈ړ��ʂ̏�����
		player_L_Arm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		player_L_Arm->rotBasis =
			D3DXVECTOR3(PLAYER_L_ARM_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_L_ARM_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_L_ARM_ROTBASIS_Z * PLAYER_SCALE_Z);
		// �A�[���̃X�P�[���̏�����
		//player_L_Arm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_L_Arm->scl = player->scl;
		// �A�[���̉�]���̏�����
		player_L_Arm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_L_Arm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̉�]�p�x�̏�����
		player_L_Arm->fangleXZ = 0.0f;
		player_L_Arm->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		player_L_Arm->use = false;
		// �A�[���̃t���[���J�E���g������
		player_L_Arm->key = 0;
		// ��]�؂�ւ��t���O��true�ɐݒ�
		player_L_Arm->rotf = false;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		player_L_Arm->num = 0;
	}
	// �E���b�O�̏���������
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		// �A�[���̎��_(�ʒu���W)�̏�����
		player_R_Leg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// �A�[���̒����_�̏�����
		player_R_Leg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �A�[���̏�����̏�����
		player_R_Leg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̌����̏�����
		player_R_Leg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �A�[���̈ړ��ʂ̏�����
		player_R_Leg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		player_R_Leg->rotBasis =
			D3DXVECTOR3(PLAYER_R_LEG_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_R_LEG_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_R_LEG_ROTBASIS_Z * PLAYER_SCALE_Z);
		// �A�[���̃X�P�[���̏�����
		//player_R_Leg->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_R_Leg->scl = player->scl;
		// �A�[���̉�]���̏�����
		player_R_Leg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_R_Leg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̉�]�p�x�̏�����
		player_R_Leg->fangleXZ = 0.0f;
		player_R_Leg->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		player_R_Leg->use = false;
		// �A�[���̃t���[���J�E���g������
		player_R_Leg->key = 0;
		// ��]�؂�ւ��t���O��true�ɐݒ�
		player_R_Leg->rotf = false;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		player_R_Leg->num = 0;
	}
	// �����b�O�̏���������
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		// �A�[���̎��_(�ʒu���W)�̏�����
		player_L_Leg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// �A�[���̒����_�̏�����
		player_L_Leg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// �A�[���̏�����̏�����
		player_L_Leg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̌����̏�����
		player_L_Leg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �A�[���̈ړ��ʂ̏�����
		player_L_Leg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ��]�̒��S�_�̏����ݒ�(���_�ł͂Ȃ��������炷�j
		player_L_Leg->rotBasis =
			D3DXVECTOR3(PLAYER_L_LEG_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_L_LEG_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_L_LEG_ROTBASIS_Z * PLAYER_SCALE_Z);
		// �A�[���̃X�P�[���̏�����
		//player_L_Leg->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_L_Leg->scl = player->scl;
		// �A�[���̉�]���̏�����
		player_L_Leg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_L_Leg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �A�[���̉�]�p�x�̏�����
		player_L_Leg->fangleXZ = 0.0f;
		player_L_Leg->fangleY = 0.0f;
		// use�t���O��true�ɐݒ�
		player_L_Leg->use = false;
		// �A�[���̃t���[���J�E���g������
		player_L_Leg->key = 0;
		// ��]�؂�ւ��t���O��true�ɐݒ�
		player_L_Leg->rotf = true;
		// �e�q�֌W���ʔԍ��̏����ݒ�(���g�p:0��,�g�p�F�{�̂Ɠ����ԍ�)
		player_L_Leg->num = 0;
	}
	// �p�[�c�e�q�֌W�ݒ�
	SetPlayerParts();
	resetno = 3;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// �{��
	if (g_pD3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
	if (g_pD3DXMeshPlayer != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer->Release();
		g_pD3DXMeshPlayer = NULL;
	}
	if (g_pD3DXBuffMatPlayer != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer->Release();
		g_pD3DXBuffMatPlayer = NULL;
	}
	// �E�A�[��
	if (g_pD3DTexturePlayer_R_Arm != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_R_Arm->Release();
		g_pD3DTexturePlayer_R_Arm = NULL;
	}
	if (g_pD3DXMeshPlayer_R_Arm != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_R_Arm->Release();
		g_pD3DXMeshPlayer_R_Arm = NULL;
	}
	if (g_pD3DXBuffMatPlayer_R_Arm != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_R_Arm->Release();
		g_pD3DXBuffMatPlayer_R_Arm = NULL;
	}
	// ���A�[��
	if (g_pD3DTexturePlayer_L_Arm != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_L_Arm->Release();
		g_pD3DTexturePlayer_L_Arm = NULL;
	}
	if (g_pD3DXMeshPlayer_L_Arm != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_L_Arm->Release();
		g_pD3DXMeshPlayer_L_Arm = NULL;
	}
	if (g_pD3DXBuffMatPlayer_L_Arm != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_L_Arm->Release();
		g_pD3DXBuffMatPlayer_L_Arm = NULL;
	}
	// �E���b�O
	if (g_pD3DTexturePlayer_R_Leg != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_R_Leg->Release();
		g_pD3DTexturePlayer_R_Leg = NULL;
	}
	if (g_pD3DXMeshPlayer_R_Leg != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_R_Leg->Release();
		g_pD3DXMeshPlayer_R_Leg = NULL;
	}
	if (g_pD3DXBuffMatPlayer_R_Leg != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_R_Leg->Release();
		g_pD3DXBuffMatPlayer_R_Leg = NULL;
	}
	// �����b�O
	if (g_pD3DTexturePlayer_L_Leg != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_L_Leg->Release();
		g_pD3DTexturePlayer_L_Leg = NULL;
	}
	if (g_pD3DXMeshPlayer_L_Leg != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_L_Leg->Release();
		g_pD3DXMeshPlayer_L_Leg = NULL;
	}
	if (g_pD3DXBuffMatPlayer_L_Leg != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_L_Leg->Release();
		g_pD3DXBuffMatPlayer_L_Leg = NULL;
	}

	//for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	//{
	//	if (g_pD3DTexturePlayer[i] != NULL)
	//	{// �e�N�X�`���̊J��
	//		g_pD3DTexturePlayer[i]->Release();
	//		g_pD3DTexturePlayer[i] = NULL;
	//	}

	//	if (g_pD3DXMeshPlayer[i] != NULL)
	//	{// ���b�V���̊J��
	//		g_pD3DXMeshPlayer[i]->Release();
	//		g_pD3DXMeshPlayer[i] = NULL;
	//	}

	//	if (g_pD3DXBuffMatPlayer[i] != NULL)
	//	{// �}�e���A���̊J��
	//		g_pD3DXBuffMatPlayer[i]->Release();
	//		g_pD3DXBuffMatPlayer[i] = NULL;
	//	}
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	//D3DXMATERIAL *pD3DXMat;
	//D3DMATERIAL9 matDef;

	//PLAYER *player = &playerWk[0];

	//for (int i = 0; i < PLAYER_MAX; i++, player++)
	//{
	//	if (player->use == true)	// �g�p��ԂȂ�`�悷��
	//	{
	//		// ���C�g��on
	//		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//		// �X�P�[���𔽉f
	//		D3DXMatrixScaling(&mtxScale, player->scl.x,
	//			player->scl.y,
	//			player->scl.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer,
	//			&g_mtxWorldPlayer, &mtxScale);

	//		// ��]�𔽉f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//		//// �ړ��𔽉f
	//		D3DXMatrixTranslation(&mtxTranslate, player->Eye.x, player->Eye.y, player->Eye.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

	//		// ���[���h�}�g���b�N�X�̐ݒ�
	//		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//		// ���݂̃}�e���A�����擾
	//		pDevice->GetMaterial(&matDef);

	//		// �}�e���A�����ɑ΂���|�C���^���擾
	//		pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer->GetBufferPointer();

	//		for (int i = 0; i < (int)g_nNumMatPlayer; i++)
	//		{
	//			// �}�e���A���̐ݒ�
	//			pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

	//			// �e�N�X�`���̐ݒ�
	//			pDevice->SetTexture(0, g_pD3DTexturePlayer);

	//			// �`��
	//			g_pD3DXMeshPlayer->DrawSubset(i);

	//		}

	//		// ���C�g��off
	//		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	}

	//}


	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	PLAYER *player = &playerWk[0];						// �v���C���[�{�̃|�C���^������
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// �v���C���[�E�A�[���|�C���^������
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// �v���C���[���A�[���|�C���^������
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// �v���C���[�E���b�O�|�C���^������
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// �v���C���[�����b�O�|�C���^������

	// �v���C���[�{�̂̕`�揈��
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPlayer, NULL, NULL, &player->scl, &player->rotBasis, &player->qAnswer, &player->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer);
				// �`��
				g_pD3DXMeshPlayer->DrawSubset(nCntMat);
			}
			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// �v���C���[�̉E�A�[���̕`��
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		if (player_R_Arm->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer_R_Arm);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPlayer_R_Arm, NULL, NULL, &player_R_Arm->scl, &player_R_Arm->rotBasis, &player_R_Arm->qAnswer, &player_R_Arm->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_R_Arm);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_R_Arm->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_R_Arm; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer_R_Arm);
				// �`��
				g_pD3DXMeshPlayer_R_Arm->DrawSubset(nCntMat);

			}
			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// �v���C���[�̍��A�[���̕`��
	for (int i = 0; i < PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		if (player_L_Arm->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer_L_Arm);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPlayer_L_Arm, NULL, NULL, &player_L_Arm->scl, &player_L_Arm->rotBasis, &player_L_Arm->qAnswer, &player_L_Arm->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_L_Arm);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_L_Arm->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_L_Arm; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer_L_Arm);
				// �`��
				g_pD3DXMeshPlayer_L_Arm->DrawSubset(nCntMat);

			}
			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// �v���C���[�̉E���b�O�̕`��
	for (int i = 0; i < PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		if (player_R_Leg->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer_R_Leg);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPlayer_R_Leg, NULL, NULL, &player_R_Leg->scl, &player_R_Leg->rotBasis, &player_R_Leg->qAnswer, &player_R_Leg->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_R_Leg);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_R_Leg->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_R_Leg; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer_R_Leg);
				// �`��
				g_pD3DXMeshPlayer_R_Leg->DrawSubset(nCntMat);
			}
			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// �v���C���[�̍����b�O�̕`��
	for (int i = 0; i < PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		if (player_L_Leg->use == true)
		{	// �g�p��ԂȂ�`�悷��
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer_L_Leg);
			// ���[���h�}�g���b�N�X�쐬
			D3DXMatrixTransformation(&g_mtxWorldPlayer_L_Leg, NULL, NULL, &player_L_Leg->scl, &player_L_Leg->rotBasis, &player_L_Leg->qAnswer, &player_L_Leg->Eye);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_L_Leg);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_L_Leg->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_L_Leg; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer_L_Leg);
				// �`��
				g_pD3DXMeshPlayer_L_Leg->DrawSubset(nCntMat);
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
	PLAYER *player = GetPlayer(0);
	PlayerBorder();

	player->posTmp = player->Eye;

	PlayerMove();

	//AreaHouse(tempPos);
	PlayerEntrance();

	// �A�j���[�V��������
	PlayerAnimation();

	PrintDebugProc("player pos: %f %f %f\n", player->Eye.x, player->Eye.y, player->Eye.z);
	PrintDebugProc("player move: %f %f %f\n", player->move.x, player->move.y, player->move.z);

#ifdef _DEBUG
	CAMERA *camera = GetCamera();

	//PrintDebugProc("\n");

	//PrintDebugProc("player rot: %f\n", player->rotDest.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rot: %f\n", camera->rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rotDest: %f\n", camera->rotDest);
	//PrintDebugProc("\n");

	PrintDebugProc("space 0: %d\n", player->havenum[0]);
	PrintDebugProc("space 1: %d\n", player->havenum[1]);
	PrintDebugProc("space 2: %d\n", player->havenum[2]);
	PrintDebugProc("space 3: %d\n", player->havenum[3]);
	PrintDebugProc("space 4: %d\n", player->havenum[4]);
	PrintDebugProc("wt: %d\n", player->weight);
	PrintDebugProc("dash: %f\n", vel);

	if (GetKeyboardTrigger(DIK_V))
	{
		dash = TRUE;
		dashTimer = 0;
		vel = 16.0f;


	}

	if (dash == TRUE)
	{
		player->move.x = -sinf(player->rot.y) * vel;
		player->move.z = -cosf(player->rot.y) * vel;

		dashTimer++;
		vel -= velRate;

		if (dashTimer >= 10)
		{
			dash = FALSE;
			dashTimer = 0;
		}
	}


#endif

	// �p�x���C��
	player->rot.y = PiCalculate360(player->rot.y);
	player->rotDest.y = PiCalculate360(player->rotDest.y);

	if (GetStage() == STAGE_GAME
		||GetStage() == STAGE_HOUSE1
		||GetStage() == STAGE_HOUSE2
		||GetStage() == STAGE_HOUSE3
		||GetStage() == STAGE_MYHOUSE)
	{
		// �V���h�E
		if (!player->bShadow)
		{	// �V���h�E�ݒu
			player->nIdxShadow = CreateShadow(player->Eye, 25.0f, 25.0f);
			player->fSizeShadow = PLAYER_SHADOW_SIZE;
			player->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
			player->bShadow = true;
		}
		else
		{
			// �V���h�E�Ǘ�
			SetPositionShadow(player->nIdxShadow, D3DXVECTOR3(player->Eye.x, 0.2f, player->Eye.z));
			SetVertexShadow(player->nIdxShadow, player->fSizeShadow, player->fSizeShadow);
			SetColorShadow(player->nIdxShadow, player->colShadow);
		}
	}
	else if (GetStage() == STAGE_RESULT)
	{
		ReleaseShadow(player->nIdxShadow);
		player->bShadow = false;
	}
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
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

	float fDiffRotY;

	if (GetKeyboardPress(kb->LEFT)||IsButtonPressed(0, gp->LEFT) || IsButtonPressed(0, gp->LEFT_POV))
	{
		if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
		{// ���O�ړ�
			player->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
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
	else if (GetKeyboardPress(kb->RIGHT) || IsButtonPressed(0, gp->RIGHT) || IsButtonPressed(0, gp->RIGHT_POV))
	{
		if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
		{// �E�O�ړ�
			player->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
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
	else if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
	{// �O�ړ�
		player->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
	{// ��ړ�
		player->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = camera->rotCamera.y;
	}

	// �ړ��ʂɊ�����������
	player->move.x += (0.0f - player->move.x) * RATE_MOVE_PLAYER;
	player->move.y += (0.0f - player->move.y) * RATE_MOVE_PLAYER;
	player->move.z += (0.0f - player->move.z) * RATE_MOVE_PLAYER;

	// �����d�ʂɂ���Ĉړ����x�̏C��
	// PlayerMoveWt();



	// �ʒu�ړ�
	player->Eye.x += player->move.x;
	player->Eye.y += player->move.y;
	player->Eye.z += player->move.z;
	// �v���C���[�̃p�[�c�ړ�
	PlayerPartsMove();

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

	// �p�x���C��
	player->rot.y = PiCalculate360(player->rot.y);

	// �����_���������߂�Y����]�p�x�����߂�
	player->fangleY = player->rot.y;		// ��]�p�x�����߂�

}

//=============================================================================
// �v���C���[�̈ړ������i�t�B�[���h�j
//=============================================================================
void PlayerBorder(void)
{
	PLAYER *player = &playerWk[0];
	int fieldnum;

	if (GetStage() == STAGE_GAME)
	{
		fieldnum = 0;
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		fieldnum = 1;
	}
	FIELD *field = GetField(fieldnum);


	// ���̕�
	if (player->Eye.x < -field->Size.x / 2 + MOVE_LIMIT)
	{
		player->Eye.x = -field->Size.x / 2 + MOVE_LIMIT;
	}

	// �E�̕�
	if (player->Eye.x > field->Size.x / 2 - MOVE_LIMIT)
	{
		player->Eye.x = field->Size.x / 2 - MOVE_LIMIT;
	}

	// ���̕�
	if (player->Eye.z < -field->Size.z / 2 + MOVE_LIMIT)
	{
		player->Eye.z = -field->Size.z / 2 + MOVE_LIMIT;
	}

	// �O�̕�
	if (player->Eye.z > field->Size.z / 2 - MOVE_LIMIT)
	{
		player->Eye.z = field->Size.z / 2 - MOVE_LIMIT;
	}

}

//=============================================================================
// �v���C���[�̈ړ����x�̏C��
//=============================================================================
void PlayerMoveWt(void)
{
	PLAYER *player = GetPlayer(0);

	player->move.x *= (1 - PLAYER_WT_ADJ * player->weight);
	player->move.y *= (1 - PLAYER_WT_ADJ * player->weight);
	player->move.z *= (1 - PLAYER_WT_ADJ * player->weight);

}

//=============================================================================
// �v���C���[�̈ړ������i�I�u�W�F�N�g�j
//=============================================================================
//void PlyColiObj(D3DXVECTOR3 objPos, float objLen, float objWid)
//{
//	PLAYER *player = GetPlayer(0);
//	
//	if (player->posTmp.x >= objPos.x + objLen)
//	{
//		player->Eye.x = player->posTmp.x;
//	}
//
//	else if (player->posTmp.x <= objPos.x - objLen)
//	{
//		player->Eye.x = player->posTmp.x;
//	}
//
//	else if (player->posTmp.z <= objPos.z - objWid)
//	{
//		player->Eye.z = player->posTmp.z;
//	}
//
//	else if (player->posTmp.z >= objPos.z + objWid)
//	{
//		player->Eye.z = player->posTmp.z;
//	}
//
//}

//=============================================================================
// �Ƃ̓��o����
//=============================================================================
void PlayerEntrance(void)
{
	PLAYER *player = &playerWk[0];
	DOOR *door = GetDoor(0);
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

	bool hitflag = false;
	for (int i = 0; i < HOME_MAX; i++, door++)
	{
		if (door->Use == true)
		{
			D3DXVECTOR3 doorpos(door->Pos.x - 16, door->Pos.y, door->Pos.z);
			if (CollisionBoxToPos(doorpos, player->Eye, D3DXVECTOR2(20.0f, 15.0f)) == true)
			{
				if (GetKeyboardTrigger(kb->NEXTDOOR) || IsButtonTriggered(0, gp->DECIDE))
				{
					if (GetStage() == STAGE_GAME)
					{
						SetFade(FADE_OUT, door->Homeno, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

					}
					else if (GetStage() == STAGE_HOUSE1
						|| GetStage() == STAGE_HOUSE2
						|| GetStage() == STAGE_HOUSE3
						|| GetStage() == STAGE_MYHOUSE)
					{
						SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
					}
					
					resetno = i;

				}
				hitflag = true;
			}
		}

	}

	if (GetFade() == FADE_IN)
	{
		PlayerPosReset();
	}

	if (GetStage() == STAGE_GAME)
	{
		Button(hitflag, ENTER_BUTTON);
		Button(false, EXIT_BUTTON);
	}
	else
	{
		Button(hitflag, EXIT_BUTTON);
		Button(false, ENTER_BUTTON);
	}
}

//=================================================================
//�v���[���[�|�W�V�����̍ăZ�b�g�֐�
//=================================================================
void PlayerPosReset(void)
{
	DOOR *door = GetDoor(resetno);
	PLAYER *player = GetPlayer(0);
	

	if (GetStage() == STAGE_GAME)
	{
		player->rot =
			player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->Eye = D3DXVECTOR3(door->Pos.x - 10.0f, door->Pos.y, door->Pos.z - 10.0f);

	}
	else
	{
		player->rot =
			player->rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		player->Eye = D3DXVECTOR3(door->Pos.x - 5.0f, door->Pos.y, door->Pos.z + 25.0f);

	}


}

//================================================================-
//���Z�b�g�i���o�[�̐ݒ�(�ԍ��̌��ւ̑O�ɃZ�b�g�����)
//================================================================
void SetResetno(int no)
{
	resetno = no;
}
//=============================================================================
// �v���C���[�p�[�c�e�q�֌W�ݒ�֐�
//=============================================================================
void SetPlayerParts(void)
{
	PLAYER *player = &playerWk[0];						// �v���C���[�{�̃|�C���^������
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// �v���C���[�E�A�[���|�C���^������
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// �v���C���[���A�[���|�C���^������
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// �v���C���[�E���b�O�|�C���^������
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// �v���C���[�����b�O�|�C���^������

	// �{�̂ɉE�r�p�[�c���֘A�t����
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// �g�p��Ԃ̃|���X�ɂ̂݃p�[�c���Z�b�g
		if (!player->use) continue;
		// ���g�p�̉E�r�p�[�c���Z�b�g
		player_R_Arm = &player_R_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Arm++)
		{	// �{�̂Ɠ����ԍ����Z�b�g
			player_R_Arm->num = player->num;
			// �g�p��Ԃɂ���
			player_R_Arm->use = true;
			break;
		}
	}
	// �{�̂ɍ��r�p�[�c���֘A�t����
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// ���g�p�̍��r�p�[�c���Z�b�g
		player_L_Arm = &player_L_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_L_Arm++)
		{	// �{�̂Ɠ����ԍ����Z�b�g
			player_L_Arm->num = player->num;
			// �g�p��Ԃɂ���
			player_L_Arm->use = true;
			break;
		}
	}
	// �{�̂ɉE���p�[�c���֘A�t����
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// ���g�p�̍��r�p�[�c���Z�b�g
		player_R_Leg = &player_R_LegWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Leg++)
		{	// �{�̂Ɠ����ԍ����Z�b�g
			player_R_Leg->num = player->num;
			// �g�p��Ԃɂ���
			player_R_Leg->use = true;
			break;
		}
	}
	// �{�̂ɍ����p�[�c���֘A�t����
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// ���g�p�̍��r�p�[�c���Z�b�g
		player_L_Leg = &player_L_LegWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_L_Leg++)
		{	// �{�̂Ɠ����ԍ����Z�b�g
			player_L_Leg->num = player->num;
			// �g�p��Ԃɂ���
			player_L_Leg->use = true;
			break;
		}
	}
}
//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void PlayerAnimation(void)
{
	PLAYER *player = &playerWk[0];						// �v���C���[�{�̃|�C���^������
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// �v���C���[�E�A�[���|�C���^������
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// �v���C���[���A�[���|�C���^������
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// �v���C���[�E���b�O�|�C���^������
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// �v���C���[�����b�O�|�C���^������

	// �|���X�{�̃A�j���[�V��������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		SetAnimation(player, NULL, NULL,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// �E�A�[���A�j���[�V��������
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		SetAnimation(player_R_Arm, PLAYER_R_ARM_ANGLE, PLAYER_R_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// ���A�[���A�j���[�V��������
	for (int i = 0; i < PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		SetAnimation(player_L_Arm, PLAYER_L_ARM_ANGLE, PLAYER_L_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// �E���b�O�A�j���[�V��������
	for (int i = 0; i < PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		SetAnimation(player_R_Leg, PLAYER_R_LEG_ANGLE, PLAYER_R_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// �����b�O�A�j���[�V��������
	for (int i = 0; i < PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		SetAnimation(player_L_Leg, PLAYER_L_LEG_ANGLE, PLAYER_L_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
}
//=============================================================================
// �v���C���[�p�[�c�ړ������֐�
//=============================================================================
void PlayerPartsMove(void)
{
	PLAYER *player = &playerWk[0];						// �v���C���[�{�̃|�C���^������
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// �v���C���[�E�A�[���|�C���^������
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// �v���C���[���A�[���|�C���^������
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// �v���C���[�E���b�O�|�C���^������
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// �v���C���[�����b�O�|�C���^������

	// �{�̂Ɛe�q�֌W�̃p�[�c���ړ�
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// �E�A�[���̈ړ�
		player_R_Arm = &player_R_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Arm++)
		{
			if (!player_R_Arm->use) continue;
			if (player_R_Arm->num == player->num)
			{	// �{�̂̍��W�ƈ�v������
				player_R_Arm->Eye = player->Eye;
				player_R_Arm->At = player->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				player_R_Arm->fangleY = player->fangleY;
			}
		}
		// ���A�[���̈ړ�
		player_L_Arm = &player_L_ArmWk[0];
		for (int j = 0; j < PLAYER_L_ARM_MAX; j++, player_L_Arm++)
		{
			if (!player_L_Arm->use) continue;
			if (player_L_Arm->num == player->num)
			{	// �{�̂̍��W�ƈ�v������
				player_L_Arm->Eye = player->Eye;
				player_L_Arm->At = player->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				player_L_Arm->fangleY = player->fangleY;
			}
		}
		// �E���b�O�̈ړ�
		player_R_Leg = &player_R_LegWk[0];
		for (int j = 0; j < PLAYER_R_LEG_MAX; j++, player_R_Leg++)
		{
			if (!player_R_Leg->use) continue;
			if (player_R_Leg->num == player->num)
			{	// �{�̂̍��W�ƈ�v������
				player_R_Leg->Eye = player->Eye;
				player_R_Leg->At = player->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				player_R_Leg->fangleY = player->fangleY;
			}
		}
		// �����b�O�̈ړ�
		player_L_Leg = &player_L_LegWk[0];
		for (int j = 0; j < PLAYER_L_LEG_MAX; j++, player_L_Leg++)
		{
			if (!player_L_Leg->use) continue;
			if (player_L_Leg->num == player->num)
			{	// �{�̂̍��W�ƈ�v������
				player_L_Leg->Eye = player->Eye;
				player_L_Leg->At = player->At;
				// �{�̂Ɠ��������_���������߂�Y����]�p�x���Z�b�g
				player_L_Leg->fangleY = player->fangleY;
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
	PLAYER *player = &playerWk[0];						// �v���C���[�{�̃|�C���^������
	float move = D3DXVec3Length(&player->move);			// �ړ��x�N�g���̑傫���v�Z

	if (pIn->use)
	{	// �g�p�����g�p���`�F�b�N
		// ��]��XZ�̐ݒ�
		pIn->axisXZ = AxisXZ;
		// ��]��Y�̐ݒ�
		pIn->axisY = AxisY;
		// XZ����]�p�x�̐ݒ�
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
		// XZ��]���x�N�g����0�̏ꍇ�̃G���[����
		if (pIn->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f) || (move < 0.001f))
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
