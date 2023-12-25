# %%
M, N = map(int,input().split())

Box = []
for row in range(N):
    Box.append(list(map(int,input().split())))

day = 0
def BFS(Box, Q):
    global day, N, M
    
    while(len(Q)):
        for _ in range(len(Q)):
            row, col = Q.pop()
            if row-1 >= 0 and Box[row-1][col] == 0:
                Box[row-1][col] = 1
                Q.appendleft((row-1, col))
            
            if row+1 < N and Box[row+1][col] == 0:
                Box[row+1][col] = 1
                Q.appendleft((row+1, col))
            
            if col-1 >= 0 and Box[row][col-1] == 0:
                Box[row][col-1] = 1
                Q.appendleft((row, col-1))
            
            if col+1 < M and Box[row][col+1] == 0:
                Box[row][col+1] = 1
                Q.appendleft((row, col+1))
        if len(Q):
            day +=1


from collections import deque

Q = deque()
num_None = 0

#initial
for row in range(N):
    for col in range(M):
        if Box[row][col] == 1:
            Q.appendleft((row,col))
        if Box[row][col] == -1:
            num_None +=1

BFS(Box, Q)
# %%
Check_All_ideal = M*N
Check_All_real = 0
for row in range(N):
    #Check_All_ideal +=len(Box[row])
    Check_All_real +=sum(Box[row])

Check_All_ideal -= 2 * num_None
#Check_All_real -= num_None

if Check_All_ideal == Check_All_real:
    print(day)
else:
    print(-1)
# %%
