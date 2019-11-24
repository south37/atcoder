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
    digit =
      if n >= 1000_000_000
        10
      elsif n >= 100_000_000
        9
      elsif n >= 10_000_000
        8
      elsif n >= 1_000_000
        7
      elsif n >= 100_000
        6
      elsif n >= 10_000
        5
      elsif n >= 1_000
        4
      elsif n >= 100
        3
      elsif n >= 10
        2
      else
        1
      end

    if A * n + B * digit <= X
      p n
      return
    end
  end

  p 0
end

main
