#include <stdio.h>
#include <conio.h> // Windows 환경에서 getch 사용을 위한 헤더파일
#include <stdlib.h>
#include <time.h>

// 로고 출력 함수
void DrawLogo() {
    printf(" ::::::::   ::::    ::::  ::::::::::: ::::    ::: :::    ::: ::::::::::: ::::::::::  ::::::::  \n");
    printf(":+:    :+:  +:+:+: :+:+:+     :+:     :+:+:   :+: :+:    :+:     :+:     :+:        :+:    :+: \n");
    printf("       +:+  +:+ +:+:+ +:+     +:+     :+:+:+  +:+ +:+    +:+     +:+     +:+        +:+        \n");
    printf("    +#++:   +#+  +:+  +#+     +#+     +#+ +:+ +#+ +#+    +:+     +#+     +#++:++#   +#++:++#++ \n");
    printf("       +#+  +#+       +#+     +#+     +#+  +#+#+# +#+    +#+     +#+     +#+               +#+ \n");
    printf("#+#    #+#  #+#       #+#     #+#     #+#   #+#+# #+#    #+#     #+#     #+#        #+#    #+# \n");
    printf(" ########   ###       ### ########### ###    ####  ########      ###     ##########  ########  \n");
}

// 부제 출력 함수
void DrawSubtitle() {
    printf("\n                                   3분까진 필요없어\n");
}

// 캐릭터 애니메이션 함수
void DrawCharacter(int position) {
    // 캐릭터의 위치에 따라 화면의 왼쪽 또는 오른쪽에 출력
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("。　　　　　　　 ＊\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　☆ ☆　°　。☆ ☆ 。\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("☆　　 ☆　 ☆　　 ☆\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("☆　　　∧☆∧　　　 ☆\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("｡☆　　(´･ω･)　 　 ☆\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　☆　　| 二⊃==○☆\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　＊☆　|　 |　　　　＊\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　。　☆(ノＵ　 。\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　　　　☆　 ※\n");
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("　　　　　☆　　°\n");
}

// 게임 시작 버튼 출력 함수
void DrawStartButton() {
    printf("\n[게임 시작] 버튼을 누르세요 (s 키)\n");
}

// 초기화 함수
void Initialize() {
    printf("게임 초기화 중...\n");
    DrawLogo(); // 로고 출력
    DrawSubtitle(); // 부제 출력
}

// 렌더링 함수
void Render(int characterPosition) {
    // 화면을 클리어하고 새로운 상태를 출력
    system("cls"); // Windows에서 화면 클리어
    DrawLogo(); // 로고 다시 출력
    DrawSubtitle(); // 부제 다시 출력
    DrawCharacter(characterPosition); // 캐릭터 출력
    DrawStartButton(); // 게임 시작 버튼 출력
}

// 업데이트 함수 (입력 처리 포함)
void Update() {
    if (_kbhit()) { // 키가 눌렸는지 확인
        char key = _getch(); // 키 입력을 받음
        printf("입력된 키: %c\n", key);

        // 키에 따른 동작 추가 가능
        if (key == 'q') {
            printf("게임 종료...\n");
            exit(0); // 'q'를 입력하면 게임 종료
        }
        else if (key == 's') {
            printf("게임 시작!\n");
            // 버튼을 누르면 문자열을 출력

        }
    }
}

// 메인 게임 루프
void GameLoop() {
    Initialize();

    clock_t start_time = clock(); // 현재 시간을 기록
    int direction = 1; // 1: 오른쪽, -1: 왼쪽
    int characterPosition = 0; // 캐릭터 위치
    int maxPosition = 20; // 최대 위치 (화면의 크기 조정 필요)

    while (1) {
        Update(); // Update는 계속 호출하여 키 입력을 처리
        // 현재 시간과 시작 시간의 차이를 확인하여 0.2초마다 렌더링
        if ((clock() - start_time) >= CLOCKS_PER_SEC / 5) {
            Render(characterPosition); // 캐릭터 위치로 렌더링

            // 캐릭터의 위치를 업데이트
            characterPosition += direction;
            if (characterPosition >= maxPosition || characterPosition <= 0) {
                direction *= -1; // 방향 변경
            }

            start_time = clock(); // 시간을 초기화하여 다음 렌더링 준비
        }
    }
}

int main() {
    GameLoop();
    return 0;
}