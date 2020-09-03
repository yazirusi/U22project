#include"Dxlib.h"
#include"sounds.h"

int rockBGM;
int bpm;
int prse;
int grse;
int jpse;
int attackse;	//攻撃を出した瞬間のSE
int attackse2;	//食らったときのSE
int dese;	//シーケンスSE
int deathse;	//死ぬときのSE
int doorse;	//ドアSE
int Titlebgm;
int clearbgm;
int GObgm;

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

	if ((attackse = LoadSoundMem("sounds/se_maoudamashii_explosion06.mp3")) == -1)return -1;
	if ((attackse2 = LoadSoundMem("sounds/se_maoudamashii_battle18.mp3")) == -1)return -1;
	if ((dese = LoadSoundMem("sounds/decision9.mp3")) == -1)return -1;
	if ((deathse = LoadSoundMem("sounds/down1.mp3")) == -1)return -1;
	if ((doorse = LoadSoundMem("sounds/door-open1.mp3")) == -1)return -1;

	if ((Titlebgm = LoadSoundMem("sounds/game_maoudamashii_7_rock52.mp3")) == -1)return -1;
	if ((clearbgm = LoadSoundMem("sounds/n12.mp3")) == -1)return -1;
	if ((GObgm = LoadSoundMem("sounds/tomoshibi.mp3")) == -1)return -1;

	//BGMの調整
	ChangeVolumeSoundMem(80, rockBGM);
	ChangeVolumeSoundMem(80, bpm);
	ChangeVolumeSoundMem(100, prse);
	ChangeVolumeSoundMem(90, grse);
	ChangeVolumeSoundMem(100, jpse);
	ChangeVolumeSoundMem(80, attackse);
	ChangeVolumeSoundMem(80, attackse2);
	ChangeVolumeSoundMem(100, dese);
	ChangeVolumeSoundMem(150, deathse);
	ChangeVolumeSoundMem(100, doorse);
	ChangeVolumeSoundMem(100, Titlebgm);
	ChangeVolumeSoundMem(100, clearbgm);
	ChangeVolumeSoundMem(100, GObgm);

	return 0;
}