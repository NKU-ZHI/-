#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <stdbool.h>
#include <stdio.h>

// ���ֿ�����
class MusicController {
private:
    int musicPlaying;

public:
    MusicController() : musicPlaying(0) {}

    void playStartMusic() {
        mciSendString("seek qidong.mp3 to start", 0, 0, 0);
        mciSendString("play source/qidong.mp3", 0, 0, 0);
        printf("���� ������С��\n");
    }

    void playExitMusic() {
        mciSendString("seek hahaha.mp3 to start", 0, 0, 0);
        mciSendString("play source/hahaha.mp3", 0, 0, 0);
        printf("���� ����� ��������\n");
    }

    void toggleBackgroundMusic() {
        if (musicPlaying == 0) {
            mciSendString("open source/wind.mp3", 0, 0, 0);
            mciSendString("play source/wind.mp3", 0, 0, 0);
            musicPlaying = 1;
            printf("���� �÷������\n");
        }
        else {
            mciSendString("pause source/wind.mp3", 0, 0, 0);
            musicPlaying = 0;
            printf("��ͣ �÷������\n");
        }
    }

    void playClickSound() {
        mciSendString("seek click.mp3 to start", 0, 0, 0);
        mciSendString("play source/click.mp3", 0, 0, 0);
        printf("����\n");
    }

    void closeStartMusic() {
        mciSendString("close source/qidong.mp3", 0, 0, 0);
        printf("�ر� ������С��\n");
    }
};

// ��Ϸ������
class ChessBoard {
private:
    int arr[15][15];
    int currentPlayer; // 1Ϊ�ڷ���-1Ϊ�׷�
    int outcome;

public:
    ChessBoard() : currentPlayer(1), outcome(0) {
        initBoard();
    }

    void initBoard() {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                arr[i][j] = 0;
            }
        }
    }

    bool placePiece(int x, int y) {
        if (arr[x][y] != 0) return false;

        arr[x][y] = currentPlayer;
        currentPlayer *= -1; // �л����
        return true;
    }

    bool checkFiveInRow(int x, int y) const {
        if (arr[x][y] == 0) return false;

        // ���ˮƽ����
        if (x >= 2 && x <= 12 &&
            arr[x][y] == arr[x - 1][y] &&
            arr[x][y] == arr[x - 2][y] &&
            arr[x][y] == arr[x + 1][y] &&
            arr[x][y] == arr[x + 2][y])
            return true;

        // ��鴹ֱ����
        if (y >= 2 && y <= 12 &&
            arr[x][y] == arr[x][y - 1] &&
            arr[x][y] == arr[x][y - 2] &&
            arr[x][y] == arr[x][y + 1] &&
            arr[x][y] == arr[x][y + 2])
            return true;

        // ������Խ��߷���
        if (x >= 2 && y >= 2 && x <= 12 && y <= 12 &&
            arr[x][y] == arr[x - 1][y - 1] &&
            arr[x][y] == arr[x - 2][y - 2] &&
            arr[x][y] == arr[x + 1][y + 1] &&
            arr[x][y] == arr[x + 2][y + 2])
            return true;

        // ��鸱�Խ��߷���
        if (x >= 2 && y <= 12 && x <= 12 && y >= 2 &&
            arr[x][y] == arr[x - 1][y + 1] &&
            arr[x][y] == arr[x - 2][y + 2] &&
            arr[x][y] == arr[x + 1][y - 1] &&
            arr[x][y] == arr[x + 2][y - 2])
            return true;

        return false;
    }

    bool checkGameOver() {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (arr[i][j] != 0 && checkFiveInRow(i, j)) {
                    outcome = arr[i][j];
                    return true;
                }
            }
        }
        return false;
    }

    int getCurrentPlayer() const { return currentPlayer; }
    int getOutcome() const { return outcome; }
};

// ��Ϸ������
class GameUI {
private:
    IMAGE background;
    ChessBoard board;
    MusicController music;

public:
    void drawChessPiece(int x, int y, int player) {
        if (player == -1) {
            setfillcolor(WHITE);
            printf("�׷�����һ����\n");
        }
        else {
            setfillcolor(BLACK);
            printf("�ڷ�����һ����\n");
        }
        fillcircle(x - x % 30 + 15, y - y % 30 + 15, 13);
    }

    void drawChessBoard() {
        loadimage(&background, "source/qipan.jpg", 480, 480);
        putimage(0, 0, &background);

        setlinecolor(BLACK);
        for (int x = 15; x < 480; x += 30) {
            line(x, 15, x, 465);
        }
        for (int y = 15; y < 480; y += 30) {
            line(15, y, 465, y);
        }

        setfillcolor(BLUE);
        fillcircle(15 + 3 * 30, 15 + 3 * 30, 3);
        fillcircle(15 + 3 * 30, 15 + 11 * 30, 3);
        fillcircle(15 + 11 * 30, 15 + 3 * 30, 3);
        fillcircle(15 + 7 * 30, 15 + 7 * 30, 3);
        fillcircle(15 + 11 * 30, 15 + 11 * 30, 3);
    }

    void showGameResult() {
        HWND hnd = GetHWnd();
        SetWindowText(hnd, "������");

        int isok = 0;
        if (board.getOutcome() == 1) {
            isok = MessageBox(NULL, "�ڷ�Ӯ��", "�˾Ͷ��������ᣬ�ͱ���", MB_OKCANCEL);
        }
        else if (board.getOutcome() == -1) {
            isok = MessageBox(NULL, "�׷�Ӯ��", "��Ҫ��˵��ǰ����ô���øճ����Ա���", MB_OKCANCEL);
        }

        if (isok == IDOK || isok == IDCANCEL) {
            exit(0);
        }
    }

    void runGame() {
        initgraph(480, 480);
        drawChessBoard();
        settextstyle(40, 20, "����");
        setbkmode(TRANSPARENT);

        ExMessage msg;
        while (1) {
            if (peekmessage(&msg, EX_MOUSE)) {
                switch (msg.message) {
                case WM_LBUTTONDOWN:
                    music.playClickSound();
                    if (board.placePiece(msg.x / 30, msg.y / 30)) {
                        drawChessPiece(msg.x, msg.y, board.getCurrentPlayer() * -1);
                    }
                    break;
                }
            }

            if (board.checkGameOver()) {
                outtextxy(180, 180, "�Ծֽ���");
                showGameResult();
                system("pause");
            }
        }
    }
};

// ���˵���
class MainMenu {
private:
    IMAGE background;
    MusicController music;
    int currentState; // 0:��ʼ����, 1:�˳�ȷ�Ͻ���

public:
    MainMenu() : currentState(0) {}

    void showStartScreen() {
        initgraph(600, 600);
        loadimage(&background, "source/chushi.jpg", 600, 600);
        putimage(0, 0, &background);
        settextstyle(40, 20, "С׭");

        outtextxy(140, 80, "��ӭ����������");
        outtextxy(200, 130, "������ͣ");
        outtextxy(200, 180, "��ʼ��Ϸ");
        outtextxy(200, 230, "�˳���Ϸ");
    }

    void showExitConfirm() {
        outtextxy(100, 300, "�����Ҫ�˳���Ϸ�𣿣�");
        outtextxy(50, 400, "�ٵ�");
        outtextxy(400, 400, "����˳�");
    }

    void handleStartScreenClick(int x, int y) {
        if (x >= 200 && x <= 360 && y >= 130 && y <= 170) {
            music.toggleBackgroundMusic();
        }
        else if (x >= 200 && x <= 360 && y >= 180 && y <= 220) {
            GameUI game;
            game.runGame();
        }
        else if (x >= 200 && x <= 360 && y >= 230 && y <= 270) {
            currentState = 1;
            music.playExitMusic();
            showExitConfirm();
        }
    }

    void handleExitConfirmClick(int x, int y) {
        if (x >= 50 && x <= 130 && y >= 400 && y <= 440) {
            currentState = 0;
            system("exit");
        }
        else if (x >= 400 && x <= 560 && y >= 400 && y <= 440) {
            exit(0);
        }
    }

    void run() {
        showStartScreen();
        MOUSEMSG msg = { 0 };

        while (1) {
            msg = GetMouseMsg();
            switch (msg.uMsg) {
            case WM_LBUTTONDOWN:
                music.playClickSound();
                if (currentState == 0) {
                    handleStartScreenClick(msg.x, msg.y);
                }
                else {
                    handleExitConfirmClick(msg.x, msg.y);
                }
                break;
            }
        }
    }
};

// ����������
class StartupScreen {
private:
    IMAGE background;
    MusicController music;

public:
    void show() {
        music.playStartMusic();
        printf("���\"������\"����������Ϸ\n");
        initgraph(1352, 739);
        loadimage(&background, "source/qidong.jpg", 1352, 739);
        putimage(0, 0, &background);
    }

    void run() {
        MOUSEMSG msg = { 0 };
        while (1) {
            msg = GetMouseMsg();
            switch (msg.uMsg) {
            case WM_LBUTTONDOWN:
                if (msg.x >= 450 && msg.x <= 880 && msg.y >= 260 && msg.y <= 390) {
                    music.closeStartMusic();
                    closegraph();
                    MainMenu menu;
                    menu.run();
                }
                break;
            }
        }
    }
};

int main() {
    StartupScreen startup;
    startup.show();
    startup.run();
    return 0;
}