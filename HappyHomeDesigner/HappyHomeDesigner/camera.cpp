//=============================================================================
//
// �J�������� [camera.cpp]
// Author : GP12B295 29 �R���P��
//			GP11B243�@32 �R���P��
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "calculate.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA					cameraWk;

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	CAMERA *camera = &cameraWk;

	camera->posCameraEye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	camera->posCameraAt = D3DXVECTOR3(POS_X_CAM_AT, POS_Y_CAM_AT, POS_Z_CAM_AT);
	camera->vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	camera->fVAngle = CAMERA_V_ANGLE * 1.3f;
	camera->fHAngle = CAMERA_H_ANGLE;
	camera->fHAngleMargin = 0.0f;
	camera->fLength = CAMERA_LENGTH;
	camera->fLengthTemp = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(void)
{

#ifdef _DEBUG
	CAMERA *camera = GetCamera();

	//�f�o�b�O����ZC�ŃJ������]
	if (GetKeyboardPress(DIK_Z))
	{// ���_����u���v
		camera->rotCamera.y += VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y > D3DX_PI)
		{
			camera->rotCamera.y -= D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fLength;
	}
	if (GetKeyboardPress(DIK_C))
	{// ���_����u�E�v
		camera->rotCamera.y -= VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y < -D3DX_PI)
		{
			camera->rotCamera.y += D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fLength;
	}

	if (GetKeyboardPress(DIK_W))
	{// ���_�ړ��u�Y�[���C���v
		camera->posCameraEye.y -= CAMERA_MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_S))
	{// ���_�ړ��u�Y�[���A�E�g�v
		camera->posCameraEye.y += CAMERA_MOVE_SPEED;
	}

#endif
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA	*camera = &cameraWk;
	/******************** �r���[�C���O�ϊ� ********************/
	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&camera->mtxView);

	// �r���[�}�g���N�X�̍쐬
	D3DXMatrixLookAtLH(&camera->mtxView,
		&camera->posCameraEye,	// ���_
		&camera->posCameraAt,	// �����_
		&camera->vecCameraUp);	// �����

								// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera->mtxView);


	/******************** �v���W�F�N�V�����ϊ� ********************/
	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&camera->mtxProjection);

	// �v���W�F�N�V�����}�g���N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&camera->mtxProjection,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l�i�߂��ƕ`�悵�Ȃ��j
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l�i�����ƕ`�悵�Ȃ��j

							// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &camera->mtxProjection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->mtxView;
}

//=============================================================================
// �v���W�F�N�V�����}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxProjection(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->mtxProjection;
}

//=============================================================================
// �J�����擾�֐�
//=============================================================================
CAMERA *GetCamera(void)
{
	return(&cameraWk);
}