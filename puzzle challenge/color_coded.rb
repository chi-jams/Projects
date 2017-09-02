
message = File.read('color_coded.txt').split(/\s+/)
puts message.size
def to_binary(colors, color)
  message = colors.map{|b| b == color ? 1 : 0 }
  message = message.join('').scan(/.{8}/).map do |b| 
    value = b.to_i(2).to_s(16)
  end

  message.join('') 
end

%w[Brown Red Blue Yellow].each do |color|
  puts to_binary(message, color).to_s
end