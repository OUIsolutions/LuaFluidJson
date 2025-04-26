//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end



LuaCEmbedTable * private_lua_fluid_parse_array(LuaCEmbed *args, cJSON *json_array){
    LuaCEmbedTable *created = LuaCembed_new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_array);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_array,i);
        if(cJSON_IsNumber(current)){
            LuaCEmbedTable_append_double(created,cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            LuaCEmbedTable_append_string(created,cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            LuaCEmbedTable_append_bool(created,(bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            char *nil_code = LuaCEmbed_get_global_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            LuaCEmbedTable_append_string(created, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_object(args,current);
            LuaCEmbedTable_append_table(created,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_array(args,current);
            LuaCEmbedTable_append_table(created,internal_created);
        }
    }
    return created;

}

LuaCEmbedTable * private_lua_fluid_parse_object(LuaCEmbed *args, cJSON *json_object){
    LuaCEmbedTable *created = LuaCembed_new_anonymous_table(args);
    int size = cJSON_GetArraySize(json_object);
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(json_object,i);
        char *key =current->string;
        if(cJSON_IsNumber(current)){
            LuaCEmbedTable_set_double_prop(created,key, cJSON_GetNumberValue(current));
        }
        else if(cJSON_IsString(current)){
            LuaCEmbedTable_set_string_prop(created,key, cJSON_GetStringValue(current));
        }
        else if(cJSON_IsBool(current)){
            LuaCEmbedTable_set_bool_prop(created,key, (bool)current->valueint);
        }
        else if(cJSON_IsNull(current)){
            char *nil_code = LuaCEmbed_get_global_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            LuaCEmbedTable_set_string_prop(created, key, nil_code);
        }
        else if(cJSON_IsObject(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_object(args,current);
            LuaCEmbedTable_set_sub_table_prop(created,key,internal_created);
        }
        else if(cJSON_IsArray(current)){
            LuaCEmbedTable *internal_created = private_lua_fluid_parse_array(args,current);
            LuaCEmbedTable_set_sub_table_prop(created,key,internal_created);
        }
    }
    return created;

}

LuaCEmbedResponse * private_loads_json_from_raw_string(LuaCEmbed *args,const char * str,const char *filename){
    cJSON *parsed = cJSON_Parse(str);
    if(!parsed && filename){
        return LuaCEmbed_send_error(PRIVATE_LUA_FLUID_CONTENT_OF_FILE_ITS_NOT_A_VALID_JSON,filename);
    }
    if(!parsed){
        return LuaCEmbed_send_error(PRIVATE_LUA_FLUID_CONTENT_ITS_NOT_A_VALID_JSON);
    }

    //here means its parsed correct
    if(cJSON_IsBool(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_bool((bool)parsed->valueint);
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNumber(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_double(cJSON_GetNumberValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsString(parsed)){
        LuaCEmbedResponse *response =LuaCEmbed_send_str(cJSON_GetStringValue(parsed));
        cJSON_Delete(parsed);
        return response;
    }

    else if(cJSON_IsNull(parsed)){
        cJSON_Delete(parsed);
        char *nil_code = LuaCEmbed_get_global_string(args, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
        return  LuaCEmbed_send_str(nil_code);
    }
    else if(cJSON_IsObject(parsed)){
        LuaCEmbedTable *created = private_lua_fluid_parse_object(args,parsed);
        cJSON_Delete(parsed);
        return LuaCEmbed_send_table(created);
    }
    else if(cJSON_IsArray(parsed)){
        LuaCEmbedTable *created = private_lua_fluid_parse_array(args,parsed);
        cJSON_Delete(parsed);
        return LuaCEmbed_send_table(created);
    }

    return NULL;
}


LuaCEmbedResponse * lua_fluid_json_loads_json_from_string(LuaCEmbed *args){
    char * content = LuaCEmbed_get_str_arg(args,0);
    if(LuaCEmbed_has_errors(args)){
        char *error  = LuaCEmbed_get_error_message(args);
        return LuaCEmbed_send_error(error);
    }

    LuaCEmbedResponse  *response = private_loads_json_from_raw_string(args,content,NULL);
    return response;
}


LuaCEmbedResponse * lua_fluid_json_loads_json_from_file(LuaCEmbed *args){
    char * filename = LuaCEmbed_get_str_arg(args,0);
    if(LuaCEmbed_has_errors(args)){
        char *error  = LuaCEmbed_get_error_message(args);
        return LuaCEmbed_send_error(error);
    }
    char * content = private_lua_fluid_json_read_file(filename);
    if(!content){
        return LuaCEmbed_send_error(PRIVATE_LUA_FLUID_FILE_NOT_FOUND_ERROR,filename);
    }

    LuaCEmbedResponse  *response = private_loads_json_from_raw_string(args,content,filename);
    free(content);
    return response;


}