//=============================================================================
//
// ���C������ [main.h]
// Author : GP12B295 29 �R���P��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <stdio.h>
#include <time.h>

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		("AppClass")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		("HappyHomeDesigner �`���t�H�[���̏��`")	// �E�C���h�E�̃L���v�V������

#define SCREEN_SCALE	(1.5f)
#define SCREEN_WIDTH	(1280 * SCREEN_SCALE)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720 * SCREEN_SCALE)		// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)			// �E�C���h�E����X
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)			// �E�C���h�E����Y

#define	NUM_VERTEX		(4)		// ���_��c
#define	NUM_POLYGON		(2)		// �|���S����

#define DEBUG_RECT		(50)	// �f�o�b�O

#define MOUSE_MARGIN	(10)

// �R�c�|���S�����_�t�H�[�}�b�g
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{	// 3D�|���S�����_�\����
	D3DXVECTOR3	vtx;		// ���_���W
	D3DXVECTOR3	nor;		// �@���x�N�g��
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2	tex;		// �e�N�X�`�����W
} VERTEX_3D;

typedef struct
{	// 2D�|���S�����_�\����
	D3DXVECTOR3 vtx;		// ���_���W
	float		rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif