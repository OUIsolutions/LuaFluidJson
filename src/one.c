
#include "imports/imports.fdefine.h"

int load_lua_fluid_josn(lua_State *state){
    LuaCEmbed * l  = newLuaCEmbedLib(state);
    LuaCEmbed_set_global_string(l, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR, LUA_FLUID_JSON_NULL_CODE_VALUE);

    LuaCEmbed_add_callback(l, PRIVATE_LUA_FLUID_JSON_LOAD_JSON_FROM_STRING_FUN, lua_fluid_json_loads_json_from_string);
    LuaCEmbed_add_callback(l, PRIVATE_LUA_FLUID_JSON_LOAD_JSON_FROM_FILE_FUN, lua_fluid_json_loads_json_from_file);
    LuaCEmbed_add_callback(l, PRIVATE_LUA_FLUID_JSON_DUMPS_TO_STRING_FUN, lua_fluid_json_dump_to_string);
    LuaCEmbed_add_callback(l, PRIVATE_LUA_FLUID_JSON_DUMPS_TO_FILE, lua_fluid_json_dump_to_file);
    LuaCEmbed_add_callback(l,PRIVATE_LUA_FLUID_IS_TABLE_A_OBJECT,lua_json_fluid_is_table_a_object);
    LuaCEmbed_add_callback(l,PRIVATE_LUA_FLUID_JSON_SET_NULL_CODE_FUN,lua_json_fluid_set_null_code);

    return LuaCembed_perform(l);
}
