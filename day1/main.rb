# frozen_string_literal:true

def answer1(arr1, arr2)
  arr1.sort!
  arr2.sort!

  sum = 0
  arr1.size.times do |idx|
    sum += (arr1[idx] - arr2[idx]).abs
  end

  sum
end

def answer2(arr1, arr2)
  arr1.to_set.reduce(0) { |acc, x| acc + x * arr2.count(x) }
end

def start
  arr1 = []
  arr2 = []
  File.open('input.txt').readlines.each do |line|
    nums = line.split('   ')
    arr1.push(nums[0].to_i)
    arr2.push(nums[1].to_i)
  end

  puts answer1 arr1, arr2
  puts answer2 arr1, arr2
end

start
