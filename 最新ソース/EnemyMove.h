#pragma once
#include"DxLib.h"

//�G�̍\����
struct ENEMY
{
	int x = 0, y = 0;//�G�̍��W
	int MapX = 0, MapY = 0;//�}�b�v�`�b�v��̍��W
	const int size = 40;//�G�̃T�C�Y
	int speed = 1;//�G�̓�������
	int direction = 0;//�G�̌����Ă������:1�Ȃ獶:-1�Ȃ�E
	int Move = 0;//�ړ���
	int MoveD = 0;//�}�b�v�`�b�v��ł̍��W
	bool Attck = false;//�U�����邽�߂̃t���O:0�Ȃ�͈͊O�F�P�Ȃ�͈͓�
	bool MoveFlg = false;//�G���������߂̃t���O:true�Ȃ瓮���Ffalse�Ȃ�~�܂�
	int Moveflg = 0;//
	int Perception = 9 * 40;//�G�̊��m�͈�
	//int ax[3] = { 0,0,0 };
	int Attackimage[1] = { 0 };
	//int count = 0;
	int drawf = 1;	//0��\���@�P�\��
	int move = 0;	//�G�̃m�[�c��񕪂̈ړ���
	bool AttckFlg = false;	//�G�̃m�[�c�̍U���t���O
};extern ENEMY Enemy;

void EnemyMove();
int Hitcheck(int hx, int hy, int direction ,bool pf/*, int Move*/);