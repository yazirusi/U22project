////���j���[�J�[�\���ړ�����
//if (g_KeyFlg & PAD_INPUT_DOWN) {
//	if (++g_MenuNumber > 2) g_MenuNumber = 0;
//}
//if (g_KeyFlg & PAD_INPUT_UP) {
//	if (--g_MenuNumber < 0) g_MenuNumber = 2;
//}
//
////�y�L�[�Ń��j���[�I��
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 0) g_GameState = 2;			//�Q�[�����C��
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 1) g_GameState = 6;			//�����L���O
////�^�C�g���摜�\��
//DrawGraph(0, 0, g_TitleImage, FALSE);
//
////���j���[�J�[�\���i�O�p�`�j�̕\��
//g_MenuY = g_MenuNumber * 52;
//DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);

//g_WaitTime++;		//���Ԃ̎擾
//if (g_WaitTime == 60) {
//	Time++;
//	g_WaitTime = 0;
//	timecnt = Time;
//
//}
//else if (g_stage >= 4) {
//	Time += 0;
//}
//SetFontSize(30);
//DrawFormatString(590, 20, 0xffffff, "%d", Time);
//timecnt += 0;
//Time = 0;
//timecnt = 0;