
local json = require("luaFluidJson/luaFluidJson")

local test = {1,2,3}
print(json.is_table_a_object(test))

local test2 = {a=20,b=30}

print(json.is_table_a_object(test2))
