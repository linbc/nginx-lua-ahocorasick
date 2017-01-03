local ffi = require("ffi")
local ffi_load = require("ahocorasick.ffi_load").load
local libahocorasick = ffi_load("libahocorasick")


--from ac_helper.cpp
ffi.cdef[[

	int LoadFuckPingbi(const char* cpath);

	const int FuckPingbi(char* pinbi_buff);

]]

local function Load (s)
    local ret = libahocorasick.LoadFuckPingbi(s)
    return ret
end

local function Pingbi(s)
	local temp = ffi.gc( ffi.new("char[1024]"), ffi.free)
	ffi.copy(temp, s)
    local ret = libahocorasick.FuckPingbi(temp)
    return ffi.string(temp)
end

return {Load = Load, Pingbi = Pingbi}

