#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# A.rb

def main()
    input = 
        ["y qee",
         "ejp mysljylc kd kxveddknmc re jsicpdrysi",
         "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd",
         "de kr kd eoya kw aej tysr re ujdr lkgc jv"]
    output = 
        ["a zoo",
         "our language is impossible to understand",
         "there are twenty six factorial possibilities",
         "so it is okay if you want to just give up"]

    map = {
    }

    input.size().times do |i|
        sz = input[i].size()
        p "error" if input[i].size() != output[i].size()

        sz.times do |k|
            ic = input[i][k, 1]
            oc = output[i][k, 1]
            
            if map.has_key?(ic) and map[ic] != oc then
                p "error"
            end
            map[ic] = oc
        end
    end

    a = [*"a".."z"] + [" "]
    b = [*"a".."z"] + [" "]
    
    map.each do |k, v|
        a -= [k]
        b -= [v]
    end
    map[a[0]] = b[0]

    #p map

    ifh = open(ARGV[0])

    t = ifh.readline().to_i

    t.times do |tt|
        i = ifh.readline().chomp
        o = ""
        i.each_char do |c|
            o += map[c]
        end
        puts "Case #%d: %s" % [tt + 1, o]
    end

    ifh.close

end

if __FILE__ == $0 then
    main()
end
