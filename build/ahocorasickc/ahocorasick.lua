local libahocorasickc = require 'ahocorasickc.libahocorasick-wrap'

local LoadFuckPingbi 	= libahocorasickc.LoadFuckPingbi
local FuckPingbi 		= libahocorasickc.FuckPingbi


local ahocorasick = {}

local meta = {
	__index = ahocorasick,
	__tostring = function (self)        
    end,
    __gc = function ( self )
    end
}

function ahocorasick:LoadFuckPingbi(path)
	LoadFuckPingbi(path)
end

function ahocorasick:FuckPingbi(value)
	return FuckPingbi(value)
end

return ahocorasick