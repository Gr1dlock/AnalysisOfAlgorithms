def print_matrix(matrix):
    n, m = len(matrix), len(matrix[0])
    print('Matrix: ')
    for i in range(n):
        for j in range(m):
            print(matrix[i][j], end=' ')
        print()


def levenshtein_matrix(s1, s2, matrix_flag):
    n, m = len(s1), len(s2)
    current_row = range(n + 1)
    matrix = [current_row]
    for i in range(1, m + 1):
        current_row = [i] + [0] * n
        for j in range(1, n + 1):
            current_row[j] = matrix[i - 1][j - 1]
            if s1[j - 1] != s2[i - 1]:
                current_row[j] += 1
            current_row[j] = min(current_row[j], matrix[i-1][j] + 1,
                                 current_row[j - 1] + 1)
        matrix.append(current_row)
    if matrix_flag:
        print_matrix(matrix)
    return matrix[m][n]


def levenshtein_recursive(s1, s2):
    n, m = len(s1), len(s2)
    if n == 0 or m == 0:
        if n != 0:
            return n
        if m != 0:
            return m
        return 0
    change = 0
    if s1[-1] != s2[-1]:
        change += 1
    return min(levenshtein_recursive(s1[:n - 1], s2) + 1,
               levenshtein_recursive(s1, s2[:m - 1]) + 1,
               levenshtein_recursive(s1[:n - 1], s2[:m - 1])
               + change)


def damerau_levenshtein_matrix(s1, s2, matrix_flag):
    n, m = len(s1), len(s2)
    current_row = range(n + 1)
    matrix = [current_row]
    for i in range(1, m + 1):
        current_row = [i] + [0] * n
        for j in range(1, n + 1):
            current_row[j] = matrix[i - 1][j - 1]
            if s1[j - 1] != s2[i - 1]:
                current_row[j] += 1
            current_row[j] = min(current_row[j], matrix[i-1][j] + 1,
                                 current_row[j - 1] + 1)
            if i > 1 and j > 1 and s1[j - 1] == s2[i - 2] \
                    and s1[j - 2] == s2[i - 1]:
                current_row[j] = min(current_row[j],
                                     matrix[i - 2][j - 2] + 1)
        matrix.append(current_row)
    if matrix_flag:
        print_matrix(matrix)
    return matrix[m][n]


def damerau_levenshtein_recursive(s1, s2):
    n, m = len(s1), len(s2)
    if n == 0 or m == 0:
        if n != 0:
            return n
        if m != 0:
            return m
        return 0
    change = 0
    if s1[-1] != s2[-1]:
        change += 1
    if n > 1 and m > 1 and s1[-1] == s2[-2] and s1[-2] == s2[-1]:
        return min(damerau_levenshtein_recursive(s1[:n - 1], s2)
                   + 1,
                   damerau_levenshtein_recursive(s1, s2[:m - 1])
                   + 1,
                   damerau_levenshtein_recursive(s1[:n - 1],
                                                 s2[:m - 1])
                   + change,
                   damerau_levenshtein_recursive(s1[:n - 2],
                                                 s2[:m - 2]) + 1)
    else:
        return min(damerau_levenshtein_recursive(s1[:n - 1], s2)
                   + 1,
                   damerau_levenshtein_recursive(s1, s2[:m - 1])
                   + 1,
                   damerau_levenshtein_recursive(s1[:n - 1],
                                                 s2[:m - 1])
                   + change)
