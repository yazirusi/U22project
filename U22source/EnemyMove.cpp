#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"
#include"main.h"
#include"images.h"

//�G�A�[�}���̕ϐ�
Airman airman;
AIR Air;

/***************************************
*�G�l�~�[�̓���
***************************************/
void EnemyMove(void) {
	airman.AirmanMove();

	for (int i = 0; i < MAXEnemy; i++) {

		//�G�������Ƃ��J�E���g
		if (Enemy[i].MoveFlg == true) {
			Enemy[i].Imgcnt++;
		}
		else {
			Enemy[i].Imgcnt = 0;
		}

		//�G����ʊO���������\��
		if ((-sx) > Enemy[i].x + Enemy[i].size || (-sx) + WIDTH < Enemy[i].x) {
			Enemy[i].drawf = false;
		}
		else {
			Enemy[i].drawf = true;
		}

		//�G�����ʂ��A�\���t���O����\���Ȃ�
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//�������牺�̏��������Ȃ�
		}

		if (Enemy[i].type == 0) {//�����G
			DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
				(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);//�G�̔���`��

			//�C���X�g�̕`��
			if (Enemy[i].MoveFlg == true) {	//�����Ă�����
				if (Enemy[i].direction == true) {
					DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[Enemy[i].Imgcnt / 15 % 6 + 1], TRUE);
				}
				else {
					DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[Enemy[i].Imgcnt / 15 % 6 + 1], TRUE);
				}
			}
			else {
				if (Enemy[i].direction == true) {
					DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[0], TRUE);
				}
				else {
					DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[0], TRUE);
				}
			}
		}
		if (Enemy[i].type == 1) {//�Ԃ��G
			//�G�̔���`��
			DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
				(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);

			//�C���X�g�̔��f
			if (Enemy[i].direction == true) {
				DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg2[0], TRUE);
			}
			else {
				DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg2[0], TRUE);
			}
		}

		//�v���C���[�̕��ɐU�����
		if (Enemy[i].type == 1) {
			if (player.px < Enemy[i].x) {
				Enemy[i].direction = false;
			}
			if (player.px > Enemy[i].x + 40) {
				Enemy[i].direction = true;
			}
		}

		//�ԐF�̓G�͓����Ȃ�
		if (Enemy[i].type != 1) {
			//�G�̍��W�ƃ}�b�v�`�b�v�̓����蔻��𒲂ׂ�
			if (Enemy[i].direction == false && Enemy[i].MoveFlg == true) {//���Ɉړ����Ă鎞�̏���
				if (Hitcheck(Enemy[i].x, Enemy[i].y, Enemy[i].direction, false) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
					Enemy[i].x -= (Enemy[i].speed);//�����Ȃ�ړ����Ă���
				}
				else
				{
					Enemy[i].direction = true;//�E�ɂ��邽�߂̃t���O
				}
			}

			if (Enemy[i].direction == TRUE && Enemy[i].MoveFlg == true) {//�E�Ɉړ����Ă鎞�̏���
				if (Hitcheck(Enemy[i].x + Enemy[i].size, Enemy[i].y, Enemy[i].direction, false) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
					Enemy[i].x += (Enemy[i].speed);//�����Ȃ�ړ����Ă���
				}
				else
				{
					Enemy[i].direction = false;//���ɂ��邽�߂̃t���O
				}
			}
		}
		if (Enemy[i].HPdrawf == true) {
			int barlen = (Enemy[i].size * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			//�G��HP�o�[
			DrawBox(Enemy[i].x + sx, Enemy[i].y - 70, Enemy[i].x + sx + barlen, Enemy[i].y - 60, 0xFF0000, TRUE);
		}
	}
}
/**************
*Airman�̏�����
**************/
void Airman::Airmaninit() {
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 4) {
				Airman::MapX = x;//�G�̃}�b�v��̂����W������
				Airman::MapY = y;//�G�̃}�b�v���y���W������
				Airman::x = (x * 40);//�G�̏���x���W
				Airman::y = (y * 40);//�G�̏���y���W
			}
		}
	}

	for (int i = 0; i < Air_MAX; i++) {
		Airman::AttackX[i] = 0;//�U�����W����������
		Airman::AttackY[i] = 0;//�U�����W����������
	}

	Airman::Perception = 12 * 40;//���m�͈͂�������
}
/***************
*Airman�̓���
****************/
void Airman::AirmanMove() {
	DrawBox((Airman::x - Airman::Move + sx), (Airman::y),
		(Airman::x + Airman::size - Airman::Move + sx), (Airman::y + Airman::size), 0xffffff, TRUE);//�G�̕`��

	//�G�A�[�}���̍����̊��m�͈�
	if (Airman::x - Airman::Perception < player.px + 40) {
		//�G�̍U�����`�悳��Ă邩����
		for (int i = 0; i < Air_MAX; i++)
		{
			if (Air.DispFlg[i] == true) {
				Air.FlgCount = 0;//�`�悳��Ă�Ȃ甲����
				break;
			}
			else
			{
				Air.FlgCount = 1;//�`�悳��ĂȂ��̂Ȃ�P������
			}
		}
		//�G�̍U�������ׂď����Ă����̂Ȃ�U���̏�������
		if (Air.FlgCount == 1)
		{
			Air.ReloadCount++;
			if (Air.ReloadCount == 120) {
				for (int i = 0; i < Air_MAX; i++)
				{
					Airman::AttackX[i] = Airman::x /*+ sx*/ - 40 - i * 120;//�G�̍U�����Wx�������
					Airman::AttackY[i] = Airman::y - (i % 2) * 120;//�G�̍U�����Wy������
					Air.DispFlg[i] = true;//���m�͈͂ɓ�������G�l�~�[�U���t���O��true�ɂ���
					Air.ReloadCount = 0;
				}
			}
		}
	}

	//�G�A�[�}���̉E���̊��m�͈�
	if (Airman::x + Airman::Perception < player.px) {

	}
}
/*************
*Air�̏�����
*************/
void AIR::AirInit() {
	for (int i = 0; i < Air_MAX; i++)
	{
		Air.DispFlg[i] = false;
	}
}
/**************************************
*�����蔻��
*hx:�G�L�����̂����W
*hy:�G�L�����̂����W
*Move�F��ʂ̃X�N���[����
*pf:�v���C���[�Ƃ̔���t���O
***************************************/
int Hitcheck(int hx, int hy, int direction, bool pf/*, int Move*/)
{
	if (pf == true) {
		if (hx > player.px && hx < player.px + 40
			&& hy > player.py - 40 && hy < player.py + 40) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int x = 0;//������
	int y = 0;//������

	y = hy / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�
	x = (hx /*+ Move*/) / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�

	return g_StageData[0][y][x];//�}�b�v�`�b�v��ł̍��W��Ԃ�

	return 0;
}
/**************************************
*�G�̏�����
***************************************/
void EnemyInit() {

	//�G�̏�����
	for (int i = 0; i < MAXEnemy; i++) {
		Enemy[i].x = 0;
		Enemy[i].drawf = false;
	}

	//�}�b�v�`�b�v�ɍ��킹�č��W��ݒ肷��
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//�󂫂̂���z��ɑ������
						Enemy[i].type = 0;	//��ɍU�����΂����
						Enemy[i].MapX = x;//�G�̃}�b�v��̂����W������
						Enemy[i].MapY = y;//�G�̃}�b�v���y���W������
						Enemy[i].x = (x * 40);//�G�̏���x���W
						Enemy[i].y = (y * 40);//�G�̏���y���W
						Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
						Enemy[i].direction = 0;
						Enemy[i].drawf = true;
						Enemy[i].HPdrawf = false;	//�G��HP�\���t���O
						break;
					}
				}
			}
			if (g_StageData[0][y][x] == 5) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//�󂫂̂���z��ɑ������
						Enemy[i].type = 1;	//���L�����ɍU����΂����
						Enemy[i].MapX = x;//�G�̃}�b�v��̂����W������
						Enemy[i].MapY = y;//�G�̃}�b�v���y���W������
						Enemy[i].x = (x * 40);//�G�̏���x���W
						Enemy[i].y = (y * 40);//�G�̏���y���W
						Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
						Enemy[i].direction = 0;
						Enemy[i].drawf = true;
						Enemy[i].HPdrawf = false;	//�G��HP�\���t���O
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < MAXAttack; i++) {
		Attackheight[i] = 25;
		AttackFlg[i] = false;//�U�����邽�߂̃t���O:0�Ȃ�͈͊O�F�P�Ȃ�͈͓�
		AttackType[i] = 0;
	}
}