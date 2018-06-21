//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : GP12A295-19-���_��
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void RankingSort();
int Compare(const void *p, const void *q);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
RANKING			rankingWk[RANKING_MAX];						// �����L���O�i�[���[�N
int				rankCnt;									// �ǂݍ��񂾃����L���O�̐�
//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum
{
	RANKING_CSV_ID = 0,		// ID
	RANKING_CSV_RANK,		// ����
	RANKING_CSV_SCORE,		// �X�R�A(��Q���z)
	RANKING_CSV_MAX,
};
//=============================================================================
// �����L���O����
//=============================================================================
void Ranking(void)
{
	// �����L���O�pcsv�t�@�C���ǂݍ���
	LoadRankingCsv();
	// �X�R�A�����Ƃ�3�ʂ̃X�R�A�Ɣ�r���A3�ʂ̃X�R�A���Ⴏ��΃����L���O�X�V���Ȃ��������L���O�\���ɃX�L�b�v

	// 3�ʂ��X�R�A������΃����L���O�X�V�������s��(�\�[�g)
	RankingSort();
	// �ŐV�̃����L���O�pcsv�t�@�C���쐬
	WriteRankingCsv();
	// �����L���O�\��

}
//=============================================================================
// �����L���O�pcsv�t�@�C���ǂݍ��ݏ���
//=============================================================================
void LoadRankingCsv(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// �ꎞ�ۑ��p�i��s�j
	char *tkn[RANKING_CSV_MAX];					// �ꎞ�ۑ��p�i���������z��j
	RANKING *ranking = &rankingWk[0];			// �|�C���^�[��������
	int skip = 1;								// �s�����w�肵�Ĕ�΂�(�ŏ��̈�s)
	rankCnt = 0;								// �J�E���^������

	if ((fp = fopen(RANKING_CSV, "r")) != NULL)
	{
		// �t�@�C���̏I���܂ŌJ��Ԃ��ǂݍ���
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// �J���}�ŕ���
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
			// �w�肵���s�����΂�
			if (skip > 0)
			{
				skip--;
				continue;
			}
			// char��int�ɕϊ�����
			ranking->id = atoi(tkn[RANKING_CSV_ID]);
			ranking->rank = atoi(tkn[RANKING_CSV_RANK]);
			ranking->score = atoll(tkn[RANKING_CSV_SCORE]);

			rankCnt++;	// �ǂݍ��ݐ��J�E���g
			ranking++;	// ���̃f�[�^��
		}
		fclose(fp);
	}
}
//=============================================================================
// �����L���O�̎擾
//=============================================================================
RANKING *GetRanking(int no)
{
	return &rankingWk[no];
}
//=============================================================================
// �ǂݍ��񂾐��擾�֐�
//=============================================================================
int GetRankingCnt(void)
{
	return (rankCnt);
}
//=============================================================================
// �����L���O�pcsv�t�@�C���������ݏ���
//=============================================================================
void WriteRankingCsv(void)
{
	FILE *fp;
	RANKING *ranking = &rankingWk[0];				// �|�C���^�[��������

	// csv�t�@�C���㏑��
	if ((fp = fopen(RANKING_CSV, "w")) != NULL)		// �������ݗp
	{
		// ��s�ڂ��o��
		fprintf(fp, "id,rank,score\n");
		// �e�f�[�^���J���}��؂�ŏo��
		for (int i = 0; i < GetRankingCnt(); i++, ranking++)
		{	// �ǂݍ��񂾐��������[�v
			fprintf(fp, "%d,%d,%lld\n", ranking->id, ranking->rank, ranking->score);
		}
		fclose(fp);
	}
}
//=============================================================================
// �����L���O�X�V����(�\�[�g)
//=============================================================================
void RankingSort()
{
	RANKING *ranking = &rankingWk[0];					// �|�C���^�[��������
	int num = sizeof rankingWk / sizeof(RANKING);		// �v�f�������߂�
	qsort(rankingWk, num, sizeof(RANKING), Compare);	// �N�C�b�N�\�[�g
	
	// ���ʂ��X�V
	for (int i = 0; i < RANKING_MAX; i++, ranking++)
	{
		ranking->rank = i + 1;
	}
}

//=============================================================================
// ��r�֐�����(�~���\�[�g)
//=============================================================================
int Compare(const void *p, const void *q)
{
	// �X�R�A�Ŕ�r
	long long n = ((RANKING*)q)->score - ((RANKING*)p)->score;
	// �X�R�A�������������ꍇ
	if (n == 0)
	{	// id�̒l���傫���ق�����ʂɂ���
		int m = ((RANKING*)q)->id - ((RANKING*)p)->id;
		return m;
	}
	// int�^�I�[�o�[�t���[�Ώ�
	//if ((RANKING*)q > (RANKING*)p) return -1;
	//if ((RANKING*)q < (RANKING*)p) return 1;
	return n;
}