local ffi = require("ffi")
local ffi_load = require("ahocorasick.ffi_load").load
local ffi_string = ffi.string
local libahocorasick = ffi_load("ahocorasick/libahocorasick")


--from ac_helper.cpp
ffi.cdef[[

	int LoadFuckPingbi(const char* cpath);

	const char* FuckPingbi(const char* str);

]]

local function Load (s)
    local ret = libahocorasick.LoadFuckPingbi(s)
    return ret
end

local function Pingbi(s)
    local ret = libahocorasick.FuckPingbi(s)
    return ret and ffi_string(ret) or nil
end

return {Load = Load, Pingbi = Pingbi}

