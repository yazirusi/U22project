#include"Dxlib.h"
#include"sounds.h"

int rockBGM;

/***************************************
* サウンド読み込み
****************************************/
int LoadSounds() {

	//ゲームBGMデータの読み込み
	if ((rockBGM = LoadSoundMem("sounds/game_maoudamashii_7_rock50.mp3")) == -1)return -1;

	//BGMの調整
	ChangeVolumeSoundMem(80, rockBGM);

	return 0;
}