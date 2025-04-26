function install_dependencies()
    local hasher = darwin.dtw.newHasher()
    hasher.digest_folder_by_content("dependencies")
    local EXPECTED_SHA = '14133ed1907c9c4a058f04af0066d4dd0f9e50ea12365e640298e9752add7a2b'
    if hasher.get_value() == EXPECTED_SHA then
        return
    end
    
    darwin.dtw.remove_any("dependencies")
    os.execute("mkdir -p dependencies")

    
    os.execute("curl -L https://github.com/OUIsolutions/LuaCEmbed/releases/download/0.8.0/LuaCEmbedOne.c -o dependencies/LuaCEmbedOne.c ")
    os.execute("curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c -o dependencies/cJSON.c")
    os.execute("curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h -o dependencies/cJSON.h")



    local new_hasher = darwin.dtw.newHasher()
    new_hasher.digest_folder_by_content("dependencies")
    print("new hasher is: " .. new_hasher.get_value())
end