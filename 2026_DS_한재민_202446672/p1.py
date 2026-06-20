from collections import deque

A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}



def bfs(A):
    """
    def를 이용하여 bfs를 정의합니다.
    answer 리스트를 만들어서 방문한 노드를 넣어줍니다.
    visited 리스트를 만들어서 방문한 노드를 넣고 중복 방문을 막습니다.
    queue를 만들고 시작 노드인 0을 넣습니다.
    visited에 시작 노드 0을 방문 했다고 표시합니다.
    while문을 이용하여 queue가 빌 때까지 반복합니다.
    queue에서 맨 앞 노드를 꺼내서 v에 저장합니다. 1회차에서는 0을 v에 저장합니다.
    꺼낸 노드 v를 answer 리스트에 저장합니다.
    현재 정점에서 연결된 정점들을 순회하면서 방문여부를 확인합니다. 1회차에서 0과 연결된 정점인 1,2,3,을 순회합니다.
    방문하지 않은 정점이 있다면 visited에 추가하고 queue 뒤에 추가합니다.
    2회차에서 1이 v에 저장되고 1과 연결된 정점인 0,2,4,5를 순회합니다. 0과 2는 이미 방문했으므로 4와 5를 visited에 추가하고 queue 뒤에 추가합니다.
    3회차에서 2가 v에 저장되고 2와 연결된 정점인 0,1,6을 순회합니다. 0과 1은 이미 방문했으므로 6을 visited에 추가하고 queue 뒤에 추가합니다.
    이것을 반복하고 최종적으로 answer 리스트에 방문한 노드가 순서대로 저장됩니다.
    """
    answer = []
    visited = []  
    queue= deque([0])
    visited.append(0)
    while queue:
        v=queue.popleft()
        answer.append(v)

        for next in A[v]:
            if next not in visited:
                visited.append(next)
                queue.append(next)
    # TODO : BFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.

    return answer


def dfs(A):
    """
    def를 이용하여 dfs를 정의합니다.
    answer 리스트를 만들어서 방문한 노드를 넣어줍니다.
    visited 리스트를 만들어서 방문한 노드를 넣고 중복 방문을 막습니다
    stack을 만들고 시작 노드인 0을 넣습니다.
    visited에 시작 노드 0을 방문 했다고 표시합니다.
    while문을 이용하여 stack이 빌 때까지 반복합니다.
    stack에서 맨 뒤 노드를 꺼내서 v에 저장합니다. 1회차에서는 0을 v에 저장합니다.
    꺼낸 노드 v를 answer 리스트에 저장합니다.
    현재 정점인 0에 연결된 정점인 1,2,3을 역순으로 순회합니다. ([3,2,1] 순서로 순회)
    방문하지 않은 정점은 visited에 추가하고 stack에 추가합니다. (stack=[3,2,1] visited={0,1,2,3})
    stack은 LIFO 구조이므로 1회차에서 3이 stack에 가장 먼저 추가되고 1이 가장 나중에 추가됩니다.
    2회차에서 1이 v에 저장되고 1과 연결된 정점인 0,2,4,5를 역순으로 순회합니다. ([5,4,2,0] 순서로 순회)
    방문하지 않은 정점은 visited에 추가하고 stack에 추가합니다. (stack=[3,2,5,4] visited={0,1,2,3,4,5})
    3회차에서 4가 v에 저장되고 4와 연결된 정점인 1을 순회합니다. 1은 이미 방문했으므로 다음 정점으로 넘어갑니다.(stack=[3,2,5] visited={0,1,2,3,4,5})
    4회차에서 5가 v에 저장되고 5와 연결된 정점인 1을 순회합니다. 1은 이미 방문했으므로 다음 정점으로 넘어갑니다.(stack=[3,2] visited={0,1,2,3,4,5})
    5회차에서 2가 v에 저장되고 2와 연결된 정점인 0,1,6을 역순으로 순회합니다. ([6,1,0] 순서로 순회)
    방문하지 않은 정점은 visited에 추가하고 stack에 추가합니다. (stack=[3,6] visited={0,1,2,3,4,5,6})
    6회차에서 6이 v에 저장되고 6과 연결된 정점인 2를 순회합니다. 2는 이미 방문했으므로 다음 정점으로 넘어갑니다.(stack=[3] visited={0,1,2,3,4,5,6})
    7회차에서 3이 v에 저장되고 3과 연결된 정점인 0을 순회합니다. 0은 이미 방문했으므로 다음 정점으로 넘어갑니다.(stack=[] visited={0,1,2,3,4,5,6})
    stack이 비었으므로 while문을 종료하고 최종적으로 answer 리스트에 방문한 노드가 순서대로 저장됩니다.
    """
    answer = []
    visited = []
    stack = [0]
    visited.append(0)
    while stack:
        v = stack.pop()
        answer.append(v)
        for next in reversed(A[v]):
            if next not in visited:
                visited.append(next)
                stack.append(next)
    # TODO : DFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.

    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')

