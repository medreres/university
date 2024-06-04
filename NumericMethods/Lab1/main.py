from math import sqrt

# The function is x^3 - x^2 + 2
def func( x ):
	return x**5 - 3 * (x ** 2) + 1

# Derivative of the above function 
# which is 3*x^x - 2*x
def derivFunc( x ):
	return 5 * (x ** 4) - 6 * x

def funcConverted(x):
    return (3 * (x ** 2) - 1) ** (1 / 5)

# Function to find the root
def newtonRaphson( x ):
    x0 = x;
    
    step = 0
    
    deriv_x0 = derivFunc(x0)
    
    while True:
       step = step + 1
       
    #    Newton method
       h = func(x0) / derivFunc(x0) 
       
    #  Newton Raphson
    #    h = func(x0) / deriv_x0 
       x1 = x0 - h
       
       if (abs(x1 - x0) < eps):
           break
       
       x0 = x1
       
       
    print("Number of steps: ", step)
    return x1

def fixedPoint(x):
    x0 = x;
    
    while True:
        x1 = funcConverted(x0)
        
        
        if abs(x1 - x0) < eps:
            return x1
        
        x0 = x1
    
    return None
       
# Driver program to test above
initialValues = [-0.6,0.6,1.3]
eps = 10 ** -4

for initialValue in initialValues:
    # res = newtonRaphson(initialValue)
    # print("Newton-Raphson ", res)
    
    res = fixedPoint(initialValue)
    print("Fixed point iteration ", res)

