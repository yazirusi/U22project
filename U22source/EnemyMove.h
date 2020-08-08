#pragma once
#include"DxLib.h"
#define Attack_MAX 10
#define Air_MAX 5
#define Air_Speed 2
#include "EnemyAttck.h"

const int MAXEnemy = 30;

//�G�̍\����
struct ENEMY
{
	int x = 0, y = 0;//�G�̍��W
	int MapX = 0, MapY = 0;//�}�b�v�`�b�v��̍��W
	const int size = 40;//�G�̃T�C�Y
	int speed = 1;//�G�̓�������
	bool direction = false;//��:false �E:true
	int Move = 0;//�ړ���
	int MoveD = 0;//�}�b�v�`�b�v��ł̍��W
	//bool Attack[MAXAttack];//�U�����邽�߂̃t���O:0�Ȃ�͈͊O�F�P�Ȃ�͈͓�
	bool MoveFlg = false;//�G���������߂̃t���O:true�Ȃ瓮���Ffalse�Ȃ�~�܂�
	//int Moveflg = 0;*/
	int Perception = 7 * 40;//�G�̊��m�͈�
	//int ax[3] = { 0,0,0 };
	//int Attackimage[1] = { 0 };
	//int count = 0;
	int drawf = 1;	//0��\���@�P�\��
	//int move = 0;	//�G�̃m�[�c��񕪂̈ړ���
	int AttackY[Attack_MAX], AttackX[Attack_MAX];//�U���̍��W
	int AttackInterval = 0;	//�G�̍U���Ԋu
	int MaxHP = 100;		//�G�̍ő�HP
	int HP = 0;			//�G��HP
	bool HPdrawf = false;	//�G��HP�\���t���O
}; extern ENEMY Enemy[MAXEnemy];

//�G�A�[�}���̍\����
struct Airman :public ENEMY
{
	void Airmaninit();
	void AirmanMove();
	void AirmanAttack();
};

struct AIR
{
	bool DispFlg[Air_MAX];
	void AirInit();
};

extern Airman airman;
extern AIR Air;

void EnemyMove();
int Hitcheck(int hx, int hy, int direction, bool pf/*, int Move*/);