import math
from sympy import *
import time
import numpy
import matplotlib.pyplot as plt
def Y_1(x, b):
    return 1 / (b**2 + x**2)

def getNodes(a, b, parts):
    x_values = numpy.linspace(a, b, parts)
    return list(x_values)

def getNodes_chebyshev(a, b, n):
    X = [((a + b) / 2) + ((b - a) / 2) * math.cos(((2 * i + 1) * math.pi) / (2 * (n ))) for i in range(n)]
    return X

def fin_diff(Y, N):
    y = Y.copy()
    for i in range(N - 1):
        for j in range(len(y) - 1):
            y[j] = y[j + 1] - y[j]
        y.pop()
        print(f'd{i + 1}y: {y}')

def div_diff(Y, X, N):
    for i, f in zip(range(N - 1), f_gen(Y, X)):
        print(f'f{i + 1}: {f}')

def f_gen(Y, X):
    f = Y.copy()
    for i in range(len(Y) - 1):
        for j in range(len(f) - 1):
            f[j] = (f[j + 1] - f[j]) / (X[j + 1 + i] - X[j])
        f.pop()
        yield f

def newton(Y, X, N):
    n = Y[0]
    for j, f in zip(range(N - 1), f_gen(Y, X)):
        a = 1
        for k in range(j + 1):
            a *= (symbols('x') - X[k])
        n += f[0] * a
    return [expand(n)]

if __name__ == '__main__':
    b = float(input("Enter b: "))
    N = 50
    left, right = -1, 1
    X = getNodes(left, right, N)
    Y = [Y_1(x, b) for x in X]

    print(f'x (nodes): {X}')
    print(f'y: {Y}\n')

    print('Finite differences:')
    start_time = time.time_ns()
    fin_diff(Y, N)
    end_time = time.time_ns()
    print()

    print('Divided differences:')
    start_time = time.time_ns()
    div_diff(Y, X, N)
    end_time = time.time_ns()
    print()

    start_time = time.time()
    n_pol1 = newton(Y, X, N)
    end_time = time.time()
    print("Execution time: {:.6f} seconds".format(end_time - start_time))
    print('\nN1 =', n_pol1)

    X_values = getNodes_chebyshev(left, right, N)
    Y_values = [Y_1(x, b) for x in X_values]
    print(X_values)
    print(Y_values)
    X = X_values
    Y = Y_values
    n_pol2 = newton(Y, X, N)
    print('\nN2 =', n_pol2)

    x_s = float(input("Enter x*: "))
    print("delta: ", abs(Y_1(x_s, b) - n_pol1[-1].subs(symbols('x'), x_s)))

    x_s = float(input("Enter x*: "))
    print("delta_Chebyshev: ", abs(Y_1(x_s, b) - n_pol2[-1].subs(symbols('x'), x_s)))

    x_vals = [i/1000 for i in range(-1000, 1001)]
    y_original = [Y_1(x_val, b) for x_val in x_vals]
    y_newton = [n_pol1[-1].subs(symbols('x'), x_val) for x_val in x_vals]
    y_newton_chebyshev = [n_pol2[-1].subs(symbols('x'), x_val) for x_val in x_vals]

    plt.plot(x_vals, y_original, label='Original Y', color='blue')
    plt.plot(x_vals, y_newton, label='Newton Polynomial', color='g', linestyle='dashed')
    plt.plot(x_vals, y_newton_chebyshev, label='Newton Polynomial_Chebyshev', color='r', linestyle='dashed')
    plt.scatter(X_values, [Y_1(x, b) for x in X_values], color='red')  # plot the nodes
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Original Function and Newton Polynomial')
    plt.legend()
    plt.grid(True)
    plt.xlim([-1.5, 1.5])
    plt.ylim([0, 10])
    plt.show()