
json = require("luaFluidJson/luaFluidJson")

teste = json.load_from_file("teste.json")

for i ,v in pairs(teste) do
   if type(v) == 'table' then
        for x,y in pairs(v) do
            print(x,y)
        end
   else
       print(i,v)

   end

end