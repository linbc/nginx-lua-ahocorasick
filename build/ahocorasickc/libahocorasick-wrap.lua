local ffi = require("ffi")
local ffi_load = require("ahocorasickc.ffi_load").load
local libahocorasickc = ffi_load("libahocorasick")

--from ac_helper.cpp
ffi.cdef[[

	int LoadFuckPingbi(const char* cpath);

	const char* FuckPingbi(const char* str);

]]


return libahocorasickc