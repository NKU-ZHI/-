#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include<graphics.h>//包含图形库头文件
#include<mmsystem.h>//包含多媒体设备接口头文件
#pragma comment(lib,"winmm.lib")//加载静态库
#include<stdbool.h>//逻辑类型
#include<stdio.h>
IMAGE p;
IMAGE q;
int num = 1;
int outcome;
int musicPlaying = 0;

int arr[15][15];
void qidongmusic() {
	// 重新设置音频文件的播放位置为0
	mciSendString("seek qidong.mp3 to start", 0, 0, 0);

	// 播放音乐
	mciSendString("play source/qidong.mp3", 0, 0, 0);
	printf("播放 启动的小曲\n");
}
void exitmusic() {
	// 重新设置音频文件的播放位置为0
	mciSendString("seek hahaha.mp3 to start", 0, 0, 0);

	// 播放音乐
	mciSendString("play source/hahaha.mp3", 0, 0, 0);
	printf("播放 你干嘛 哈哈哎呦\n");
}

void change()
{
	exitmusic();
	HWND hnd = GetHWnd();//获取窗口句柄（相当于窗口的指针）
	SetWindowText(hnd, "五子棋");
	int isok=0;//设置窗口标题
	if (outcome == 1)											
		isok = MessageBox(NULL, "黑方赢咯", "菜就多练，不会，就别玩", MB_OKCANCEL); //弹出消息盒子,提示用户操作
	else if (outcome == -1)
		isok = MessageBox(NULL, "白方赢咯", "你要老说以前，怎么不拿刚出生对比呢", MB_OKCANCEL);

	if (IDOK == isok)                                             //返回点了哪里
	{            
		exit(0);                                     //点了ok

	}
	else if (IDCANCEL == isok)                               //点了取消
	{

		exit(0);

	}
}
void ifmusic()
{
	if (musicPlaying == 0) {
		// 如果音乐暂停状态，开始播放音乐
		mciSendString("open source/wind.mp3", 0, 0, 0);
		mciSendString("play source/wind.mp3", 0, 0, 0);
		musicPlaying = 1; // 设置音乐为播放状态
		printf("播放 让风告诉你\n");
	}
	else {
		// 如果音乐正在播放，暂停音乐
		mciSendString("pause source/wind.mp3", 0, 0, 0);
		musicPlaying = 0; // 设置音乐为暂停状态
		printf("暂停 让风告诉你\n");
	}

}
void climusic()
{
	// 重新设置音频文件的播放位置为0
	mciSendString("seek click.mp3 to start", 0, 0, 0);

	// 播放音乐
	mciSendString("play source/click.mp3", 0, 0, 0);
		printf("鸡叫\n");
}

void initboard()//初始化，二维数组全部设为0，确保游戏开始时棋盘上没有任何棋子
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			arr[i][j] = 0;
		}
	}
}
int full(int x, int y)//用于填上棋子
{
	if (arr[x][y] != 0)//如果下棋的位置有了棋子，也就是这个位置的二维数组的值不是0
		return 0;//不执行操作，返回0，退出函数
	else
		arr[x][y] = num;//反之，即下棋的位置没有棋子，也就是这个位置的数组元素是0，那么让元素有值num,即下上了棋子
	return 1;//退出函数，返回1
}
void draw(int m, int n)//接收传入的鼠标点击的坐标信息
{

	//开始时候num=1，下的就是黑棋
	if (num == -1)
	{
		setfillcolor(WHITE);
		printf("白方下了一步棋\n");
	}
	else if (num == 1)
	{
		setfillcolor(BLACK);
		printf("黑方下了一步棋\n");

	}
	//传入的m,n是像素点，最大像素点是480，除以30便是16
	//也就是一行或者一列有的棋子的最大数量
	int x;
	int y;
	x = m / 30;
	y = n / 30;
	if (full(x, y) == 0)//如果传入的位置有了棋子，结束函数，不操作
		return;
	fillcircle(m - m % 30 + 15, n - n % 30 + 15, 13);//如果没有棋子，在对应的位置画上一个棋子

	num *= -1;//用于切换棋子颜色，上一个黑，下一个就是白


}
int check_five(int x, int y)
//用于检测是否有一个地方棋子使得已经五子连了
{

	if (arr[x][y] == arr[x - 1][y] && arr[x][y] == arr[x - 2][y] && arr[x][y] == arr[x + 1][y] && arr[x][y] == arr[x + 2][y])
		return 1;
	if (arr[x][y] == arr[x][y - 1] && arr[x][y] == arr[x][y - 2] && arr[x][y] == arr[x][y + 1] && arr[x][y] == arr[x][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y - 1] && arr[x][y] == arr[x - 2][y - 2] && arr[x][y] == arr[x + 1][y + 1] && arr[x][y] == arr[x + 2][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y + 1] && arr[x][y] == arr[x + 2][y - 2] && arr[x][y] == arr[x + 1][y - 1] && arr[x][y] == arr[x - 2][y + 2])
		return 1;
	//上面分别是四种获胜情况，横着，竖着，左斜，右斜
	return 0;
}
int check_over(){
//检测游戏结束与否，遍历所有棋子，如果这个地方没有下子，继续遍历下一个棋子，如果这个地方的棋子直接使得五子连珠，返回1

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (check_five(i, j) == 1)
			{
				outcome = arr[i][j];//用于检测获胜方是哪一方，结果是1，黑方赢，-1，白方赢
				return 1;
			}

		}
	}

}
void game()
//将游戏函数封装，便于使用
{
	ExMessage msg;

	initgraph(480, 480);
	loadimage(&p, "source/qipan.jpg", 480, 480);
	putimage(0, 0, &p);
	setlinecolor(BLACK);//用黑色填线的颜色
	//画出棋盘
	for (int x = 15; x < 480; x += 30)
	{
		line(x, 15, x, 465);
	}
	for (int y = 15; y < 480; y += 30)
	{
		line(15, y, 465, y);
	}
	setfillcolor(BLUE);
	//用上述指定的颜色，填充下面对应的点的圈
	fillcircle(15 + 3 * 30, 15 + 3 * 30, 3);
	fillcircle(15 + 3 * 30, 15 + 11 * 30, 3);
	fillcircle(15 + 11 * 30, 15 + 3 * 30, 3);
	fillcircle(15 + 7 * 30, 15 + 7 * 30, 3);
	fillcircle(15 + 11 * 30, 15 + 11 * 30, 3);
	//依次为横纵坐标，填充区域圆的半径大小
	settextstyle(40, 20, "隶书");
	setbkmode(TRANSPARENT);
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE))    //用于检查是否有消息在消息队列中，如果有，会取出第一条消息
		{
			switch (msg.message)    //检查消息的类型
			{
			case WM_LBUTTONDOWN:            //若为左键，执行以下代码
				climusic();
				draw(msg.x, msg.y);        //调用draw()函数，将鼠标点击位置的坐标传入，进行绘制棋子
				break;

			}
		}
		if (check_over() == 1)
		{
			outtextxy(180, 180, "对局结束");
			change();
			system("pause");
		}
	}
}
void initgame()
//初始面板操作系统的封装
{
	initgraph(600, 600);
	loadimage(&q, "source/chushi.jpg", 600, 600);
	putimage(0, 0, &q);
	settextstyle(40, 20, "小篆");

	outtextxy(140, 80, "欢迎来到五子棋");
	outtextxy(200, 130, "播放暂停");
	outtextxy(200, 180, "开始游戏");
	outtextxy(200, 230, "退出游戏");

	MOUSEMSG msg = { 0 };//定义一个与鼠标相关的结构体变量

	int currentState = 0; // 0 表示开始界面，1 表示退出确认界面

	while (1) {
		msg = GetMouseMsg();
		switch (msg.uMsg) {
		case WM_LBUTTONDOWN: // 鼠标左键按下
			printf("Clicked at (%d, %d)\n", msg.x, msg.y);
			climusic();

			if (currentState == 0) {
				// 在开始界面处理点击事件
				if (msg.x >= 200 && msg.x <= 360 && msg.y >= 130 && msg.y <= 170)
					// 在音乐播放暂停按钮中
				{
					ifmusic();
				}
				else if (msg.x >= 200 && msg.x <= 360 && msg.y >= 180 && msg.y <= 220)
					// 在游戏开始按钮中
				{
					game();
				}
				else if (msg.x >= 200 && msg.x <= 360 && msg.y >= 230 && msg.y <= 270)
					// 在游戏退出按钮中
				{
					currentState = 1; // 进入退出确认界面
					exitmusic();
					outtextxy(100, 300, "你真的要退出游戏吗？？");
					outtextxy(50, 400, "假的");
					outtextxy(400, 400, "真的退出");
				}
			}
			else if (currentState == 1) {
				// 在退出确认界面处理点击事件
				if (msg.x >= 50 && msg.x <= 130 && msg.y >= 400 && msg.y <= 440)
					// 不退出游戏
				{

					currentState = 0;
					system("exit");// 返回上一步，回到开始界面
				}
				else if (msg.x >= 400 && msg.x <= 560 && msg.y >= 400 && msg.y <= 440)
					// 退出游戏
				{
					exit(0);
				}
			}
		}
	}
}
  
int main()
{
	qidongmusic();
	printf("点击\"五子棋\"即可启动游戏\n");
	initgraph(1352, 739);
	loadimage(&q, "source/qidong.jpg", 1352, 739);
	putimage(0, 0, &q);
	MOUSEMSG msg = { 0 };
	while (1) {
		msg = GetMouseMsg();
		switch (msg.uMsg) {
		case WM_LBUTTONDOWN: // 鼠标左键按下		
				if (msg.x >= 450 && msg.x <= 880 && msg.y >= 260 && msg.y <= 390)
					// 在五子棋界面
				{
					mciSendString("close source/qidong.mp3", 0, 0, 0);
					printf("关闭 启动的小曲\n");
					closegraph();
					initgame();
				}
		}
	}
	return 0;
}































