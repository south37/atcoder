# N = gets.chomp.to_i
# H = gets.chomp.split.map(&:to_i)
S = gets.chomp.chars # array of chars
K = gets.chomp.to_i

# Run Length Encoding v2
# cnts = []
# cnt = 1
# chr = S[0]
# 1.upto(S.size-1).each do |i|
#   if S[i] == S[i-1]
#     cnt += 1
#   else
#     cnts << [chr, cnt]
#     chr = S[i]
#     cnt = 1
#   end
# end
# cnts << [chr, cnt]

# Run Length Encoding v1
cnts = [] # <<chr, cnt>>
i = 0
n = S.size
while (i < n)  # rep(i, N)
  cnt = 1
  while (i < n - 1 && S[i] == S[i+1])
    cnt += 1
    i += 1
  end
  cnts << [S[i], cnt]
  i += 1
end

# p cnts

if cnts.size == 1
  p (cnts[0][1] * K) / 2
else
  if cnts[0][0] == cnts[-1][0] # the char of pre and sub are same
    ans = 0
    ans += cnts[0][1] / 2
    ans += cnts[-1][1] / 2
    ans += (cnts[0][1] + cnts[-1][1]) / 2 * (K-1)  # united
    cnts[1..-2].each do |(chr, cnt)|
      ans += cnt / 2 * K
    end
    p ans
  else
    ans = 0
    cnts.each do |(chr, cnt)|
      if cnt > 1
        ans += cnt / 2
      end
    end
    p ans * K
  end
end
