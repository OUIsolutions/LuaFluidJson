




char *private_lua_fluid_json_read_file(const char *filename) {
    long size;

    FILE  *file = fopen(filename,"rb");

    if(!file){
        return NULL;
    }

    if(fseek(file,0,SEEK_END) == -1){
        fclose(file);
        return NULL;
    }


    size = ftell(file);

    if(size == -1){
        fclose(file);
        return NULL;
    }

    if(size == 0){
        fclose(file);
        return NULL;
    }


    if(fseek(file,0,SEEK_SET) == -1){
        fclose(file);
        return NULL;
    }

    unsigned char *content = (unsigned char*)malloc(size +1);
    long  bytes_read = (long)fread(content,1,size,file);
    if(bytes_read <=0 ){
        free(content);
        fclose(file);
        return NULL;
    }
    //verifying if its binary
    for(int i = 0;i < size;i++){
        if(content[i] == 0){
            fclose(file);
            free(content);
            return NULL;
        }
    }
    char *converted  = (char*)content;
    converted[size] = '\0';
    fclose(file);
    return converted;
}

int  private_lua_fluid_write_file(const char *filename, const char *value) {

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return -1;
    }
    fputs(value, file);

    fclose(file);
    return 0;
}
