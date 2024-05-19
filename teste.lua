
json = require("luaFluidJson/luaFluidJson")

local teste = {
    a =30,
    b= 'null',
    c=function()end,
    nome='mateus',
    array = {1,2,3}
}

json.dumps_to_file(teste,"saida.json",false)