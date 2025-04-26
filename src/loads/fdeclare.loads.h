//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.consts.h"
//silver_chain_scope_end

LuaCEmbedTable * private_lua_fluid_parse_array(LuaCEmbed *args, cJSON *json_array);

LuaCEmbedTable * private_lua_fluid_parse_object(LuaCEmbed *args, cJSON *json_object);


LuaCEmbedResponse * private_loads_json_from_raw_string(LuaCEmbed *args,const char * str,const char *filename);


LuaCEmbedResponse * lua_fluid_json_loads_json_from_string(LuaCEmbed *args);

LuaCEmbedResponse * lua_fluid_json_loads_json_from_file(LuaCEmbed *args);
