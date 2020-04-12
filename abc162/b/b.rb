N = gets.chomp.to_i
# A, B, C = gets.chomp.split.map(&:to_i)
# S = gets.chomp.chars

ans = 0
1.upto(N).each do |i|
  if (i % 3 == 0)
    next
  end
  if (i%5 == 0)
    next
  end
  ans += i
end

p ans
