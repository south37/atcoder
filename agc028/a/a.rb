N, M = gets.chomp.split.map(&:to_i)
S = gets.chomp.chars
T = gets.chomp.chars

def gcd(a, b)
  if (a < b)
    # swap(a, b)
    tmp = a
    a = b
    b = tmp
  end

  if (b == 0)
    return a
  end

  gcd(b, a % b)
end

L = N * M / gcd(N, M)

X = {}
LN = L/N
LM = L/M
0.upto(N-1).each do |i|
  X[i * LN] = S[i]
end

def solve
  ans = true
  0.upto(M-1).each do |i|
    if (X[i * LM] == nil) || (X[i * LM] == T[i])
      # OK
    else
      ans = false
      break
    end
  end

  if ans
    p L
  else
    p -1
  end
end

solve
