darwin.add_recipe({
  name = "local",
  description = "Builds the LuaFluidJson module locally with gcc",
  outs = { "release/luaFluidJson" },
  inputs = { "src/" },
  callback = function()
    prepare()
    os.execute("gcc src/one.c -ldl -shared -fpic -o release/luaFluidJson/luaFluidJson.so")
    os.execute("cd release && zip -r luaFluidJson.zip luaFluidJson")
  end
})
