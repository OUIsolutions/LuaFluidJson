
local json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons='null'
}
local ident = true
json.dumps_to_file(user,"test/target/out.json",ident);
