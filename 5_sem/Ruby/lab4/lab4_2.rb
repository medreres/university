def gauss
    n = gets.chomp.to_i
    if n < 3 || n > 9
      raise "N must be more than 3 and less than 9"
      return
    end
  
    vec = Array.new(n){|index| index + 1}
    matrix = (0..n - 1).map{Array.new(n - 1)}
    matrix.size.times do |i|
      matrix.size.times do |j|
        if i == j
          matrix[i][j] = 2.0
        else
          matrix[i][j] = 7.0
        end
      end
    end
  
    puts matrix.map(&:inspect), "\n"
    
    puts vec, "\n"
  
    matrix.size.times do |i|
      coef = matrix[i][i]
      matrix.size.times do |j|
        matrix[i][j] /= coef
      end
      vec[i] /= coef
      matrix.size.times do |j|
        if j != i
          coef1 = matrix[j][i] / matrix[i][i]
          matrix.size.times do |k|
            matrix[j][k] -= matrix[i][k] * coef1
          end
          vec[j] -= vec[i] * coef1
        end
      end
      puts matrix.map(&:inspect), "\n"
    end
  
    vec
  end
  
  print gauss, "\n"