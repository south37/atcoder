N = gets.chomp.to_i
Box = []
N.times do
  w, h = gets.chomp.split.map(&:to_i)
  Box << [w, h]
end

Box.sort_by! { |(w, h)| [h, - w] } # if h is same, w is in decreasing order

sorted = [] # LIS
Box.each do |(w, _)| # Now, we consider only w
  if sorted.size == 0
    sorted << w
    next
  end

  i = sorted.bsearch_index { |x| x >= w }
  case i
  when nil  # w is larger than all elements in sorted
    sorted << w
  else
    sorted[i] = w
  end
end

p sorted.size
