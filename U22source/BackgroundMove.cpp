#include "DxLib.h"
#include "images.h"
#include "BackgroundMove.h"
#include "player.h"
#include "map.h"
//#include "map.h"

int spd = 2;         //�X�N���[���X�s�[�h
int scrool = 0;  //�\���ʒu

/***********************
*�w�i�̃X�N���[��
***********************/
void BackScrool(){

	DrawGraph(0, 0, Backimg3, TRUE);

	//�w�i���X�N���[���\��
	SetDrawArea(0, 0, 1280, 850);
	DrawGraph(spd % 1280 + 1280, 0, Backimg2, TRUE);
	DrawGraph(spd % 1280, 0, Backimg2, TRUE);
	DrawGraph(scrool % 1280 + 1280, 0, Backimg, TRUE);
	DrawGraph(scrool % 1280, 0, Backimg, TRUE);
	SetDrawArea(0, 0, 1280, 850);

}
/***********************
*�X�N���[���̏�����
***********************/
void ScroolInit() {
	spd = 2;
	scrool = 0;
	msx = 0;
	sx = 0;
}