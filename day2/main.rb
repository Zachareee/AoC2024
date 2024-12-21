# frozen_string_literal: True

def test_safe?(arr)
  return false if arr[0] == arr[1]

  compare = arr[0] < arr[1] ? :< : :>
  prev = arr[0]
  arr[1..].each do |num|
    result = (num - prev).abs
    return false if result < 1 || result > 3
    return false unless prev.public_send(compare, num)

    prev = num
  end

  true
end

def answer1(arrs)
  unsafe = 0
  arrs.each do |line|
    unsafe += 1 unless test_safe?(line)
  end
  arrs.size - unsafe
end

def answer2(arrs)
  safe = 0
  arrs.select do |line|
    line.size.times do |num|
      if test_safe?(line[...num] + line[num + 1..])
        safe += 1
        break
      end
    end
  end
  safe
end

def start
  arrs = []
  File.open('input.txt').readlines.each do |line|
    arrs.push line.split(' ').map(&:to_i)
  end

  puts answer1(arrs)
  puts answer2(arrs)
end

start
