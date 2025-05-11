#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <stdbool.h>
#include <stdio.h>

// 音乐控制类
class MusicController {
private:
    int musicPlaying;

public:
    MusicController() : musicPlaying(0) {}

    void playStartMusic() {
        mciSendString("seek qidong.mp3 to start", 0, 0, 0);
        mciSendString("play source/qidong.mp3", 0, 0, 0);
        printf("播放 启动的小曲\n");
    }

    void playExitMusic() {
        mciSendString("seek hahaha.mp3 to start", 0, 0, 0);
        mciSendString("play source/hahaha.mp3", 0, 0, 0);
        printf("播放 你干嘛 哈哈哎呦\n");
    }

    void toggleBackgroundMusic() {
        if (musicPlaying == 0) {
            mciSendString("open source/wind.mp3", 0, 0, 0);
            mciSendString("play source/wind.mp3", 0, 0, 0);
            musicPlaying = 1;
            printf("播放 让风告诉你\n");
        }
        else {
            mciSendString("pause source/wind.mp3", 0, 0, 0);
            musicPlaying = 0;
            printf("暂停 让风告诉你\n");
        }
    }

    void playClickSound() {
        mciSendString("seek click.mp3 to start", 0, 0, 0);
        mciSendString("play source/click.mp3", 0, 0, 0);
        printf("鸡叫\n");
    }

    void closeStartMusic() {
        mciSendString("close source/qidong.mp3", 0, 0, 0);
        printf("关闭 启动的小曲\n");
    }
};

// 游戏棋盘类
class ChessBoard {
private:
    int arr[15][15];
    int currentPlayer; // 1为黑方，-1为白方
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
        currentPlayer *= -1; // 切换玩家
        return true;
    }

    bool checkFiveInRow(int x, int y) const {
        if (arr[x][y] == 0) return false;

        // 检查水平方向
        if (x >= 2 && x <= 12 &&
            arr[x][y] == arr[x - 1][y] &&
            arr[x][y] == arr[x - 2][y] &&
            arr[x][y] == arr[x + 1][y] &&
            arr[x][y] == arr[x + 2][y])
            return true;

        // 检查垂直方向
        if (y >= 2 && y <= 12 &&
            arr[x][y] == arr[x][y - 1] &&
            arr[x][y] == arr[x][y - 2] &&
            arr[x][y] == arr[x][y + 1] &&
            arr[x][y] == arr[x][y + 2])
            return true;

        // 检查主对角线方向
        if (x >= 2 && y >= 2 && x <= 12 && y <= 12 &&
            arr[x][y] == arr[x - 1][y - 1] &&
            arr[x][y] == arr[x - 2][y - 2] &&
            arr[x][y] == arr[x + 1][y + 1] &&
            arr[x][y] == arr[x + 2][y + 2])
            return true;

        // 检查副对角线方向
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

// 游戏界面类
class GameUI {
private:
    IMAGE background;
    ChessBoard board;
    MusicController music;

public:
    void drawChessPiece(int x, int y, int player) {
        if (player == -1) {
            setfillcolor(WHITE);
            printf("白方下了一步棋\n");
        }
        else {
            setfillcolor(BLACK);
            printf("黑方下了一步棋\n");
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
        SetWindowText(hnd, "五子棋");

        int isok = 0;
        if (board.getOutcome() == 1) {
            isok = MessageBox(NULL, "黑方赢咯", "菜就多练，不会，就别玩", MB_OKCANCEL);
        }
        else if (board.getOutcome() == -1) {
            isok = MessageBox(NULL, "白方赢咯", "你要老说以前，怎么不拿刚出生对比呢", MB_OKCANCEL);
        }

        if (isok == IDOK || isok == IDCANCEL) {
            exit(0);
        }
    }

    void runGame() {
        initgraph(480, 480);
        drawChessBoard();
        settextstyle(40, 20, "隶书");
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
                outtextxy(180, 180, "对局结束");
                showGameResult();
                system("pause");
            }
        }
    }
};

// 主菜单类
class MainMenu {
private:
    IMAGE background;
    MusicController music;
    int currentState; // 0:开始界面, 1:退出确认界面

public:
    MainMenu() : currentState(0) {}

    void showStartScreen() {
        initgraph(600, 600);
        loadimage(&background, "source/chushi.jpg", 600, 600);
        putimage(0, 0, &background);
        settextstyle(40, 20, "小篆");

        outtextxy(140, 80, "欢迎来到五子棋");
        outtextxy(200, 130, "播放暂停");
        outtextxy(200, 180, "开始游戏");
        outtextxy(200, 230, "退出游戏");
    }

    void showExitConfirm() {
        outtextxy(100, 300, "你真的要退出游戏吗？？");
        outtextxy(50, 400, "假的");
        outtextxy(400, 400, "真的退出");
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

// 启动界面类
class StartupScreen {
private:
    IMAGE background;
    MusicController music;

public:
    void show() {
        music.playStartMusic();
        printf("点击\"五子棋\"即可启动游戏\n");
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