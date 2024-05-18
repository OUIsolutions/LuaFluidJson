
LuaCEmbedTable * private_loads_json_from_raw_string(const char * str);

LuaCEmbedResponse * lua_luid_json_loads_json_from_string(LuaCEmbed *args);

LuaCEmbedResponse * lua_fluid_json_loads_json_from_file(LuaCEmbed *args){
    char * filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error  = lua.get_error_message(args);
        return lua.response.send_error(error);
    }
    char * content = private_lua_fluid_json_read_file(filename);
    if(!content){
        int required_size = (int)(strlen(PRIVATE_FILE_NOT_FOUND_ERROR) + strlen(filename) +2);
        char *menssage = malloc(required_size * sizeof(char));
        sprintf(menssage,PRIVATE_FILE_NOT_FOUND_ERROR,filename);
        return lua.response.send_error();

    }

}