# https://codegolf.stackexchange.com/questions/129340/staircase-numbers#129346

#uncompressed
def number num
    nums = num.to_s
    it = true
    (0...nums.size).each do |digit|
        it &= nums[-digit-1].to_i == num % (digit + 2)
    end
    it
end

def v2 n
    s = n.to_s
    t = true
    (0...s.size).each { |d|
        t &= s[-d-1].to_i == n % (d + 2)
    }
    t
end

# v3 ungolfed
c = lambda{ |n|
    s = n.to_s
    t = true
    (0...s.size).each { |d|
        t &= s[-d-1].to_i == n % (d + 2)
    }
    t
}

c=lambda{|n|s=n.to_s;t=true;(0...s.size).each{|d|t&=s[-d-1].to_i==n% (d+2)};t}

ans = %w[1 10 20 1101 1121 11311 31101 40210 340210 4620020 5431101 7211311 12040210]

ans.each do |i|
    print i + ' '
    #print number i.to_i
    puts c.(i.to_i)
end
