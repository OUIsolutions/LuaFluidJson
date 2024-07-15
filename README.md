# LuaFluidJson
An json Parser for lua that doesn't require any adaptation


Beside others parsers that requires adaptation to load and dump jsons, these LuaFluidJson use 
the native mechanics of lua to implement the load and dump processing, allowing a super easy way
to deal with jsons.

<h3 style="color:red;">THESE LIB ITS NOT PRODUCTION READY USE WITH RESPONSIBILITY</h3>

### Platforms supported: 
**Linux** (Tested on Fedora and Ubuntu)

### Installation
The installation doesn't require lua rocks or any package manager, just download the
[Lib Package](https://github.com/OUIsolutions/LuaFluidJson/releases/download/v0.50/src.zip) into your project and copy the internal content in the root of your main,and you can start using 

### Installation from Terminal 
if you prefer just run these command into your root project start point to install  the lib 
~~~shell

wget https://github.com/OUIsolutions/LuaFluidJson/releases/download/v0.51/src.zip  && unzip src.zip  -d . 
~~~



### Dumping Json file
these code dumps the following struct into a json file 
```lua
local json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons={
        {name='son1',maried='null'}
    }
}
local ident = true
json.dumps_to_file(user,"test/target/out.json",ident);
 
```

### Dumping a json String 
if you need to dump a JSON String its also easy, you can just call the **dumps_to_string** function 

```lua 
local json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    age=27,
    maried=true,
    sons={
        {name='son1',maried=false }
    }
}
local ident = true
local value = json.dumps_to_string(user,ident);

print(value)
```

### Loading a Json from File 
you can easly load a json direct from file
```lua

local json = require("luaFluidJson/luaFluidJson")


local parsed = json.load_from_file("test/target/element.json");

print("name:"..parsed.name)
print("age:"..parsed.age)
print("maried:"..tostring(parsed.maried))
for i,v in ipairs(parsed.sons) do
    local son_name = v["name"]
    print("son name:"..son_name)
end
```
### Loading a Json from String 
its also possible to load a json from string 

```lua

local json = require("luaFluidJson/luaFluidJson")

local test = '{"name":"mateus","age":27}'

local parsed = json.load_from_string(test);

print("name:"..parsed.name)
print("age:"..parsed.age)

```
### The Null Code
since the lua nill doesn't work as other languages "nulls" ,the lib consider null as a string 
so if you put "null" into your code, the lib will consider as a null value

```lua 
local json = require("luaFluidJson/luaFluidJson")

local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons='null'
}
local ident = true
json.dumps_to_file(user,"test/target/out.json",ident);
```
### Null Scape
its also possible to scape null putting another code into its place 

```lua 

local json = require("luaFluidJson/luaFluidJson")
json.set_null_code("custom_null")
local user  ={

    name='Nateus',
    age=27,
    maried=false,
    sons='custom_null'
}
local ident = true
json.dumps_to_file(user,"test/target/out.json",ident);
```

### Identifying objects
if you want to ensure the following table will be parsed as a object, you can just call the 
**is_table_a_object** function

```lua 

local json = require("luaFluidJson/luaFluidJson")

local test = {1,2,3}
print(json.is_table_a_object(test))

local test2 = {a=20,b=30}

print(json.is_table_a_object(test2))

```
