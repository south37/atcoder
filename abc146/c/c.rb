# N = gets.chomp.to_i
A, B, X = gets.chomp.split.map(&:to_i)
# S = gets.chomp

# AN + B d(N) <= X
# AN <= (X-d(N) B) <= (X-B)

def main
  if (X-B) < 0 # X must larger than B
    p 0
    return
  end

  maximium = [(X-B) / A + 1, 1000_000_000].min
  maximium.downto(1).each do |n|
    digit = n.to_s.size
    if A * n + B * digit <= X
      p n
      return
    end
  end

  p 0
end

main
