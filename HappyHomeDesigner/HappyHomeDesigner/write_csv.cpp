//=============================================================================
//
// CSV�t�@�C���o�͏��� [write_csv.cpp]
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
#include "write_csv.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓌^
//*****************************************************************************

//=============================================================================
// CSV�f�[�^�������o��
//=============================================================================
void WriteCsv(void)
{
	FILE *fp;
	FURNITURE *furniture = GetFurniture(0);			// �|�C���^�[��������
	char fname[64];									// �t�@�C���������p

	int i = 0;
	// �o�̓t�@�C�����𐶐�����
	sprintf(fname, "data/EXCEL_DATA/set_furniture.csv", i);

	// set_furniture�ɏ㏑������ꍇ
	if ((fp = fopen(fname, "w")) != NULL)	// �������ݗp
	{
		// ��s�ڂ��o��
		fprintf(fp, "�Ƌ�̎��,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
		// �e�f�[�^���J���}��؂�ŏo��
		for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
		{	// �ǂݍ��񂾉Ƌ�̐����������[�v
			// �Ƌ�̎��,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
			fprintf(fp, "%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d\n", furniture->name, furniture->use, furniture->pos.x, furniture->pos.y, furniture->pos.z,
				furniture->rot.x, furniture->rot.y, furniture->rot.z,
				furniture->scl.x, furniture->scl.y, furniture->scl.z,
				furniture->type, furniture->house_num, furniture->weight, furniture->price, furniture->ratio);
		}
		fclose(fp);
	}
}