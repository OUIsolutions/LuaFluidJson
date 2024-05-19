




cJSON  * lua_fluid_json_dump_to_cJSON_array(LuaCEmbedTable *table);

cJSON  * lua_fluid_json_dump_to_cJSON_object(LuaCEmbedTable *table);

cJSON  * lua_fluid_json_dump_table_to_cJSON(LuaCEmbedTable *table);


LuaCEmbedResponse * lua_fluid_json_dump_to_string(LuaCEmbed *args){
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    bool ident = true;

    if(lua.args.get_type(args,1) != lua.types.NOT_FOUND){
        ident = lua.args.get_bool(args,1);
    }
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    cJSON *result = NULL;
    int element_type = lua.args.get_type(args,0);
    if(element_type == lua.types.STRING){
        char *value = lua.args.get_str(args,0);
        result = cJSON_CreateString(value);
    }

    else if(element_type == lua.types.NUMBER){
        double value = lua.args.get_double(args,0);
        result = cJSON_CreateNumber(value);
    }

    else if(element_type == lua.types.BOOL){
        bool value = lua.args.get_bool(args,0);
        result = cJSON_CreateBool(value);
    }

    else if(element_type == lua.types.TABLE){
        LuaCEmbedTable  *value = lua.args.get_table(args,0);
        result = lua_fluid_json_dump_table_to_cJSON(value);
    }
    else{
        return lua.response.send_error(
                PRIVATE_LUA_FLUID_ELEMENT_CANNOT_BE_DUMPED,
                lua.convert_arg_code(element_type)
        );
    }

    char *result_str  = NULL;
    if(ident){
        result_str = cJSON_Print(result);
    }
    else{
        result_str = cJSON_PrintUnformatted(result);
    }
    cJSON_Delete(result);
    LuaCEmbedResponse *response = lua.response.send_str(result_str);
    free(result_str);
    return response;
}


LuaCEmbedResponse * lua_fluid_json_dump_to_file(LuaCEmbed *args){

    char * output = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    bool ident = true;

    if(lua.args.get_type(args,2) != lua.types.NOT_FOUND){
        ident = lua.args.get_bool(args,2);
    }
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    cJSON *result = NULL;
    int element_type = lua.args.get_type(args,0);
    if(element_type == lua.types.STRING){
        char *value = lua.args.get_str(args,0);
        result = cJSON_CreateString(value);
    }

    else if(element_type == lua.types.NUMBER){
        double value = lua.args.get_double(args,0);
        result = cJSON_CreateNumber(value);
    }

    else if(element_type == lua.types.BOOL){
        bool value = lua.args.get_bool(args,0);
        result = cJSON_CreateBool(value);
    }

    else if(element_type == lua.types.TABLE){
        LuaCEmbedTable  *value = lua.args.get_table(args,0);
        result = lua_fluid_json_dump_table_to_cJSON(value);
    }
    else{
        return lua.response.send_error(
                PRIVATE_LUA_FLUID_ELEMENT_CANNOT_BE_DUMPED,
                lua.convert_arg_code(element_type)
        );
    }

    char *result_str  = NULL;
    if(ident){
        result_str = cJSON_Print(result);
    }
    else{
        result_str = cJSON_PrintUnformatted(result);
    }

    cJSON_Delete(result);
    private_lua_fluid_write_file(output,result_str);
    free(result_str);
    return NULL;
}

