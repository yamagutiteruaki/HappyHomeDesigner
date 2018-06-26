//=============================================================================
//
// ���͏��� [sound.cpp]
// Author : GP12B295 29 �R���P��
//
//=============================================================================
#include "sound.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

// ���܂��Ȃ�
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void		SetSound(void);
long		GetVol(LPDIRECTSOUNDBUFFER8 pBuffer);
void		SetBgmVol(int no, int type);
void		UpdateSoundBgm(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pBgm[SOUND_BGM_MAX];
LPDIRECTSOUNDBUFFER8	g_pSe[SOUND_SE_MAX];
LPDIRECTSOUNDBUFFER8	g_pVoice[SOUND_VOICE_MAX];
int						g_nBgmFlag;
bool					g_bBgmBoss;
long g_nVol[SOUND_BGM_MAX];


// �T�E���h�t�@�C���̃p�X�isound.h�̒ʂ��i���o�[�Ə��Ԃ����킹�邱�Ɓj
const TCHAR* c_soundFilename[] = {
	// BGM
	_T("data/SOUND/BGM/bgm_maoudamashii_ethnic25.wav"),
	_T("data/SOUND/BGM/Stage_bgm_maoudamashii_fantasy05.wav"),
	_T("data/SOUND/BGM/bgm_maoudamashii_ethnic31.wav"),
	// SE
	_T("data/SOUND/SE/Take_se_maoudamashii_system45.wav"),
	_T("data/SOUND/SE/Time_se_maoudamashii_chime14.wav"),
	_T("data/SOUND/SE/Deci_se_maoudamashii_system22.wav"),
	_T("data/SOUND/SE/Voice_00_se_maoudamashii_onepoint03.wav"),
	_T("data/SOUND/SE/nyu3.wav"),
	_T("data/SOUND/SE/robot - footstep2.wav")
};

// �O���[�o���ϐ�
IDirectSound8 *g_pDirectSound = NULL;	// �T�E���h�C���^�[�t�F�[�X

// �T�E���h�̏�����
// hWnd:�E�B���h�E�n���h��
HRESULT InitSound( HWND hWnd )
{
	// DirectSound�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// �������x���ݒ� 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;
	g_nBgmFlag = SOUND_BGM_TITLE;
	g_bBgmBoss = false;

	for (int i = 0; i < SOUND_BGM_MAX; i++)
	{
		g_nVol[i] = VOLUME_MIN;
	}

	SetSound();

	return S_OK;
}

void UpdateSound(void)
{
	UpdateSoundBgm();
#ifdef _DEBUG
	PrintDebugProc("�y SOUND �z  BGM FLAG[%d]\n", g_nBgmFlag);
	for (int i = 0; i < SOUND_BGM_MAX; i++)
	{
		PrintDebugProc("BGM00%d[%l]\n", i, GetVol(g_pBgm[i]));
	}
#endif
}

// ��Еt��
void UninitSound()
{
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}
}

// �T�E���h�̃��[�h
// no:�T�E���h�i���o�[�i�w�b�_�ɒ�`���ꂽ�񋓌^�萔�j
LPDIRECTSOUNDBUFFER8 LoadSound( int no )
{
	// MMIO = �}���`���f�B�A���o�́A�̗��B
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;						// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;						// MMIO�n���h��
	MMIOINFO mmioInfo;						// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;							// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID pBlock;				// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD  dwSize;				// �Z�J���_���o�b�t�@�̃T�C�Y

	// 1.�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)c_soundFilename[no], &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// �����������Ƃɓǂݍ���
	
	if(size != formatChunk.cksize) 		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR) 		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.�f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���
	
	if(size != dataChunk.cksize)  		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// 6.�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);			// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// �T�E���h�o�b�t�@�����o��
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7.���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// �f�[�^�]��
	delete[] pData;					// ���̓ǂݍ��ݗ̈������

	// �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Z�J���_���o�b�t�@��Ԃ��Ă悤�₭����...
	return pBuffer;
}

void UpdateSoundBgm(void)
{
	switch (g_nBgmFlag)
	{
	case SOUND_BGM_TITLE:
		SetBgmVol(BGM_TITLE, true);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_GAME:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_GAME, true);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_RESULT:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, true);
		break;
	}
}

void SetSoundBgm(int nBgm)
{
	g_nBgmFlag = nBgm;
}

void SetSoundBgmBoss(bool bBgm)
{
	g_bBgmBoss = bBgm;
}

// ����炷
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
// flag   :1(E_DS8_FLAG_LOOP)�Ȃ烋�[�v�Đ�
void PlaySound(  LPDIRECTSOUNDBUFFER8 pBuffer, int flag/*=0*/ )
{	// ��������炷�̂ŁA�ŏ�����炵�����ꍇ��SetCurrentPosition(0)�����邱��
	pBuffer->Play(0, 0, flag);
}

void PlayContinuitySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag)
{
	pBuffer->SetCurrentPosition(0);
	PlaySound(pBuffer, flag);
}

// �����~�߂�
void StopSound( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )	// ���Ă�����
	{
		pBuffer->Stop();	// �Ӗ��I�ɂ�PabUse�ɂȂ�B
	}
}

// �Đ������ǂ������ׂ�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )
	{
		return true;
	}
	return false;
}

HRESULT SetVol( LPDIRECTSOUNDBUFFER8 pBuffer, long nVol)
{
	DWORD status;

	pBuffer->GetStatus(&status);
	pBuffer->SetVolume(nVol);
	return DS_OK;
}

long GetVol(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;
	long lVol;
	pBuffer->GetStatus(&status);
	pBuffer->GetVolume(&lVol);
	return lVol;
}

//=============================================================================
// �T�E���h�ݒ�֐�
//=============================================================================
void SetSound(void)
{
	// BGM������Ȃ��悤�Ƀ��[�h�ƕ�����
	for (int i = BGM_00; i < SOUND_BGM_MAX; i++)
	{
		// �eBGM���[�h
		g_pBgm[i] = LoadSound(i);
	}
	for (int i = BGM_00; i < SOUND_BGM_MAX; i++)
	{
		// �eBGM�{�����[���Z�b�g
		PlaySound(g_pBgm[i], E_DS8_FLAG_LOOP);
		SetVol(g_pBgm[i], VOLUME_MIN);
	}

	for (int i = 0; i < SOUND_SE_MAX; i++)
	{	
		// �eSE���[�h
		g_pSe[i] = LoadSound(i + SE_00);
		//// �eSE�{�����[���Z�b�g
		//if (i != SE_00 || i != SE_11 || i != SE_13)
		//{
		//	SetVol(g_pSe[i], VOLUME_SE);
		//}
	}

	//SetVol(g_pSe[11], SE_11_VOLUME_SE);

	//for (int i = 0; i < SOUND_VOICE_MAX; i++)
	//{
	//	// �eSE���[�h
	//	g_pVoice[i] = LoadSound(i + VOICE_00);
	//}
}

//=============================================================================
// SE�Đ��֐�
//=============================================================================
void SetSe(int nVoice, int nFlag, bool bContinuity)
{
	if (bContinuity)
	{
		PlayContinuitySound(g_pSe[nVoice], nFlag);
	}
	else
	{
		PlaySound(g_pSe[nVoice], nFlag);
	}
}

//=============================================================================
// Voice�Đ��֐�
//=============================================================================
void SetVoice(int nVoice, int nFlag, bool bContinuity)
{
	if (bContinuity)
	{
		PlayContinuitySound(g_pVoice[nVoice], nFlag);
	}
	else
	{
		PlaySound(g_pVoice[nVoice], nFlag);
	}
}

//=============================================================================
// BGM�{�����[���R���g���[��
//=============================================================================
void SetBgmVol(int no, int type)
{
	// type 0=�t�F�[�h�A�E�g 1=�t�F�[�h�C��
	if (type == VOLUME_FADE_OUT)
	{
		if (g_nVol[no] > VOLUME_MIN)
		{
			g_nVol[no] -= VOLUME_CONTROL_DOWN;
			if (g_nVol[no] < VOLUME_MIN)
			{
				g_nVol[no] = VOLUME_MIN;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
	else if (type == VOLUME_FADE_IN)
	{
		if (g_nVol[no] < VOLUME_MAX)
		{
			g_nVol[no] += VOLUME_CONTROL_UP;
			if (g_nVol[no] > VOLUME_MAX)
			{
				g_nVol[no] = VOLUME_MAX;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
	else if (type == VOLUME_FADE_HALF)
	{
		if (g_nVol[no] > VOLUME_HALF)
		{
			g_nVol[no] -= VOLUME_CONTROL_DOWN;
			if (g_nVol[no] < VOLUME_HALF)
			{
				g_nVol[no] = VOLUME_HALF;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
}