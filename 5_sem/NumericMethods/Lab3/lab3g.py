import numpy as np
import math
import sympy
max_iterations = 2000
epsilon = 1e-6
def jacobi(x_v: list):
    n = len(x_v)
    x, y, z = sympy.symbols('x y z')
    y1 = sympy.sqrt((5 - 1.5*y**2 - z**2)/3)
    y2 = (-6*x*y*z + x - 3*z)/5
    y3 = 1/(5*x - y)
    eqs = [y1, y2, y3]
    x_v_s = [x, y, z]
    J = np.identity(n)
    for i in range(n):
        for j in range(n):
            J[i][j] = sympy.diff(eqs[i], x_v_s[j]).subs(x_v_s[0], x_v[0]).subs(x_v_s[1], x_v[1]).subs(x_v_s[2], x_v[2])
    return J

def msi(init):
    x, y, z = init
    for i in range(max_iterations):
        x_new = math.sqrt((5 - 1.5*y**2 - z**2)/3)
        y_new = (-6*x*y*z + x - 3*z)/5
        z_new = 1/(5*x - y)
        
        # Check for convergence
        a = np.array([x, y, z])
        b = np.array([x_new, y_new, z_new])
        
        if np.linalg.norm(b - a, ord=np.inf) < epsilon:
            break
        
        x, y, z = x_new, y_new, z_new
        
        # Print intermediate results
        print(f"Iteration {i + 1}: x = {x}, y = {y}, z = {z}")
    return np.array([x, y, z])


initial = [1.25, 0, 5]
#print('\n x = {}\n'.format(msi(initial)))
print(np.linalg.norm(jacobi(initial), ord=1))
#     print("Did not converge.")
if np.linalg.norm(jacobi(initial), ord=1)<1:
    print('\n x = {}\n'.format(msi(initial)) )
    x=1.28445716
    y=0.12975697
    z=0.15891864
    print(3*x**2+1.5*y**2+z**2-5)
    print(6*x*y*z-x+5*y+3*z-1e-6)
    print(5*x*z-y*z-1)
else:
    print(np.linalg.norm(jacobi(initial), ord=1))
    print("Did not converge.")

