#include "DxLib.h"
#include <time.h>
#include "time.h"

/***********************************************
 * 起動した日にちの表示
 ***********************************************/
void TimeDisp() {
	time_t jikan = time(NULL);
	struct tm imanojikan;

	errno_t error;

	error = localtime_s(&imanojikan, &jikan);

	SetFontSize(32);
	DrawFormatString(50, 5, 0xffffff, "起動日　%d年 %d月 %d日", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday);
	DrawFormatString(1000, 5, 0xffffff, "ESC:終了");
	SetFontSize(16);
}