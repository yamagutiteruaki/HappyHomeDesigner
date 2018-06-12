//=============================================================================
//
// CSVファイル出力処理 [write_csv.cpp]
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
#include "write_csv.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙型
//*****************************************************************************

//=============================================================================
// CSVデータを書き出す
//=============================================================================
void WriteCsv(void)
{
	FILE *fp;
	FURNITURE *furniture = GetFurniture(0);			// ポインターを初期化

	if ((fp = fopen(FURNITURE_CSV, "w")) != NULL)	// 書き込み用
	{
		// 一行目を出力
		fprintf(fp, "家具の種類,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
		// 各データをカンマ区切りで出力
		for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
		{	// 読み込んだ家具の数分だけループ
			// 家具の種類,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
			fprintf(fp, "%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d\n", furniture->name, furniture->use, furniture->pos.x, furniture->pos.y, furniture->pos.z,
				furniture->rot.x, furniture->rot.y, furniture->rot.z,
				furniture->scl.x, furniture->scl.y, furniture->scl.z,
				furniture->type, furniture->house_num, furniture->weight, furniture->price, furniture->ratio);
		}
		fclose(fp);
	}
}