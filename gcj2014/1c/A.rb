#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# A.rb

def main()
    n = gets.to_i

    1.upto(n) do |nn|
        print("Case #%d: " % nn)

        x, y = gets.split("/").map{|s| s.to_i }
        g = gcd(x, y)
        x = x / g
        y = y / g

        r = "impossible"
        if (1 << 46) % y == 0 then
            1.upto(46) do |k|
                if x * (1 << k) >= y  then
                    r = k
                    break
                end
            end
        end

        puts r
    end
end

def gcd(x, y)
    return gcd(y, x) if x > y
    return y if x == y || x == 0
    return gcd(y % x, x)
end

if __FILE__ == $0 then
    main()
end
