#pragma once
#include "DxLib.h"

//�v���C���[�̍\����
struct PLAYER
{
	//player�֐��Ŏg���ϐ�
	int p_x = 0, p_y = 0, sp_y = 0;  //�}�b�v�`�b�v��̃v���C���[�̍��W
	int px = 0, py = 0, spy = 0;	//�v���C���[�`��̍��W
	int pcnt = 0;	//�C���X�g�̃J�E���g
	int jlong = 0;    //�����������ŃW�����v�͂�ς���
	int jlength = 0;    //���SHIFT�𗣂��Ă�����͂��󂯕t����
	int jflag = 0;	//�W�����v�t���O
	int hozonY = 0;    //�W�����v�����u�Ԃ̍��W
	int tempY = 0;	//�W�����v���Ɏg������ւ������̕ϐ�
	int dflag = 0;	//���~�t���O
	int direF = 0;	//�����t���O 0:�E�����@1:������

	//�v���C���[�̃X�e�[�^�X
	int hp = 100;	//HP

	//playerattack�p�ϐ�(�ő�T�����`��)
	int af[5] = { 0,0,0,0,0 };	//�U���t���O	0:�Ȃ� 1:�U��
	int ax = 0;
	int pa[5] = { 0,0,0,0,0 };
	int ay[5] = { 0,0,0,0,0 };
	int apx[5] = { 0,0,0,0,0 };
	int adireF[5] = { 0,0,0,0,0 };	//0�F�E�����@1�F������
	int ajudge[5] = { 0,0,0,0,0 };	//0�F�p�[�t�F�N�g	1:�O���[�g
	int acolor[5] = { 0xFF0000,0xFFFF00 };	//�Y�����@0:��(perfect)�@1:���F(great)

}; extern PLAYER player;

//�֐��̐錾
void PlayerMove();	//�v���C���[�ړ�
int CheckHitBlock(int j,int a);	//�u���b�N�Ƃ̓����蔻��