


---@class LuaFluidJson
---@field load_from_string fun(str:string): any 
---@field load_from_file fun(str:string):any
---@field dumps_to_string fun(entry:table,ident:boolean| nil): string
---@field dumps_to_file fun(entry:table,output:string,ident:boolean|nil)
---@field is_table_a_object fun(element:table):boolean
---@field set_null_code fun(null_code:string)



local info = debug.getinfo(1, "S")
local path = info.source:match("@(.*/)") or ""


local lib_path = ''

if os.getenv("HOME") then
    lib_path = path.."luaFluidJson.so"
else
    perror("undefined os")
end 

local load_lua = package.loadlib(lib_path, "load_lua_fluid_json")

---@type LuaFluidJson
local lib = load_lua()

return lib