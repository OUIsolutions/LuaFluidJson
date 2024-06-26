



local dtw = require("build/luaDoTheWorld/luaDoTheWorld")


local RECONSTRUCT = false
local TEST_DIR ="test/main_test"
local SIDE_EFFECT = "test/target"
local side_effect_copy_path  = SIDE_EFFECT.."copy"


---@param inputstr string
---@param sep string
---@returns string[]
local function slipt (inputstr, sep)

    local t={}
    for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
            table.insert(t, str)
    end
    return t
end



local function handle_side_effect(dir,current_assignature)

    local side_effect_expected_folder = dir.."/side_effect"

    local test_were_predictible = dtw.isdir(side_effect_expected_folder)

    if not test_were_predictible or RECONSTRUCT then
        print("created"..side_effect_expected_folder)
        dtw.copy_any_overwriting(SIDE_EFFECT,side_effect_expected_folder)
    end
end



---@param unit string
---@param start_assignature string
local function test_unit(unit,start_assignature)

    local paths =  slipt(unit,"/")
    local name  = paths[#paths]

    if name == nil then
        print("name of test "..unit.."not provide")
        return true
    end

    local file_path = unit..name..".lua"

    print("testing: "..file_path)

    local output,code = io.popen("lua "..file_path,"r"):read("a")
    if output then
       dtw.write_file(unit.."expected.txt",output)
     end

    print("valgrind testing: "..file_path)
    os.execute("valgrind  lua "..file_path.."  >> out.txt 2>&1")

    local output_valgrind  = dtw.load_file("out.txt")


    local heap_test = string.find(output_valgrind, "All heap blocks were freed ")
    local error_test = string.find(output_valgrind,"0 errors from 0 contexts")
    dtw.remove_any("out.txt")
    if heap_test == nil or  error_test == nil then
        print(output_valgrind)
        return true
    end




    local test_assignature  = dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)
    --means code generated side effect
    if start_assignature ~= dtw.generate_sha_from_folder_by_content(SIDE_EFFECT) then
        handle_side_effect(unit,test_assignature)
    end


    --validate_commad_result(result)

end


---@param start_assignature string
local function exec_tests(start_assignature)
    print("starting tests")

    local concat_path = true;
    local tests  = dtw.list_dirs(TEST_DIR,concat_path)

    for i, t in ipairs(tests) do
        local error = test_unit(t,start_assignature)
         dtw.copy_any_overwriting(side_effect_copy_path,SIDE_EFFECT);

        if error then
            return
        end
    end

end

local function main()


    print("compiling")

    local code = os.execute("gcc -Wall  -shared -fpic -o luaFluidJson/luaFluidJson_lib.so  src/main.c")
    if code == 1 then
        return
    end

    local start_assignature = dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)

    dtw.copy_any_overwriting(SIDE_EFFECT,side_effect_copy_path)

    exec_tests(start_assignature)

    dtw.copy_any_overwriting(side_effect_copy_path,SIDE_EFFECT);
    dtw.remove_any(side_effect_copy_path)

    os.execute("zip -r src.zip luaFluidJson/")
end


main()