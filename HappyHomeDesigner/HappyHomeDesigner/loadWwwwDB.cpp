//=============================================================================
//
// CSVファイル読み込み処理 [loadWwwwDB.cpp]
// Author : 宋彦霖
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "loadWwwwDB.h"
#include "wwwwwwww.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LOADFILENAME	"data/EXCEL_DATA/wwwwwwww_db.csv"		// 読み込むファイル名
#define BUFC_MAX		(128)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	LOAD_CSV_ID = 0,
	LOAD_CSV_NAME,
	LOAD_CSV_USE,
	LOAD_CSV_POS_X,
	LOAD_CSV_POS_Y,
	LOAD_CSV_POS_Z,
	LOAD_CSV_ROT_X,
	LOAD_CSV_ROT_Y,
	LOAD_CSV_ROT_Z,
	LOAD_CSV_MAX,
};
//=============================================================================
// CSVデータを読み込む
//=============================================================================
void LoadWWWWDB(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// 一時保存用（一行）
	char *tkn[LOAD_CSV_MAX];					// 一時保存用（分割した配列）
	int skip = 1;								// 行数を指定して飛ばす(最初の一行)

	WWWW *wwww = GetWWWW(0);

	if ((fp = fopen(LOADFILENAME, "r")) != NULL)
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
			wwww->use = atoi(tkn[LOAD_CSV_USE]);
			wwww->wwww.Pos.x = (float)atof(tkn[LOAD_CSV_POS_X]);
			wwww->wwww.Pos.y = (float)atof(tkn[LOAD_CSV_POS_Y]);
			wwww->wwww.Pos.z = (float)atof(tkn[LOAD_CSV_POS_Z]);
			wwww->wwww.Rot.x = (float)atof(tkn[LOAD_CSV_ROT_X]) * (D3DX_PI / 180);
			wwww->wwww.Rot.y = (float)atof(tkn[LOAD_CSV_ROT_Y]) * (D3DX_PI / 180);
			wwww->wwww.Rot.z = (float)atof(tkn[LOAD_CSV_ROT_Z]) * (D3DX_PI / 180);

			wwww++;	// 次のデータに
		}
		fclose(fp);
	}
}