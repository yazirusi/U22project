#pragma once
#include "DxLib.h"

//�v���C���[�̍\����
struct PLAYER
{
	//player�֐��Ŏg���ϐ�
	int p_x, p_y, sp_y;  //�}�b�v�`�b�v��̃v���C���[�̍��W
	int px, py, spy;	//�v���C���[�`��̍��W
	int pcnt;	//�C���X�g�̃J�E���g
	int jlong;    //�����������ŃW�����v�͂�ς���
	int jlength;    //���SHIFT�𗣂��Ă�����͂��󂯕t����
	int jflag;	//�W�����v�t���O
	int hozonY;    //�W�����v�����u�Ԃ̍��W
	int tempY;	//�W�����v���Ɏg������ւ������̕ϐ�
	int dflag;	//���~�t���O

	//playerattack�p�ϐ�(�ő�T�����`��)
	int af[5];	//�U���t���O	0:�Ȃ� 1:�U��
	int ax;
	int pa[5];
	int ay[5];
	int apx[5];
}; extern PLAYER player;

//�֐��̐錾
void PlayerMove();	//�v���C���[�ړ�
int CheckHitBlock();	//�u���b�N�Ƃ̓����蔻��