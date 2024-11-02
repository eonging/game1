
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

typedef struct {
    float x, y, w; // 점을 표현하는 벡터
} vec3;

// 3x3 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// 회전 행렬 생성
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

// 행렬 곱셈
Matrix3x3 multiplyMatrices(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// vec3 점을 변환
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = a.x * b.m[0][0] + a.y * b.m[0][1] + b.m[0][2];
    result.y = a.x * b.m[1][0] + a.y * b.m[1][1] + b.m[1][2];
    result.w = 1.0f; // w는 항상 1로 설정
    return result;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(int angle) {
    clearScreen();

    // 중심점 P 위치
    int pX = WIDTH / 2;
    int pY = HEIGHT / 2;

    // O와 Q의 초기 위치
    vec3 o = { 0.0f, 0.0f, 1.0f }; // O의 위치를 vec3로 표현
    vec3 q = { 0.0f, 0.0f, 1.0f }; // Q의 위치를 vec3로 표현

    // O를 위한 이동 및 회전 행렬 생성
    Matrix3x3 translationDistO = createTranslationMatrix(0, 3);  // O는 중심에서 거리 3만큼 떨어짐
    Matrix3x3 rotationO = createRotationMatrix(angle);            // O의 회전 각도
    Matrix3x3 translationToP = createTranslationMatrix(pX, pY);

    Matrix3x3 combinedO = multiplyMatrices(rotationO, translationDistO);
    combinedO = multiplyMatrices(translationToP, combinedO);
    o = Mul(o, combinedO); // O의 위치 변환

    // Q를 위한 이동 및 회전 행렬 생성 (각도는 O보다 빠르게 증가, 거리 5)
    Matrix3x3 translationDistQ = createTranslationMatrix(0, 5);
    Matrix3x3 rotationQ = createRotationMatrix(angle * 2);         // Q는 더 빠른 속도로 회전
    Matrix3x3 combinedQ = multiplyMatrices(rotationQ, translationDistQ);
    combinedQ = multiplyMatrices(translationToP, combinedQ);
    q = Mul(q, combinedQ); // Q의 위치 변환

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("P"); // 중심점 P
            }
            else if ((int)o.x == x && (int)o.y == y) {
                printf("O"); // 회전하는 점 O
            }
            else if ((int)q.x == x && (int)q.y == y) {
                printf("Q"); // 회전하는 점 Q
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
