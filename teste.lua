
json = require("luaFluidJson/luaFluidJson")

local teste = {
    a =30,
    b= 40,
    nome='mateus',
    array = {1,2,3}
}

json.dumps_to_file(teste,"saida.json",true)