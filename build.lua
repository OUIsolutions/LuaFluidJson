
os.execute("gcc -Wall  -shared -fpic -o luaFluidJson/luaFluidJson.so  src/main.c")

os.execute("x86_64-w64-mingw32-gcc -Wall  -shared -fpic -o luaFluidJson/luaFluidJson.dll  src/main.c")
