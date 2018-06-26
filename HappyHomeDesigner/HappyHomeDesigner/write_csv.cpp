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
void WriteCsv(int no)
{
	FILE *fp;
	FURNITURE *furniture = GetFurniture(0);			// �|�C���^�[��������
	char fname[64];									// �t�@�C���������p
	int n = 0;										// csv�t�@�C�����i�[�p


	// �V����csv�t�@�C�����쐬����ꍇ(M�L�[)
	if (no == CREATE)
	{
		// �����̃t�@�C�����Ɣ��Ȃ��o�̓t�@�C�����𐶐����鏈��
		// EXCEL_DATA�t�H���_�ɂ���csv�t�@�C���̐������߂�
		n = GetCsvCnt(__argc, __argv) - DEFAULT_FILE_CNT;
		// �t�@�C�����̖����̐��������߂��t�@�C����+1�Ƃ��ăt�@�C�����𐶐�����
		sprintf(fname, "data/EXCEL_DATA/set_furniture%d.csv", n);
		// csv�t�@�C���V�K�쐬
		if ((fp = fopen(fname, "w")) != NULL)	// �������ݗp
		{
			// ��s�ڂ��o��
			fprintf(fp, "�Ƌ�̎��,id,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
			// �e�f�[�^���J���}��؂�ŏo��
			for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
			{	// �ǂݍ��񂾉Ƌ�̐����������[�v
				// �Ƌ�̎��,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
				fprintf(fp, "%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d\n", furniture->name, furniture->id, furniture->use, furniture->pos.x, furniture->pos.y, furniture->pos.z,
					furniture->rot.x, furniture->rot.y, furniture->rot.z,
					furniture->scl.x, furniture->scl.y, furniture->scl.z,
					furniture->type, furniture->house_num, furniture->weight, furniture->price, furniture->ratio);
			}
			fclose(fp);
		}
	}
	// set_furniture�ɏ㏑������ꍇ(Q�L�[)
	if (no == OVERWRITE)
	{
		// �㏑���Ώۂ̃t�@�C�������擾����
		sprintf(fname, "data/EXCEL_DATA/set_furniture%d.csv", GetfinalCsvNum());
		// csv�t�@�C���㏑��
		if ((fp = fopen(fname, "w")) != NULL)	// �������ݗp
		{
			// ��s�ڂ��o��
			fprintf(fp, "�Ƌ�̎��,id,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio\n");
			// �e�f�[�^���J���}��؂�ŏo��
			for (int i = 0; i < GetFurnitureCnt(); i++, furniture++)
			{	// �ǂݍ��񂾉Ƌ�̐����������[�v
				// �Ƌ�̎��,use,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z,scl.x,scl.y,scl.z,type,house_num,weight,price,ratio
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
// CSV�t�@�C�����擾�֐�
//=============================================================================
int GetCsvCnt(int argc, char *argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR *dir = "data/EXCEL_DATA/set_furniture*.csv";		// �g���q��csv�̃t�@�C�����w��
	int fileCount = 0;										// �t�@�C�����J�E���g������

	hFind = FindFirstFile(dir, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			fileCount++;									// �t�@�C�����J�E���g
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
	// �t�@�C������Ԃ�
	return fileCount;
}
