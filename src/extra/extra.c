


bool lua_json_fluid_table_is_object(LuaCEmbedTable *table){
    long size = lua.tables.get_size(table);
    for(int i =0; i < size;i++){
        if(lua.tables.has_key(table,i) == false){
            return false;
        }
    }
    return true;
}
