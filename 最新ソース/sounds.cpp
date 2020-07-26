#include"Dxlib.h"
#include"sounds.h"

int rockBGM;
int bpm;
int prse;
int grse;
int jpse;


/***************************************
* サウンド読み込み
****************************************/
int LoadSounds() {

	//ゲームBGMデータの読み込み
	if ((rockBGM = LoadSoundMem("sounds/game_maoudamashii_7_rock50.mp3")) == -1)return -1;

	// bpmの音
	if ((bpm = LoadSoundMem("sounds/VSQSE_0031_metronome_02.mp3")) == -1)return -1;

	// perfectの時の判定音
	if ((prse = LoadSoundMem("sounds/perfect.mp3")) == -1)return -1;

	// greatの時の判定音
	if ((grse = LoadSoundMem("sounds/great.mp3")) == -1)return -1;

	// ジャンプの時の音
	if ((jpse = LoadSoundMem("sounds/ジャンプ.mp3")) == -1)return -1;

	//BGMの調整
	ChangeVolumeSoundMem(80, rockBGM);

	ChangeVolumeSoundMem(80, bpm);

	ChangeVolumeSoundMem(100, prse);

	ChangeVolumeSoundMem(90, grse);

	ChangeVolumeSoundMem(100, jpse);

	return 0;
}