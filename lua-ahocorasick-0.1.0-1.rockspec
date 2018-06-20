package = "lua-ahocorasick"
version = "0.1.0-1"
source = {
   url = "git+https://github.com/linbc/nginx-lua-ahocorasick.git",
   tag = "0.1.0-1",
}

description = {
    summary = "A fast Aho–Corasick lua module",
    detailed = [[
        The Lua Aho–Corasick module provides Aho–Corasick support for Lua. It features:
        - Fast, standards compliant Aho–Corasick_algorithm
        - No dependencies on other libraries
    ]],
    homepage = "https://github.com/linbc/nginx-lua-ahocorasick.git",
    license = "MIT"
}

dependencies = {
    "lua >= 5.1"
}

build = {
    type = "builtin",
    modules = {
        ahocorasick = {
            sources = { "ac_mem_pool.c", "aho_corasick.c", "node.c", "ac_helper.cpp" },
            defines = {
-- LuaRocks does not support platform specific configuration for Solaris.
-- Uncomment the line below on Solaris platforms if required.
--                "USE_INTERNAL_ISINF"
            }
        }
    },
    install = {
        lua = {
        },
        bin = {
        }
    },
    -- Override default build options (per platform)
    platforms = {
        win32 = { modules = { ahocorasick = { defines = {
            "DISABLE_INVALID_NUMBERS", "USE_INTERNAL_ISINF"
        } } } }
    },
    copy_directories = { "tests" }
}

-- vi:ai et sw=4 ts=4:
