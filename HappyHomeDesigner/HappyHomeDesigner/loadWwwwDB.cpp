//=============================================================================
//
// CSV�t�@�C���ǂݍ��ݏ��� [loadWwwwDB.cpp]
// Author : �v�F��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "loadWwwwDB.h"
#include "wwwwwwww.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	LOADFILENAME	"data/EXCEL_DATA/wwwwwwww_db.csv"		// �ǂݍ��ރt�@�C����
#define BUFC_MAX		(128)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �񋓌^
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
// CSV�f�[�^��ǂݍ���
//=============================================================================
void LoadWWWWDB(void)
{
	FILE *fp;
	char buf[BUFC_MAX];							// �ꎞ�ۑ��p�i��s�j
	char *tkn[LOAD_CSV_MAX];					// �ꎞ�ۑ��p�i���������z��j
	int skip = 1;								// �s�����w�肵�Ĕ�΂�(�ŏ��̈�s)

	WWWW *wwww = GetWWWW(0);

	if ((fp = fopen(LOADFILENAME, "r")) != NULL)
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
			wwww->use = atoi(tkn[LOAD_CSV_USE]);
			wwww->wwww.Pos.x = (float)atof(tkn[LOAD_CSV_POS_X]);
			wwww->wwww.Pos.y = (float)atof(tkn[LOAD_CSV_POS_Y]);
			wwww->wwww.Pos.z = (float)atof(tkn[LOAD_CSV_POS_Z]);
			wwww->wwww.Rot.x = (float)atof(tkn[LOAD_CSV_ROT_X]) * (D3DX_PI / 180);
			wwww->wwww.Rot.y = (float)atof(tkn[LOAD_CSV_ROT_Y]) * (D3DX_PI / 180);
			wwww->wwww.Rot.z = (float)atof(tkn[LOAD_CSV_ROT_Z]) * (D3DX_PI / 180);

			wwww++;	// ���̃f�[�^��
		}
		fclose(fp);
	}
}