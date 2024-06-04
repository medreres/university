#Lab3_2

A = true
B = true
C = false
$X = 12
Y = 3
Z = -2

P = false

def bool_to_int(bool)
    return bool ? 1 : 0
end

#Task 1
def taskA(a, b)
  !(a or b) and (a and !b)
end

def taskB(a, b, c, x, y, z)
  bool_to_int(z != y) <= bool_to_int(6 >= y) and a or b and c and (x >= 1.5)
end

def taskC(x, y, z)
  (8-x*2 <= z) and (x**2 >= y**2) or (z >= 15)
end

def taskD(x, y, z)
  (x > 0) and (y < 0) or z >= (x*y + (-y/x)) -z * (-2)
end

def taskG(a, b, c)
  !(a or b and !(c or (!a and b)))
end

def taskH(x, y)
  (x**2 + y**2) >= 1 or (x >= 0) or (y >= 0)
end

def taskI(a, b, c)
  (a and (c and b != b or a) or c) and b
end

#Task2
def task2(x, p)
  ((Math.log(x) <= x) and not p and (Math.sqrt(x) > x*x) or (2*x == x))
end

#Task 1 results
puts "A: #{taskA(A, B)}"
puts "B: #{taskB(A, B, C, $X, Y, Z)}"
puts "C: #{taskC($X, Y, Z)}"
puts "D: #{taskD($X, Y, Z)}"
puts "G: #{taskG(A, B, C)}"
puts "H: #{taskH($X, Y)}"
puts "I: #{taskI(A, B, C)}"

$X = 4
#Task 2 results
puts "task2: #{task2($X, P)}"