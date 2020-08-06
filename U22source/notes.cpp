#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"
#include "sounds.h"
#include "main.h"
#include "map.h"
#include "EnemyMove.h"

//notes�\����
NOTES note;

//BPM
const double rockbgm = 182.03;
const double fps = 1.0 / 60.0;	//�P�t���[��������̕b��

//1���߂�����܂ł̎���(ms)
const double nps = (60.0 / rockbgm) * 2;

/********************
*�m�[�c
********************/
void notes() {
	//1�t���[����ms�ɕϊ�
	note.f += fps;

	//1���߂������ms�ƌ��݂̃t���[��(ms)���r
	if (nps < note.f) {
		note.nxbf = 1;
		note.f = note.f - nps;
		note.beatcnt++;
	}

	if (note.beatcnt == 68) {
		note.beatcnt = 0;
		note.f = 0;
	}

	if (CheckSoundMem(rockBGM) == 0 && note.bgmflg == 1) {
		note.bgmflg = 0;
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
	DrawFormatString(30, 520, 0xFFFFFF, "%d", mcnt[0]);
	DrawFormatString(30, 550, 0xFFFFFF, "%d", mcnt[1]);
	DrawFormatString(30, 580, 0xFFFFFF, "%d", mcnt[2]);
	DrawFormatString(30, 580, 0xFFFFFF, "%d", player.protect);*/

	//�R���{���̕\��
	if (note.conbo != 0) {
		SetFontSize(32);
		DrawFormatString(800, 750, 0xffffff, "%d�R���{", note.conbo);
		SetFontSize(16);
	}

	//�m�[�c�̕\��
	for (int i = 0; i < note.maxn; i++) {

		if (note.nbf[i] == 0 && note.nxbf == 1) {//�r�[�g�t���O���P�̎�
			note.nbf[i] = 1;
			note.mcntf[i] = 1;
			/*if(note.encnt % 3 == 0){
				note.nbf[i] = 2;
			}*/
			note.encnt++;
			note.nxbf = 0;//�P�t���O�����Ă���ʂ�Ȃ�
		}

		if (note.nbf[i] != 0) {
			note.nx[i] += 2;
		}

		
		if (note.mcntf[i] == 1) {
			note.mcnt[i] += 2;
		}

		//BGM�𗬂�
		if (note.mcnt[i] == 640) {
			if (note.bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
				note.bgmflg = 1;
				note.mcnt[i] = 300;
				note.mcntf[i] = 0;
			}
			note.mcnt[i] = 300;
			note.mcntf[i] = 0;
		}

		//�^�񒆂ɗ���܂�
		if (note.nx[i] != 660) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, note.nx[i] - 300);	//�����x

			if (note.nx[i] == 640) {
				PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			}

			//�m�[�c�̕\��
			if (note.nbf[i] == 1) {
				DrawLine(note.nx[i], 760, note.nx[i], 850, 0x99FFFF, 8);
				DrawLine(1280 - note.nx[i], 760, 1280 - note.nx[i], 850, 0x99FFFF, 8);
			}

			//����
			if (g_NowKey & PAD_INPUT_5 && note.nx[i] >= 620) {
				Enemy.MoveFlg = false;
				//�p�[�t�F�N�g����(+4F)
				if (abs(note.nx[i] - 640) <= 2 * note.spd) {
					PlaySoundMem(prse, DX_PLAYTYPE_BACK, TRUE);
					note.hf = 1;
					note.conbo++;
					player.col += 10;
				}

				//�O���[�g(10F)
				if (abs(note.nx[i] - 640) <= 5 * note.spd && abs(note.nx[i] - 640) > 2 * note.spd) {
					PlaySoundMem(grse, DX_PLAYTYPE_BACK, TRUE);
					note.hf = 2;
					note.conbo++;
					player.col += 4;
				}

				//�~�X
				if (abs(note.nx[i] - 640) > 5 * note.spd) {
					note.conbo = 0;
					if (player.col > 1) {
						player.col -= 4;
					}
				}

				/*//�G�̍s���m�[�c��������
				if (note.nbf[i] == 2) {
					if (Enemy.Attck == false) {
						Enemy.MoveFlg = true;
					}
					else {
						Enemy.AttckFlg = true;
					}
				}*/
				judgeinit(i);//�m�[�c�̏�����
			}
			
		}
		else {	//���肵�Ȃ�������
			note.conbo = 0;
			player.right = false;
			player.left = false;
			Enemy.MoveFlg = false;
			/*//�G�̍s���m�[�c��������
			if (note.nbf[i] == 2) {
				if (Enemy.Attck == false) {
					Enemy.MoveFlg = true;
				}
				else {
					Enemy.AttckFlg = true;
				}
			}*/
			if (player.col > 1) {
				player.col -= 4;
			}
			//player.protect = false;//�h��I��
			note.nx[i] = 300;	//�����ʒu�ɖ߂�
			note.nf[i] = 0;
			note.nbf[i] = 0;
			note.nxf = 1;
		}
		//�������m�[�c�̏�����
		if (note.nf[note.maxn] == 1 && note.bcnt != 256) {
			if (i == 0) {
				note.bcnt += 4;	//�����x�p�J�E���g
			}
		}
		else {
			note.bcnt = 0;
			note.nf[note.maxn] = 0;
		}
	}
	if (note.nf[note.maxn] == 1 && note.bcnt != 256) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (note.bcnt));
		DrawLine(note.nx[note.maxn], 760, note.nx[note.maxn], 850, 0x00FF00, 8);
		DrawLine(1280 - note.nx[note.maxn], 760, 1280 - note.nx[note.maxn], 850, 0x00FF00, 8);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�����x�̏�����
}
/********************
*�m�[�c�̔���\��
********************/
void notesjudge() {

	//�p�[�t�F�N�g
	if (note.hf == 1 && (note.dc++) < 40) {
		DrawGraph(540, 730, P[(note.dc) / 4 % 4], TRUE);
	}
	//�O���[�g
	if (note.hf == 2 && note.hf != 0 && (note.dc++) < 40) {
		DrawGraph(540, 730, G[(note.dc) / 4 % 2], TRUE);
	}
	if (note.dc >= 40) {
		note.dc = 0;
		note.hf = 0;
	}
}
/**************************
*���肵�����̃m�[�c�̏�����
**************************/
int judgeinit(int i) {
	note.bcnt = 0;
	note.nf[note.maxn] = 0;
	note.dc = 0;
	note.nf[i] = 1;	//�t���O
	note.nf[note.maxn] = 1;	//����p�̃t���O
	note.nx[note.maxn] = note.nx[i];	//����p�̕ϐ�
	note.nbf[i] = 0;
	note.nx[i] = 300;
	note.nxf = 1;
	return 0;
}
/**************************
*�m�[�c�֐��̏�����
**************************/
int notesinit(int i) {
	note.nx[i] = 300;
	note.nf[i] = 0;
	note.nbf[i] = 0;
	note.mcnt[i] = 300;
	note.mcntf[i] = 0;
	note.bcnt = 0;
	note.hf = 0;
	note.conbo = 0;
	note.encnt = 0;
	note.nxf = 0;
	note.bgmflg = 0;
	note.notesInitflg = 0;
	note.min = 0;
	note.nxbf = 0;
	note.sbf = 0;
	note.beatcnt = 0;
	note.f = 0.0;
	note.dc = 0;
	return 0;
}
/********************
*�m�[�c�̍��W�̍ŏ��l
********************/
int nxmin(int max) {
	int min = 600;
	for (int i = 0; i < max; ++i) {
		if (min > note.nx[i] && note.nx[i] != 300) {
			min = note.nx[i];
		}
	}

	return min;
}