//=============================================================================
//
// �J�������� [camera.cpp]
// Author : GP12B295 29 �R���P��
//          �v�F��
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "calculate.h"
#include "player.h"
#include "stage.h"
#include "field.h"
#include "furniture.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CameraWork(D3DXVECTOR3 *at);
void CameraWorkReset();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA	cameraWk;
bool	CameraReset = false;	// �J�������Z�b�g�̃X�C�b�`

//=============================================================================
// ����������
//=============================================================================

HRESULT InitCamera(int nType)
{
	CAMERA *camera = &cameraWk;

	camera->posCameraEye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	camera->posCameraAt = D3DXVECTOR3(POS_X_CAM_AT, POS_Y_CAM_AT, POS_Z_CAM_AT);
	camera->vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera->rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	camera->fVAngle = CAMERA_V_ANGLE * 1.3f;
	camera->fHAngle = CAMERA_H_ANGLE;
	camera->fHAngleMargin = 0.0f;
	camera->fLength = CAMERA_LENGTH;
	camera->fChaseLength = CAMERA_LENGTH;
	camera->fLengthTemp = 0;

	camera->rotDest = 0.0f;


	return S_OK;
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
#endif

	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer(0);
	
	D3DXVECTOR3 limit;
	int fieldnum;

	if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		fieldnum = 1;
	}
	else
	{
		fieldnum = 0;
	}
FIELD *field = GetField(fieldnum);

	float limitpos_x=field->Size.x/2;
	float limitpos_z=field->Size.z/2;

	if (fabs(camera->posCameraEye.z) > limitpos_z
		|| fabs(camera->posCameraEye.x) > limitpos_x)

	{
		if (fabs(camera->posCameraEye.x) > fabs(camera->posCameraEye.z))
		{
			if (camera->posCameraEye.x < -limitpos_x)
			{

				limit = camera->posCameraEye - player->Eye;						//limit�ɍ��W���i�[
				D3DXVec3Normalize(&limit, &limit);								//limit�𐳋K��
				camera->fLength = (-limitpos_x - player->Eye.x) / limit.x;		//���K������limit����ǂ̊O�ɏo�Ȃ��悤��length�̏C��
				camera->posCameraEye = camera->fLength*limit;					//�Đݒ肵��length����J�������W�̍Đݒ�
																				//�ȉ��R���l
			}
			else if (camera->posCameraEye.x > limitpos_x)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (limitpos_x - player->Eye.x) / limit.x;
				camera->posCameraEye = camera->fLength*limit;

			}
			else
			{
				//camera->fLength = camera->fChaseLength;
			}

		}

		else if (fabs(camera->posCameraEye.x) < fabs(camera->posCameraEye.z))
		{
			if (camera->posCameraEye.z < -limitpos_z)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (-limitpos_z - player->Eye.z) / limit.z;
				camera->posCameraEye = camera->fLength*limit;

			}
			else if (camera->posCameraEye.z > limitpos_z)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (limitpos_z - player->Eye.z) / limit.z;
				camera->posCameraEye = camera->fLength*limit;

			}
			else
			{
				camera->fLength = camera->fChaseLength;
			}

		}
	}
	else if (fabs(camera->posCameraEye.z) < limitpos_z
		&& fabs(camera->posCameraEye.x) < limitpos_x)
	{
		camera->fLength = camera->fChaseLength;

	}
	if (camera->fLength > camera->fChaseLength)
	{
		camera->fLength = camera->fChaseLength;
	}



	//�f�o�b�O����ZC�ŃJ������]
	if (GetKeyboardPress(DIK_Z) || IsButtonPressed(0, BUTTON_LZ_UP))
	{// ���_����u���v
		camera->rotCamera.y += VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y > D3DX_PI)
		{
			camera->rotCamera.y -= D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fChaseLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fChaseLength;

		CameraReset = false;
	}
	if (GetKeyboardPress(DIK_C) || IsButtonPressed(0, BUTTON_LZ_DOWN))
	{// ���_����u�E�v
		camera->rotCamera.y -= VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y < -D3DX_PI)
		{
			camera->rotCamera.y += D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fChaseLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fChaseLength;

		CameraReset = false;
	}

	if (camera->fLength >= CAMERA_LENGTH_MIN
		&&camera->fLength <= CAMERA_LENGTH_MAX)
	{
		if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_LRZ_DOWN))
		{// ���_�ړ��u�Y�[���C���v
			//camera->posCameraEye.y -= CAMERA_MOVE_SPEED;
			camera->fChaseLength -= CAMERA_MOVE_SPEED;

			// �ړ�����
			if (camera->fChaseLength < CAMERA_LENGTH_MIN)
			{
				camera->fChaseLength = CAMERA_LENGTH_MIN;
			}
		camera->fLength = camera->fChaseLength;

		}
		if ((float)fabs(camera->posCameraEye.x) < limitpos_x && (float)fabs(camera->posCameraEye.z) < limitpos_z)
		{
			if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_LRZ_UP))
			{// ���_�ړ��u�Y�[���A�E�g�v
			 //camera->posCameraEye.y += CAMERA_MOVE_SPEED;
				camera->fChaseLength += CAMERA_MOVE_SPEED;

				// �ړ�����
				if (camera->fChaseLength > CAMERA_LENGTH_MAX)
				{
					camera->fChaseLength = CAMERA_LENGTH_MAX;
				}
				camera->fLength = camera->fChaseLength;

			}
		}
	}

	// �J�������Z�b�g
	if (GetKeyboardTrigger(DIK_X))
	{
		camera->rotDest = player->rot.y + D3DX_PI;

		CameraReset = true;
	}

	// �J�������Z�b�g�̉��o
	if (CameraReset == true)
	{
		CameraWorkReset();
	}

	// �J�������[�N
	CameraWork(&(player->Eye));

	// �p�x�̏C��
	camera->rotCamera.y = PiCalculate360(camera->rotCamera.y);
	camera->rotDest = PiCalculate360(camera->rotDest);

#ifdef _DEBUG
	//PrintDebugProc("Camera[pos]: %f,%f,%f\n", camera->posCameraEye.x, camera->posCameraEye.y, camera->posCameraEye.z);
	//PrintDebugProc("CameraReset: %d\n", CameraReset);
	//PrintDebugProc("CameraLength: %f\n", camera->fLength);
	//PrintDebugProc("\n");

#endif
	


}

//=============================================================================
// �J�������[�N
//=============================================================================
void CameraWork(D3DXVECTOR3 *at)
{
	D3DXVECTOR3 vec(0.0f, 0.25f, -1.0f);		// ���K�����ꂽ�����_����̌���
	D3DXMATRIX	mtx;
	CAMERA *camera = GetCamera();

	camera->posCameraAt = *at;
	camera->posCameraAt.y += 40;

	// �J�����̑��ΓI�ȉ�]�p�x���s��ɕϊ�����
	D3DXMatrixRotationYawPitchRoll(&mtx, camera->rotCamera.y, camera->rotCamera.x, camera->rotCamera.z);

	// ���K�����ꂽ�_�ɉ�]�s����|����
	D3DXVec3TransformCoord(&vec, &vec, &mtx);

	// �J�����̈ʒu = �J�����̒����_ + (�����_����̊p�x * ���_�܂ł̋���)
	camera->posCameraEye = camera->posCameraAt + (vec * camera->fLength);

}

//=============================================================================
// �J�������Z�b�g�̉��o
//=============================================================================
void CameraWorkReset()
{
	CAMERA *camera = GetCamera();
	float Diff;						// ����

	// �ړI�̊p�x�܂ł̍���
	Diff = camera->rotDest - camera->rotCamera.y;
	if (Diff > D3DX_PI)
	{
		Diff -= D3DX_PI * 2.0f;
	}
	if (Diff < -D3DX_PI)
	{
		Diff += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	camera->rotCamera.y += (float)(Diff * 0.15);

	if (camera->rotCamera.y > D3DX_PI)
	{
		camera->rotCamera.y -= D3DX_PI * 2.0f;
	}
	if (camera->rotCamera.y < -D3DX_PI)
	{
		camera->rotCamera.y += D3DX_PI * 2.0f;
	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camera = &cameraWk;
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