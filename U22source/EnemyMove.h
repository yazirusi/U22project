#pragma once
#include"DxLib.h"
#define Attack_MAX 10
#define Air_MAX 4
#define Air_Speed 2
#include "EnemyAttck.h"

const int MAXEnemy = 20;

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
	bool drawf = true;	//FALSE��\���@TRUE�\��
	//int move = 0;	//�G�̃m�[�c��񕪂̈ړ���
	int AttackY[Attack_MAX], AttackX[Attack_MAX];//�U���̍��W
	int AttackInterval = 0;	//�G�̍U���Ԋu�ϐ�
	const int MAXAttackInterval[3] = { 90,150,150 };	//�U���Ԋu
	int MaxHP[3] = { 100,30 ,300};		//�G�̍ő�HP
	int HP = 0;			//�G��HP
	bool HPdrawf = false;	//�G��HP�\���t���O
	int type = 0;	//�G�̎��
	int Imgcnt = 0;	//�G�̃C���X�g�J�E���g
	int Jump = 20;
	bool JumpFlg = false;
	int JumpCount = 0;
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
	int Downx, Downy;
	int Upx, Upy;
	int ReloadCount = 0;
	int FlgCount = 0;
	bool DispFlg[Air_MAX];
	void AirInit();
	int AirMove(int X, int Y);
};

extern Airman airman[MAXEnemy];
extern AIR Air[MAXEnemy];

void EnemyMove();
int Hitcheck(int hx, int hy, int direction, bool pf/*, int Move*/);
void EnemyInit();