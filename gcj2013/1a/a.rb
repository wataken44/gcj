#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# a.rb

require 'bigdecimal'

PI = BigDecimal.new("3.1415926535897932384626433832795")

def ar(r, k)
    return (2 * r - 3) * k + k * (k + 1) * 2
end

def go(r, t)
    # {(r + 1)^2 - r^2 + (r + 3)^2 - (r + 2)^2 + 
    # ... (r + 2k - 1) ^ 2 - (r + 2k - 2) ^ 2} * pi < t * pi

    # sum(2r + 4n - 3, 1 <= n <= k) < t
    
    # ((2r - 3) * k + k * (k + 1) / 2 * 4) < t

    k_min = BigDecimal("1")
    k_max = BigDecimal("100000000000000000000")
    tb = BigDecimal(t.to_s)

    while(true) do
        if (k_min >= k_max) || (k_min == k_max - 1) then
            break
        end

        if((k_min + k_max) % 2 == 0) then
            k_mid = (k_min + k_max) / 2
        else
            k_mid = (k_min + k_max - 1) / 2
        end
        #puts "%d %d %d %d %d %d" % [r, k_min, k_mid, k_max, ar(r, k_mid), tb]

        if ar(r, k_mid) <= tb then
            k_min = k_mid
        else
            k_max = k_mid
        end
        #puts "%d %d %d %d %d %d" % [r, k_min, k_mid, k_max, ar(r, k_mid), tb]

    end

    return k_min
end

def slow(r, t)
    k = 1
    ar = (r + 1) * (r + 1) - r * r

    while(true) do
        kk = k + 1

        ar += ((r + 2 * kk - 1) **2) - ((r + 2 * kk - 2)**2) 

        break if ar > t 

        k = kk
    end

    return k
end

def main()


    ttt = STDIN.gets.to_i

    1.upto(ttt) do |tt|
        result = 0

        arr = STDIN.gets.chomp.split(" ")
        r = arr[0].to_i
        t = arr[1].to_i

        result = go(r, t)
        #golden = slow(r, t)

        puts "Case #%d: %d" % [tt, result]

        #if result != golden then
        #    puts "!", r, t
        #end
    end
end

if __FILE__ == $0 then
    main()
end
