#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"

//notes�֐��̕ϐ�
int nx[10]; //�m�[�c�̍��W
int nf[10];//�m�[�c���Ƃ̃t���O
int bcnt;	//�u�����h�̃J�E���g
int hf = 0;	//�p�[�t�F�N�g����

/*//BPM�̍\����
extern struct BPM {
};
struct BPM bpm;
*/
//notesjudge�֐��̕ϐ�
int dc;	//�\�����鎞�Ԃ̃J�E���g

/********************
*�m�[�c
********************/
void notes() {

	//���̘g
	DrawLine(0, 800, 200, 800, 0xFFFFFF, 4);
	DrawLine(200, 798, 200, 850, 0xFFFFFF, 4);
	DrawLine(1080, 800, 1280, 800, 0xFFFFFF, 4);
	DrawLine(1080, 798, 1080, 850, 0xFFFFFF, 4);

	int maxn = 8;	//�\������m�[�c���̐�
	int widthn = 55; //�m�[�c�ƃm�[�c�̊Ԋu(WIDTH/maxn)

	for (int i = 0; i < maxn; i++) {
		if (nf[maxn + 1] == 1 || (nx[0] - 200) >= i * widthn)	//�ŏ��������炷�A�ニ�[�v
			nx[i]++;

		if (nx[i] != 640) {	//�^�񒆂ɗ�����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i] - 200);	//�����x
			if (nf[i] == 0 && nx[i] != 200) {
				DrawLine(nx[i], 800, nx[i], 850, 0x99FFFF, 8);
				DrawLine(1280 - nx[i], 800, 1280 - nx[i], 850, 0x99FFFF, 8);
			}
			if (g_NowKey & PAD_INPUT_1 && nx[i] >= 610 && nf[maxn] == 0) {	//Z�L�[����������
				if (nx[i] >= 635)
					hf = 1; //�p�[�t�F�N�g����
				if (nx[i] >= 615 && nx[i] < 635)
					hf = 2;
				nf[i] = 1;	//�t���O
				nf[maxn] = 1;	//����p�̃t���O
				nx[maxn] = nx[i];	//����p�̕ϐ�
			}
		}
		else {
			nf[maxn + 1] = 1;	//���[�v�t���O
			nx[i] = 200;	//�����ʒu�ɖ߂�
			nf[i] = 0;
		}
		if (nf[i] == 1 || nf[maxn] == 1 && bcnt != 255) {
			bcnt++;	//�����x�p�J�E���g
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (bcnt));
			DrawLine(nx[maxn], 800, nx[maxn], 850, 0x00FF00, 8);
			DrawLine(1280 - nx[maxn], 800, 1280 - nx[maxn], 850, 0x00FF00, 8);
		}
		else {
			bcnt = 0;
			nf[maxn] = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�����x�̏�����
}
/********************
*�m�[�c�̔���\��
********************/
void notesjudge() {

	if (hf == 1 && (dc++) < 40) {
		DrawGraph(540, 730, P[(dc) / 4 % 4], TRUE);
	}
	if (hf == 2 && hf != 0 && (dc++) < 40) {
		DrawGraph(540, 730, G[(dc) / 4 % 2], TRUE);
	}
	if (dc >= 40) {
		dc = 0;
		hf = 0;
	}
}