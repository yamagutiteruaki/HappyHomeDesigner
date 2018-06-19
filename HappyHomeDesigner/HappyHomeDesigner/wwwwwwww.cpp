//=============================================================================
//
// 草 [wwwwwwww.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "wwwwwwww.h"
#include "camera.h"
#include "stage.h"
#include "calculate.h"
#include "loadWwwwDB.h"

#ifdef _DEBUG
#include "debugproc.h"
#include "input.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexWWWW(LPDIRECT3DDEVICE9 Device, int no);
void SetUseWWWW(int no, bool use);
void SetPosWWWW(int no, float x, float y, float z);
void SetRotWWWW(int no, float x, float y, float z);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureWWWW[WWWW_MAX];		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 VtxBuffWWWW[WWWW_MAX];		// 頂点バッファへのポインタ
WWWW					wwwwWk[WWWW_MAX];			// ワーク

const char *FileNameWWWW[1] =
{
	"data/TEXTURE/glass_wall00.png"
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWWWW(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	WWWW *wwww = GetWWWW(0);

	for (int i = 0; i < WWWW_MAX; i++)
	{
		(wwww + i)->use = FALSE;
		(wwww + i)->wwww.Pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		(wwww + i)->wwww.Rot = D3DXVECTOR3(-(D3DX_PI / 2), 0.0f, 0.0f);
		(wwww + i)->wwww.Size = D3DXVECTOR3(50.0f, 0.0f, 50.0f);

		D3DXCreateTextureFromFile(
		Device,						// デバイスへのポインタ
		FileNameWWWW[0],			// ファイルの名前
		&TextureWWWW[i]);			// 読み込むメモリー

		MakeVertexWWWW(Device, i);
	}

	// LoadWWWWDB();

	SetUseWWWW(0, TRUE);	SetPosWWWW(0, 80, 20, 60);
	//SetUseWWWW(1, TRUE);	SetPosWWWW(1, 130, 20, 60);
	//SetUseWWWW(2, TRUE);	SetPosWWWW(2, 180, 20, 60);
	//SetUseWWWW(3, TRUE);	SetPosWWWW(3, 230, 20, 60);
	//SetUseWWWW(4, FALSE);	SetPosWWWW(4, 280, 20, 60);
	//SetUseWWWW(5, TRUE);	SetPosWWWW(5, 330, 20, 60);

	//SetUseWWWW(6, TRUE);	SetPosWWWW(6, 80, 20, 60);		SetRotWWWW(6, -(D3DX_PI / 2), D3DX_PI, 0);
	//SetUseWWWW(7, TRUE);	SetPosWWWW(7, 130, 20, 60);		SetRotWWWW(7, -(D3DX_PI / 2), D3DX_PI, 0);
	//SetUseWWWW(8, TRUE);	SetPosWWWW(8, 180, 20, 60);		SetRotWWWW(8, -(D3DX_PI / 2), D3DX_PI, 0);
	//SetUseWWWW(9, TRUE);	SetPosWWWW(9, 230, 20, 60);		SetRotWWWW(9, -(D3DX_PI / 2), D3DX_PI, 0);
	//SetUseWWWW(10, FALSE);	SetPosWWWW(10, 280, 20, 60);	SetRotWWWW(10, -(D3DX_PI / 2), D3DX_PI, 0);
	//SetUseWWWW(11, TRUE);	SetPosWWWW(11, 330, 20, 60);	SetRotWWWW(11, -(D3DX_PI / 2), D3DX_PI, 0);

	//SetUseWWWW(12, TRUE);	SetPosWWWW(12, 55, 20, 85);		SetRotWWWW(12, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(13, TRUE);	SetPosWWWW(13, 55, 20, 135);	SetRotWWWW(13, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(14, TRUE);	SetPosWWWW(14, 55, 20, 185);	SetRotWWWW(14, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(15, TRUE);	SetPosWWWW(15, 55, 20, 235);	SetRotWWWW(15, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(16, TRUE);	SetPosWWWW(16, 55, 20, 285);	SetRotWWWW(16, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(17, TRUE);	SetPosWWWW(17, 55, 20, 335);	SetRotWWWW(17, -(D3DX_PI / 2), D3DX_PI / 2, 0);

	//SetUseWWWW(18, TRUE);	SetPosWWWW(18, 55, 20, 85);		SetRotWWWW(18, -(D3DX_PI / 2), -D3DX_PI / 2, 0);
	//SetUseWWWW(19, TRUE);	SetPosWWWW(19, 55, 20, 135);	SetRotWWWW(19, -(D3DX_PI / 2), -D3DX_PI / 2, 0);
	//SetUseWWWW(20, TRUE);	SetPosWWWW(20, 55, 20, 185);	SetRotWWWW(20, -(D3DX_PI / 2), -D3DX_PI / 2, 0);
	//SetUseWWWW(21, TRUE);	SetPosWWWW(21, 55, 20, 235);	SetRotWWWW(21, -(D3DX_PI / 2), -D3DX_PI / 2, 0);
	//SetUseWWWW(22, TRUE);	SetPosWWWW(22, 55, 20, 285);	SetRotWWWW(22, -(D3DX_PI / 2), -D3DX_PI / 2, 0);
	//SetUseWWWW(23, TRUE);	SetPosWWWW(23, 55, 20, 335);	SetRotWWWW(23, -(D3DX_PI / 2), -D3DX_PI / 2, 0);

	//SetUseWWWW(24, TRUE);	SetPosWWWW(24, 80, 20, 360);
	//SetUseWWWW(25, TRUE);	SetPosWWWW(25, 130, 20, 360);
	//SetUseWWWW(26, TRUE);	SetPosWWWW(26, 180, 20, 360);
	//SetUseWWWW(27, TRUE);	SetPosWWWW(27, 230, 20, 360);
	//SetUseWWWW(28, TRUE);	SetPosWWWW(28, 280, 20, 360);
	//SetUseWWWW(29, TRUE);	SetPosWWWW(29, 330, 20, 360);

	//SetUseWWWW(30, TRUE);	SetPosWWWW(30, 355, 20, 85);		SetRotWWWW(30, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(31, TRUE);	SetPosWWWW(31, 355, 20, 135);	SetRotWWWW(31, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(32, TRUE);	SetPosWWWW(32, 355, 20, 185);	SetRotWWWW(32, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(33, TRUE);	SetPosWWWW(33, 355, 20, 235);	SetRotWWWW(33, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(34, TRUE);	SetPosWWWW(34, 355, 20, 285);	SetRotWWWW(34, -(D3DX_PI / 2), D3DX_PI / 2, 0);
	//SetUseWWWW(35, TRUE);	SetPosWWWW(35, 355, 20, 335);	SetRotWWWW(35, -(D3DX_PI / 2), D3DX_PI / 2, 0);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWWWW(void)
{
	for (int i = 0; i < WWWW_MAX; i++)
	{
		//フィールド
		if (TextureWWWW != NULL)
		{// テクスチャの開放
			TextureWWWW[i]->Release();
			TextureWWWW[i] = NULL;
		}

		if (VtxBuffWWWW != NULL)
		{// 頂点バッファの開放
			VtxBuffWWWW[i]->Release();
			VtxBuffWWWW[i] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWWWW(void)
{
	WWWW *wwww = GetWWWW(0);

#ifdef _DEBUG

	PrintDebugProc("Pos: %f, %f, %f\n", wwww->wwww.Pos.x, wwww->wwww.Pos.y, wwww->wwww.Pos.z);
	PrintDebugProc("Rot: %f, %f, %f\n", wwww->wwww.Rot.x, wwww->wwww.Rot.y, wwww->wwww.Rot.z);

	PrintDebugProc("use: %d, %d, %d, %d, %d, %d\n",
		(wwww + 0)->use,
		(wwww + 1)->use,
		(wwww + 2)->use,
		(wwww + 3)->use,
		(wwww + 4)->use,
		(wwww + 5)->use
		);


	if (GetKeyboardPress(DIK_NUMPAD8))
	{
		wwww->wwww.Pos.z += 1.0f;
	}

	else if (GetKeyboardPress(DIK_NUMPAD5))
	{
		wwww->wwww.Pos.z -= 1.0f;
	}

	if (GetKeyboardPress(DIK_NUMPAD4))
	{
		wwww->wwww.Pos.x -= 1.0f;
	}
	else if (GetKeyboardPress(DIK_NUMPAD6))
	{
		wwww->wwww.Pos.x += 1.0f;
	}

	if (GetKeyboardPress(DIK_NUMPAD7))
	{
		wwww->wwww.Pos.y -= 1.0f;
	}
	else if (GetKeyboardPress(DIK_NUMPAD9))
	{
		wwww->wwww.Pos.y += 1.0f;
	}

	if (GetKeyboardPress(DIK_NUMPAD1))
	{
		wwww->wwww.Rot.y -= (D3DX_PI / 180);
	}
	//if (GetKeyboardPress(DIK_NUMPAD2))
	//{
	//	wwww->wwww.Rot.y += (D3DX_PI / 180);
	//}
	if (GetKeyboardPress(DIK_NUMPAD3))
	{
		wwww->wwww.Rot.y += (D3DX_PI / 180);
	}
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWWWW(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	WWWW *wwww = GetWWWW(0);

	for (int i = 0; i < WWWW_MAX; i++, wwww++)
	{
		// 使用しているのか
		if (wwww->use == FALSE) continue;

		// 場所をチェック
		if (GetStage() != STAGE_GAME) break;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&wwww->wwww.world);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, wwww->wwww.Rot.y, wwww->wwww.Rot.x, wwww->wwww.Rot.z);
		D3DXMatrixMultiply(&wwww->wwww.world, &wwww->wwww.world, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, wwww->wwww.Pos.x, wwww->wwww.Pos.y, wwww->wwww.Pos.z);
		D3DXMatrixMultiply(&wwww->wwww.world, &wwww->wwww.world, &mtxTranslate);

		// ワールドマトリックスの設定
		Device->SetTransform(D3DTS_WORLD, &wwww->wwww.world);

		// 頂点バッファをデバイスのデータストリームにバインド
		Device->SetStreamSource(0, VtxBuffWWWW[i], 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		Device->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		Device->SetTexture(0, TextureWWWW[i]);

		// ポリゴンの描画
		Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexWWWW(LPDIRECT3DDEVICE9 Device, int no)
{
	WWWW *wwww = GetWWWW(no);

	// オブジェクトの頂点バッファを生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * WWWW_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&VtxBuffWWWW[no],			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuffWWWW[no]->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < WWWW_MAX; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-(wwww)->wwww.Size.x / 2, 0.0f, +(wwww)->wwww.Size.z / 2);
			pVtx[1].vtx = D3DXVECTOR3(+(wwww)->wwww.Size.x / 2, 0.0f, +(wwww)->wwww.Size.z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-(wwww)->wwww.Size.x / 2, 0.0f, -(wwww)->wwww.Size.z / 2);
			pVtx[3].vtx = D3DXVECTOR3(+(wwww)->wwww.Size.x / 2, 0.0f, -(wwww)->wwww.Size.z / 2);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		VtxBuffWWWW[no]->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 取得
//=============================================================================
WWWW *GetWWWW(int no)
{
	return &wwwwWk[no];
}


//=============================================================================
// 
//=============================================================================
void SetUseWWWW(int no, bool use)
{
	WWWW *wwww = GetWWWW(no);
	wwww->use = use;
}

//=============================================================================
// 
//=============================================================================
void SetPosWWWW(int no, float x, float y, float z)
{
	WWWW *wwww = GetWWWW(no);
	wwww->wwww.Pos.x = x;
	wwww->wwww.Pos.y = y;
	wwww->wwww.Pos.z = z;
}

//=============================================================================
// 
//=============================================================================
void SetRotWWWW(int no, float x, float y, float z)
{
	WWWW *wwww = GetWWWW(no);
	wwww->wwww.Rot.x = x;
	wwww->wwww.Rot.y = y;
	wwww->wwww.Rot.z = z;
}