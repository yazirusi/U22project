#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"
#include "sounds.h"
#include "main.h"
#include "map.h"

//notes�֐��̕ϐ�
int nx[100]; //�m�[�c�̍��W
int nf[100];//�m�[�c���Ƃ̃t���O
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
	int widthn = 80;//(WIDTH - 400)/(maxn*2); //�m�[�c�ƃm�[�c�̊Ԋu(WIDTH/maxn)
	int maxn = ((680 / 2) / widthn) + 1;	//�\������m�[�c���̐�

	static int bgmflg;		//bgm�𗬂��t���O
	static int notesInitflg;	//�������̃t���O
	static int nxf;		//���[�v�̃t���O
	static int min;		//�m�[�c�̍��W�̍ŏ��l
	static int conbo;	//�R���{��

	//���̘g
	DrawLine(0, 760, 300, 760, 0xFFFFFF, 4);
	DrawLine(300, 758, 300, 850, 0xFFFFFF, 4);
	DrawLine(980, 760, 1280, 760, 0xFFFFFF, 4);
	DrawLine(980, 758, 980, 850, 0xFFFFFF, 4);

	//�R���{���̕\��
	if (conbo != 0) {
		SetFontSize(32);
		DrawFormatString(800, 750, 0xffffff, "%d�R���{", conbo);
		SetFontSize(16);
	}

	//�m�[�c�ʒu�̏�����
	if (notesInitflg == 0) {
		for (int i = 0; i < 100; i++) {
			nx[i] = 300;
		}
		notesInitflg = 1;
	}
	//nx[0] += 2;

	//�m�[�c�̕\��
	for (int i = 0; i < maxn; i++) {

		//�m�[�c�̈�T��
		if (i != 0 && nx[0] - 300 >= i * widthn && nxf == 0) {
			nx[i] += 2;
		}
		else if (i == 0 && nxf == 0) {
			nx[i] += 2;
		}
		min = nxmin(maxn);	//�ŏ��l��T��

		//�m�[�c�̂Q�T�ڈȍ~
		if (nxf == 1 && nx[i] == 300 && min - nx[i] >= widthn) {
			nx[i] += 2;
		}
		else if (nxf == 1 && nx[i] != 300) {
			nx[i] += 2;
		}

		//�^�񒆂ɗ�����
		if (nx[i] != 640) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i] - 300);	//�����x

			//�m�[�c�̕\��
			if (nf[i] == 0 && nx[i] != 300) {
				DrawLine(nx[i], 760, nx[i], 850, 0x99FFFF, 8);
				DrawLine(1280 - nx[i], 760, 1280 - nx[i], 850, 0x99FFFF, 8);
			}

			//Z�L�[����������
			if (g_NowKey & PAD_INPUT_6 && nx[i] >= 580 && nf[i] == 0) {
				bcnt = 0;
				nf[maxn] = 0;
				hf = 0;
				dc = 0;
				//�p�[�t�F�N�g����
				if (nx[i] >= 625) {

					//�U���t���O(�ő�T�����`��)
					for (int ai = 0; ai < 5; ai++) {
						if (player.af[ai] == 0) {
							player.af[ai] = 1;
							player.ay[ai] = player.py;
							player.apx[ai] = player.px;
							player.adireF[ai] = player.direF;
							player.ajudge[ai] = 0;
							break;
						}
					}

					hf = 1;
					conbo++;
				}

				//�O���[�g
				if (nx[i] >= 605 && nx[i] < 625) {
					//�U���t���O(�ő�T�����`��)
					for (int ai = 0; ai < 5; ai++) {
						if (player.af[ai] == 0) {
							player.af[ai] = 1;
							player.ay[ai] = player.py;
							player.apx[ai] = player.px;
							player.adireF[ai] = player.direF;
							player.ajudge[ai] = 1;
							break;
						}
					}

					hf = 2;
					conbo++;
				}

				//�~�X
				if (nx[i] < 605) {
					conbo = 0;
				}

				nf[i] = 1;	//�t���O
				nf[maxn] = 1;	//����p�̃t���O
				nx[maxn] = nx[i];	//����p�̕ϐ�

				//�f�o�b�O�p
				//�U���t���O(�ő�T�����`��)
				/*for (int ai = 0; ai < 5; ai++) {
					if (player.af[ai] == 0) {
						player.af[ai] = 1;
						player.ay[ai] = player.py;
						player.apx[ai] = player.px;
						player.adireF[ai] = player.direF;
						break;
					}
				}*/
			}
		}
		else {
			if (nf[i] == 0) {
				conbo = 0;
			}
			//�ŏ��̃m�[�c�������Ƃ��ɋȂ𗬂�
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_LOOP, FALSE);
				bgmflg = 1;
				nxf = 1;
			}
			PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			nf[maxn + 1] = 1;	//���[�v�t���O
			nx[i] = 300;	//�����ʒu�ɖ߂�
			nf[i] = 0;
		}
		//�������m�[�c�̏�����
		if (nf[i] == 1 || nf[maxn] == 1 && bcnt != 255) {
			bcnt++;	//�����x�p�J�E���g
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (bcnt));
			DrawLine(nx[maxn], 760, nx[maxn], 850, 0x00FF00, 8);
			DrawLine(1280 - nx[maxn], 760, 1280 - nx[maxn], 850, 0x00FF00, 8);
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

	//�p�[�t�F�N�g
	if (hf == 1 && (dc++) < 40) {
		DrawGraph(540, 730, P[(dc) / 4 % 4], TRUE);
	}
	//�O���[�g
	if (hf == 2 && hf != 0 && (dc++) < 40) {
		DrawGraph(540, 730, G[(dc) / 4 % 2], TRUE);
	}
	if (dc >= 40) {
		dc = 0;
		hf = 0;
	}
}
/********************
*�m�[�c�̍��W�̍ŏ��l
********************/
int nxmin(int max) {
	int min = 600;
	for (int i = 0; i < max; ++i) {
		if (min > nx[i] && nx[i] != 300) {
			min = nx[i];
		}
	}

	return min;
}