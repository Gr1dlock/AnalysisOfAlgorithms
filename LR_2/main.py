import multiplication
import random
import time


def random_matrix(m, n):
    matrix = [[random.randint(0, 100) for i in range(n)] for j in range(m)]
    return matrix


def print_matrix(matrix):
    for i in matrix:
        for j in i:
            print(j, end=' ')
        print()


if __name__ == '__main__':
    for i in range(100, 1100, 100):
        stand_time = 0
        vinograd_time = 0
        optimized_time = 0
        a = random_matrix(i, i)
        b = random_matrix(i, i)
        for j in range(100):
            time_1 = time.perf_counter()
            multiplication.standard_multiply(a , b)
            time_2 = time.perf_counter()
            multiplication.vinograd_multiply(a, b)
            time_3 = time.perf_counter()
            multiplication.optimized_vinograd_multiply(a, b)
            time_4 = time.perf_counter()
            stand_time += time_2 - time_1
            vinograd_time += time_3 - time_2
            optimized_time += time_4 - time_3
        print(i, 'x', i, ' matrix')
        print('Standard time: {:.7f}'.format(stand_time / 100))
        print('Vinograd time: {:.7f}'.format(vinograd_time / 100))
        print('Optimized  time: {:.7f}'.format(optimized_time / 100))
        print()

    for i in range(101, 1101, 100):
        stand_time = 0
        vinograd_time = 0
        optimized_time = 0
        a = random_matrix(i, i)
        b = random_matrix(i, i)
        for j in range(100):
            time_1 = time.perf_counter()
            multiplication.standard_multiply(a , b)
            time_2 = time.perf_counter()
            multiplication.vinograd_multiply(a, b)
            time_3 = time.perf_counter()
            multiplication.optimized_vinograd_multiply(a, b)
            time_4 = time.perf_counter()
            stand_time += time_2 - time_1
            vinograd_time += time_3 - time_2
            optimized_time += time_4 - time_3
        print(i, 'x', i, ' matrix')
        print('Standard time: {:.7f}'.format(stand_time / 100))
        print('Vinograd time: {:.7f}'.format(vinograd_time / 100))
        print('Optimized  time: {:.7f}'.format(optimized_time / 100))
        print()


