#pragma once
#include "DxLib.h"

//notes�֐��̕ϐ�
//notes�̍\����
struct NOTES
{
	int nx[100]; //�m�[�c�̍��W
	int nf[100];//�m�[�c���Ƃ̉������Ƃ��̃t���O
	int nbf[100];//�m�[�c���Ƃ̏o���t���O 0:�\�����Ȃ� 1:�v���C���[�̍s���m�[�c 2:�G�ƃv���C���[�̍s���m�[�c
	int mcnt[100];//���g���m�[��
	int mcntf[100];//���g���m�[���p�t���O
	int bcnt = 0;	//�u�����h�̃J�E���g
	int hf = 0;	//�p�[�t�F�N�g����
	int conbo = 0;	//�R���{��
	int encnt = 0;
	const int maxn = 20;	//�\������m�[�c���̐�
	int nxf = 0;		//���[�v�̃t���O
	int bgmflg = 0;		//bgm�𗬂��t���O
	int notesInitflg = 0;	//�������̃t���O
	int min = 0;		//�m�[�c�̍��W�̍ŏ��l
	int nxbf = 0;
	int sbf = 0;
	int beatcnt = 0;	//77����
	double f = 0.0;
	int dc = 0;	//�\�����鎞�Ԃ̃J�E���g
}; extern NOTES note;
/*extern int nx[100]; //�m�[�c�̍��W
extern int nf[100];//�m�[�c���Ƃ̃t���O
extern int nbf[100];//�m�[�c���Ƃ̏o���t���O
extern int mcnt[100];//���g���m�[��
extern int mcntf[100];//���g���m�[���p�t���O
extern int bcnt;	//�u�����h�̃J�E���g
extern int hf;	//�p�[�t�F�N�g����
extern int conbo;*/

void notes();	//�m�[�c�`��֐�
void notesjudge();	//�m�[�c����`��
int nxmin(int max);	//�\������Ă���m�[�c�̒��̍ŏ��l�𒲂ׂ�
int judgeinit(int i);	//���肵����m�[�c������������֐�
int notesinit(int i);	//�m�[�c�֐��Ŏg���ϐ��̏�����