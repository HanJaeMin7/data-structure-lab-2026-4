import sys
from collections import deque

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    """
    def를 이용하여 count_stages를 정의합니다.   
    행 개수를 N, 열 개수를 M으로 저장합니다.
    방문 여부를 저장하는 visited 리스트를 만듭니다. 
    N개의 행과 M개의 열을 가지는 2차원 리스트를 만들고 False로 초기화합니다. 
    row를 visited에 추가합니다.
    무대의 개수를 저장하는 answer 변수를 0으로 초기화 합니다.
    for문을 이용해서 모든 원소를 순회합니다. 
    if문을 이용해서 현재 값이 0이고 방문하지 않은 경우에만 새로운 무대를 발견한 것으로 간주합니다. 
    BFS를 사용하기 위해 queue를 만들고 시작 좌표를 queue에 추가합니다. 그리고 방문여부를 True로 표시합니다.
    while문을 이용해서 queue가 빌 때까지 반복합니다. 
    queue에서 가장 먼저 들어온 좌표를 꺼내서 r,c에 저장합니다.
    r,c에서 상하좌우 좌표를 하나씩 계산하여 nr, nc에 저장합니다.
    if문을 이용해서 nr, nc가 콘서트 공간의 범위 내에 있는지 확인합니다.
    if문을 이용해서 nr, nc의 값이 0이고 방문하지 않은 경우에만 방문여부를 True로 표시하고 queue에 추가합니다.
    다음으로 queue에 저장된 한 좌표를 꺼내서 상하좌우를 순회하고 새 좌표를 queue에 계속추가하며 BFS를 반복합니다.
    하나의 콘서트 공간을 모두 탐색하면 벽(1)과 방문한 좌표로 인한 제한때문에 더 이상 queue에 추가할 좌표가 없어 queue가 비게 되면 while문이 종료되고 answer에 1을 더합니다.
    모든 좌표를 순회할 때까지 이 과정을 반복하고 최종적으로 answer에 콘서트 공간에 있는 무대의 개수가 저장됩니다. 
    """
    N = len(concerts)
    M = len(concerts[0])
    visited=[]
    for i in range(N):
        row = []
        for j in range(M):
            row.append(False)
        visited.append(row)
    answer = 0
    for i in range(N):
        for j in range(M):
            if concerts[i][j]==0 and not visited[i][j]:
                queue = deque()
                queue.append((i,j))
                visited[i][j]=True
                while queue:
                    r,c = queue.popleft()
                    for nr, nc in [(r-1,c),(r+1,c),(r,c-1),(r,c+1)]:
                        if 0 <= nr < N and 0 <= nc < M:
                            if concerts[nr][nc]==0 and not visited[nr][nc]:
                                visited[nr][nc]=True
                                queue.append((nr,nc))
                answer+=1
    # TODO : 콘서트 공간에서 무대의 개수를 계산해 반환해주는 함수를 작성해주세요.

    return answer

print(count_stages(concerts))
