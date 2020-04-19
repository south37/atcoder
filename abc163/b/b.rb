N, M = gets.chomp.split.map(&:to_i)
A = gets.chomp.split.map(&:to_i)
# S = gets.chomp.chars

sum = 0
0.upto(M-1).each do |i|
  sum += A[i]
end

if (N >= sum)
  p N - sum
else
  p (-1)
end
