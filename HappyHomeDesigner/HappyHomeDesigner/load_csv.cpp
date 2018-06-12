//=============================================================================
//
// CSV�t�@�C���ǂݍ��ݏ��� [load_csv.cpp]
// Author : GP12A295-19-���_��
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Cnt;								// �ǂݍ��񂾉Ƌ�̐�

//*****************************************************************************
// �񋓌^
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
// CSV�f�[�^��ǂݍ���
//=============================================================================
void LoadCsv(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// �ꎞ�ۑ��p�i��s�j
	char *tkn[LOAD_CSV_MAX];					// �ꎞ�ۑ��p�i���������z��j
	FURNITURE *furniture = GetFurniture(0);		// �|�C���^�[��������
	int skip = 1;								// �s�����w�肵�Ĕ�΂�(�ŏ��̈�s)
	Cnt = 0;									// �J�E���^������

	if ((fp = fopen(FURNITURE_CSV, "r")) != NULL)
	{
		// �t�@�C���̏I���܂ŌJ��Ԃ��ǂݍ���
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// �J���}�ŕ���

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
			// �w�肵���s�����΂�
			if (skip > 0)
			{
				skip--;
				continue;
			}
			// char��int, double�ɕϊ�����
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
			
			Cnt++;			// �ǂݍ��񂾉Ƌ�̐��J�E���g
			furniture++;	// ���̃f�[�^��
		}
		fclose(fp);
	}
}
//=============================================================================
// �ǂݍ��񂾉Ƌ�̐��擾�֐�
//=============================================================================
int GetFurnitureCnt(void)
{
	return (Cnt);
}
