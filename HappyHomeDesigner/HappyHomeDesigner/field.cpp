//=============================================================================
//
// 地面処理 [field.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "field.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"
#include "fade.h"
#include "player.h"
#include "collision.h"


/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_LIMIT				(0)
#define HOUSE_LEN				(200.0f)
#define HOUSE_WID				(170.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void AreaHouse(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField[FIELD_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField[FIELD_MAX];	// 頂点バッファへのポインタ

FIELD					g_aField[FIELD_MAX];

const char *FileNameField[FIELD_MAX] =
{
	TEXTURE_FIELD,		// 家1
	TEXTURE_FIELD1,		// 家2
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);

	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				FileNameField[i],			// ファイルの名前
				&g_pD3DTextureField[i]);	// 読み込むメモリー
		}

		field->Pos.x = 0.0f;	//X座標の設定
		field->Pos.y = 0.0f;//Y座標は0固定
		field->Pos.z = 0.0f;	//Z座標の設定

		field->Size = D3DXVECTOR3(FIELD_SIZE_X / (i*3 + 1), 0.0f, FIELD_SIZE_Z / (i*3 + 1));
		//field->Size = D3DXVECTOR3(FIELD_SIZE_X/2, 0.0f, FIELD_SIZE_Z/2);

	}
		MakeVertexField(pDevice);




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		//フィールド
		if (g_pD3DTextureField != NULL)
		{// テクスチャの開放
			g_pD3DTextureField[i]->Release();
			g_pD3DTextureField[i] = NULL;
		}

		if (g_pD3DVtxBuffField != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffField[i]->Release();
			g_pD3DVtxBuffField[i] = NULL;
		}
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	AreaHouse();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{
		SetFade(FADE_OUT, STAGE_HOUSE1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F2))
	{
		SetFade(FADE_OUT, STAGE_HOUSE2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F3))
	{
		SetFade(FADE_OUT, STAGE_HOUSE3, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F4))
	{
		SetFade(FADE_OUT, STAGE_MYHOUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F5))
	{
		SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
#endif



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DXMATERIAL matDef;
	int fieldnum;

	if (GetStage() == STAGE_GAME)
	{
		fieldnum = 0;
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE
		|| GetStage() == STAGE_RESULT)
	{
		fieldnum = 1;
	}
	FIELD *field = GetField(fieldnum);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&field->world);


	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
	D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &field->world);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField[fieldnum], 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureField[fieldnum]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{	
	FIELD *field = GetField(0);
	VERTEX_3D *pVtx;
	for (int i = 0; i < FIELD_MAX; i++, field++, pVtx += 4)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffField[i],		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}
		//for (int i = 0; i < FIELD_MAX; i++)
		{//頂点バッファの中身を埋める

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffField[i]->Lock(0, 0, (void**)&pVtx, 0);



			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[1].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[2].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, -field->Size.z / 2);
				pVtx[3].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, -field->Size.z / 2);

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
			g_pD3DVtxBuffField[i]->Unlock();
		}
	}
	return S_OK;
}

FIELD *GetField(int no)
{
	return &g_aField[no];
}


