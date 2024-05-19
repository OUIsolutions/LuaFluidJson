local json = require("luaFluidJson/luaFluidJson")

local test = '{"name":"mateus","age":27}'

local parsed = json.load_from_string(test);

print("name:"..parsed.name)
print("age:"..parsed.age)
