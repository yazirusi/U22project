#include "DxLib.h"
#include "images.h"
#include "BackgroundMove.h"
#include "player.h"
//#include "map.h"

//
int spd;         //�X�N���[���X�s�[�h
int scrool = 0;  //�\���ʒu

/***********************
*�w�i�̃X�N���[��
***********************/
void BackScrool(){
	//�v���C���[���i��ł��邩�ǂ����̔���
	//�i��œ���� spd��2�����@�����łȂ���� 0����
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		if (CheckHitBlock(2,0) == 0) {
			spd = 2;
			scrool -= spd ;
		}
	}
	else {
		spd = 0;
	}
	//�v���C���[���i��ł��邩�ǂ����̔���
	//�i��œ���� spd��2�����@�����łȂ���� 0����
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (CheckHitBlock(1,0) == 0) {
			spd = 2;
			scrool += spd ;
		}
	}
	else {
		spd = 0;
	}
	if (scrool > 0) {
		scrool = 0;
	}
	//�w�i���X�N���[���\��
	SetDrawArea(0, 0, 1280, 850);
	DrawGraph(scrool % 1280 + 1280,0, Backimg,TRUE);
	DrawGraph(scrool % 1280,0, Backimg, TRUE);
	SetDrawArea(0, 0, 1280, 850);


}