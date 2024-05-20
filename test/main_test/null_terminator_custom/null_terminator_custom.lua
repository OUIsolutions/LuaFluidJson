
local json = require("luaFluidJson/luaFluidJson")
json.set_null_code("custom_null")
local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons='custom_null'
}
local ident = true
json.dumps_to_file(user,"test/target/out.json",ident);
