#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"

//�G�A�[�}���̕ϐ�
Airman airman;
AIR Air;

/***************************************
*�G�l�~�[�̓���
***************************************/
void EnemyMove(void) {
	airman.AirmanMove();
	//�G�̎��S����	0:���S�@1:�\��
	if (Enemy.drawf == 0) {
		return;
	}

	if (Enemy.drawf == 1) {
		DrawBox((Enemy.x - Enemy.Move + sx), (Enemy.y),
			(Enemy.x + Enemy.size - Enemy.Move + sx), (Enemy.y + Enemy.size), 0x00ffff, TRUE);//�G�̕`��
	}

	/*//�v���C���[���������t���O���L�[�������Ă邩
	if (Enemy.Moveflg == 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		Enemy.Move -= 2;//�G�L�����̈ړ��ɉ��Z����X�N���[����
		if (Enemy.Attck == true) {
			Enemy.MoveD -= 2;
		}
		Enemy.Moveflg = 0;//�t���O��������
	}
	//�v���C���[���������t���O���L�[�������Ă邩
	else if (Enemy.Moveflg == 2 && CheckHitKey(KEY_INPUT_LEFT) != 1)
	{
		Enemy.Move += 2;//�G�L�����̈ړ��ɉ��Z����X�N���[����
		if (Enemy.Attck == true) {
			Enemy.MoveD += 2;
		}
		Enemy.Moveflg = 0;
	}*/

	//�G�̍��W�ƃ}�b�v�`�b�v�̓����蔻��𒲂ׂ�
	if (Enemy.direction == false) {//���Ɉړ����Ă鎞�̏���
		if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction, false) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
			Enemy.x -= (Enemy.speed);//�����Ȃ�ړ����Ă���
			Enemy.move -= (Enemy.speed);
		}
		else
		{
			Enemy.direction = true;//�E�ɂ��邽�߂̃t���O
		}
	}

	if (Enemy.direction == TRUE) {//�E�Ɉړ����Ă鎞�̏���
		if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction, false) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
			Enemy.x += (Enemy.speed);//�����Ȃ�ړ����Ă���
			Enemy.move -= (Enemy.speed);
		}
		else
		{
			Enemy.direction = false;//���ɂ��邽�߂̃t���O
		}
	}
	if (Enemy.HPdrawf == true) {
		int barlen = (Enemy.size * (Enemy.HP * 100) / Enemy.MaxHP) / 100;
		//�G��HP�o�[
		DrawBox(Enemy.x + sx, Enemy.y - 30, Enemy.x + sx + barlen, Enemy.y - 20, 0xFF0000, TRUE);
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

	Airman::Perception = 10 * 40;//���m�͈͂�������
}
/***************
*Airman�̓���
****************/
void Airman::AirmanMove() {
	DrawBox((Airman::x - Airman::Move + sx), (Airman::y),
		(Airman::x + Airman::size - Airman::Move + sx), (Airman::y + Airman::size), 0xffffff, TRUE);//�G�̕`��

	//�G�A�[�}���̍����̊��m�͈�
	if (Airman::x - Airman::Perception < player.px + 40 && Air.DispFlg[0] == false) {
		for (int i = 0; i < Air_MAX; i++)
		{
			Airman::AttackX[i] = Airman::x /*+ sx*/ - 40 - i * 80;//�G�̍U�����Wx�������
			Airman::AttackY[i] = Airman::y - (i % 2) * 120;//�G�̍U�����Wy������
			Air.DispFlg[i] = true;//���m�͈͂ɓ�������G�l�~�[�U���t���O��true�ɂ���
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