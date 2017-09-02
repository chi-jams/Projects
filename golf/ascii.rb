# https://codegolf.stackexchange.com/questions/105998/recreate-the-ascii-table-as-an-ascii-table

def ascii_raw
  output = (" Dec  Chr   |"*3)[1..-5]
  output << "\n" + "-"*34 + "\n";

  (32..63).each do |row|
    line = ""
    (0..2).each do |column|
      line << sprintf("%-5s%-6s| ", row+column*32, row+column*32 == 32 ? "Space" : row+column*32 == 127 ? "DEL" : (row+column*32).chr)


    end
    output << line[0..-5]
    output << "\n"
  end

  output
end

def ascii_compressed
puts((" Dec  Chr   |"*3)[1..-5],"-"*34)
(32..63).each{|r|l="";(0..2).each{|c|n=r+c*32;l<<sprintf("%-5s%-6s| ",n,n==32? "Space":n==127? "DEL": n.chr)};puts l[0..-5]}
end

puts ascii_raw
puts "\ncompressed ver\n\n"
ascii_compressed
