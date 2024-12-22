# frozen_string_literal: True

def test_safe?(arr)
  return false if arr[0] == arr[1]

  compare = arr[0] < arr[1] ? :< : :>
  prev = arr[0]
  arr[1..].each do |num|
    result = (num - prev).abs
    return false if result < 1 || result > 3 || !prev.public_send(compare, num)

    prev = num
  end
  true
end

def answer1(arrs)
  arrs.select do |line|
    test_safe?(line)
  end.size
end

def test_safe_remove_one(line)
  line.size.times do |num|
    return true if test_safe?(line[...num] + line[num + 1..])
  end
  false
end

def answer2(arrs)
  arrs.select(&method(:test_safe_remove_one)).count
end

def start
  arrs = [] # : Array[Array[Integer]]
  File.open('input.txt').readlines.each do |line|
    arrs << line.split(' ').map(&:to_i)
  end

  puts answer1(arrs)
  puts answer2(arrs)
end

start
