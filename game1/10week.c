#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 100
#define HEIGHT 30
#define RECT_WIDTH 11
#define RECT_HEIGHT 5
#define PI 3.14159265358979323846

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearConsole() {
    system("cls");
}

void drawRectangle(int x, int y) {
    for (int i = 0; i < RECT_HEIGHT; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < RECT_WIDTH; j++) {
            printf("��");
        }
    }
}

int main() {
    double angle = 0.0;
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    while (1) {
        clearConsole();
        // ȸ�� �߽� ��ǥ�� �������� ���� ���
        int offsetX = (int)(RECT_WIDTH / 2 * cos(angle) - RECT_HEIGHT / 2 * sin(angle));
        int offsetY = (int)(RECT_WIDTH / 2 * sin(angle) + RECT_HEIGHT / 2 * cos(angle));

        // �簢���� �»�� ��ǥ ���
        int rectX = centerX + offsetX - RECT_WIDTH / 2;
        int rectY = centerY + offsetY - RECT_HEIGHT / 2;

        drawRectangle(rectX, rectY);

        angle += (2 * PI) / (3 * 1000 / 50);  // 3�ʿ� 1���� ȸ�� (50ms���� ������Ʈ)
        if (angle >= 2 * PI) {
            angle -= 2 * PI;
        }
        Sleep(50);  // 50ms ����
    }

    return 0;
}
