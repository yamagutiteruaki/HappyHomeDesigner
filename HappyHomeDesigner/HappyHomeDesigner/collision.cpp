//=============================================================================
//
// 判定処理 [collision.cpp]
// Author : GP12B295 29 山口輝明
//
// 当たり判定を行うcpp
//
//=============================================================================
#include "main.h"
#include "collision.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//=============================================================================
// 当たり判定関数
//=============================================================================
//void Collision(void)
//{
//
//}


//=============================================================================
// BBの判定関数
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// 当たり判定の確認(BB)
	if (((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z - size2.y)) && ((pos2.z + size2.y) > (pos1.z - size1.y)))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// BCの判定関数
//=============================================================================
bool CollisionBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// 当たり判定の確認(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// Boxと座標の判定関数
//=============================================================================
bool CollisionBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1)
{
	// 当たり判定の確認(BoxとPos)
	if (((pos1.x + size1.x) > (pos2.x)) && ((pos2.x) > (pos1.x - size1.x))
		&& ((pos1.y + size1.y) > (pos2.y)) && ((pos2.y) > (pos1.y - size1.y)))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// レイとスフィアの当たり判定
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
	{	// レイの長さが0
		return false;
	}

	float fS = fB * fB - fA * fC;
	if (fS < 0.0f)
	{	// 衝突なし
		return false;
	}

	fS = sqrtf(fS);
	float fA1 = (fB - fS) / fA;
	float fA2 = (fB + fS) / fA;

	if (fA1 < 0.0f || fA2 < 0.0f)
	{	// レイの反対で衝突
		return false;
	}

	return true;
}
