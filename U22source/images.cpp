#include"DxLib.h"
#include"images.h"
#include"EnemyMove.h"

//�ϐ��̒�`
int p[12];	//�v���C���[�̃C���X�g
int pa[4];//�v���C���[�̍U���C���X�g
int P[4]; //Pefect����i�C���X�g�j
int G[2]; //Great����
int pj[6];//�v���C���[�̃W�����v�C���X�g
int pd[8];//�v���C���[�̎��S�C���X�g
int hpg;  //HP�Q�[�W�C���X�g
int ag;   //�U���̃Q�[�W�C���X�g
int ef[4];//�U���̃G�t�F�N�g

int EnemyAttackImg;

int EnemyImg[7];	//�G�C���X�g
int EnemyImg2[7];	//�G�C���X�g
int EnemyImg3[7];	//�G�C���X�g
int lasboss[4];
int baria;

int Backimg;  //�w�i�C���X�g
int Backimg2;  //�w�i�C���X�g
int Backimg3;  //�w�i�C���X�g
int Backimg4;  //�w�i�C���X�g
int Backimg5;	//���X�{�X

int roadimg;
int roadimg2;
int roadimg3;

int UI[2];

int Titleimg;
int GameOverimg;

/**********************************************
*  �摜�ǂݍ���
***********************************************/
int LoadImages()
{
	//����̃C���X�g
	if ((P[0] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;
	if ((P[1] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;
	if ((P[2] = LoadGraph("images/Perfect(�ԐF).png")) == -1) return -1;
	if ((P[3] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;
	if ((G[0] = LoadGraph("images/great(���F).png")) == -1) return -1;
	if ((G[1] = LoadGraph("images/great(���F).png")) == -1) return -1;

	//�v���C���[�̃C���X�g
	if ((p[0] = LoadGraph("images/idle-1.png")) == -1) return -1;
	if ((p[1] = LoadGraph("images/run-1.png")) == -1) return -1;
	if ((p[2] = LoadGraph("images/run-3.png")) == -1) return -1;
	if ((p[3] = LoadGraph("images/run-4.png")) == -1) return -1;
	if ((p[4] = LoadGraph("images/run-5.png")) == -1) return -1;
	if ((p[5] = LoadGraph("images/run-6.png")) == -1) return -1;
	if ((p[6] = LoadGraph("images/Iidle-1.png")) == -1) return -1;
	if ((p[7] = LoadGraph("images/Irun-1.png")) == -1) return -1;
	if ((p[8] = LoadGraph("images/Irun-3.png")) == -1) return -1;
	if ((p[9] = LoadGraph("images/Irun-4.png")) == -1) return -1;
	if ((p[10] = LoadGraph("images/Irun-5.png")) == -1) return -1;
	if ((p[11] = LoadGraph("images/Irun-6.png")) == -1) return -1;
	if ((pa[0] = LoadGraph("images/attack-1.png")) == -1) return -1;
	if ((pa[1] = LoadGraph("images/attack-2.png")) == -1) return -1;
	if ((pa[2] = LoadGraph("images/attack-1_m.png")) == -1) return -1;
	if ((pa[3] = LoadGraph("images/attack-2_m.png")) == -1) return -1;
	if ((pj[0] = LoadGraph("images/jump-1.png")) == -1) return -1;
	if ((pj[1] = LoadGraph("images/jump-2.png")) == -1) return -1;
	if ((pj[2] = LoadGraph("images/jump-3.png")) == -1) return -1;
	if ((pj[3] = LoadGraph("images/jump-1_m.png")) == -1) return -1;
	if ((pj[4] = LoadGraph("images/jump-2_m.png")) == -1) return -1;
	if ((pj[5] = LoadGraph("images/jump-3_m.png")) == -1) return -1;
	if ((pd[0] = LoadGraph("images/dead-1.png")) == -1) return -1;
	if ((pd[1] = LoadGraph("images/dead-2.png")) == -1) return -1;
	if ((pd[2] = LoadGraph("images/dead-3.png")) == -1) return -1;
	if ((pd[3] = LoadGraph("images/dead-4.png")) == -1) return -1;
	if ((pd[4] = LoadGraph("images/dead-1_m.png")) == -1) return -1;
	if ((pd[5] = LoadGraph("images/dead-2_m.png")) == -1) return -1;
	if ((pd[6] = LoadGraph("images/dead-3_m.png")) == -1) return -1;
	if ((pd[7] = LoadGraph("images/dead-4_m.png")) == -1) return -1;
	if ((hpg = LoadGraph("images/hg.png")) == -1)return -1;
	if ((ag = LoadGraph("images/ag.png")) == -1)return -1;
	if ((ef[0] = LoadGraph("images/effect1.png")) == -1)return -1;
	if ((ef[1] = LoadGraph("images/effect2.png")) == -1)return -1;
	if ((ef[2] = LoadGraph("images/effect3.png")) == -1)return -1;
	if ((ef[3] = LoadGraph("images/effect4.png")) == -1)return -1;

	//�G�̃C���X�g
	if ((EnemyAttackImg = LoadGraph("images/note.bmp")) == -1) return -1;
	if ((EnemyImg[0] = LoadGraph("images/e_idle-1.png")) == -1) return -1;
	if ((EnemyImg[1] = LoadGraph("images/e_walk-1.png")) == -1) return -1;
	if ((EnemyImg[2] = LoadGraph("images/e_walk-2.png")) == -1) return -1;
	if ((EnemyImg[3] = LoadGraph("images/e_walk-3.png")) == -1) return -1;
	if ((EnemyImg[4] = LoadGraph("images/e_walk-4.png")) == -1) return -1;
	if ((EnemyImg[5] = LoadGraph("images/e_walk-5.png")) == -1) return -1;
	if ((EnemyImg[6] = LoadGraph("images/e_walk-6.png")) == -1) return -1;
	if ((EnemyImg2[0] = LoadGraph("images/e2_idle-1.png")) == -1) return -1;
	if ((EnemyImg2[1] = LoadGraph("images/e2_walk-1.png")) == -1) return -1;
	if ((EnemyImg2[2] = LoadGraph("images/e2_walk-2.png")) == -1) return -1;
	if ((EnemyImg2[3] = LoadGraph("images/e2_walk-3.png")) == -1) return -1;
	if ((EnemyImg2[4] = LoadGraph("images/e2_walk-4.png")) == -1) return -1;
	if ((EnemyImg2[5] = LoadGraph("images/e2_walk-5.png")) == -1) return -1;
	if ((EnemyImg2[6] = LoadGraph("images/e2_walk-6.png")) == -1) return -1;
	if ((EnemyImg3[0] = LoadGraph("images/e3_idle-1.png")) == -1) return -1;
	if ((lasboss[0] = LoadGraph("images/g_enemy1.png")) == -1) return -1;
	if ((lasboss[1] = LoadGraph("images/g_enemy2.png")) == -1) return -1;
	if ((lasboss[2] = LoadGraph("images/g_enemy3.png")) == -1) return -1;
	if ((lasboss[3] = LoadGraph("images/g_enemy4.png")) == -1) return -1;

	//�w�i
	if ((Backimg = LoadGraph("images/bac.bmp")) == -1)return -1;
	if ((Backimg2 = LoadGraph("images/bac2.bmp")) == -1)return -1;
	if ((Backimg3 = LoadGraph("images/bac3.bmp")) == -1)return -1;
	if ((Backimg4 = LoadGraph("images/bac_3_2.bmp")) == -1)return -1;
	if ((roadimg = LoadGraph("images/road01.bmp")) == -1)return -1;
	if ((roadimg2 = LoadGraph("images/road02.bmp")) == -1)return -1;
	if ((roadimg3 = LoadGraph("images/road03.bmp")) == -1)return -1;
	if ((Backimg5 = LoadGraph("images/lassboss_stage.png")) == -1)return -1;
	if ((baria = LoadGraph("images/baria.png")) == -1)return -1;


	//�^�C�g���Ƃ�
	if ((Titleimg = LoadGraph("images/Title03.png")) == -1)return -1;
	if ((GameOverimg = LoadGraph("images/gameover.png")) == -1)return -1;

	if ((UI[0] = LoadGraph("images/button01_1.bmp")) == -1)return -1;
	if ((UI[1] = LoadGraph("images/button01_2.bmp")) == -1)return -1;

	return 0;
}