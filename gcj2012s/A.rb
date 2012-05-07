#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# A.rb


def main()

    tt = STDIN.gets.to_i
    
    1.upto(tt) do |t|
        arr = STDIN.gets.chomp.split(" ").map{|s| next s.to_i }
        
        l = arr.shift
        m = arr.shift
        k = arr.sort

        r = -1
        if(k[-1] <= l) then
            r = (k.size - 1) * l + k[-1]
        end

        puts "Case #%d: %d" % [t, r]

    end
end

if __FILE__ == $0 then
    main()
end


if __FILE__ == $0 then

end
