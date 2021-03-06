//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "field.h"
#include "main.h"
#include "debugproc.h"
#include "stage.h"
#include "load_csv.h"
#include "write_csv.h"
#include "ranking.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void RankingSort();
int Compare(const void *p, const void *q);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
RANKING			rankingWk[RANKING_MAX];						// ランキング格納ワーク
int				rankCnt;									// 読み込んだランキングの数
//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	RANKING_CSV_ID = 0,		// ID
	RANKING_CSV_RANK,		// 順位
	RANKING_CSV_SCORE,		// スコア(被害総額)
	RANKING_CSV_MAX,
};
enum
{	// 順位
	FIRST=0,				// 一位
	SECOND,					// 二位
	THIRD,					// 三位
	FOURTH					// 四位
};

//=============================================================================
// ランキング処理
//=============================================================================
void Ranking(void)
{
	// ランキング用csvファイル読み込み
	LoadRankingCsv();
	// IDの最大値を抽出する
	int max = rankingWk[0].id;	// id最大値格納用
	for (int i = 1; i < RANKING_MAX - 1; i++)
	{
		if (max < rankingWk[i].id) max = rankingWk[i].id;
	}
	// 被害金額(スコア)を取得(一時的に四位のスコアとする)
	rankingWk[FOURTH].score = GetPrice();
	rankingWk[FOURTH].id = max + 1;			// ID付与(既存のIDの最大値+1のID)
	// スコアをもとに3位のスコアと比較し、3位のスコアより低ければランキング更新しない
	if (rankingWk[FOURTH].score > rankingWk[THIRD].score)
	{	// 3位よりスコア高ければランキング更新処理を行う(ソート)
		RankingSort();
		// 最新のランキング用csvファイル作成
		WriteRankingCsv();
	}
	// ランキング表示？

}
//=============================================================================
// ランキング用csvファイル読み込み処理
//=============================================================================
void LoadRankingCsv(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// 一時保存用（一行）
	char *tkn[RANKING_CSV_MAX];					// 一時保存用（分割した配列）
	RANKING *ranking = &rankingWk[0];			// ポインターを初期化
	int skip = 1;								// 行数を指定して飛ばす(最初の一行)
	rankCnt = 0;								// カウンタ初期化

	if ((fp = fopen(RANKING_CSV, "r")) != NULL)
	{
		// ファイルの終わりまで繰り返し読み込む
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// カンマで分割
			for (int i = 0; i < RANKING_CSV_MAX; i++)
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
			// charをintに変換する
			ranking->id = atoi(tkn[RANKING_CSV_ID]);
			ranking->rank = atoi(tkn[RANKING_CSV_RANK]);
			ranking->score = atoll(tkn[RANKING_CSV_SCORE]);

			rankCnt++;	// 読み込み数カウント
			ranking++;	// 次のデータに
		}
		fclose(fp);
	}
}
//=============================================================================
// ランキングの取得
//=============================================================================
RANKING *GetRanking(int no)
{
	return &rankingWk[no];
}
//=============================================================================
// 読み込んだ数取得関数
//=============================================================================
int GetRankingCnt(void)
{
	return (rankCnt);
}
//=============================================================================
// ランキング用csvファイル書き込み処理
//=============================================================================
void WriteRankingCsv(void)
{
	FILE *fp;
	RANKING *ranking = &rankingWk[0];				// ポインターを初期化

	// csvファイル上書き
	if ((fp = fopen(RANKING_CSV, "w")) != NULL)		// 書き込み用
	{
		// 一行目を出力
		fprintf(fp, "id,rank,score\n");
		// 各データをカンマ区切りで出力
		for (int i = 0; i < RANKING_MAX - 1; i++, ranking++)
		{	// 3位までのデータを書き込む
			fprintf(fp, "%d,%d,%lld\n", ranking->id, ranking->rank, ranking->score);
		}
		fclose(fp);
	}
}
//=============================================================================
// ランキング更新処理(ソート)
//=============================================================================
void RankingSort()
{
	RANKING *ranking = &rankingWk[0];					// ポインターを初期化
	int num = sizeof rankingWk / sizeof(RANKING);		// 要素数を求める
	qsort(rankingWk, num, sizeof(RANKING), Compare);	// クイックソート
	
	// 順位を更新
	for (int i = 0; i < RANKING_MAX; i++, ranking++)
	{
		ranking->rank = i + 1;
	}
}

//=============================================================================
// 比較関数処理(降順ソート)
//=============================================================================
int Compare(const void *p, const void *q)
{
	// スコアで比較
	long long n = ((RANKING*)q)->score - ((RANKING*)p)->score;
	// スコアが同じだった場合
	if (n == 0)
	{	// idの値が大きいほうを上位にする
		int m = ((RANKING*)q)->id - ((RANKING*)p)->id;
		return m;
	}
	// int型オーバーフロー対処
	//if ((RANKING*)q > (RANKING*)p) return -1;
	//if ((RANKING*)q < (RANKING*)p) return 1;
	return n;
}