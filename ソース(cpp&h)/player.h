#pragma once
#include "DxLib.h"

//�ϐ��̐錾
extern int p_x, p_y, sp_y;  //�v���C���[�̍��W
extern int px, py, spy;	//�v���C���[�`��̍��W
extern int pcnt;	//�C���X�g�̃J�E���g
/*int g_KeyFlg;  //���̓L�[���
int	g_OldKey;  // �O��̓��̓L�[
int	g_NowKey;	// ����̓��̓L�[*/

//�W�����v�ϐ�
extern int jlong;    //�����������ŃW�����v�͂�ς���
extern int jlength;    //���SHIFT�𗣂��Ă�����͂��󂯕t����
extern int jflag;	//�W�����v�t���O
extern int hozonY;    //�W�����v�����u�Ԃ̍��W
extern int jy;        //�W�����v�����u�Ԃ̍��W
extern int tempY;
extern int dflag;	//���~�t���O

//�֐��̐錾
void PlayerMove();	//�v���C���[�ړ�
int CheckHitBlock();	//�u���b�N�Ƃ̓����蔻��