#pragma once
#include "DxLib.h"

//BGM
extern int rockBGM;
extern int bpm;
extern int prse;
extern int grse;
extern int jpse;
extern int attackse;	//攻撃を出した瞬間のSE
extern int attackse2;	//食らったときのSE
extern int dese;	//シーケンスSE
extern int deathse;	//死ぬときのSE
extern int doorse;	//ドアSE

int LoadSounds();	//音楽読み込み
