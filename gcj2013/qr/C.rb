#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# C.rb

def main()
    t = gets.to_i
    1.upto(t) do |tt|
        ret = 0
        arr = gets.chomp.split(" ").map{|s|next s.to_i}
        a = arr[0]
        b = arr[1]

        sa = Math.sqrt(a).floor
        sb = Math.sqrt(b).ceil

        [sa - 1, 0].max.upto(sb + 1) do |k|
            kk = k * k
            next if(kk < a || kk > b)
            s = k.to_s
            ss = kk.to_s
            if s == s.reverse && ss == ss.reverse then
                ret += 1
            end
        end

        puts "Case #%d: %d" % [tt, ret]
    end
end

if __FILE__ == $0 then
    main()
end
