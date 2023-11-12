# %%
import sys
sys.stdin = open("sample_input (2).txt", "r")

from queue import PriorityQueue

T = int(input())

# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
   
    N, K = map(int, input().split())

    A = sorted([int(i) for i in input().split()])
    F = sorted([int(i) for i in input().split()], reverse=True)

    Score = PriorityQueue()
    for i in range(N):
        Score.put([A[i]* F[i]*(-1), i , {'A': A[i], 'F': F[i]}]) 
    i = 0
    while i < K:
        Max = Score.get()
        Max_Second = Score.get()
        Train = (Max[0] - Max_Second[0])*(-1) // Max[2]['F'] + 1
        Train = 1
        if Train < 1:
            Train = 1
        if Train > K-i:
            Train = K-i
             
        Max[2]['A'] = Max[2]['A'] - Train
        Max[0] = Max[2]['A'] * Max[2]['F'] *(-1)
        i = i + Train

        if Max_Second[0]*(-1) >= Max[0] *(-1):
            Train = (Max_Second[0] - Max[0])*(-1) // Max_Second[2]['F'] + 1
            Train = 1
            if Train < 1:
                Train = 1
            if Train > K-i:
                Train = K-i
                
            Max_Second[2]['A'] = Max_Second[2]['A'] - Train
            Max_Second[0] = Max_Second[2]['A'] * Max_Second[2]['F'] *(-1)
            i = i + Train
        Score.put(Max_Second)

        for _ in range(Score.qsize()):
            Target = Score.get()
            if Target[0]*(-1) >= Max[0] *(-1):
                Train = (Target[0] - Max[0])*(-1) // Target[2]['F'] + 1
                Train = 1
                if Train < 1:
                    Train = 1
                if Train > K-i:
                    Train = K-i
                    
                Target[2]['A'] = Target[2]['A'] - Train
                Target[0] = Target[2]['A'] * Target[2]['F'] *(-1)
                i = i + Train
            Score.put(Target)

        
        #Score.put(Max_Second)
        Score.put(Max)
        
    print(f"#{test_case} {Score.get()[0]*(-1)}")

# %%

# %%
# import sys
# sys.stdin = open("sample_input (2).txt", "r")
# T = int(input())
# # 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
# for test_case in range(1, T + 1):
   
#     N, K = map(int, input().split())

#     A = sorted([int(i) for i in input().split()])
#     F = sorted([int(i) for i in input().split()], reverse=True)

#     Score = [A[i]* F[i] for i in range(N)]
#     i = 0
#     while i < K:
#         Sorted_Score = sorted(Score, reverse=True)
#         Max_Index = Score.index(Sorted_Score[0])
#         Max_Second_Index = Score.index(Sorted_Score[1])
#         Train = (Score[Max_Index] - Score[Max_Second_Index]) // F[Max_Index] + 1
#         Train =1
#         if Train<1:
#             Train = 1
#         if Train > K-i:
#             Train = K-i
             
#         A[Max_Index] = A[Max_Index] - Train
#         i = i + Train
#         Score = [A[i]* F[i] for i in range(N)]
        
#     print(f"#{test_case} {max(Score)}")
# %%
# from queue import PriorityQueue
# S = PriorityQueue()
# S.put(1)
# S.put(2)
# S.put(3)
# print(S.get())
# # %%
