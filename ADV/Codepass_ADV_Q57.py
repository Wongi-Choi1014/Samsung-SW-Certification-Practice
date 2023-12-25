# %%
import copy

N = int(input())

Arr = [[0 for _ in range(N)]for _ in range(N)]

result = []

def set_queen(Arr, row, col, N):
    for i in range(1, N):
        if col-i >= 0:
            Arr[row][col-i] -= 1
        if col + i < N:
            Arr[row][col+i] -= 1

        if row-i>=0:
            Arr[row-i][col] -=1
            if col - i >= 0:
                #if Arr[row - i][col - i] <= 0:
                Arr[row - i][col - i] -= 1
            if col + i < N:
                #if Arr[row - i][col + i] <= 0:
                Arr[row - i][col + i] -= 1
        if row + i < N:
            Arr[row+i][col] -=1
            if col - i >= 0:
                #if Arr[row+i][col-i] <= 0:
                Arr[row+i][col-i] -= 1
            if col + i < N:
                #if Arr[row+i][col+i] <= 0:
                Arr[row+i][col+i] -= 1

def unset_queen(Arr, row, col, N):
    for i in range(1, N):
        if col-i >= 0:
            Arr[row][col-i] += 1
        if col + i < N:
            Arr[row][col+i] += 1

        if row-i>=0:
            Arr[row-i][col] +=1
            if col - i >= 0:
                #if Arr[row - i][col - i] <= 0:
                Arr[row - i][col - i] += 1
            if col + i < N:
                #if Arr[row - i][col + i] <= 0:
                Arr[row - i][col + i] += 1
        if row + i < N:
            Arr[row+i][col] +=1
            if col - i >= 0:
                #if Arr[row+i][col-i] <= 0:
                Arr[row+i][col-i] += 1
            if col + i < N:
                #if Arr[row+i][col+i] <= 0:
                Arr[row+i][col+i] += 1



def Back_Tracking(Arr, r, col, cnt, N, result):
    #for r in range(row, N):
    for c in range(N):
        #if row == r and c<col:
        #    continue
        #Arr_search = copy.deepcopy(Arr)

        if Arr[r][c] == 0:
            if cnt+1 == N:
                result.append(1)
                return
        #if cnt == N:
        #    return
            if c == N-1 and r == N-1:
                return
            #if c < N-1:
            #    Back_Tracking(Arr_search, r, c+1, cnt+1, N, result)
            #else:
            #    Back_Tracking(Arr_search, r+1 , 0, cnt+1, N, result)
            Arr[r][c] = 1
            set_queen(Arr, r, c, N)
            Back_Tracking(Arr, r+1, 0, cnt+1, N, result)
            unset_queen(Arr, r, c, N)
            Arr[r][c] = 0


Back_Tracking(Arr, 0, 0, 0, N, result)
print(len(result))


# %%
