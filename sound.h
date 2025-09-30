//================================================
//
// サウンド処理 [sound.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*************************************************
// インクルードファイル
//*************************************************
#include"main.h"

//*************************************************
// サウンドクラスの定義
//*************************************************
class CSound
{
public:

	// サウンドの種類
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// 
		SOUND_LABEL_TUTORIALBGM,	// 
		SOUND_LABEL_GAMEBGM,	// 
		SOUND_LABEL_BGM,	// 
		SOUND_LABEL_SELECT,	// 
		SOUND_LABEL_ENTER,	// 
		SOUND_LABEL_SHOT,	// 
		SOUND_LABEL_DAMAGE,	// 
		SOUND_LABEL_WALK,	// 
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	HRESULT Play(SOUND_LABEL label,const float fVolume);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2* m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// サウンド情報構造体の定義
	struct SOUND_INFO
	{
		const char* pFilename;  // ファイル名
		int nCntLoop;			// ループカウント
	};

	// サウンドの情報
	SOUND_INFO m_aSoundInfo[SOUND_LABEL_MAX] = 
	{
		{"data/BGM/title_bgm.wav", -1},  // BGM
		{"data/BGM/tutorial_bgm.wav", -1},  // BGM
		{"data/BGM/game_bgm.wav", -1},  // BGM
		{"data/BGM/ranking_bgm.wav", -1},  // BGM
		{"data/SE/cursor_se.wav", 0},  // BGM
		{"data/SE/select_se.wav", 0},  // BGM
		{"data/SE/shot_se.wav", 0},  // BGM
		{"data/SE/damage_se.wav", 0},  // BGM
		{"data/SE/walk_se.wav", 0},  // BGM
	};				
};
#endif