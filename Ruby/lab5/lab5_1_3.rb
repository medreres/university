#var 3

PI = 3.14159265359
N_iterations = 10000

def function1(x)
  Math.sqrt(Math.exp(x) - 1)
end

def function2(x)
  Math.exp(x)*Math.sin(x)
end

def prm(a, b, n, dx=(b - a)/n)
  x = a + dx / 2
  sum = 0
  (1..n).each do
    y = yield(x)
    sum += dx * y
    x += dx
  end
  sum
end

def trp(a, b, n, dx=(b-a)/n)
  x = a + dx
  sum = dx * (yield(a) / 2 - yield(b) / 2)
  loop do
    y = yield(x)
    sum += dx * y
    x += dx
    break if x > b
  end
  sum
end


# var 3

def series_f(x, i)
  ((-1)**i)*((x**(2*i+1))/(2*i+1))
end

def sum(x, n)
  x_left_bound = 0.1
  x_right_bound = 1.0
  n_left_bound = 10
  n_right_bound = 58
  if x < x_left_bound || x > x_right_bound
    raise "X is out of bounds"
  end

  sum = 0
  if n >= n_left_bound && n <= n_right_bound
    (0..n).each do |i|
      sum += yield(x, i)
    end
  else
    e = 0.001
    fault = e + 1
    prev_sum = sum
    i = 0
    while i < 100 || fault > e
      sum += yield(x, i)

      i += 1
      fault = (prev_sum - sum).abs
      prev_sum = sum
    end
  end

  sum
end




puts "First integral:\n"
res = prm(0.0, 0.1, N_iterations) {|x| function1(x)}
puts "Rectangle method: ", res, "\n"
res = trp(0.0, 0.1, N_iterations) {|x| function1(x)}
puts "Trapezoid method: ", res, "\n" 

puts "First integral:\n"
res = prm(0.0, PI/2, N_iterations) {|x| function2(x)}
puts "Rectangle method: ", res, "\n"
res = trp(0.0, PI/2, N_iterations) {|x| function2(x)}
puts "Trapezoid method: ", res, "\n"


res = sum(0.4, 40) {|x, i| series_f(x, i)}
puts "Series sum (sum is finite): ", res, "\n"
res = sum(1.0, 1100) {|x, i| series_f(x, i)}
puts "Series sum (sum is infinite): ", res, "\n"