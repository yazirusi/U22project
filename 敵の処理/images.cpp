#include"DxLib.h"
#include"images.h"
#include"EnemyMove.h"

//�ϐ��̒�`
int p[6];	//�v���C���[�̃C���X�g
int P[4]; //Pefect����i�C���X�g�j
int G[2]; //Great����

/**********************************************
*  �摜�ǂݍ���
***********************************************/
int LoadImages()
{
	if ((P[0] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;

	if ((P[1] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;

	if ((P[2] = LoadGraph("images/Perfect(�ԐF).png")) == -1) return -1;

	if ((P[3] = LoadGraph("images/Perfect(���F).png")) == -1) return -1;

	if ((G[0] = LoadGraph("images/great(���F).png")) == -1) return -1;

	if ((G[1] = LoadGraph("images/great(���F).png")) == -1) return -1;

	if ((p[0] = LoadGraph("images/idle-1.png")) == -1) return -1;

	if ((p[1] = LoadGraph("images/run-1.png")) == -1) return -1;

	if ((p[2] = LoadGraph("images/run-3.png")) == -1) return -1;

	if ((p[3] = LoadGraph("images/run-4.png")) == -1) return -1;

	if ((p[4] = LoadGraph("images/run-5.png")) == -1) return -1;

	if ((p[5] = LoadGraph("images/run-6.png")) == -1) return -1;

	if ((Enemy.Attackimage[0] = LoadGraph("images/����.png")) == -1) return -1;

	return 0;
}