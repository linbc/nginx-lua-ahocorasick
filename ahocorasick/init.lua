local ffi = require("ffi")
local ffi_load = require("ahocorasick.ffi_load").load
local ffi_new = ffi.new
local ffi_free = ffi.free
local ffi_gc = ffi.gc
local ffi_string = ffi.string
local libahocorasick = ffi_load("ahocorasick/libahocorasick")


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
	local temp = ffi_gc( ffi_new("char[1024]"), ffi_free)
	ffi.copy(temp, s)
    local ret = libahocorasick.FuckPingbi(temp)
    return ffi_string(temp)
end

return {Load = Load, Pingbi = Pingbi}

