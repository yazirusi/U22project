#pragma once
#include "DxLib.h"

//notes�֐��̕ϐ�
extern int nx[10]; //�m�[�c�̍��W
extern int nf[10];//�m�[�c���Ƃ̃t���O
extern int bcnt;	//�u�����h�̃J�E���g
extern int hf;	//�p�[�t�F�N�g����

/*//BPM�̍\����
extern struct BPM {
};
struct BPM bpm;
*/
//notesjudge�֐��̕ϐ�
extern int dc;	//�\�����鎞�Ԃ̃J�E���g

void notes();	//�m�[�c�`��֐�
void notesjudge();	//�m�[�c����`��