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
int nf[100];//�m�[�c���Ƃ̉������Ƃ��̃t���O
int nbf[100];//�m�[�c���Ƃ̏o���t���O
int mcnt[100];//���g���m�[��
int mcntf[100];//���g���m�[���p�t���O
int bcnt;	//�u�����h�̃J�E���g
int hf = 0;	//�p�[�t�F�N�g����
int conbo;	//�R���{��

//BPM
const double rockbgm = 182.03;
const double fps = 1.0 / 60.0;	//�P�t���[��������̕b��

//8������������܂ł̎���(ms)
double nps = (60.0 / rockbgm) * 2;

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
	static int nxbf;
	static int sbf;
	static int beatcnt;	//77����

	static double f = 0.0;

	//�m�[�c�̏�����
	if (notesInitflg == 0) {
		for (int i = 0; i < 100; i++) {
			nx[i] = 300;
			mcnt[i] = 300;
		}
		notesInitflg = 1;
	}

	//1�t���[����ms�ɕϊ�
	f += fps;

	//1���߂������ms�ƌ��݂̃t���[��(ms)���r
	if (nps < f) {
		nxbf = 1;
		f = f - nps;
		beatcnt++;
	}

	if (beatcnt == 68) {
		beatcnt = 0;
		f = 0;
	}

	if (CheckSoundMem(rockBGM) == 0 && bgmflg == 1) {
		bgmflg = 0;
	}

	//DrawFormatString(30, 430, 0xFFFFFF, "%d", CheckSoundMem(rockBGM));

	//���̘g
	DrawLine(0, 760, 300, 760, 0xFFFFFF, 4);
	DrawLine(300, 758, 300, 850, 0xFFFFFF, 4);
	DrawLine(980, 760, 1280, 760, 0xFFFFFF, 4);
	DrawLine(980, 758, 980, 850, 0xFFFFFF, 4);

	/*DrawFormatString(30, 400, 0xFFFFFF, "%lf", fps);
	DrawFormatString(30, 460, 0xFFFFFF, "%d", beatcnt);
	DrawFormatString(30, 490, 0xFFFFFF, "%d", nx[0]);
	DrawFormatString(30, 520, 0xFFFFFF, "%d", mcnt[0]);*/

	//�R���{���̕\��
	if (conbo != 0) {
		SetFontSize(32);
		DrawFormatString(800, 750, 0xffffff, "%d�R���{", conbo);
		SetFontSize(16);
	}

	//�m�[�c�̕\��
	for (int i = 0; i < maxn; i++) {

		if (nbf[i] == 0 && nxbf == 1) {//�r�[�g�t���O���P�̎�
			nbf[i] = 1;
			mcntf[i] = 1;
			nxbf = 0;//�P�t���O�����Ă���ʂ�Ȃ�
		}

		if (nbf[i] == 1) {	//�o���t���O���P�Ȃ�m�[�c������
			nx[i] += 2;
		}

		
		if (mcntf[i] == 1) {
			mcnt[i] += 2;
		}

		//�������Ȃ������Ƃ�
		if (mcnt[i] == 640) {
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
				bgmflg = 1;
				mcnt[i] = 300;
				mcntf[i] = 0;
			}
		}

		//�^�񒆂ɗ���܂�
		if (nx[i] != 640) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i] - 300);	//�����x

			//�m�[�c�̕\��
			DrawLine(nx[i], 760, nx[i], 850, 0x99FFFF, 8);
			DrawLine(1280 - nx[i], 760, 1280 - nx[i], 850, 0x99FFFF, 8);

			//Z�L�[����������
			if (g_NowKey & PAD_INPUT_6 && nx[i] >= 600) {
				bcnt = 0;
				nf[maxn] = 0;
				hf = 0;
				dc = 0;
				//�p�[�t�F�N�g����(+4F)
				if (nx[i] >= 632) {
					PlaySoundMem(prse, DX_PLAYTYPE_BACK, TRUE);
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

				//�O���[�g(10F)
				if (nx[i] >= 620 && nx[i] < 632) {
					PlaySoundMem(grse, DX_PLAYTYPE_BACK, TRUE);
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
				if (nx[i] < 620) {
					conbo = 0;
				}

				nf[i] = 1;	//�t���O
				nf[maxn] = 1;	//����p�̃t���O
				nx[maxn] = nx[i];	//����p�̕ϐ�
				nbf[i] = 0;
				nx[i] = 300;

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
				nxf = 1;
			}
		}
		else {	//�^�񒆗�����
			if (nf[i] == 0) {
				conbo = 0;
			}
			//BGM
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
				bgmflg = 1;
			}
			PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			nx[i] = 300;	//�����ʒu�ɖ߂�
			nf[i] = 0;
			nbf[i] = 0;
			nxf = 1;
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