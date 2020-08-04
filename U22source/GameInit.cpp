#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include"EnemyMove.h"

//��`
int	g_GameState = 0;		// �Q�[���X�e�[�^�X

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		//�}�b�v�z��̃v���C���[�ʒu
		player.p_x = 1;
		player.p_y = 17;

		//�v���C���[�̍��W
		player.px = 40;
		player.py = 680;
		//player.py = 640;
	}
	//�v���C���[�̃X�e�[�^�X�̏�����
	player.hp = 100;

	//�m�[�c�̏�����
	for (int i = 0; i < 100; i++) {
		notesinit(i);
	}
	g_GameState = 2;

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				Enemy.MapX = x;//�G�̃}�b�v��̂����W������
				Enemy.MapY = y;//�G�̃}�b�v���y���W������
				Enemy.x = (x * 40);//�G�̏���x���W
				Enemy.y = (y * 40);//�G�̏���y���W
			}
		}
	}
}