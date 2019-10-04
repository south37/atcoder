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
