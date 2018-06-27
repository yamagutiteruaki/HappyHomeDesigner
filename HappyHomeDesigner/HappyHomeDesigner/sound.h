//=============================================================================
//
// 入力処理 [sound.h]
// Author : GP12B295 29 山口輝明
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VOLUME_CONTROL_UP	(120)			// 音量上昇幅
#define VOLUME_CONTROL_DOWN	(20)			// 音量下降幅
#define VOLUME_MAX			(-500)			// 最大音量
#define VOLUME_HALF			(-2000)			// 中間音量
#define VOLUME_MIN			(-8000)			// 最小音量
#define VOLUME_SE			(-800)			// SEボリューム
#define VOLUME_VOICE		(-500)			// ボイスボリューム

#define SE_11_CONTINUITY	(5)				// ヒットSEの再生間隔
#define SE_11_VOLUME_SE		(-1200)			// SE11のボリューム設定

#define SOUND_BGM_MAX		(SE_00)
#define SOUND_SE_MAX		(VOICE_00 - SE_00)
#define SOUND_VOICE_MAX		(SOUND_MAX - VOICE_00)

enum
{	// サウンド通しナンバー(sound.cppの順番と合わせる事)
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
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

enum
{	// 再生用フラグ
	VOLUME_FADE_OUT,
	VOLUME_FADE_IN,
	VOLUME_FADE_HALF
};

enum
{	// 連続再生フラグ
	CONTINUITY_OFF,
	CONTINUITY_ON
};

enum
{	// BGMフラグ
	SOUND_BGM_TITLE,
	SOUND_BGM_GAME,
	SOUND_BGM_RESULT
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT					InitSound( HWND hWnd );	// 初期化
void					UninitSound();			// 後片付け
void					UpdateSound(void);
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// サウンドのロード
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// 音ごとに再生
void					PlayContinuitySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// 再生中かどうか
HRESULT					SetVol(LPDIRECTSOUNDBUFFER8 pBuffer, long nVol);
void					SetSoundBgm(int nBgm);
void					SetSoundBgmBoss(bool bBgm);
void					SetSe(int nVoice, int nFlag, bool bContinuity);
void					SetVoice(int nVoice, int nFlag, bool bContinuity);
#endif