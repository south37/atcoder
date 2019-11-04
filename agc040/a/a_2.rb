# N = gets.chomp.to_i
# A, B, C = gets.chomp.split.map(&:to_i)
S = gets.chomp.chars
N = S.size + 1

# We use queue
DP = Array.new(N, -1)  # A

if S[0] == '<'
  DP[0] = 0
end
if S[N-2] == '>'
  DP[N-1] = 0
end

1.upto(N-2).each do |i|
  if (S[i-1] == '>' && S[i] == '<')
    DP[i] = 0
  end
end

# Set number from left
1.upto(N-2).each do |i|
  next if DP[i-1] == -1

  if (S[i-1] == '<' && S[i] == '<')
    DP[i] = DP[i-1] + 1
  end
end

# Set number from right
(N-2).downto(1).each do |i|
  next if DP[i+1] == -1

  if (S[i-1] == '>' && S[i] == '>')
    DP[i] = DP[i+1] + 1
  end
end

if S[0] == '>'
  DP[0] = DP[1] + 1
end
if S[N-2] == '<'
  DP[N-1] = DP[N-2]+1
end

# Set < >
1.upto(N-2).each do |i|
  if (S[i-1] == '<' && S[i] == '>')
    DP[i] = [DP[i-1], DP[i+1]].max + 1
  end
end

# For Debug
# p DP

ans = 0
0.upto(N-1).each do |i|
  ans += DP[i]
end

p ans
