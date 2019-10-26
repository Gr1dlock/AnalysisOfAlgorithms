import random


COMB_COEF = 1.247330950103979


def insertion(arr):
    result = list(arr)
    for i in range(1, len(result)):
        j = i - 1
        key = result[i]
        while result[j] > key and j >= 0:
            result[j + 1] = result[j]
            j -= 1
        result[j + 1] = key
    return result


def comb(arr):
    result = list(arr)
    gap = len(result)
    while gap > 1:
        gap = max(1, int(gap / COMB_COEF))
        for i in range(len(result) - gap):
            j = i + gap
            if result[i] > result[j]:
                result[i], result[j] = result[j], result[i]
    return result


def quick(arr):
    if len(arr) <= 1:
        return arr
    else:
        q = random.choice(arr)
        left = []
        middle = []
        right = []
        for elem in arr:
            if elem < q:
                left.append(elem)
            elif elem > q:
                right.append(elem)
            else:
                middle.append(elem)
        return quick(left) + middle + quick(right)
