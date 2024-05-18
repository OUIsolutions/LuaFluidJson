



#include  "dependencies/LuaCEmbed.h"
LuaCEmbedNamespace lua;
#include "io/io.h"
#include "loads/loads.h"
#include "io/io.c"
#include "loads/loads.c"



int load_lua(lua_State *state){
    lua = newLuaCEmbedNamespace();
    bool set_functions_as_public  = false;
    LuaCEmbed * l  = lua.newLuaLib(state,set_functions_as_public);

    char *teste = private_lua_fluid_json_read_file("README.mdfff");
    if(teste){
        printf("%s\n",teste);
    }
    else{
        printf("não possivel abri\n");
    }
    return lua.perform(l);
}