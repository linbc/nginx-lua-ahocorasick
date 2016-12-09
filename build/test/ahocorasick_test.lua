package.path = package.path..';../?.lua;/opt/openresty/lualib/?.so;/usr/local/openresty/lualib/?.so'

local ahocorasick   = require 'ahocorasickc.ahocorasick'

local function test()
	local path = "..\\_fuck_pingbi.txt"
	ahocorasick:LoadFuckPingbi(path)
	local str = "a493664527h"
    print(ahocorasick:FuckPingbi(str))
end

test()