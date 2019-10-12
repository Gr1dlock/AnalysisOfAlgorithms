def standard_multiply(a, b):
    m = len(a)
    n = len(b)
    q = len(b[0])
    if len(a[0]) != n:
        return None
    c = [[0 for i in range(q)] for j in range(m)]
    for i in range(m):
        for j in range(q):
            for k in range(n):
                c[i][j] = c[i][j] + a[i][k] * b[k][j]
    return c


def vinograd_multiply(a, b):
    m = len(a)
    n = len(b)
    q = len(b[0])
    if len(a[0]) != n:
        return None
    # Part I
    r = n // 2
    mul_a = [0] * m
    for i in range(m):
        for j in range(r):
            mul_a[i] = mul_a[i] + a[i][j * 2] * a[i][j * 2 + 1]

    # Part II
    mul_b = [0] * q
    for i in range(q):
        for j in range(r):
            mul_b[i] = mul_b[i] + b[j * 2][i] * b[j * 2 + 1][i]

    # Part III
    c = [[0 for i in range(q)] for j in range(m)]
    for i in range(m):
        for j in range(q):
            c[i][j] = -mul_a[i] - mul_b[j]
            for k in range(r):
                c[i][j] = c[i][j] + (a[i][2 * k] + b[2 * k + 1][j]) \
                          * (a[i][2 * k + 1] + b[2 * k][j])

    # Part IV
    if n % 2 == 1:
        for i in range(m):
            for j in range(q):
                c[i][j] = c[i][j] + a[i][n - 1] * b[n - 1][j]
    return c


def optimized_vinograd_multiply(a, b):
    m = len(a)
    n = len(b)
    q = len(b[0])
    if len(a[0]) != n:
        return None

    # Part I
    mul_a = [0] * m
    for i in range(m):
        for j in range(0, n - 1, 2):  # Optimization for n // 2
            mul_a[i] -= a[i][j] * a[i][j + 1]  # Optimization for negative and +=

    # Part II
    mul_b = [0] * q
    for i in range(q):
        for j in range(0, n - 1, 2):  # Optimization for n // 2
            mul_b[i] -= b[j][i] * b[j + 1][i]  # Optimization for negative and +=

    last = n - 1  # Optimization for odd numbers
    flag = n % 2 == 1
    # Part III
    c = [[0 for i in range(q)] for j in range(m)]
    for i in range(m):
        for j in range(q):
            tmp = mul_a[i] + mul_b[j]  # Optimization for buffer
            for k in range(0, n - 1, 2):  # Optimization for n // 2
                tmp += (a[i][k] + b[k + 1][j]) \
                       * (a[i][k + 1] + b[k][j])  # Optimization for +=
            if flag:  # Optimization for odd numbers
                tmp += a[i][last] * b[last][j]
            c[i][j] = tmp

    return c
