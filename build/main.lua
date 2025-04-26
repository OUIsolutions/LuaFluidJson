
function main()

    darwin.dtw.remove_any("release")

    install_dependencies()


    darwin.silverchain.generate({
        src = "src",
        project_short_cut="LuaFluidJson",
        tags = { "dependencie", "consts", "macros", "globals", "fdeclare", "fdefine" },
        implement_main = false
    })

  local no_dep_amalgamation = darwin.camalgamator.generate_amalgamation_with_callback("src/one.c",
        function(import, path)
            if import == "src/imports/../dependencie.dependencies.h"  then
                return "dont-include"
            end
            return "include-once"

        end,
        MAX_CONNTENT,
        MAX_RECURSION
    )
    darwin.dtw.write_file("release/luaFluidJson_no_dep.c", no_dep_amalgamation)

    local builded = false
    if darwin.argv.one_of_args_exist("build_local") then
        darwin.dtw.copy_any_overwriting("extra/starter.lua","release/luaFluidJson/luaFluidJson.lua")

        os.execute("gcc src/one.c -ldl -shared  -fpic -o release/luaFluidJson/luaFluidJson.so")
        builded = true
    end

    if darwin.argv.one_of_args_exist("build_release") then
        

        
        builded = true
    end
    
    if builded then
        os.execute("cd release && zip -r luaFluidJson.zip luaFluidJson")
    end

   -- darwin.dtw.remove_any("release/luaFluidJson")


end