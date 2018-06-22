require 'ahocorasick'

local ret = ahocorasick.load('_fuck_pingbi.txt')
print(ret)
print(ahocorasick.match('a西藏自由h'))

