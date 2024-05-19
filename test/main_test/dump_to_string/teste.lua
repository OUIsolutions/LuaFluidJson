local json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons={
        {name='son1',maried='nill'}
    }
}
local ident = true
local dumped = json.dumps_to_string(json,ident);
print(dumped)
