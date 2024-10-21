


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
#include "extra/extra.h"

#include "io/io.c"
#include "loads/loads.c"
#include "dump/dump.c"
#include "extra/extra.c"


int load_lua(lua_State *state){
    lua = newLuaCEmbedNamespace();
    LuaCEmbed * l  = lua.newLuaLib(state);
    lua.globals.set_string(l, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR, LUA_FLUID_JSON_NULL_CODE_VALUE);

    lua.add_callback(l, PRIVATE_LUA_FLUID_JSON_LOAD_JSON_FROM_STRING_FUN, lua_fluid_json_loads_json_from_string);
    lua.add_callback(l, PRIVATE_LUA_FLUID_JSON_LOAD_JSON_FROM_FILE_FUN, lua_fluid_json_loads_json_from_file);
    lua.add_callback(l, PRIVATE_LUA_FLUID_JSON_DUMPS_TO_STRING_FUN, lua_fluid_json_dump_to_string);
    lua.add_callback(l, PRIVATE_LUA_FLUID_JSON_DUMPS_TO_FILE, lua_fluid_json_dump_to_file);
    lua.add_callback(l,PRIVATE_LUA_FLUID_IS_TABLE_A_OBJECT,lua_json_fluid_is_table_a_object);
    lua.add_callback(l,PRIVATE_LUA_FLUID_JSON_SET_NULL_CODE_FUN,lua_json_fluid_set_null_code);

    return lua.perform(l);
}
