#include "Location2D.h"
#include <stack>
#include <deque>
#include <cstdio>
#include <queue>
using namespace std;

const int MAZE_SIZE = 6;

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1'},
    {'e','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};

bool isValidLoc(int r, int c) {
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)
        return false;

    return (map[r][c] == '0' ||
        map[r][c] == 'x' ||
        map[r][c] == 'e');
}

int main() {

    int ds_num;

    printf("DFS 데이터 구조 라이브러리 선택 : 1) stack, 2) deque\n");
    scanf_s("%d", &ds_num);

    switch (ds_num) {

    case 1: {

        stack<Location2D> locStack;
        locStack.push(Location2D(1, 0));
        while (!locStack.empty()) {

            Location2D here = locStack.top();
            locStack.pop();

            int r = here.row;
            int c = here.col;

            printf("(%d,%d)", r, c);

            if (map[r][c] == 'x') {
                printf("미로 탐색 성공\n");
                break;
            }

            map[r][c] = '.';

            if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
        }

        break;
    }

    case 2: {

        deque<Location2D> locDeque;

        locDeque.push_front(Location2D(1, 0));

        while (!locDeque.empty()) {

            Location2D here = locDeque.front();
            locDeque.pop_front();

            int r = here.row;
            int c = here.col;

            printf("(%d,%d)", r, c);

            if (map[r][c] == 'x') {
                printf("미로 탐색 성공\n");
                break;
            }

            map[r][c] = '.';

            if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
        }

        break;
    }

    }
    printf("\n===== BFS 시작 =====\n");

    char bfsMap[MAZE_SIZE][MAZE_SIZE];

    char origin[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1'},
        {'e','0','1','0','0','1'},
        {'1','0','0','0','1','1'},
        {'1','0','1','0','1','1'},
        {'1','0','1','0','0','x'},
        {'1','1','1','1','1','1'}
    };

    for (int i = 0; i < MAZE_SIZE; i++)
        for (int j = 0; j < MAZE_SIZE; j++)
            bfsMap[i][j] = origin[i][j];

    queue<Location2D> q;

    q.push(Location2D(1, 0));

    while (!q.empty()) {

        Location2D here = q.front();
        q.pop();

        int r = here.row;
        int c = here.col;

        printf("(%d,%d)", r, c);

        if (bfsMap[r][c] == 'x') {
            printf("BFS 탐색 성공\n");
            break;
        }

        bfsMap[r][c] = '.';

        if (r - 1 >= 0 && (bfsMap[r - 1][c] == '0' || bfsMap[r - 1][c] == 'x'))
            q.push(Location2D(r - 1, c));
        if (r + 1 < MAZE_SIZE && (bfsMap[r + 1][c] == '0' || bfsMap[r + 1][c] == 'x'))
            q.push(Location2D(r + 1, c));
        if (c - 1 >= 0 && (bfsMap[r][c - 1] == '0' || bfsMap[r][c - 1] == 'x'))
            q.push(Location2D(r, c - 1));
        if (c + 1 < MAZE_SIZE && (bfsMap[r][c + 1] == '0' || bfsMap[r][c + 1] == 'x'))
            q.push(Location2D(r, c + 1));
    }
    return 0;
}