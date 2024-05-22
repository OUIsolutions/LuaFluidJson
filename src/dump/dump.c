




cJSON  * lua_fluid_json_dump_to_cJSON_array(LuaCEmbedTable *table){
    long size = lua.tables.get_size(table);
    cJSON * created_array = cJSON_CreateArray();
    for(int i = 0; i<size;i++){
        int type = lua.tables.get_type_by_index(table,i);

        if(type == lua.types.NUMBER){
            double value = lua.tables.get_double_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateNumber(value));
        }

        if(type == lua.types.STRING){
            char *value = lua.tables.get_string_by_index(table,i);
            char *nil_code = lua.globals.get_string(table->main_object, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);

            if(strcmp(nil_code, value) == 0){
                cJSON_AddItemToArray(created_array, cJSON_CreateNull());

            }else{
                cJSON_AddItemToArray(created_array, cJSON_CreateString(value));

            }
        }

        if(type == lua.types.BOOL){
            bool value = lua.tables.get_bool_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateBool(value));
        }

        if(type == lua.types.TABLE){
            LuaCEmbedTable *internal = lua.tables.get_sub_table_by_index(table,i);
            cJSON *value = lua_fluid_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToArray(created_array, value);
        }

    }
    return created_array;
}

cJSON  * lua_fluid_json_dump_to_cJSON_object(LuaCEmbedTable *table){
    long size = lua.tables.get_size(table);
    cJSON * created_object = cJSON_CreateObject();
    for(int i = 0; i<size;i++){
        char *key =lua.tables.get_key_by_index(table,i);
        int type = lua.tables.get_type_by_index(table,i);

        if(type == lua.types.NUMBER){
            double value = lua.tables.get_double_by_index(table,i);
            cJSON_AddNumberToObject(created_object,key,value);
        }
        if(type == lua.types.STRING){
            char *value = lua.tables.get_string_by_index(table,i);
            char *nil_code = lua.globals.get_string(table->main_object, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            if(strcmp(nil_code,value)==0){
                cJSON_AddNullToObject(created_object,key);
            }else{
                cJSON_AddStringToObject(created_object,key, value);
            }


        }
        if(type == lua.types.BOOL){
            bool value = lua.tables.get_bool_by_index(table,i);;
            cJSON_AddBoolToObject(created_object,key, value);
        }

        if(type == lua.types.TABLE){
            LuaCEmbedTable *internal = lua.tables.get_sub_table_by_index(table,i);
            cJSON *value = lua_fluid_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToObject(created_object,key,value);
        }

    }
    return created_object;
}

cJSON  * lua_fluid_json_dump_table_to_cJSON(LuaCEmbedTable *table){

    if(lua_json_fluid_table_is_object(table)){

        return lua_fluid_json_dump_to_cJSON_object(table);
    }
    return lua_fluid_json_dump_to_cJSON_array(table);
}


LuaCEmbedResponse * lua_fluid_json_dump_to_string(LuaCEmbed *args){


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

    bool ident = true;

    if(lua.args.get_type(args,1) != lua.types.NILL){
        ident = lua.args.get_bool(args,1);
    }

    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    char *result_str  = NULL;
    if(ident){
        result_str = cJSON_Print(result);
    }
    else{
        result_str = cJSON_PrintUnformatted(result);
    }

    LuaCEmbedResponse *response = lua.response.send_str(result_str);
    cJSON_Delete(result);
    free(result_str);
    return response;
}


LuaCEmbedResponse * lua_fluid_json_dump_to_file(LuaCEmbed *args){


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


    char * output = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        cJSON_Delete(result);
        return lua.response.send_error(error_msg);
    }
    bool ident = true;

    if(lua.args.get_type(args,2) != lua.types.NILL){
        ident = lua.args.get_bool(args,2);
    }

    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        cJSON_Delete(result);
        return lua.response.send_error(error_msg);
    }

    char *result_str  = NULL;
    if(ident){
        result_str = cJSON_Print(result);
    }
    else{
        result_str = cJSON_PrintUnformatted(result);
    }

    cJSON_Delete(result);
    int error= private_lua_fluid_write_file(output,result_str);
    free(result_str);
    if(error){
        return lua.response.send_error(PRIVATE_LUA_FLUI_IMPOSSIBLE_TO_WRITE_FILE,output);
        
    }
    return NULL;
}

