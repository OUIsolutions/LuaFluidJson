
local json = require("luaFluidJson/luaFluidJson")


local parsed = json.load_from_file("test/target/element.json");

print("name:"..parsed.name)
print("age:"..parsed.age)
print("maried:"..tostring(parsed.maried))
for i,v in ipairs(parsed.sons) do
    local son_name = v["name"]
    print("son name:"..son_name)
end