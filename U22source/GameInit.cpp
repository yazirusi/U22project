#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"
#include "EnemyAttck.h"

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
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//�󂫂̂���z��ɑ������
						Enemy[i].MapX = x;//�G�̃}�b�v��̂����W������
						Enemy[i].MapY = y;//�G�̃}�b�v���y���W������
						Enemy[i].x = (x * 40);//�G�̏���x���W
						Enemy[i].y = (y * 40);//�G�̏���y���W
						Enemy[i].HP = Enemy[i].MaxHP;
						Enemy[i].direction = 0;
						Enemy[i].drawf = 1;	//0��\���@�P�\��
						Enemy[i].HPdrawf = false;	//�G��HP�\���t���O
						for (int a = 0; a < MAXAttack; a++) {
							Attackheight[a] = 25;
							AttackFlg[a] = false;//�U�����邽�߂̃t���O:0�Ȃ�͈͊O�F�P�Ȃ�͈͓�
						}
						break;
					}
				}
			}
		}
	}
	airman.Airmaninit();//�G�A�[�}���̏�����
	Air.AirInit();//�G�A�[�}���̍U���̏�����
}