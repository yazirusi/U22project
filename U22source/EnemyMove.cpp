#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"
#include"main.h"
#include"images.h"

//�G�A�[�}���̕ϐ�
Airman airman[MAXEnemy];
AIR Air[MAXEnemy];

/***************************************
*�G�l�~�[�̓���
***************************************/
void EnemyMove(void) {

	for (int i = 0; i < MAXEnemy; i++) {
		Air[0].ReloadCount = i;
		airman[i].AirmanMove();

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
		else if(Enemy[i].HP > 0){
			Enemy[i].drawf = true;
		}

		//�G�����ʂ��A�\���t���O����\���Ȃ�
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//�������牺�̏��������Ȃ�
		}

		if (Enemy[i].type == 0) {//�����G
			if (debug == true) {
				DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
					(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);//�G�̔���`��
			}
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
		if (Enemy[i].type == 2) {//���X�{�X
			//�G�̔���`��
			if (debug == true) {
				DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
					(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size + 80), 0xff0000, FALSE);
			}
			//�C���X�g�̔��f
			DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, lasboss[0], TRUE);
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
			static int barlen;
			if (Enemy[0].type == 2) {//�炷�ڂ���������
				barlen = (200 * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			}
			else {
				barlen = (Enemy[i].size * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			}
			//�G��HP�o�[
			DrawBox(Enemy[i].x + sx, Enemy[i].y - 80, Enemy[i].x + sx + barlen, Enemy[i].y - 60, 0xFF0000, TRUE);
		}
	}
}
/**************
*Airman�̏�����
**************/
void Airman::Airmaninit() {
	x = 0;

	static int intt = 0;
	static int innt = 0;

	Perception = 12 * 40;//���m�͈͂�������

	for (int j = intt; j < MAPHEIGHT; j++) {
		for (int k = innt; k < MAPWIDTH; k++) {
			if (g_StageData[g_stage][j][k] == 4) {
				/*MapX = k;
				MapY = j;*/
				x = (k * 40);
				y = (j * 40);
				HP = 80;
				intt = j;
				innt = k + 1;
				break;
			}
		}
	}
}
/***************
*Airman�̓���
****************/
void Airman::AirmanMove() {

	const int Gravity = 1;

	if (x != 0 && y != 0 && direction == false) {
		//DrawBox((x - Move + sx), (y), (x + size - Move + sx), (y + size), 0xffffff, TRUE);//�G�̕`��
		DrawTurnGraph(x + sx + 3, y - size, EnemyImg3[0], TRUE);
	}
	if (x != 0 && y != 0 && direction == true){
		DrawGraph(x + sx + 3, y - size, EnemyImg3[0], TRUE);
	}

	//JumpCount++;

	/*if (JumpCount == 180 && JumpFlg == false) {
		JumpFlg = true;
	}*/

	if (JumpFlg == false) {
		Jump -= Gravity;
		y -= Jump;
	}

	if (Hitcheck(x, y + size - Jump, 0, false) == 1 && JumpFlg == false) {
		//y -= Jump;
		Jump = 20;
		JumpFlg = true;
	}
	if (JumpFlg == true)
	{
		JumpCount++;
		if (JumpCount == 180) {
			JumpCount = 0;
			JumpFlg = false;
		}
	}
	//�U���Ԋu
	if (AttackInterval > 0) {
		AttackInterval--;
	}

	//HP�\��
	if (HPdrawf == true) {
		int barlen;
		barlen = (size * HP * 100 / 80) / 100;
		//�G��HP�o�[
		DrawBox(x + sx, y - 80, x + sx + barlen, y - 60, 0xFF0000, TRUE);
	}

	/*else if (Hitcheck(x, y + size - Jump, 0, false) == 1 && JumpFlg == true)
	{
		y -= 0;
		Jump = 20;
		JumpCount = 0;
		JumpFlg = false;
	}*/
}
/*************
*Air�̏�����
*************/
void AIR::AirInit() {
	for (int j = 0; j < Air_MAX; j++) {
		DispFlg[j] = false;
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

	return g_StageData[g_stage][y][x];//�}�b�v�`�b�v��ł̍��W��Ԃ�

	return 0;
}
/**************************************
*�G�̏�����
***************************************/
void EnemyInit() {

	static int width;

	//�G�̏�����
	for (int i = 0; i < MAXEnemy; i++) {
		Enemy[i].x = 0;
		Enemy[i].drawf = false;
		Enemy[i].HP = 0;
	}
	//�}�b�v�`�b�v�ɍ��킹�č��W��ݒ肷��
	if (g_stage == 0) {
		width = MAPWIDTH;
	}
	else {
		width = 33;
	}

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < width; x++) {
			/*if (g_StageData[g_stage][y][x] == 3) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].drawf == false) {	//�󂫂̂���z��ɑ������
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
			if (g_StageData[g_stage][y][x] == 5) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].drawf == false) {	//�󂫂̂���z��ɑ������
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
			}*/
			for (int i = 0,e = g_StageData[g_stage][y][x];
				i < MAXEnemy && (e == 3 || e == 5 || e == 6) ; i++) {
				if (Enemy[i].drawf == false) {	//�󂫂̂���z��ɑ������
					Enemy[i].MapX = x;//�G�̃}�b�v��̂����W������
					Enemy[i].MapY = y;//�G�̃}�b�v���y���W������
					Enemy[i].x = (x * 40);//�G�̏���x���W
					Enemy[i].y = (y * 40);//�G�̏���y���W
					Enemy[i].direction = 0;
					Enemy[i].drawf = true;
					Enemy[i].HPdrawf = false;	//�G��HP�\���t���O
					if(e == 3)Enemy[i].type = 0;	//��ɍU����΂����
					if(e == 5)Enemy[i].type = 1;	//���L�����ɍU����΂����
					if (e == 6) {
						Enemy[i].type = 2;	//���X�{�X
						Enemy[i].HPdrawf = true;	//�G��HP�\���t���O
					}
					Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
					break;
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