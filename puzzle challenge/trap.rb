
message = File.read("trap.txt")

puts message.scan(/_\w+/).map{|w| w.sub("_", "")}.join(' ')

puts "Mac OS 10.6.5 based on the instruction sets specified by _..."