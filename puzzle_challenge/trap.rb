
codes = File.read("trap_codes.txt").split("\n")

conversion_table = codes.map do |line|
  err_code, err_name = line.split(/\s+/)

  [err_name, err_code.to_i(16)]
end.to_h

message = File.read("trap.txt").gsub(/[_,]/, '').gsub('minus', '-')
              .gsub('plus', '+').gsub(/\w+/) { |word| conversion_table[word] }

message.split("\n").each {|equation| puts(eval(equation).chr)}


