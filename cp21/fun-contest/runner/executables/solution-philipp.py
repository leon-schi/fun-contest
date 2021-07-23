n, m = map(int, input().split())

adj = [[] for _ in range(n)]

in_deg = [0] * n
out_deg = [0] * n

for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    adj[a].append((b, i+1))
    in_deg[b] += 1
    out_deg[a] += 1

for v in range(n):
    if in_deg[v] != out_deg[v]:
        print("IMPOSSIBLE")
        exit()

ans = []
stack = [(0, -1)]

while stack:
    v, edge_id = stack[-1]
    if adj[v]:
        stack.append(adj[v].pop())
    else:
        stack.pop()
        ans.append(edge_id)

ans.pop()
if len(ans) < m:
    print("IMPOSSIBLE")
else:
    print(*ans[::-1])
