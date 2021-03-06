# N = gets.chomp.to_i
# A, B, C = gets.chomp.split.map(&:to_i)
S = gets.chomp.chars
N = S.size + 1

DP = Array.new(N, -1)
def calc(i)
  if (DP[i] > 0)
    return DP[i]
  end

  if (i > 0 && i < N-1)
    if (S[i-1] == '>' && S[i] == '<')
      return (DP[i] = 0)
    end
    if (S[i-1] == '<' && S[i] == '>')
      m = [calc(i-1), calc(i+1)].max
      return (DP[i] = m + 1);
    end
    if (S[i-1] == '<' && S[i] == '<')
      return (DP[i] = calc(i-1) + 1)
    end
    if (S[i-1] == '>' && S[i] == '>')
      return (DP[i] = calc(i+1) + 1)
    end
  end

  if i == 0
    if S[i] == '<'
      return (DP[i] = 0)
    else # S[i] == '>'
      return (DP[i] = calc(i+1) + 1)
    end
  end

  if i == N-1
    if S[i-1] == '<'
      return (DP[i] = calc(i-1) + 1)
    else # S[i-1] == '>'
      return (DP[i] = 0)
    end
  end
end

0.upto(N-1).each do |i|
  calc(i);
end
ans = 0
0.upto(N-1).each do |i|
  ans += DP[i]
end

p ans
