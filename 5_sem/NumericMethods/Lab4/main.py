# cSpell:disable 
from typing import List
import copy
import time
import math


import sympy
import numpy
import numpy as np

import matplotlib.pyplot as plt



def func(x:float)-> float:
    return x**5 - 3*x**2-17*x+1

def chebyshev_zeros_first_kind(n):
    zeros = [math.cos((2 * k + 1) * math.pi / (2 * n)) for k in range(0, n)]
    return zeros


def lagrange_interpolation(interpolation_point: float, x_values: List[float], y_values: List[float], polynomial_degree: int) -> float:
    # Set interpolated value initially to zero
    yp = 0

    # Implementing Lagrange Interpolation
    for i in range(polynomial_degree):
        
        p = 1
        
        for j in range(polynomial_degree):
            if i != j:
                p = p * (interpolation_point - x_values[j])/(x_values[i] - x_values[j])
        
        yp = yp + p * y_values[i]    
    
    return yp

if __name__=="__main__":
    # Interval
    # it should have been [1,3]
    A = -3
    B = 3
    
    nodes_amount:int = int(input("Input the amount of nodes:"))
    polynomial_degree = nodes_amount-1
    
    if(nodes_amount<1):
        raise Exception("n must be bigger than 0")
    
    # рівновіддалені точки
    x_evenly_spaced = numpy.linspace(A,B,nodes_amount,endpoint=True)
    x_chebysh_zeroes = chebyshev_zeros_first_kind(nodes_amount)
    
    # знаходимо значення в заданих точках
    y_map_evenly_spaced = [func(x) for x in x_evenly_spaced]
    y_map_chebysh_zeroes = [func(x) for x in x_chebysh_zeroes]
    
    # оригінальний графік
    x_set = [i/100 for i in range(A * 100,B * 100 + 1)]
    y_set_original = [func(x) for x in x_set]
    
    # find values to graph
    # ці значення легко перевіряються підставивши початкові значення та звірити їх
    y_set_lagrange_evenly_spaced = [lagrange_interpolation(x, x_evenly_spaced, y_map_evenly_spaced, polynomial_degree) for x in x_set]
    y_set_lagrange_chebysh_zeroes = [lagrange_interpolation(x, x_chebysh_zeroes, y_map_chebysh_zeroes, polynomial_degree) for x in x_set]
    
    # find the interpolation point
    interpolation_point = float(input('Input an interpolation point:'))
    start = time.time()
    y_interpolated_evenly_spaced = lagrange_interpolation(interpolation_point, x_evenly_spaced,y_map_evenly_spaced,polynomial_degree)
    y_interpolated_chebysh_zeroes = lagrange_interpolation(interpolation_point, x_chebysh_zeroes, y_map_chebysh_zeroes, polynomial_degree)
    y_original = func(interpolation_point)
    end = time.time()
    print('y_interpolated_evenly_spaced: ',y_interpolated_evenly_spaced)
    print('y_interpolated_chebysh_zeroes: ',y_interpolated_chebysh_zeroes)
    print('y_original: ',y_original)
    
    print(f"Duration of Lagrange:{end-start:.10f}")
    
    # Чебиш ефективний лише за n > 6
    # plot config
    plt.plot(x_set, y_set_original, label='Original Y', color='blue')
    plt.plot(x_set, y_set_lagrange_evenly_spaced, label='Lagrange Polynomial Evenly Spaced', color='g', linestyle='dashed')
    plt.plot(x_set, y_set_lagrange_chebysh_zeroes, label='Lagrange Polynomial Chebysh Zeroes', color='red', linestyle='dotted')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.xlim([A,B])
    plt.show()
    



