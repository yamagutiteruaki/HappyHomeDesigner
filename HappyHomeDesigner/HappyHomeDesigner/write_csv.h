//=============================================================================
//
// CSVファイル出力処理 [write_csv.h]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#ifndef _WRITE_CSV_H_
#define _WRITE_CSV_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	DEFAULT_FILE_CNT	(2)			// 元からEXCEL_DATAフォルダに入ってたcsvファイル数

//**************************************
// ファイル出力方法
//**************************************
enum
{
	CREATE = 0,			// 新規csvファイル作成
	OVERWRITE,			// 上書き保存
	FILE_OUTPUT_MAX		// ファイル出力方法の種類数
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void WriteCsv(int no);
int GetCsvCnt(int argc, char *argv[]);

#endif
