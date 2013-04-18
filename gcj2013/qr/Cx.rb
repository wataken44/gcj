#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# Cx.rb

def main()
    a = 1
    b = 10**15

    sa = Math.sqrt(a).floor
    sb = Math.sqrt(b).ceil

    ret = []
    [sa - 1, 0].max.upto(sb + 1) do |k|
        kk = k * k
        next if(kk < a || kk > b)
        s = k.to_s
        ss = kk.to_s
        if s == s.reverse && ss == ss.reverse then
            ret << kk
        end
    end
    p ret
end

if __FILE__ == $0 then
    main()
end
