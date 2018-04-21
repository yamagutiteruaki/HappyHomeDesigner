//=============================================================================
//
// �v�Z���� [calculate.cpp]
// Author : GP12B295 29 �R���P��
//
// �v�Z�����S�ʂ��s��cpp
//
//=============================================================================
#include "calculate.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//=============================================================================
// ����
//=============================================================================
float DotProduct(D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
	float ans = 0;
	//ans = (vl->x * vr->x) + (vl->y * vr->y) + (vl->z * vr->z);
	ans = D3DXVec3Dot(vl, vr);
	return(ans);
}

//=============================================================================
// �O��
//=============================================================================
D3DXVECTOR3 *CrossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
	//ret->x = (vl->y * vr->z) - (vl->z * vr->y);
	//ret->y = (vl->z * vr->x) - (vl->x * vr->z);
	//ret->z = (vl->x * vr->y) - (vl->y * vr->x);
	D3DXVec3Cross(ret, vl, vr);
	return(ret);
}

//=============================================================================
// XZ�̊p�x�Z�o�����iatan2�G���[�h�~�t���j
//=============================================================================
float PreventionAtan2XZ(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	vecTa.x = pos1.x - pos2.x;
	vecTa.z = pos1.z - pos2.z;

	// atan2�̃G���[�h�~
	if (vecTa.x == 0 && vecTa.z == 0)
	{
		vecTa.x += 0.00001;
	}

	// �p�x�v�Z
	float fHAngle = atan2(vecTa.z, vecTa.x);

	return fHAngle;
}

//=============================================================================
// PI��������
//=============================================================================
float PiCalculateTitle(float fAngle)
{
	// 90�x�𒴂�����360�x������
	if (fAngle >= D3DX_PI * 0.53f)
	{
		fAngle -= D3DX_PI;
	}
	else if (fAngle < -D3DX_PI * 0.53f)
	{
		fAngle += D3DX_PI;
	}
	return fAngle;
}

//=============================================================================
// PI���������i180�x�j
//=============================================================================
float PiCalculate180(float fAngle)
{
	// 180�x�𒴂�����360�x������
	if (fAngle >= D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	return fAngle;
}

//=============================================================================
// PI���������i360�x�j
//=============================================================================
float PiCalculate360(float fAngle)
{
	// 360�x�𒴂�����360�x������
	if (fAngle > D3DX_PI * 2)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < 0.0f)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	return fAngle;
}

//=============================================================================
// �N�H�[�^�j�I������
//=============================================================================
void QuaternionCalculate(D3DXVECTOR3 *pOrigin, D3DXVECTOR3 *pAxis, float fAngle, D3DXVECTOR3 *pPos)
{
	// �����A�������ʗp�̕ϐ����`
	D3DXQUATERNION qReversal, qAnswer;
	// ��]���������_�̏����ʒu
	D3DXQUATERNION qOrigin(pOrigin->x, pOrigin->y, pOrigin->z, 0.0f);
	// �P�ʃN�H�[�^�j�I��
	D3DXQUATERNION qQuaternion(0.0f, 0.0f, 0.0f, 1.0f);

	// ��pAxis���̉�]�N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationAxis(&qQuaternion, pAxis, fAngle);
	// XYZ�}�C�i�X�̋������Z�o
	D3DXQuaternionConjugate(&qReversal, &qQuaternion);
	// qReversal�EqOrigin�EqQuaternion���s��v�Z
	D3DXQuaternionMultiply(&qAnswer, &qReversal, &qOrigin);
	// qAnswer�ɉ�]������̌��ʂ��i�[
	D3DXQuaternionMultiply(&qAnswer, &qAnswer, &qQuaternion);

	// ��]�����̌��ʂ𔽉f
	pPos->x = qAnswer.x;
	pPos->y = qAnswer.y;
	pPos->z = qAnswer.z;
}

//=============================================================================
// �J���[�p���b�g�Ăяo������
//=============================================================================
D3DXCOLOR SetColorPallet(int nColor)
{
	D3DXCOLOR temp;
	//temp = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	switch (nColor)
	{
	case COLOR_PALLET_WHITE:		// �z���C�g
		temp = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case COLOR_PALLET_RED:			// ���b�h
		temp = D3DXCOLOR(0.8f, 0.2f, 0.0f, 1.0f);
		break;
	case COLOR_PALLET_YELLOW:		// �C�G���[
		temp = D3DXCOLOR(0.9f, 0.9f, 0.0f, 1.0f);
		break;
	case COLOR_PALLET_GREEN:		// �O���[��
		temp = D3DXCOLOR(0.0f, 1.0f, 0.05f, 1.0f);
		break;
	case COLOR_PALLET_CYAN:			// �V�A��
		temp = D3DXCOLOR(0.0f, 0.9f, 0.9f, 1.0f);
		break;
	case COLOR_PALLET_BLUE:			// �u���[
		temp = D3DXCOLOR(0.0f, 0.2f, 0.8f, 1.0f);
		break;
	case COLOR_PALLET_MAGENTA:		// �}�[���_
		temp = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case COLOR_PALLET_BROWN:		// �u���E��
		temp = D3DXCOLOR(0.6f, 0.4f, 0.0f, 1.0f);
		break;
	case COLOR_PALLET_LIGHTGREEN:	// ���C�g�O���[��
		temp = D3DXCOLOR(0.3f, 0.9f, 0.3f, 1.0f);
		break;
	case COLOR_PALLET_ORANGE:		// �I�����W
		temp = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
		break;
	case COLOR_PALLET_BLACK:		// �u���b�N
		temp = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case COLOR_PALLET_LIGHTBLUE:	// ���C�g�u���[
		temp = D3DXCOLOR(0.4f, 0.7f, 1.0f, 1.0f);
		break;
	case COLOR_PALLET_GRAY:			// �O���C
		temp = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		break;
	}
	return temp;
}

//=============================================================================
// int�z��̃V���b�t���֐�
//=============================================================================
void SetShuffle(int *nShuffle, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		int j = rand() % nSize;
		int t = nShuffle[i];
		nShuffle[i] = nShuffle[j];
		nShuffle[j] = t;
	}
}