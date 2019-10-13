N, K = gets.chomp.split.map(&:to_i)
a = gets.chomp.split.map(&:to_i)

# Now, we consider a[l..r] as the candidate.
# If a[l..r] < K, then we increase r and try a[l..r+1].
# If a[l..r] >= K, then we increase and trye a[l+1..r].
# Loop this.

l = 0
r = 0
ans = 0
summed = a[0]
while (r < N && l < N)
  # p "a[#{l}..#{r}]: #{summed}"
  if (summed >= K)
    ans += N - r  # sum all righter. (N-1) - r + 1.
    summed -= a[l]
    l += 1
  else # summed < K
    r += 1
    if r < N
      # p "a[#{r}]: #{a[r]}"
      summed += a[r]
    else
      break
    end
  end
end

p ans
