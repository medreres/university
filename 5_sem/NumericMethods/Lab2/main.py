import numpy as np
from typing import List

def is_diagonally_dominant(A: List[List[int]]):
    matrix_size = len(A)
    
    for index in range(0,matrix_size):
        row = A[index]
        
        dominator = row[index] # get the diagonal element and ensure it's greater then all the others
        
        left_part = row[:index]
        right_part = row[index+1:]
        
        left_absolute_sum = abs(sum([abs(element) for element in left_part]))
        right_absolute_sum = abs(sum([abs(element) for element in right_part]))
        
        total_absolute_sum = left_absolute_sum + right_absolute_sum
        
        if  dominator < total_absolute_sum:
            return False;
    
    return True    

# iterative method
# метод зейделя
def gauss_seidel(A, b, x0, tol=1e-6):
    
    if not is_diagonally_dominant(A):
        print('Matrix is not diagonally dominant')
        return
    
    size = len(b)
    
    x = x0.copy()

    # iterate either until max_iterations are met or precision is satisfied
    while True:
        for i in range(size):
            updated_x = b[i]
            
            for j in range(size):
                
                if (i == j):
                    continue
                
                updated_x -= A[i][j] * x[j]
            
            
            x[i] = updated_x / A[i][i]

        if np.all(np.abs(x - x0) < tol):
            return x  # Convergence reached

        x0 = x.copy()

    return x  # Return the approximate solution


# визначником матриці є квадрат добутку діагональних елементів трикутної матриці
def get_det(U):
    acc = 1
    for i in range(len(U)):
        acc = acc * U[i][i]
        
    return acc ** 2

def forward_substitution(L, b):
    n = len(L)
    y = np.zeros(n)

    for i in range(n):
        y[i] = (b[i] - sum(L[i, j] * y[j] for j in range(i))) / L[i, i]

    return y

def backward_substitution(U, y):
    n = len(U)
    x = np.zeros(n)

    for i in range(n - 1, -1, -1):
        x[i] = (y[i] - sum(U[i, j] * x[j] for j in range(i + 1, n))) / U[i, i]

    return x
   
def inverse_from_cholesky(L):
    n = len(L)
    identity = np.eye(n)
    inverse_A = np.zeros((n, n))

    for i in range(n):
        # Solve L^T * x = b for each column of the identity matrix
        column_of_inverse = np.linalg.solve(L.T, np.linalg.solve(L, identity[:, i]))
        inverse_A[:, i] = column_of_inverse

    return inverse_A

def matrix_infinity_norm(matrix):
    # Норма нескінченного порядку матриці
    norm = max(sum(abs(element) for element in row) for row in matrix)
    return norm

def matrix_frobenius_norm(matrix):
    # Друга норма матриці (норма Фробеніуса)
    # Для квадратної матриці 
    # A друга норма визначається як корінь з суми квадратів всіх її елементів.
    norm_squared = sum(sum(element**2 for element in row) for row in matrix)
    matrix_norm = norm_squared ** 0.5
    return matrix_norm
    
    
# direct method
# метод кв кореня
# 1. Знаходимо розклад матрицi A = sT DS
# 2. Знаходимо розв’язок системи рiвнянь sT Dy = b.
# 3. Iз системи Sx = y знайдемо x.
def root_square_method(A, b):
    size = len(A)
    
    # lower triangular Cholesky factor.
    L = np.zeros((size, size))
    
    # S - upper triangular
    # S_T - lower triangular
    
    # * нижня трикутна
    for i in range(size):
        for j in range(i+1):
            # * decomposition loop
            if i == j:
                sum_val = sum(L[i][k] ** 2 for k in range(j)) 
                L[i][j] = np.sqrt(A[i][i] - sum_val)
            else:
                sum_val = sum(L[i][k] * L[j][k] for k in range(j))
                L[i][j] = (1 / L[j][j] * (A[i][j] - sum_val))
   
    A_inv = inverse_from_cholesky(L)
    # першу норму чи другу. чи п=неперервну    
    # норма Чебишева
    print('Conditional number of matrix A using numpy', np.linalg.norm(A) * np.linalg.norm(A_inv))
    print('Conditional number of matrix A using own algorithm', matrix_frobenius_norm(A) * matrix_frobenius_norm(A_inv))
    print('Conditional number 1 of matrix A using own algorithm', matrix_infinity_norm(A) * matrix_infinity_norm(A_inv))
    
    print('A inverse using own algorithm\n', A_inv)
    print("A inverse using numpy\n", np.linalg.inv(A))
    
    print("Product of inverse and ordinary\n", np.around(np.matrix(A_inv) * np.matrix(A)))
    
    # * прямий хід
    y = forward_substitution(L,b)

    # * зворотній хід
    x = backward_substitution(L.transpose(), y)
        
    return x
    
# Equations matrix
A = np.array([[4, -1, 1, 0],
              [-1, 4, -1, 1],
              [1, -1, 4, -1],
              [0, 1, -1, 4]])


b = np.array([1, 1, 1, 1])

# Error
EPS = 0.0001

# To ensure there is no infinite loop
max_iter = 1000

solution_vector = gauss_seidel(A, b, np.zeros(len(A)))
solution_vector_2 = root_square_method(A,b)
print('Gaus seidel ',solution_vector)
print('root_sqkuare_method ',solution_vector_2)