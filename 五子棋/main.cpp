#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include<graphics.h>//����ͼ�ο�ͷ�ļ�
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
#include<stdbool.h>//�߼�����
#include<stdio.h>
IMAGE p;
IMAGE q;
int num = 1;
int outcome;
int musicPlaying = 0;

int arr[15][15];
void qidongmusic() {
	// ����������Ƶ�ļ��Ĳ���λ��Ϊ0
	mciSendString("seek qidong.mp3 to start", 0, 0, 0);

	// ��������
	mciSendString("play source/qidong.mp3", 0, 0, 0);
	printf("���� ������С��\n");
}
void exitmusic() {
	// ����������Ƶ�ļ��Ĳ���λ��Ϊ0
	mciSendString("seek hahaha.mp3 to start", 0, 0, 0);

	// ��������
	mciSendString("play source/hahaha.mp3", 0, 0, 0);
	printf("���� ����� ��������\n");
}

void change()
{
	exitmusic();
	HWND hnd = GetHWnd();//��ȡ���ھ�����൱�ڴ��ڵ�ָ�룩
	SetWindowText(hnd, "������");
	int isok=0;//���ô��ڱ���
	if (outcome == 1)											
		isok = MessageBox(NULL, "�ڷ�Ӯ��", "�˾Ͷ��������ᣬ�ͱ���", MB_OKCANCEL); //������Ϣ����,��ʾ�û�����
	else if (outcome == -1)
		isok = MessageBox(NULL, "�׷�Ӯ��", "��Ҫ��˵��ǰ����ô���øճ����Ա���", MB_OKCANCEL);

	if (IDOK == isok)                                             //���ص�������
	{            
		exit(0);                                     //����ok

	}
	else if (IDCANCEL == isok)                               //����ȡ��
	{

		exit(0);

	}
}
void ifmusic()
{
	if (musicPlaying == 0) {
		// ���������ͣ״̬����ʼ��������
		mciSendString("open source/wind.mp3", 0, 0, 0);
		mciSendString("play source/wind.mp3", 0, 0, 0);
		musicPlaying = 1; // ��������Ϊ����״̬
		printf("���� �÷������\n");
	}
	else {
		// ����������ڲ��ţ���ͣ����
		mciSendString("pause source/wind.mp3", 0, 0, 0);
		musicPlaying = 0; // ��������Ϊ��ͣ״̬
		printf("��ͣ �÷������\n");
	}

}
void climusic()
{
	// ����������Ƶ�ļ��Ĳ���λ��Ϊ0
	mciSendString("seek click.mp3 to start", 0, 0, 0);

	// ��������
	mciSendString("play source/click.mp3", 0, 0, 0);
		printf("����\n");
}

void initboard()//��ʼ������ά����ȫ����Ϊ0��ȷ����Ϸ��ʼʱ������û���κ�����
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			arr[i][j] = 0;
		}
	}
}
int full(int x, int y)//������������
{
	if (arr[x][y] != 0)//��������λ���������ӣ�Ҳ�������λ�õĶ�ά�����ֵ����0
		return 0;//��ִ�в���������0���˳�����
	else
		arr[x][y] = num;//��֮���������λ��û�����ӣ�Ҳ�������λ�õ�����Ԫ����0����ô��Ԫ����ֵnum,������������
	return 1;//�˳�����������1
}
void draw(int m, int n)//���մ�����������������Ϣ
{

	//��ʼʱ��num=1���µľ��Ǻ���
	if (num == -1)
	{
		setfillcolor(WHITE);
		printf("�׷�����һ����\n");
	}
	else if (num == 1)
	{
		setfillcolor(BLACK);
		printf("�ڷ�����һ����\n");

	}
	//�����m,n�����ص㣬������ص���480������30����16
	//Ҳ����һ�л���һ���е����ӵ��������
	int x;
	int y;
	x = m / 30;
	y = n / 30;
	if (full(x, y) == 0)//��������λ���������ӣ�����������������
		return;
	fillcircle(m - m % 30 + 15, n - n % 30 + 15, 13);//���û�����ӣ��ڶ�Ӧ��λ�û���һ������

	num *= -1;//�����л�������ɫ����һ���ڣ���һ�����ǰ�


}
int check_five(int x, int y)
//���ڼ���Ƿ���һ���ط�����ʹ���Ѿ���������
{

	if (arr[x][y] == arr[x - 1][y] && arr[x][y] == arr[x - 2][y] && arr[x][y] == arr[x + 1][y] && arr[x][y] == arr[x + 2][y])
		return 1;
	if (arr[x][y] == arr[x][y - 1] && arr[x][y] == arr[x][y - 2] && arr[x][y] == arr[x][y + 1] && arr[x][y] == arr[x][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y - 1] && arr[x][y] == arr[x - 2][y - 2] && arr[x][y] == arr[x + 1][y + 1] && arr[x][y] == arr[x + 2][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y + 1] && arr[x][y] == arr[x + 2][y - 2] && arr[x][y] == arr[x + 1][y - 1] && arr[x][y] == arr[x - 2][y + 2])
		return 1;
	//����ֱ������ֻ�ʤ��������ţ����ţ���б����б
	return 0;
}
int check_over(){
//�����Ϸ������񣬱����������ӣ��������ط�û�����ӣ�����������һ�����ӣ��������ط�������ֱ��ʹ���������飬����1

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (check_five(i, j) == 1)
			{
				outcome = arr[i][j];//���ڼ���ʤ������һ���������1���ڷ�Ӯ��-1���׷�Ӯ
				return 1;
			}

		}
	}

}
void game()
//����Ϸ������װ������ʹ��
{
	ExMessage msg;

	initgraph(480, 480);
	loadimage(&p, "source/qipan.jpg", 480, 480);
	putimage(0, 0, &p);
	setlinecolor(BLACK);//�ú�ɫ���ߵ���ɫ
	//��������
	for (int x = 15; x < 480; x += 30)
	{
		line(x, 15, x, 465);
	}
	for (int y = 15; y < 480; y += 30)
	{
		line(15, y, 465, y);
	}
	setfillcolor(BLUE);
	//������ָ������ɫ����������Ӧ�ĵ��Ȧ
	fillcircle(15 + 3 * 30, 15 + 3 * 30, 3);
	fillcircle(15 + 3 * 30, 15 + 11 * 30, 3);
	fillcircle(15 + 11 * 30, 15 + 3 * 30, 3);
	fillcircle(15 + 7 * 30, 15 + 7 * 30, 3);
	fillcircle(15 + 11 * 30, 15 + 11 * 30, 3);
	//����Ϊ�������꣬�������Բ�İ뾶��С
	settextstyle(40, 20, "����");
	setbkmode(TRANSPARENT);
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE))    //���ڼ���Ƿ�����Ϣ����Ϣ�����У�����У���ȡ����һ����Ϣ
		{
			switch (msg.message)    //�����Ϣ������
			{
			case WM_LBUTTONDOWN:            //��Ϊ�����ִ�����´���
				climusic();
				draw(msg.x, msg.y);        //����draw()�������������λ�õ����괫�룬���л�������
				break;

			}
		}
		if (check_over() == 1)
		{
			outtextxy(180, 180, "�Ծֽ���");
			change();
			system("pause");
		}
	}
}
void initgame()
//��ʼ������ϵͳ�ķ�װ
{
	initgraph(600, 600);
	loadimage(&q, "source/chushi.jpg", 600, 600);
	putimage(0, 0, &q);
	settextstyle(40, 20, "С׭");

	outtextxy(140, 80, "��ӭ����������");
	outtextxy(200, 130, "������ͣ");
	outtextxy(200, 180, "��ʼ��Ϸ");
	outtextxy(200, 230, "�˳���Ϸ");

	MOUSEMSG msg = { 0 };//����һ���������صĽṹ�����

	int currentState = 0; // 0 ��ʾ��ʼ���棬1 ��ʾ�˳�ȷ�Ͻ���

	while (1) {
		msg = GetMouseMsg();
		switch (msg.uMsg) {
		case WM_LBUTTONDOWN: // ����������
			printf("Clicked at (%d, %d)\n", msg.x, msg.y);
			climusic();

			if (currentState == 0) {
				// �ڿ�ʼ���洦�����¼�
				if (msg.x >= 200 && msg.x <= 360 && msg.y >= 130 && msg.y <= 170)
					// �����ֲ�����ͣ��ť��
				{
					ifmusic();
				}
				else if (msg.x >= 200 && msg.x <= 360 && msg.y >= 180 && msg.y <= 220)
					// ����Ϸ��ʼ��ť��
				{
					game();
				}
				else if (msg.x >= 200 && msg.x <= 360 && msg.y >= 230 && msg.y <= 270)
					// ����Ϸ�˳���ť��
				{
					currentState = 1; // �����˳�ȷ�Ͻ���
					exitmusic();
					outtextxy(100, 300, "�����Ҫ�˳���Ϸ�𣿣�");
					outtextxy(50, 400, "�ٵ�");
					outtextxy(400, 400, "����˳�");
				}
			}
			else if (currentState == 1) {
				// ���˳�ȷ�Ͻ��洦�����¼�
				if (msg.x >= 50 && msg.x <= 130 && msg.y >= 400 && msg.y <= 440)
					// ���˳���Ϸ
				{

					currentState = 0;
					system("exit");// ������һ�����ص���ʼ����
				}
				else if (msg.x >= 400 && msg.x <= 560 && msg.y >= 400 && msg.y <= 440)
					// �˳���Ϸ
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
	printf("���\"������\"����������Ϸ\n");
	initgraph(1352, 739);
	loadimage(&q, "source/qidong.jpg", 1352, 739);
	putimage(0, 0, &q);
	MOUSEMSG msg = { 0 };
	while (1) {
		msg = GetMouseMsg();
		switch (msg.uMsg) {
		case WM_LBUTTONDOWN: // ����������		
				if (msg.x >= 450 && msg.x <= 880 && msg.y >= 260 && msg.y <= 390)
					// �����������
				{
					mciSendString("close source/qidong.mp3", 0, 0, 0);
					printf("�ر� ������С��\n");
					closegraph();
					initgame();
				}
		}
	}
	return 0;
}































