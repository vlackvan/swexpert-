함수 안에 함수 정의 불가
union find 에서 union은 함수와 함수를 잇는 것
find에서 path compression 하려면 return parent[i] = find(parent[i]) -> 이후 find는 O(1)
무리 개수 = parent[i] == i 인 노드 개수