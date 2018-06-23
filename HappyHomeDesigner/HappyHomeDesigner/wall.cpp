//=============================================================================
//
// 地面処理 [wall.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "wall.h"
#include "field.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT MakeVertexWall(LPDIRECT3DDEVICE9 pDevice,int no);



//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureWall[WALL_MAX*WALL_KIND];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWall[WALL_MAX*WALL_KIND];	// 頂点バッファへのポインタ

WALL					g_aWall[WALL_MAX*WALL_KIND];

const char *FileNameWall[WALL_KIND] =
{
	TEXTURE_WALL,		// 家1
	TEXTURE_WALL1,		// 家2
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWall(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WALL *wall = GetWall(0);


	for (int i = 0; i < WALL_KIND*WALL_MAX; i++, wall++)
	{
		FIELD *field = GetField(i/4);

		wall->Pos.x = 0.0f;	//X座標の設定
		wall->Pos.y = -(field->Size.x) / 2;//Y座標は0固定
		wall->Pos.z = WALL_SIZE_Z/((i/4)+1);//Z座標の設定

		wall->Rot.x = -D3DX_PI / 2;
		wall->Rot.y = (D3DX_PI / 2)*i ;

		wall->Size.x = field->Size.x;
		wall->Size.y = 0.0f;
		wall->Size.z = wall->Pos.z*2;

	}

	if (nType == STAGE_INIT_FAST)
	{
		for (int i = 0; i < WALL_KIND*WALL_MAX; i++)
		{

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				FileNameWall[i / 4],			// ファイルの名前
				&g_pD3DTextureWall[i]);	// 読み込むメモリー

			MakeVertexWall(pDevice, i);

		}
	}
		return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	for (int i = 0; i < WALL_KIND*WALL_MAX; i++)
	{
		//フィールド
		if (g_pD3DTextureWall != NULL)
		{// テクスチャの開放
			g_pD3DTextureWall[i]->Release();
			g_pD3DTextureWall[i] = NULL;
		}

		if (g_pD3DVtxBuffWall != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffWall[i]->Release();
			g_pD3DVtxBuffWall[i] = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;


	int no;
	if (GetStage() == STAGE_GAME)
	{
		no = 0;
	}
	else
	{
		no = 4;
	}
		WALL *wall = GetWall(no);
for (int i=no; i < no+4; i++, wall++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&wall->world);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, wall->Pos.x, wall->Pos.y, wall->Pos.z);
		D3DXMatrixMultiply(&wall->world, &wall->world, &mtxTranslate);

		//回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, wall->Rot.y, wall->Rot.x, wall->Rot.z);
		D3DXMatrixMultiply(&wall->world, &wall->world, &mtxRot);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &wall->world);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffWall[i], 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureWall[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexWall(LPDIRECT3DDEVICE9 pDevice,int no)
{

	WALL *wall = GetWall(no);

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* WALL_MAX*WALL_KIND,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffWall[no],		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffWall[no]->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < WALL_MAX*WALL_KIND; i++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-wall->Size.x /2, 0.0f, wall->Size.z /2);
			pVtx[1].vtx = D3DXVECTOR3(wall->Size.x /2, 0.0f, wall->Size.z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-wall->Size.x / 2, 0.0f, -wall->Size.z / 2);
			pVtx[3].vtx = D3DXVECTOR3(wall->Size.x / 2, 0.0f, -wall->Size.z / 2);

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
		g_pD3DVtxBuffWall[no]->Unlock();
	}

	return S_OK;
}

WALL *GetWall(int no)
{
	return &g_aWall[no];
}
