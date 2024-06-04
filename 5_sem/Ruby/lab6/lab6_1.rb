#Variant 1

class Passanger
    attr_accessor :items_count, :items_weight
    
    def initialize(items_count, items_weight)
      @items_count = items_count
      @items_weight = items_weight
    end
    
    def get_avg_weight()
      avg = items_count/items_weight
      avg
    end
    
    def show()
      puts "\nItems count : #{items_count} Items weight : #{items_weight} Average item weight : #{get_avg_weight()}"    
    end
  
  end
  
  passangers = [Passanger.new(1, 4.0), 
                Passanger.new(10, 5.0), 
                Passanger.new(5, 3.0), 
                Passanger.new(3, 2.0), 
                Passanger.new(11, 8.0),
                Passanger.new(5, 3.5),
                Passanger.new(4, 4.5),
                Passanger.new(8, 5.2),
                Passanger.new(12, 8.35)]
  
  total_weight = passangers.reduce(0){|sum, passanger| sum + passanger.get_avg_weight()}
  total_items = passangers.reduce(0){|sum, passanger| sum + passanger.items_count}
  avg_weight = total_weight/passangers.length
  avg_items = total_items.to_f/passangers.length
  
  puts "Average item weight : #{avg_weight}"
  puts "Average item count : #{avg_items}"
  
  def show(passangers)
    passangers.each do |passanger|
      passanger.show()
    end
  end
  
  show(passangers)
  
  def task1(passangers, avg_weight)
    puts "\n\nPassengers whose average item weight is in range [#{avg_weight-0.3} , #{avg_weight+0.3}]:"
    passangers.each do |passanger|
      if (avg_weight - passanger.get_avg_weight()).abs < 0.3
        passanger.show()
      end
    end
  end
  
  def task2(passangers, avg_items)
    puts "\n\nNumber of passengers who have more than 2 items : "
    passangers.each do |passanger|
      if passanger.items_count > 2
        passanger.show()
      end
    end
    puts "\nNumber of passangers who have more than #{avg_items} (average amount of items) : "
    passangers.each do |passanger|
      if passanger.items_count > avg_items
        passanger.show()
      end
    end
  end
  
  def task3(passangers)
    ids = []
    puts "\n\nPassangers whose item weights do not differ more than 0.5 kg : "
    passangers.each_with_index do |passanger, id|
      for i in id...passangers.length
        if (passangers[i].items_weight - passanger.items_weight).abs <= 0.5
          if (ids.include?(i) == false) and (i != id)
            if ids.include?(id) == false
              ids << id
            end
            ids << i
          end
        end
      end
    end
    ids.each do |i|
      passangers[i].show()
    end
  end
  
  def task4(passangers)
    max_obj = Passanger.new(0, 0.0)
    puts "\n\nPassanger that has more items and heavier bagage than others : "
    passangers.each do |passanger|
      if(passanger.items_count > max_obj.items_count) && (passanger.items_weight > max_obj.items_weight)
        max_obj = passanger
      end
    end
    if max_obj.items_count != 0
      max_obj.show()
    else
      puts "\nThere is no such passanger"
    end
  end
  
  def task5(passangers)
    puts "\nIs there a passanger with only 1 item which weight is less than 30 kg?"
    if passangers.any?{|passanger| passanger.items_count == 1 and passanger.items_weight < 30.0}
      puts "Yes"
    else
      puts "No"
    end
  end
  
  task1(passangers, avg_weight)
  task2(passangers, avg_items)
  task3(passangers)
  task4(passangers)
  task5(passangers)