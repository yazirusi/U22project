#include"Dxlib.h"
#include"sounds.h"

int rockBGM;

/***************************************
* �T�E���h�ǂݍ���
****************************************/
int LoadSounds() {

	//�Q�[��BGM�f�[�^�̓ǂݍ���
	if ((rockBGM = LoadSoundMem("sounds/game_maoudamashii_7_rock50.mp3")) == -1)return -1;

	//BGM�̒���
	ChangeVolumeSoundMem(80, rockBGM);

	return 0;
}