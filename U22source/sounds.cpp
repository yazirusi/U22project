#include"Dxlib.h"
#include"sounds.h"

int rockBGM;
int bpm;
int prse;
int grse;
int jpse;
int attackse;	//�U�����o�����u�Ԃ�SE
int attackse2;	//�H������Ƃ���SE
int dese;	//�V�[�P���XSE
int deathse;	//���ʂƂ���SE
int doorse;	//�h�ASE
int Titlebgm;
int clearbgm;
int GObgm;

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

	if ((attackse = LoadSoundMem("sounds/se_maoudamashii_explosion06.mp3")) == -1)return -1;
	if ((attackse2 = LoadSoundMem("sounds/se_maoudamashii_battle18.mp3")) == -1)return -1;
	if ((dese = LoadSoundMem("sounds/decision9.mp3")) == -1)return -1;
	if ((deathse = LoadSoundMem("sounds/down1.mp3")) == -1)return -1;
	if ((doorse = LoadSoundMem("sounds/door-open1.mp3")) == -1)return -1;

	if ((Titlebgm = LoadSoundMem("sounds/game_maoudamashii_7_rock52.mp3")) == -1)return -1;
	if ((clearbgm = LoadSoundMem("sounds/n12.mp3")) == -1)return -1;
	if ((GObgm = LoadSoundMem("sounds/tomoshibi.mp3")) == -1)return -1;

	//BGM�̒���
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