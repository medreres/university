import math 
from sympy import *

N = 3
def Y(x, b):
    return 1/(b**2 + x**2)

def getNodes():
    return [-1,0,1]

def getNodes_chebyshev(a, b, n):
    X = []
    for i in range (n):
        X.append(((a+b)/2)+((b-a)/2)*math.cos(((2*i+1)*math.pi)/(2*(n+1))))
    return X

def w(j, X, n):
    result = 1
    x = symbols('x')
    for i in range(n):
        result *= (x - X[i])
    result /= x - X[j]
    return result


def lagrange(b, X, n):
    L = 0
    polynoms = []
    for j in range(n):
        L += w(j,X,n) / w(j,X,n).subs(symbols('x'), X[j]) * Y(X[j], b)
        polynoms.append(expand(L))
    return polynoms

if __name__== 'main':
    b = float(input("Ведіть b: ")) 

    X = getNodes()
    print(f'x (вузли): {X}')
    lag_pol = lagrange(b, X, N)
    print("L" + str(N - 1) + " = " + str(lag_pol[-1]))

    X = getNodes_chebyshev(-1,1,N)
    print(f'x (вузли)_Сhebyshev: {X}')
    lag_pol_сhebyshev = lagrange(b, X, N)
    print("L" + str(N - 1) + "_Сhebyshev = " + str(lag_pol_сhebyshev[-1]))

    
    x_s = float(input("Ведіть x*: ")) 
    print("delta: ",abs(Y(x_s, b) - lag_pol[-1].subs(symbols('x'), x_s)))

    x_s = float(input("Ведіть x*: ")) 
    print("delta_Сhebyshev: ",abs(Y(x_s, b) - lag_pol_сhebyshev[-1].subs(symbols('x'), x_s)))

    # Create a range of x values for plotting
    x_vals = [i/1000 for i in range(-1000, 1001)]  # This creates a range from -1 to 1 with a step of 0.001
    
    # Evaluate the original function Y and the Lagrange polynomial on x_vals
    y_original = [Y(x_val, b) for x_val in x_vals]
    y_lagrange = [lag_pol[-1].subs(symbols('x'), x_val) for x_val in x_vals]
    y_lagrange_сhebyshev = [lag_pol_сhebyshev[-1].subs(symbols('x'), x_val) for x_val in x_vals]
    # Plot the original function and the Lagrange polynomial
    import matplotlib.pyplot as plt
    plt.plot(x_vals, y_original, label='Original Y', color='blue')
    plt.plot(x_vals, y_lagrange, label='Lagrange Polynomial', color='g', linestyle='dashed')
    plt.plot(x_vals, y_lagrange_сhebyshev, label='Lagrange Polynomial_Chebyshev', color='r', linestyle='dashed')
    plt.scatter(X, [Y(x, b) for x in X], color='red')  # plot the nodes
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Original Function and Lagrange Polynomial')
    plt.legend()
    plt.grid(True)
    plt.xlim([-1.5, 1.5])
    plt.ylim([0, 10])
    plt.show()