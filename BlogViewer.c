#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);
}
int main() {
	time_t nowtime;
	struct tm *timeinfo;
	time( &nowtime );
	timeinfo = localtime( &nowtime );
	int y = timeinfo->tm_year + 1900;
	int m = timeinfo->tm_mon + 1;
	int d = timeinfo->tm_mday;
	setColor(7, 0);
	printf("Current system time:");
	setColor(15, 0);
	printf("%04d-%02d-%02d\n", y, m, d);
	setColor(7, 0);
	printf("You will be directed to ");
	char url[50], cmd[60] = "explorer ";
	sprintf(url, "https://blog.zhangzisu.cn/%04d/%02d/%02d/", y, m, d);
	setColor(10, 0);
	printf("https");
	setColor(15, 0);
	printf("://blog.zhangzisu.cn");
	setColor(8, 0);
	printf("%s\n", url + 25);
	setColor(7, 0);
	printf("Tips:\nThe blog's content format is ");
	setColor(10, 0);
	printf("https:");
	setColor(15, 0);
	printf("//blog.zhangzisu.cn/yyyy/mm/dd/post-name");
	setColor(7, 0);
	printf("\n");
	setColor(8, 0);
	printf("Press enter to visit the blog......\n");
	system("pause >nul");
	setColor(7, 0);
	strcat(cmd, url);
	system(cmd);
	return 0;
}
