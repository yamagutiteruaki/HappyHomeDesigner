//=============================================================================
//
// ���菈�� [collision.cpp]
// Author : GP12B295 29 �R���P��
//
// �����蔻����s��cpp
//
//=============================================================================
#include "main.h"
#include "collision.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//=============================================================================
// �����蔻��֐�
//=============================================================================
//void Collision(void)
//{
//
//}


//=============================================================================
// BB�̔���֐�
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// �����蔻��̊m�F(BB)
	if (((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z - size2.y)) && ((pos2.z + size2.y) > (pos1.z - size1.y)))
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// BC�̔���֐�
//=============================================================================
bool CollisionBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// �����蔻��̊m�F(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2))
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// Box�ƍ��W�̔���֐�
//=============================================================================
bool CollisionBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1)
{
	// �����蔻��̊m�F(Box��Pos)
	if (((pos1.x + size1.x) > (pos2.x)) && ((pos2.x) > (pos1.x - size1.x))
		&& ((pos1.y + size1.y) > (pos2.y)) && ((pos2.y) > (pos1.y - size1.y)))
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// ���C�ƃX�t�B�A�̓����蔻��
//=============================================================================
bool CollisionRayToSphere(D3DXVECTOR3 posRay, D3DXVECTOR3 vecRay, D3DXVECTOR3 posTag, float nLength)
{
	posTag.x -= posRay.x;
	posTag.y -= posRay.y;
	posTag.z -= posRay.z;

	float fA = vecRay.x * vecRay.x + vecRay.y * vecRay.y + vecRay.z * vecRay.z;
	float fB = vecRay.x * posTag.x + vecRay.y * posTag.y + vecRay.z * posTag.z;
	float fC = posTag.x * posTag.x + posTag.y * posTag.y + posTag.z * posTag.z - nLength * nLength;

	if (fA == 0.0f)
	{	// ���C�̒�����0
		return false;
	}

	float fS = fB * fB - fA * fC;
	if (fS < 0.0f)
	{	// �Փ˂Ȃ�
		return false;
	}

	fS = sqrtf(fS);
	float fA1 = (fB - fS) / fA;
	float fA2 = (fB + fS) / fA;

	if (fA1 < 0.0f || fA2 < 0.0f)
	{	// ���C�̔��΂ŏՓ�
		return false;
	}

	return true;
}
