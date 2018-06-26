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
void WriteCsv(int no)
{
	FILE *fp;
	FURNITURE *furniture = GetFurniture(0);			// ポインターを初期化
	char fname[64];									// ファイル名生成用
	int n = 0;										// csvファイル数格納用


	// 新たにcsvファイルを作成する場合(Mキー)
	if (no == CREATE)
	{
		// 既存のファイル名と被らない出力ファイル名を生成する処理
		// EXCEL_DATAフォルダにあるcsvファイルの数を求める
		n = GetCsvCnt(__argc, __argv) - DEFAULT_FILE_CNT;
		// ファイル名の末尾の数字を求めたファイル数+1としてファイル名を生成する
		sprintf(fname, "data/EXCEL_DATA/set_furniture%d.csv", n);
		// csvファイル新規作成
		if ((fp = fopen(fname, "w")) != NULL)	// 書き込み用
		{
			// 一行目を出力
			fprintf(fp, "家具の種類,id,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
			// 各データをカンマ区切りで出力
			for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
			{	// 読み込んだ家具の数分だけループ
				// 家具の種類,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
				fprintf(fp, "%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d\n", furniture->name, furniture->id, furniture->use, furniture->pos.x, furniture->pos.y, furniture->pos.z,
					furniture->rot.x, furniture->rot.y, furniture->rot.z,
					furniture->scl.x, furniture->scl.y, furniture->scl.z,
					furniture->type, furniture->house_num, furniture->weight, furniture->price, furniture->ratio);
			}
			fclose(fp);
		}
	}
	// set_furnitureに上書きする場合(Qキー)
	if (no == OVERWRITE)
	{
		// 上書き対象のファイル名を取得する
		sprintf(fname, "data/EXCEL_DATA/set_furniture%d.csv", GetfinalCsvNum());
		// csvファイル上書き
		if ((fp = fopen(fname, "w")) != NULL)	// 書き込み用
		{
			// 一行目を出力
			fprintf(fp, "家具の種類,id,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
			// 各データをカンマ区切りで出力
			for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
			{	// 読み込んだ家具の数分だけループ
				// 家具の種類,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
				fprintf(fp, "%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%ll,%d\n",
					furniture->name, furniture->id, furniture->use, furniture->pos.x, furniture->pos.y, furniture->pos.z,
					furniture->rot.x, furniture->rot.y, furniture->rot.z,
					furniture->scl.x, furniture->scl.y, furniture->scl.z,
					furniture->type, furniture->house_num, furniture->weight, furniture->price, furniture->ratio);
			}
			fclose(fp);
		}
	}
}
//=============================================================================
// CSVファイル数取得関数
//=============================================================================
int GetCsvCnt(int argc, char *argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR *dir = "data/EXCEL_DATA/set_furniture*.csv";		// 拡張子がcsvのファイルを指定
	int fileCount = 0;										// ファイル数カウント初期化

	hFind = FindFirstFile(dir, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			fileCount++;									// ファイル数カウント
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
	// ファイル数を返す
	return fileCount;
}
