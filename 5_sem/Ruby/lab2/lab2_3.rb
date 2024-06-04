input = gets.chomp
num = 0
for i in 0..input.length
  if input[i] == "1"
    num+=2**(input.length-i-1)
  end
end
puts num