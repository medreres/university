puts "Enter x: "
x = gets.chomp.to_f

puts "Enter j: "
j = gets.chomp.to_f

first_additive = Math.cos(24 * Math::PI / 2)


logarithm_cubic_x = Math.log(x ** 3)
tangens_fifth = Math.tan(logarithm_cubic_x) ** 5

divider = Math.sqrt((x + Math::E ** j).abs)
divisor = tangens_fifth + 4.2 * (10 ** -2.8)

result = first_additive + divisor / divider

puts "Your result is #{result}"