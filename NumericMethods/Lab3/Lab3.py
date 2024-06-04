import numpy as np
import sympy as sp
from matplotlib import pyplot

def jacobi(x_v: list):
    n = len(x_v)
    x, y = sp.symbols('x y')
    y1 = sp.tan(x * y + 0.1) - 2 * x ** 2
    y2 = 0.6 * x ** 2 + 2 * y ** 2 - 1
    eqs = [y1, y2]
    x_v_s = [x, y]
    J = np.identity(n)

    for i in range(n):
        for j in range(n):
            J[i][j] = sp.diff(eqs[i], x_v_s[j]).subs(x_v_s[0], x_v[0]).subs(x_v_s[1], x_v[1])
    return J


def solve_newton(init: tuple, eps, mod=False):
    x, y = init
    k = 0
    if not mod:
        while True:
            k += 1
            y1 = sp.tan(x * y + 0.1) - 2 * x ** 2
            y2 = 0.6 * x ** 2 + 2 * y ** 2 - 1
            J = jacobi([x, y])
            x_sol = np.array([x, y]) - np.dot(np.linalg.inv(J), np.array([y1, y2]))
            if abs(x_sol[0] - x) < eps:
                break
            x, y = x_sol[0], x_sol[1]
    else:
        J = jacobi([x, y])
        while True:
            k += 1
            y1 = sp.tan(x * y + 0.1) - 2 * x ** 2
            y2 = 0.6 * x ** 2 + 2 * y ** 2 - 1
            x_sol = np.array([x, y]) - np.dot(np.linalg.inv(J), np.array([y1, y2]))
            if abs(x_sol[0] - x) < eps:
                break
            x, y = x_sol[0], x_sol[1]
    return x_sol, k


def solve_msi(init: tuple, end: tuple, eps):
    n = len(init)
    y1 = lambda x, y: sp.tan(x * y + 0.1) - 2 * x ** 2
    y2 = lambda x, y: 0.6 * x ** 2 + 2 * y ** 2 - 1
    f_v = [y1, y2]
    x_sol = [0, 0]
    a = init
    x_k = end
    k = 0
    while True:
        k += 1
        for i in range(n):
            x_sol[i] = x_k[i] - f_v[i](x_k[0], x_k[1]) * (a[i] - x_k[i]) / (f_v[i](a[0], a[1]) - f_v[i](x_k[0], x_k[1]))
        if abs(x_sol[0] - x_k[0]) < eps:
            break
        x_k = x_sol.copy()
    return x_sol, k






def main():
    

    eps = 1e-6
    

    newton = solve_newton((0.3, 0.4), eps)
    print('\nNewton:\n x = {}\n k = {}'.format(newton[0], newton[1]))  # ------------- 7

    mod_newton = solve_newton((0.3, 0.4), eps, True)
    print('Modified Newton:\n x = {}\n k = {}'.format(mod_newton[0], mod_newton[1]))  # -- 8

    msi = solve_msi((0.5, 0.6), (0.1, 0.4), eps)
    print('MSI:\n x = {}\n k = {}'.format(msi[0], msi[1]))  # ----------- 6


if __name__ == '__main__':
    main()