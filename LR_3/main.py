import sorting
import time
import random


def time_count():
    for i in range(100, 1100, 100):
        insertion_time = 0
        comb_time = 0
        quick_time = 0
        arr = [random.randint(0, 1000) for k in range(i)]
        for j in range(100):
            time_1 = time.perf_counter()
            res = sorting.insertion(arr)
            time_2 = time.perf_counter()
            res = sorting.comb(arr)
            time_3 = time.perf_counter()
            res = sorting.quick(arr)
            time_4 = time.perf_counter()
            insertion_time += time_2 - time_1
            comb_time += time_3 - time_2
            quick_time += time_4 - time_3
        print('Random array length: ', i)
        print('Insertion sort: {:7f}'.format(insertion_time / 100))
        print('Comb sort: {:7f}'.format(comb_time / 100))
        print('Quick sort: {:7f}'.format(quick_time / 100))
        print()

    for i in range(100, 1100, 100):
        insertion_time = 0
        comb_time = 0
        quick_time = 0
        arr = [k for k in range(i)]
        for j in range(100):
            time_1 = time.perf_counter()
            res = sorting.insertion(arr)
            time_2 = time.perf_counter()
            res = sorting.comb(arr)
            time_3 = time.perf_counter()
            res = sorting.quick(arr)
            time_4 = time.perf_counter()
            insertion_time += time_2 - time_1
            comb_time += time_3 - time_2
            quick_time += time_4 - time_3
        print('Sorted array length: ', i)
        print('Insertion sort: {:7f}'.format(insertion_time / 100))
        print('Comb sort: {:7f}'.format(comb_time / 100))
        print('Quick sort: {:7f}'.format(quick_time / 100))
        print()
    for i in range(100, 1100, 100):
        insertion_time = 0
        comb_time = 0
        quick_time = 0
        arr = [k for k in range(i, 0, -1)]
        for j in range(100):
            time_1 = time.perf_counter()
            res = sorting.insertion(arr)
            time_2 = time.perf_counter()
            res = sorting.comb(arr)
            time_3 = time.perf_counter()
            res = sorting.quick(arr)
            time_4 = time.perf_counter()
            insertion_time += time_2 - time_1
            comb_time += time_3 - time_2
            quick_time += time_4 - time_3
        print('Inverse array length: ', i)
        print('Insertion sort: {:7f}'.format(insertion_time / 100))
        print('Comb sort: {:7f}'.format(comb_time / 100))
        print('Quick sort: {:7f}'.format(quick_time / 100))
        print()


if __name__ == '__main__':
    arr = [1]
    res = sorting.insertion(arr)
    print(res)
    res = sorting.comb(arr)
    print(res)
    res = sorting.quick(arr)
    print(res)

