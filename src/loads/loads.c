


LuaCEmbedTable * private_lua_fluid_parse_array(LuaCEmbed *args, cJSON *json_array){
    LuaCEmbedTable *created = lua.tables.new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_array);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_array,i);
        if(cJSON_IsNumber(current)){
            lua.tables.append_double(created,cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            lua.tables.append_string(created,cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            lua.tables.append_bool(created,(bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            char *nil_code = lua.globals.get_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            lua.tables.append_string(created, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_object(args,current);
            lua.tables.append_table(created,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_array(args,current);
            lua.tables.append_table(created,internal_created);
        }
    }
    return created;

}

LuaCEmbedTable * private_lua_fluid_parse_object(LuaCEmbed *args, cJSON *json_object){
    LuaCEmbedTable *created = lua.tables.new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_object);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_object,i);
        char *key =current->string;
        if(cJSON_IsNumber(current)){
            lua.tables.set_double_prop(created,key, cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            lua.tables.set_string_prop(created,key, cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            lua.tables.set_bool_prop(created,key, (bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            char *nil_code = lua.globals.get_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            lua.tables.set_string_prop(created, key, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_object(args,current);
            lua.tables.set_sub_table_prop(created,key,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_array(args,current);
            lua.tables.set_sub_table_prop(created,key,internal_created);
        }
    }
    return created;

}

LuaCEmbedResponse * private_loads_json_from_raw_string(LuaCEmbed *args,const char * str,const char *filename){
    cJSON *parsed = cJSON_Parse(str);
    if(!parsed && filename){
        return lua.response.send_error(PRIVATE_LUA_FLUID_CONTENT_OF_FILE_ITS_NOT_A_VALID_JSON,filename);
    }
    if(!parsed){
        return lua.response.send_error(PRIVATE_LUA_FLUID_CONTENT_ITS_NOT_A_VALID_JSON);
    }

    //here means its parsed correct
    if(cJSON_IsBool(parsed)){
        LuaCEmbedResponse *response =lua.response.send_bool((bool)parsed->valueint);
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNumber(parsed)){
        LuaCEmbedResponse *response =lua.response.send_double(cJSON_GetNumberValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsString(parsed)){
        LuaCEmbedResponse *response =lua.response.send_str(cJSON_GetStringValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNull(parsed)){
        cJSON_Delete(parsed);
        char *nil_code = lua.globals.get_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
        return  lua.response.send_str(nil_code);
    }
    else if(cJSON_IsObject(parsed)){
        LuaCEmbedTable *created = private_lua_fluid_parse_object(args,parsed);
        cJSON_Delete(parsed);
        return lua.response.send_table(created);
    }
    else if(cJSON_IsArray(parsed)){
        LuaCEmbedTable *created = private_lua_fluid_parse_array(args,parsed);
        cJSON_Delete(parsed);
        return lua.response.send_table(created);
    }

    return NULL;
}


LuaCEmbedResponse * lua_fluid_json_loads_json_from_string(LuaCEmbed *args){
    char * content = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error  = lua.get_error_message(args);
        return lua.response.send_error(error);
    }

    LuaCEmbedResponse  *response = private_loads_json_from_raw_string(args,content,NULL);
    return response;
}


LuaCEmbedResponse * lua_fluid_json_loads_json_from_file(LuaCEmbed *args){
    char * filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error  = lua.get_error_message(args);
        return lua.response.send_error(error);
    }
    char * content = private_lua_fluid_json_read_file(filename);
    if(!content){
        return lua.response.send_error(PRIVATE_LUA_FLUID_FILE_NOT_FOUND_ERROR,filename);
    }

    LuaCEmbedResponse  *response = private_loads_json_from_raw_string(args,content,filename);
    free(content);
    return response;


}