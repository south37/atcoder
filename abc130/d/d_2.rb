N, K = gets.chomp.split.map(&:to_i)
a = gets.chomp.split.map(&:to_i)

# Now, we consider a[l..r] as the candidate.
# If a[l..r] < K, then we increase r and try a[l..r+1].
# If a[l..r] >= K, then we increase and trye a[l+1..r].
# Loop this.

ans = 0
sum = 0
l = 0
r = 0
while (l < N)
  while (sum < K && r < N)
    sum += a[r]
    r += 1
  end
  if sum < K  # No more a[r]
    break
  end

  # Now, sum is the summention of a[l..r-1]
  ans += N-r+1 # (N-1)-(r-1)+1 = N-r+1
  sum -= a[l]
  l += 1
end

p ans
