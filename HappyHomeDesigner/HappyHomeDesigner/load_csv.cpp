//=============================================================================
//
// CSVファイル読み込み処理 [load_csv.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "furniture.h"
#include "field.h"
#include "main.h"
#include "debugproc.h"
#include "stage.h"
#include "load_csv.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Cnt;								// 読み込んだ家具の数

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	LOAD_CSV_USE = 1,
	LOAD_CSV_POS_X,
	LOAD_CSV_POS_Y,
	LOAD_CSV_POS_Z,
	LOAD_CSV_ROT_X,
	LOAD_CSV_ROT_Y,
	LOAD_CSV_ROT_Z,
	LOAD_CSV_SCL_X,
	LOAD_CSV_SCL_Y,
	LOAD_CSV_SCL_Z,
	LOAD_CSV_TYPE,
	LOAD_CSV_HOUSE_NUM,
	LOAD_CSV_WEIGHT,
	LOAD_CSV_PRICE,
	LOAD_CSV_RATIO,
	LOAD_CSV_MAX,
};
//=============================================================================
// CSVデータを読み込む
//=============================================================================
void LoadCsv(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// 一時保存用（一行）
	char *tkn[LOAD_CSV_MAX];					// 一時保存用（分割した配列）
	FURNITURE *furniture = GetFurniture(0);		// ポインターを初期化
	int skip = 1;								// 行数を指定して飛ばす(最初の一行)
	Cnt = 0;									// カウンタ初期化

	if ((fp = fopen(FURNITURE_CSV, "r")) != NULL)
	{
		// ファイルの終わりまで繰り返し読み込む
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// カンマで分割

			for (int i = 0; i < LOAD_CSV_MAX; i++)
			{
				if (i == 0)
				{
					tkn[i] = strtok(buf, ",");
				}
				else
				{
					tkn[i] = strtok(NULL, ",");
				}
			}
			// 指定した行数を飛ばす
			if (skip > 0)
			{
				skip--;
				continue;
			}
			// charをint, doubleに変換する
			strcpy(furniture->name, tkn[0]);
			furniture->use = atoi(tkn[LOAD_CSV_USE]);
			furniture->pos.x = (float)atof(tkn[LOAD_CSV_POS_X]);
			furniture->pos.y = (float)atof(tkn[LOAD_CSV_POS_Y]);
			furniture->pos.z = (float)atof(tkn[LOAD_CSV_POS_Z]);

			furniture->rot.x = (float)atof(tkn[LOAD_CSV_ROT_X]);
			furniture->rot.y = (float)atof(tkn[LOAD_CSV_ROT_Y]);
			furniture->rot.z = (float)atof(tkn[LOAD_CSV_ROT_Z]);

			furniture->scl.x = (float)atof(tkn[LOAD_CSV_SCL_X]);
			furniture->scl.y = (float)atof(tkn[LOAD_CSV_SCL_Y]);
			furniture->scl.z = (float)atof(tkn[LOAD_CSV_SCL_Z]);

			furniture->type = atoi(tkn[LOAD_CSV_TYPE]);
			furniture->house_num = atoi(tkn[LOAD_CSV_HOUSE_NUM]);
			furniture->weight = atoi(tkn[LOAD_CSV_WEIGHT]);
			furniture->price = atoi(tkn[LOAD_CSV_PRICE]);
			furniture->ratio = atoi(tkn[LOAD_CSV_RATIO]);
			
			Cnt++;			// 読み込んだ家具の数カウント
			furniture++;	// 次のデータに
		}
		fclose(fp);
	}
}
//=============================================================================
// 読み込んだ家具の数取得関数
//=============================================================================
int GetFurnitureCnt(void)
{
	return (Cnt);
}
