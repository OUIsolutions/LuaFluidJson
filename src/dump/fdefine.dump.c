//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end





cJSON  * lua_fluid_json_dump_to_cJSON_array(LuaCEmbedTable *table){
    long size = LuaCEmbedTable_get_full_size(table);
    cJSON * created_array = cJSON_CreateArray();
    for(int i = 0; i<size;i++){
        int type = LuaCEmbedTable_get_type_by_index(table,i);

        if(type == LUA_CEMBED_NUMBER){
            double value = LuaCEmbedTable_get_double_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateNumber(value));
        }

        if(type == LUA_CEMBED_STRING){
            char *value = LuaCEmbedTable_get_string_by_index(table,i);
            char *nil_code = LuaCEmbed_get_global_string(table->main_object, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);

            if(strcmp(nil_code, value) == 0){
                cJSON_AddItemToArray(created_array, cJSON_CreateNull());

            }else{
                cJSON_AddItemToArray(created_array, cJSON_CreateString(value));

            }
        }

        if(type == LUA_CEMBED_BOOL){
            bool value = LuaCEmbedTable_get_bool_by_index(table,i);
            cJSON_AddItemToArray(created_array, cJSON_CreateBool(value));
        }

        if(type == LUA_CEMBED_TABLE){
            LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table,i);
            cJSON *value = lua_fluid_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToArray(created_array, value);
        }

    }
    return created_array;
}

// Estrutura auxiliar para armazenar chaves e seus índices para ordenação
typedef struct {
    char *key;
    int index;
} KeyIndexPair;

// Função de comparação para qsort
static int compare_keys(const void *a, const void *b) {
    return strcmp(((KeyIndexPair*)a)->key, ((KeyIndexPair*)b)->key);
}

cJSON  * lua_fluid_json_dump_to_cJSON_object(LuaCEmbedTable *table){
    long size = LuaCEmbedTable_get_full_size(table);
    cJSON * created_object = cJSON_CreateObject();
    
    // Criar array para armazenar pares de chave-índice
    KeyIndexPair *pairs = (KeyIndexPair*)malloc(size * sizeof(KeyIndexPair));
    if (!pairs) {
        // Em caso de falha na alocação, recorrer ao método original
        for(int i = 0; i < size; i++){
            char *key = LuaCembedTable_get_key_by_index(table, i);
            int type = LuaCEmbedTable_get_type_by_index(table, i);
            
            if(type == LUA_CEMBED_NUMBER){
                double value = LuaCEmbedTable_get_double_by_index(table,i);
                cJSON_AddNumberToObject(created_object,key,value);
            }
            if(type == LUA_CEMBED_STRING){
                char *value = LuaCEmbedTable_get_string_by_index(table,i);
                char *nil_code = LuaCEmbed_get_global_string(table->main_object, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
                if(strcmp(nil_code,value)==0){
                    cJSON_AddNullToObject(created_object,key);
                }else{
                    cJSON_AddStringToObject(created_object,key, value);
                }
            }
            if(type == LUA_CEMBED_BOOL){
                bool value = LuaCEmbedTable_get_bool_by_index(table,i);
                cJSON_AddBoolToObject(created_object,key, value);
            }

            if(type == LUA_CEMBED_TABLE){
                LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table,i);
                cJSON *value = lua_fluid_json_dump_table_to_cJSON(internal);
                cJSON_AddItemToObject(created_object,key,value);
            }
        }
        return created_object;
    }
    
    // Preencher o array com as chaves e seus índices
    for(int i = 0; i < size; i++){
        pairs[i].key = LuaCembedTable_get_key_by_index(table, i);
        pairs[i].index = i;
    }
    
    // Ordenar as chaves alfabeticamente
    qsort(pairs, size, sizeof(KeyIndexPair), compare_keys);
    
    // Adicionar os elementos ao objeto JSON na ordem ordenada
    for(int i = 0; i < size; i++){
        char *key = pairs[i].key;
        int idx = pairs[i].index;
        int type = LuaCEmbedTable_get_type_by_index(table, idx);
        
        if(type == LUA_CEMBED_NUMBER){
            double value = LuaCEmbedTable_get_double_by_index(table, idx);
            cJSON_AddNumberToObject(created_object, key, value);
        }
        if(type == LUA_CEMBED_STRING){
            char *value = LuaCEmbedTable_get_string_by_index(table, idx);
            char *nil_code = LuaCEmbed_get_global_string(table->main_object, PRIVATE_LUA_FLUID_JSON_NULL_CODE_GLOBAL_VAR);
            if(strcmp(nil_code, value) == 0){
                cJSON_AddNullToObject(created_object, key);
            }else{
                cJSON_AddStringToObject(created_object, key, value);
            }
        }
        if(type == LUA_CEMBED_BOOL){
            bool value = LuaCEmbedTable_get_bool_by_index(table, idx);
            cJSON_AddBoolToObject(created_object, key, value);
        }
        if(type == LUA_CEMBED_TABLE){
            LuaCEmbedTable *internal = LuaCEmbedTable_get_sub_table_by_index(table, idx);
            cJSON *value = lua_fluid_json_dump_table_to_cJSON(internal);
            cJSON_AddItemToObject(created_object, key, value);
        }
    }
    
    // Liberar memória
    free(pairs);
    
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
    int element_type = LuaCEmbed_get_arg_type(args,0);
    if(element_type == LUA_CEMBED_STRING){
        char *value = LuaCEmbed_get_str_arg(args,0);
        result = cJSON_CreateString(value);
    }

    else if(element_type == LUA_CEMBED_NUMBER){
        double value = LuaCEmbed_get_double_arg(args,0);
        result = cJSON_CreateNumber(value);
    }

    else if(element_type == LUA_CEMBED_BOOL){
        bool value = LuaCEmbed_get_bool_arg(args,0);
        result = cJSON_CreateBool(value);
    }

    else if(element_type == LUA_CEMBED_TABLE){
        LuaCEmbedTable  *value = LuaCEmbed_get_arg_table(args,0);
        result = lua_fluid_json_dump_table_to_cJSON(value);
    }
    else{
        return LuaCEmbed_send_error(
                PRIVATE_LUA_FLUID_ELEMENT_CANNOT_BE_DUMPED,
                LuaCembed_convert_arg_code(element_type)
        );
    }

    bool ident = true;

    if(LuaCEmbed_get_arg_type(args,1) != LUA_CEMBED_NIL){
        ident = LuaCEmbed_get_bool_arg(args,1);
    }

    if(LuaCEmbed_has_errors(args)){
        char *error_msg = LuaCEmbed_get_error_message(args);
        return LuaCEmbed_send_error(error_msg);
    }

    char *result_str  = NULL;
    if(ident){
        result_str = cJSON_Print(result);
    }
    else{
        result_str = cJSON_PrintUnformatted(result);
    }

    LuaCEmbedResponse *response = LuaCEmbed_send_str(result_str);
    cJSON_Delete(result);
    free(result_str);
    return response;
}


LuaCEmbedResponse * lua_fluid_json_dump_to_file(LuaCEmbed *args){


    cJSON *result = NULL;
    int element_type = LuaCEmbed_get_arg_type(args,0);
    if(element_type == LUA_CEMBED_STRING){
        char *value = LuaCEmbed_get_str_arg(args,0);
        result = cJSON_CreateString(value);
    }

    else if(element_type == LUA_CEMBED_NUMBER){
        double value = LuaCEmbed_get_double_arg(args,0);
        result = cJSON_CreateNumber(value);
    }

    else if(element_type == LUA_CEMBED_BOOL){
        bool value = LuaCEmbed_get_bool_arg(args,0);
        result = cJSON_CreateBool(value);
    }

    else if(element_type == LUA_CEMBED_TABLE){
        LuaCEmbedTable  *value = LuaCEmbed_get_arg_table(args,0);
        result = lua_fluid_json_dump_table_to_cJSON(value);
    }
    else{
        return LuaCEmbed_send_error(
                PRIVATE_LUA_FLUID_ELEMENT_CANNOT_BE_DUMPED,
                LuaCembed_convert_arg_code(element_type)
        );
    }


    char * output = LuaCEmbed_get_str_arg(args,1);
    if(LuaCEmbed_has_errors(args)){
        char *error_msg = LuaCEmbed_get_error_message(args);
        cJSON_Delete(result);
        return LuaCEmbed_send_error(error_msg);
    }
    bool ident = true;

    if(LuaCEmbed_get_arg_type(args,2) != LUA_CEMBED_NIL){
        ident = LuaCEmbed_get_bool_arg(args,2);
    }

    if(LuaCEmbed_has_errors(args)){
        char *error_msg = LuaCEmbed_get_error_message(args);
        cJSON_Delete(result);
        return LuaCEmbed_send_error(error_msg);
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
        return LuaCEmbed_send_error(PRIVATE_LUA_FLUI_IMPOSSIBLE_TO_WRITE_FILE,output);
        
    }
    return NULL;
}
