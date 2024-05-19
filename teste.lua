
json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    sss=true,

    age=27.4,
    sons={
        {name='son1',maried=true }
    }
}
local ident = true
local value = json.dumps_to_string(user,ident);
print(value)

