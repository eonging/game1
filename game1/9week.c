#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float m[3][3]; // 3x3 ���
} Matrix3x3;

typedef struct {
    float x, y, w; // ���� ǥ���ϴ� ����
} vec3;

// 3x3 ��� �ʱ�ȭ
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

// �̵� ��� ����
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    return mat;
}

// ��� ����
Matrix3x3 multiplyMatrices(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// vec3 ���� ��ȯ
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = a.x * b.m[0][0] + a.y * b.m[0][1] + b.m[0][2];
    result.y = a.x * b.m[1][0] + a.y * b.m[1][1] + b.m[1][2];
    result.w = 1.0f; // w�� �׻� 1�� ����
    return result;
}

// �ܼ� ȭ�� �����
void clearScreen() {
    system("cls");
}

// ȭ�� �׸���
void draw(int angle) {
    clearScreen();

    // �߽��� P ��ġ
    int pX = WIDTH / 2;
    int pY = HEIGHT / 2;

    // O�� Q�� �ʱ� ��ġ
    vec3 o = { 0.0f, 0.0f, 1.0f }; // O�� ��ġ�� vec3�� ǥ��
    vec3 q = { 0.0f, 0.0f, 1.0f }; // Q�� ��ġ�� vec3�� ǥ��

    // O�� ���� �̵� �� ȸ�� ��� ����
    Matrix3x3 translationDistO = createTranslationMatrix(0, 3);  // O�� �߽ɿ��� �Ÿ� 3��ŭ ������
    Matrix3x3 rotationO = createRotationMatrix(angle);            // O�� ȸ�� ����
    Matrix3x3 translationToP = createTranslationMatrix(pX, pY);

    Matrix3x3 combinedO = multiplyMatrices(rotationO, translationDistO);
    combinedO = multiplyMatrices(translationToP, combinedO);
    o = Mul(o, combinedO); // O�� ��ġ ��ȯ

    // Q�� ���� �̵� �� ȸ�� ��� ���� (������ O���� ������ ����, �Ÿ� 5)
    Matrix3x3 translationDistQ = createTranslationMatrix(0, 5);
    Matrix3x3 rotationQ = createRotationMatrix(angle * 2);         // Q�� �� ���� �ӵ��� ȸ��
    Matrix3x3 combinedQ = multiplyMatrices(rotationQ, translationDistQ);
    combinedQ = multiplyMatrices(translationToP, combinedQ);
    q = Mul(q, combinedQ); // Q�� ��ġ ��ȯ

    // ȭ�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("P"); // �߽��� P
            }
            else if ((int)o.x == x && (int)o.y == y) {
                printf("O"); // ȸ���ϴ� �� O
            }
            else if ((int)q.x == x && (int)q.y == y) {
                printf("Q"); // ȸ���ϴ� �� Q
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    for (int angle = 0; angle < 360; angle += 5) {
        draw(angle);
        Sleep(100);
    }
    return 0;
}
