


#include "constants.h"
#include  "dependencies/LuaCEmbed.h"

#ifndef cJSON__h
#include "dependencies/cJSON/cJSON.h"
#include "dependencies/cJSON/cJSON.c"
#endif


LuaCEmbedNamespace lua;
#include "io/io.h"
#include "loads/loads.h"
#include "dump/dump.h"
#include "io/io.c"
#include "loads/loads.c"
#include "dump/dump.c"


int load_lua(lua_State *state){
    lua = newLuaCEmbedNamespace();
    bool set_functions_as_public  = false;
    LuaCEmbed * l  = lua.newLuaLib(state,set_functions_as_public);
    lua.add_callback(l, PRIVATE_LUA_LOAD_JSON_FROM_STRING_FUN, lua_fluid_json_loads_json_from_string);
    lua.add_callback(l, PRIVATE_LUA_LOAD_JSON_FROM_FILE_FUN,lua_fluid_json_loads_json_from_file);

    return lua.perform(l);
}