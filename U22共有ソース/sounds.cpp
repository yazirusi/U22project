#include"Dxlib.h"
#include"sounds.h"

int rockBGM;
int bpm;

/***************************************
* �T�E���h�ǂݍ���
****************************************/
int LoadSounds() {

	//�Q�[��BGM�f�[�^�̓ǂݍ���
	if ((rockBGM = LoadSoundMem("sounds/game_maoudamashii_7_rock50.mp3")) == -1)return -1;

	// bpm�̉�
	if ((bpm = LoadSoundMem("sounds/VSQSE_0031_metronome_02.mp3")) == -1)return -1;


	//BGM�̒���
	ChangeVolumeSoundMem(80, rockBGM);

	ChangeVolumeSoundMem(80, bpm);

	return 0;
}