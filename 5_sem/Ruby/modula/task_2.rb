require 'minitest/autorun'

class Student
  attr_accessor :id, :last_name, :first_name, :middle_name, :birthdate, :address, :phone, :faculty, :course, :group

  def initialize(id, last_name, first_name, middle_name, birthdate, address, phone, faculty, course, group)
    @id = id
    @last_name = last_name
    @first_name = first_name
    @middle_name = middle_name
    @birthdate = birthdate
    @address = address
    @phone = phone
    @faculty = faculty
    @course = course
    @group = group
  end

  def to_s
    "ID: #{@id}, Surname: #{@last_name}, Name: #{@first_name}, Middle Name: #{@middle_name}, Birthyear: #{@birthdate}, Adress: #{@address}, Telephone: #{@phone}, Faculty: #{@faculty}, Course: #{@course}, Group: #{@group}"
  end
end

class StudentDatabase
  def initialize
    @students = []
  end

  def add_student(student)
    @students << student
  end

  def students_by_faculty(faculty)
    @students.select { |student| student.faculty == faculty }
  end

  def students_by_faculty_and_course(faculty, course)
    @students.select { |student| student.faculty == faculty && student.course == course }
  end

  def students_born_after(year)
    @students.select { |student| student.birthdate > year }
  end

  def students_in_group(group)
    @students.select { |student| student.group == group }
  end

  def print_students(student_list)
    student_list.each { |student| puts student.to_s }
  end
end
# Создаем массив объектов Student


# Create student objects and populate the databas

# puts "Students from the Engineering faculty:"
# db.print_students(db.students_by_faculty('Engineering'))

# puts "\nStudents from the Science faculty, 1st year:"
# db.print_students(db.students_by_faculty_and_course('Science', 1))

# puts "\nStudents born after 1990:"
# db.print_students(db.students_born_after(1990))

# puts "\nStudents in group E301:"
# db.print_students(db.students_in_group('E301'))

require 'minitest/autorun'
#require_relative 'StudentDatabase'
class TestDB < Minitest::Test
  def test_db
    db = StudentDatabase.new
    db.add_student(Student.new(1, 'Smith', 'John', 'A', 1990, '123 Main St', '123-456-7890', 'Engineering', 2, 'E101'))
    db.add_student(Student.new(2, 'Johnson', 'Sarah', 'B', 1991, '456 Elm St', '987-654-3210', 'Science', 1, 'S201'))
    db.add_student(Student.new(3, 'Brown', 'Michael', 'C', 1992, '789 Oak St', '555-123-4567', 'Engineering', 3, 'E301'))
    res = db.students_by_faculty("Engineering")
    assert_equal(1, res[0].id)
    assert_equal(3, res[1].id)
    res = db.students_by_faculty_and_course("Science", 1)
    assert_equal(2, res[0].id)
    res = db.students_born_after(1990)
    assert_equal(2, res[0].id)
    assert_equal(3, res[1].id)
    res = db.students_in_group("E301")
    assert_equal(3, res[0].id)
  end
end