#pragma once
#include "DxLib.h"

//notes�֐��̕ϐ�
extern int nx[100]; //�m�[�c�̍��W
extern int nf[100];//�m�[�c���Ƃ̃t���O
extern int nbf[100];//�m�[�c���Ƃ̏o���t���O
extern int mcnt[100];//���g���m�[��
extern int mcntf[100];//���g���m�[���p�t���O
extern int bcnt;	//�u�����h�̃J�E���g
extern int hf;	//�p�[�t�F�N�g����
extern int conbo;

//notesjudge�֐��̕ϐ�
extern int dc;	//�\�����鎞�Ԃ̃J�E���g

void notes();	//�m�[�c�`��֐�
void notesjudge();	//�m�[�c����`��
int nxmin(int max);
