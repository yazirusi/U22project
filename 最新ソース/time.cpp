#include "DxLib.h"
#include <time.h>
#include "time.h"

/***********************************************
 * �N���������ɂ��̕\��
 ***********************************************/
void TimeDisp() {
	time_t jikan = time(NULL);
	struct tm imanojikan;

	errno_t error;

	error = localtime_s(&imanojikan, &jikan);

	SetFontSize(32);
	DrawFormatString(50, 5, 0xffffff, "�N�����@%d�N %d�� %d��", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday);
	DrawFormatString(1000, 5, 0xffffff, "ESC:�I��");
	SetFontSize(16);
}