H, W, A, B = gets.chomp.split.map(&:to_i)

def solve
  if (A == 0) && (B == 0)  # OK
    0.upto(H-1).each do
      print W.times.map { 0 }.join("") + "\n"
    end
    return
  end

  # OK
  if (A == 0)  # B >= 1
    0.upto(H-1).each do |h|
      if (h <= B-1)
        print W.times.map { 1 }.join("") + "\n"
      else
        print W.times.map { 0 }.join("") + "\n"
      end
    end
    return
  end
  # OK
  if (B == 0)  # A >= 1
    0.upto(H-1).each do |h|
      row = []
      0.upto(W-1).each do |w|
        if (w <= A-1)
          row << 1
        else
          row << 0
        end
      end
      print row.join("") + "\n"
    end
    return
  end

  # OK
  0.upto(H-1).each do |h|
    row = []
    0.upto(W-1).each do |w|
      if (w <= A-1) && (h <= B-1)
        row << 1
      elsif (w > A-1) && (h <= B-1)
        row << 0
      elsif (w <= A-1) && (h > B-1)
        row << 0
      else # w > A-1 && h > B-1
        row << 1
      end
    end
    print row.join("") + "\n"
  end
end

solve
