#include"Dxlib.h"
#include"sounds.h"

int rockBGM;
int bpm;
int prse;
int grse;
int jpse;


/***************************************
* �T�E���h�ǂݍ���
****************************************/
int LoadSounds() {

	//�Q�[��BGM�f�[�^�̓ǂݍ���
	if ((rockBGM = LoadSoundMem("sounds/game_maoudamashii_7_rock50.mp3")) == -1)return -1;

	// bpm�̉�
	if ((bpm = LoadSoundMem("sounds/VSQSE_0031_metronome_02.mp3")) == -1)return -1;

	// perfect�̎��̔��艹
	if ((prse = LoadSoundMem("sounds/perfect.mp3")) == -1)return -1;

	// great�̎��̔��艹
	if ((grse = LoadSoundMem("sounds/great.mp3")) == -1)return -1;

	// �W�����v�̎��̉�
	if ((jpse = LoadSoundMem("sounds/�W�����v.mp3")) == -1)return -1;

	//BGM�̒���
	ChangeVolumeSoundMem(80, rockBGM);

	ChangeVolumeSoundMem(80, bpm);

	ChangeVolumeSoundMem(100, prse);

	ChangeVolumeSoundMem(90, grse);

	ChangeVolumeSoundMem(100, jpse);

	return 0;
}