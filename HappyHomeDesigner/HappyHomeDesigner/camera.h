//=============================================================================
//
// �J�������� [camera.h]
// Author  GP11B243�@32 �R���P��
//          �v�F��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_ANGLE_MARGIN		(0.1f)

#define CAMERA_MOVE_SPEED		(7)
#define CAMERA_MOVE_SLANT		(CAMERA_MOVE_SPEED * 0.71f)
#define CAMERA_ROT_SPEED		(0.05f)
#define CAMERA_ROT_SLANT		(CAMERA_ROT_SPEED * 0.71f)
#define CAMERA_ROT_SPEED_AUTO	(0.2f)


#define CAMERA_V_ANGLE			(D3DX_PI)
#define CAMERA_H_ANGLE			(D3DX_PI * 0.5f)

#define CAMERA_H_ANGLE_MARGIN		(D3DX_PI / 180 * 45)
#define CAMERA_MARGIN_SPEED			(D3DX_PI / 180)
#define CAMERA_LENGTH_SPEED			(10.0f)
#define CAMERA_LENGTH_AUTO_SPEED	(30.0f)
#define CAMERA_LENGTH				(200.0f)
#define CAMERA_LENGTH_MIN			(100.0f)
#define CAMERA_LENGTH_MAX			(300.0f)


#define CAMERA_ROT_MOUSE_X			(0.002f)
#define CAMERA_ROT_MOUSE_Y			(0.002f)


#define ROOT_2					(1.414213f)

#define	POS_X_CAM				(0.0f)					// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM				(50.0f)										// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM				(-100.0f)										// �J�����̏����ʒu(Z���W)

#define	POS_X_CAM_AT			(POS_X_CAM)
#define	POS_Y_CAM_AT			(0.0f)
#define	POS_Z_CAM_AT			(0.0f)

#define	VIEW_ANGLE				(D3DXToRadian(35.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z				(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(5000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)									// �J�����̈ړ���


typedef struct
{
	D3DXVECTOR3			posCameraEye;				// �J�����̎��_
	D3DXVECTOR3			posCameraAt;				// �J�����̒����_
	D3DXVECTOR3			vecCameraUp;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			rotCamera;					// �J�����̉�]
	D3DXVECTOR3			vecTag;

	float				rotDest;					// �J�����̖ڕW�p�x

	D3DXVECTOR3			posCameraAtTps;				// �|�W�V����
	D3DXVECTOR3			posCameraAtNormal;			// �|�W�V����

	D3DXVECTOR3			vecCameraAtPos;

	D3DXMATRIX			mtxView;				// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			mtxWorld;				// ���[���h�}�g���b�N�X

	float				fHAngleMargin;
	float				fHAngle;
	float				fVAngle;
	float				fHAngleDiff;
	float				fVAngleDiff;
	float				fLength;				//�����_�ƃJ�����̋���
	float				fChaseLength;			//fLength��ۑ����邽�߁@�J�����̐������Ɏg�p
	float				fLengthTemp;
	float				fMoveSpeed;
	float				fRotSpeed;

	int					nCameraMode;
	int					nSetCount;

	bool				bCameraReverse;
}CAMERA;

enum
{
	CAMERA_GAME,
	CAMERA_VIEW
};

enum
{
	CAMERA_NORMAL,
	CAMERA_TPS,
	CAMERA_TARGET
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT			InitCamera(int nType);
void			UninitCamera(void);
void			UpdateCamera(void);
void			SetCamera(void);
D3DXVECTOR3		GetRotCamera(void);
D3DXMATRIX		GetMtxView(void);
D3DXMATRIX		GetMtxProjection(void);
CAMERA			*GetCamera(void);
#endif