#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"

//��`
int	g_GameState = 0;		// �Q�[���X�e�[�^�X

//Airman airman;

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit()
{
	g_GameState = 2;

	PlayerInit();
	ScroolInit();

	//�m�[�c�̏�����
	for (int i = 0; i < 100; i++) {
		notesinit(i);
	}

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				Enemy.MapX = x;//�G�̃}�b�v��̂����W������
				Enemy.MapY = y;//�G�̃}�b�v���y���W������
				Enemy.x = (x * 40);//�G�̏���x���W
				Enemy.y = (y * 40);//�G�̏���y���W
				Enemy.HP = Enemy.MaxHP;
				Enemy.direction = 0;
				Enemy.Attck = false;//�U�����邽�߂̃t���O:0�Ȃ�͈͊O�F�P�Ȃ�͈͓�
				Enemy.drawf = 1;	//0��\���@�P�\��
				Enemy.HPdrawf = false;	//�G��HP�\���t���O
			}
		}
	}
	airman.Airmaninit();//�G�A�[�}���̏�����
	Air.AirInit();//�G�A�[�}���̍U���̏�����
}