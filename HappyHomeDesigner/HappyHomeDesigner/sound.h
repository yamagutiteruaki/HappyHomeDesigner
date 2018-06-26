//=============================================================================
//
// ���͏��� [sound.h]
// Author : GP12B295 29 �R���P��
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define VOLUME_CONTROL_UP	(120)			// ���ʏ㏸��
#define VOLUME_CONTROL_DOWN	(20)			// ���ʉ��~��
#define VOLUME_MAX			(-500)			// �ő剹��
#define VOLUME_HALF			(-2000)			// ���ԉ���
#define VOLUME_MIN			(-8000)			// �ŏ�����
#define VOLUME_SE			(-800)			// SE�{�����[��
#define VOLUME_VOICE		(-500)			// �{�C�X�{�����[��

#define SE_11_CONTINUITY	(5)				// �q�b�gSE�̍Đ��Ԋu
#define SE_11_VOLUME_SE		(-1200)			// SE11�̃{�����[���ݒ�

#define SOUND_BGM_MAX		(SE_00)
#define SOUND_SE_MAX		(VOICE_00 - SE_00)
#define SOUND_VOICE_MAX		(SOUND_MAX - VOICE_00)

enum
{	// �T�E���h�ʂ��i���o�[(sound.cpp�̏��Ԃƍ��킹�鎖)
	BGM_00,
	BGM_01,
	BGM_02,
	SE_00,
	SE_01,
	SE_02,
	SE_03,
	SE_04,
	SE_05,
	VOICE_00,
	SOUND_MAX
};

enum
{
	BGM_TITLE,
	BGM_GAME,
	BGM_RESULT
};

enum
{
	SE_TAKE,
	SE_CHIME,
	SE_DECI,
	SE_VOICE,
	SE_ITEM,
	SE_ENEMY_WALK
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

enum
{	// �Đ��p�t���O
	VOLUME_FADE_OUT,
	VOLUME_FADE_IN,
	VOLUME_FADE_HALF
};

enum
{	// �A���Đ��t���O
	CONTINUITY_OFF,
	CONTINUITY_ON
};

enum
{	// BGM�t���O
	SOUND_BGM_TITLE,
	SOUND_BGM_GAME,
	SOUND_BGM_RESULT
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
void					UpdateSound(void);
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
void					PlayContinuitySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���
HRESULT					SetVol(LPDIRECTSOUNDBUFFER8 pBuffer, long nVol);
void					SetSoundBgm(int nBgm);
void					SetSoundBgmBoss(bool bBgm);
void					SetSe(int nVoice, int nFlag, bool bContinuity);
void					SetVoice(int nVoice, int nFlag, bool bContinuity);
#endif