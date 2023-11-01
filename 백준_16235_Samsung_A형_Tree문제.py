# %%
import numpy as np


def Spring(Tree_Map, Power, Dead_Tree):
    for i in range(len(Tree_Map)):
        for j in range(len(Tree_Map)):
            Age_Sum = sum(Tree_Map[i][j])
            Tree_Map[i][j] = sorted(Tree_Map[i][j])
            for k in reversed(range(len(Tree_Map[i][j]))):
                if Age_Sum > Power[i][j]:
                    Age_Sum = Age_Sum - Tree_Map[i][j][k]
                    Dead_Tree.append({'x': i,'y':j,'Value':Tree_Map[i][j][k]})
                    del Tree_Map[i][j][k]
                if Age_Sum<0:
                    Age_Sum = 0
            Tree_Map[i][j] = list(map(lambda x: x+1, Tree_Map[i][j]))
            Power[i][j] = Power[i][j] - Age_Sum

def Summer(Tree_Map, Power, Dead_Tree):
    for i in range(len(Dead_Tree)):
        Power[Dead_Tree[i]['x'], Dead_Tree[i]['y']] = Power[Dead_Tree[i]['x'], Dead_Tree[i]['y']] + (Dead_Tree[i]['Value'] // 2)
    Dead_Tree = []

def Fall(Tree_Map):
    for i in range(len(Tree_Map)):
        for j in range(len(Tree_Map)):
            Count_5_Age = 0
            for k in range(len(Tree_Map[i][j])):
                if Tree_Map[i][j][k] % 5 == 0:
                    Count_5_Age = Count_5_Age + 1
            if Count_5_Age > 0:
                x = i-1
                for x_idx in range(3):
                    y = j-1
                    for y_idx in range(3):
                        if x_idx == 1 and y_idx == 1:
                            pass
                        elif x>=0 and y >= 0 and x <= len(Tree_Map)-1 and y <=  len(Tree_Map)-1:
                            for Tree_idx in range(Count_5_Age):
                                Tree_Map[x][y].append(1)
                        y = y+1
                    x = x+1

                # if i>0:
                #     Tree_Map[i-1][j][k].append(1)
                # if j>0:
                #     Tree_Map[i][j-1][k].append(1)
                # if i< len(Tree_Map)-1:
                #     Tree_Map[i][j-1][k].append(1)
                # if j< len(Tree_Map)


def Winter(Power, A):
    Power = Power + A
    return Power
#input #1
N, M, K = map(int, input().split())

Tree_Map = [[[]for col in range(N)] for row in range(N)]
Power = np.full((N,N),5)
A = np.zeros((N,N))

#input #2
for i in range(N):
    A_input = input().split()
    for j in range(N):
        A[i][j] = int(A_input[j])

#input #3
for i in range(M):
    x,y,z = map(int, input().split())
    Tree_Map[x-1][y-1].append(z)
    
#Calculate
Dead_Tree = []
for i in range(K):
    Spring(Tree_Map, Power, Dead_Tree)
    Summer(Tree_Map, Power, Dead_Tree)
    Fall(Tree_Map)
    Power = Winter(Power, A)
    test = 'test'
    #print(Tree_Map)

result_ = 0
for Tree_Map_row in Tree_Map:
    for Tree_Map_idx in Tree_Map_row:
        result_ = result_ + len(Tree_Map_idx)

# %%
a = print(input())

# %%
a = input().split()
# %%
import numpy as np
a = np.full((5,5),'A')
# %%
a = [[[]for col in range(3)] for row in range(4)]
# %%
a,b,c = map(int, input().split())
# %%
a = [3,2,1]
a = sorted(a)
# %%
a = [[[1,2,3],[4,5,6]],[[1,2,3],[1,2,3]]]
# %%
result_= 0
for i in a:
    for j in i:
        result_ = result_ + sum(j)
# %%
a = sum(1)
# %%
len(a)
# %%
len(a[0][0]>1)

# %%

# %%
3 //2
# %%
list(reversed(range(len([1,2,3]))))
# %%
a = [1,1,1]
a = a
# %%
a = list(map(lambda x: x+1, a))
# %%
A+Power+Power
# %%
aa = np.ones((1,1))
def AA(aa):
    print(aa.dd(np.ones((1,1))))
AA(aa)

# %%
aa = np.ones((2,2))

# %%
aa[0][1] = 2
# %%
