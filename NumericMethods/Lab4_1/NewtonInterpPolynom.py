from sympy import *
import math
import matplotlib.pyplot as plt
import time
X = [-1,0,1]
#Y = [1/5,1/4,1/5]
N = 3


def getNodes_chebyshev(a, b, n):
    X = []
    for i in range (n):
        X.append(((a+b)/2)+((b-a)/2)*math.cos(((2*i+1)*math.pi)/(2*(n+1))))
    return X

def Y_1(x, b):
    return 1/(b**2 + x**2)
    #return 3**x





def fin_diff():
    y = Y.copy()
    for i in range(N - 1):
        for j in range(len(y) - 1):
            y[j] = y[j + 1] - y[j]
        y.pop()
        print(f'd{i + 1}y: {y}')


def div_diff():
    for i, f in zip(range(N - 1), f_gen()):
        print(f'f{i + 1}: {f}')


def f_gen():
    f = Y.copy()
    for i in range(N - 1):
        for j in range(len(f) - 1):
            f[j] = (f[j + 1] - f[j]) / (X[j + 1 + i] - X[j])
        f.pop()
        yield f


def newton():
    n = Y[0]
    polynoms = []
    for j, f in zip(range(N - 1), f_gen()):
        a = 1
        for k in range(j + 1):
            a *= (symbols('x') - X[k])            
        n += f[0] * a
    polynoms.append(expand(n))
    return polynoms


if __name__ == '__main__':
    b = float(input("Ведіть b: "))
    Y = [Y_1(x, b) for x in X]  
    print(f'x: {X}')
    print(f'y: {Y}\n')
    print('Finite differences:')
    start_time = time.time_ns()
    fin_diff()
    end_time = time.time_ns()
    execution_time = end_time - start_time
    #print("Час виконання функції: {:.50f} секунд".format(execution_time))    
    print()
    print('Divided differences:')
    start_time = time.time_ns()
    div_diff()
    end_time = time.time_ns()
    execution_time = end_time - start_time
    #print("Час виконання функції: {:.50f} секунд".format(execution_time))   


    start_time = time.time()
    n_pol1 = newton()
    end_time = time.time()
    execution_time = end_time - start_time
    print("Час виконання функції: {:.6f} секунд".format(execution_time))    
    print('\nN1 =', n_pol1)
    
    X_values=getNodes_chebyshev(-1, 1, 3)    
    Y_values = [Y_1(x, b) for x in X_values]   
    print(X_values) 
    print(Y_values)
    X=X_values
    Y=Y_values
    n_pol2 = newton()
    print('\nN2 =', n_pol2)

    x_s = float(input("Ведіть x*: ")) 
    print("delta: ",abs(Y_1(x_s, b) - n_pol1[-1].subs(symbols('x'), x_s)))

    x_s = float(input("Ведіть x*: ")) 
    print("delta_Сhebyshev: ",abs(Y_1(x_s, b) - n_pol2[-1].subs(symbols('x'), x_s)))


    x_vals = [i/1000 for i in range(-1000, 1001)]  # This creates a range from -1 to 1 with a step of 0.001
    y_original = [Y_1(x_val, b) for x_val in x_vals]
    y_newton = [n_pol1[-1].subs(symbols('x'), x_val) for x_val in x_vals]
    y_newton_сhebyshev = [n_pol2[-1].subs(symbols('x'), x_val) for x_val in x_vals]
    plt.plot(x_vals, y_original, label='Original Y', color='blue')
    plt.plot(x_vals, y_newton, label='Newton Polynomial', color='g', linestyle='dashed')
    plt.plot(x_vals, y_newton_сhebyshev, label='Newton Polynomial_Chebyshev', color='r', linestyle='dashed')
    plt.scatter(X_values, [Y_1(x, b) for x in X_values], color='red')  # plot the nodes
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Original Function and Lagrange Polynomial')
    plt.legend()
    plt.grid(True)
    plt.xlim([-1.5, 1.5])
    plt.ylim([0, 10])
    plt.show()
   