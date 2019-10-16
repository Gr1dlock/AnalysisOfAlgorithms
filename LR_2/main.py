import multiplication
import random
import time


def random_matrix(m, n):
    matrix = [[random.randint(0, 100) for i in range(n)] for j in range(m)]
    return matrix


def print_matrix(matrix):
    if not matrix:
        print('Invalid matrix')
    else:
        for i in matrix:
            for j in i:
                print(j, end=' ')
            print()


def compare_time():
    for i in range(100, 1100, 100):
        stand_time = 0
        vinograd_time = 0
        optimized_time = 0
        a = random_matrix(i, i)
        b = random_matrix(i, i)
        for j in range(10):
            time_1 = time.process_time()
            multiplication.standard_multiply(a , b)
            time_2 = time.process_time()
            multiplication.vinograd_multiply(a, b)
            time_3 = time.process_time()
            multiplication.optimized_vinograd_multiply(a, b)
            time_4 = time.process_time()
            stand_time += time_2 - time_1
            vinograd_time += time_3 - time_2
            optimized_time += time_4 - time_3
        print(i, 'x', i, ' matrix')
        print('Standard time: {:.7f}'.format(stand_time / 10))
        print('Vinograd time: {:.7f}'.format(vinograd_time / 10))
        print('Optimized  time: {:.7f}'.format(optimized_time / 10))
        print()


    for i in range(101, 1101, 100):
        stand_time = 0
        vinograd_time = 0
        optimized_time = 0
        a = random_matrix(i, i)
        b = random_matrix(i, i)
        for j in range(10):
            time_1 = time.process_time()
            multiplication.standard_multiply(a , b)
            time_2 = time.process_time()
            multiplication.vinograd_multiply(a, b)
            time_3 = time.process_time()
            multiplication.optimized_vinograd_multiply(a, b)
            time_4 = time.process_time()
            stand_time += time_2 - time_1
            vinograd_time += time_3 - time_2
            optimized_time += time_4 - time_3
        print(i, 'x', i, ' matrix')
        print('Standard time: {:.7f}'.format(stand_time / 10))
        print('Vinograd time: {:.7f}'.format(vinograd_time / 10))
        print('Optimized  time: {:.7f}'.format(optimized_time / 10))
        print()


if __name__ == '__main__':
    A = [[2, 7], [1, 3]]
    B = [[-3, 7], [1, -2]]
    C = multiplication.standard_multiply(A, B)
    print_matrix(C)

