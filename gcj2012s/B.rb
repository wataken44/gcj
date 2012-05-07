#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# B.rb

def main()

    tt = STDIN.gets.to_i
    
    1.upto(tt) do |t|

        arr = STDIN.gets.chomp.split(" ")

        n = arr[0].to_i
        s = arr[1]

        h = Hash.new{ |h, k| h[k] = 0 }
        ret = []

        0.upto(s.size - n) do |st|
            k = s[st, n]
            h[k] += 1
            ret << k if h[k] > 1 
        end
        
        rs = ret.size == 0 ? "NONE" : ret.sort.uniq.join(" ")
        puts "Case #%d: %s" % [t, rs]
    end
end

if __FILE__ == $0 then
    main()
end


if __FILE__ == $0 then

end
