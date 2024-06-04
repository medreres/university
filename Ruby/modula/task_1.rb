def calculate_f(a, b, c, x)
    ax = a.to_i
    bx = b.to_i
    cx = c.to_i
    if((ax & bx) | (ax & cx)) == 0
        x = x.to_i
    end
    if b != 0 && x < 0
        a * x**2 + b
    elsif b == 0 && x > 0
        (x-a)/(x-c)
    else
        x/c
    end
end
  
def main
    print "Enter the value of a: "
    a = gets.to_f
    print "Enter the value of b: "
    b = gets.to_f
    print "Enter the value of c: "
    c = gets.to_f
    print "Enter the value of Xstart: "
    x_start = gets.to_f
    print "Enter the value of Xend: "
    x_end = gets.to_f
    print "Enter the value of dX: "
    dx = gets.to_f
  
    puts "X\tF(X)"
  
    x = x_start
    while x <= x_end
      f_x = calculate_f(a, b, c, x)
      puts "#{x}\t#{f_x}"
      x += dx
    end
end
  
main
require 'minitest/autorun'
class TestFunc < Minitest::Test
    def test_func
        a = 2
        b = 4
        c = 8
        x_start = -2
        x_end = 2
        dx = 1
        x = x_start
        arr = [12, 6, 0, 0, 0]
        i = 0
        while x <= x_end
          f_x = calculate_f(a, b, c, x)
          assert_equal(arr[i], f_x)
          x += dx
          i = i + 1
        end
    end
end
  