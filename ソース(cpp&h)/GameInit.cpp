#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"

//��`
int	g_GameState = 1;		// �Q�[���X�e�[�^�X

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		//�}�b�v�z��̃v���C���[�ʒu
		p_x = 1;
		p_y = 17;

		//�v���C���[�̍��W
		px = 40;
		py = 680;
	}

	//�m�[�c�ʒu�̏�����
	for (int i = 0; i < 10; i++) {
		nx[i] = 200;
	}
	g_GameState = 2;
}