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

    Score = [A[i]* F[i] for i in range(N)]

    i = 0
    left = min(Score)
    right = max(Score)
    mid = (left + right) //2

    while i < K:
        screen = 0
        screen_idx = []


        for idx in range(N):
            if Score[idx] >= mid:
                screen_value = (Score[idx] - mid) // F[idx] + 1
                screen += screen_value
                screen_idx.append((idx,screen_value))

        if screen +i > K:
            left = mid
            mid = (left + right) //2
            if mid == left:
                for idx,value in screen_idx:
                    if i == K:
                        break

                    v = value
                    while(v):
                        if v +i <= K:
                            i += v
                            A[idx] -= v
                            Score[idx] = A[idx] * F[idx]
                            break
                        v -=1
        else:
            #right = mid
            i += screen
            for idx,value in screen_idx:
                A[idx] -= value
                Score[idx] = A[idx] * F[idx]
            left = min(Score)
            right = max(Score)
            mid = (left + right) //2
            #if right ==0:
            #    break

        
    print(f"#{test_case} {max(Score)}")

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
