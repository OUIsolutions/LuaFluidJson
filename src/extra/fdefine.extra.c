


bool lua_json_fluid_table_is_object(LuaCEmbedTable *table){
    long size = lua.tables.get_size(table);
    for(int i =0; i < size;i++){
        if(lua.tables.has_key(table,i) == false){
            return false;
        }
    }
    return true;
}
LuaCEmbedResponse * lua_json_fluid_is_table_a_object(LuaCEmbed *args){
    LuaCEmbedTable *table = lua.args.get_table(args,0);
    if(lua.has_errors(args)){
        char*error= lua.get_error_message(args);
        return lua.response.send_error(error);
    }
    bool response = lua_json_fluid_table_is_object(table);
    return lua.response.send_bool(response);
}

LuaCEmbedResponse * lua_json_fluid_set_null_code(LuaCEmbed *args){
    char *new_nil_code = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char*error= lua.get_error_message(args);
        return lua.response.send_error(error);
    }
    lua.globals.set_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR, new_nil_code);
    return NULL;
}
