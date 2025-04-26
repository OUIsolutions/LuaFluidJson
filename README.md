# LuaFluidJson

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version: 0.6.0](https://img.shields.io/badge/Version-0.6.0-blue.svg)](https://github.com/OUIsolutions/LuaFluidJson/releases/tag/v0.6.0)

A JSON parser for Lua that works with native Lua mechanics - no adaptations required.

> ⚠️ **WARNING**: This library is not production-ready. Use with caution.

## Table of Contents
- [Overview](#overview)
- [Supported Platforms](#supported-platforms)
- [Installation](#installation)
  - [Direct Download](#direct-download)
  - [Terminal Installation](#terminal-installation)
- [Building from Source](#building-from-source)
- [Usage](#usage)
  - [Dumping JSON](#dumping-json)
    - [To File](#to-file)
    - [To String](#to-string)
  - [Loading JSON](#loading-json)
    - [From File](#from-file)
    - [From String](#from-string)
  - [Handling NULL Values](#handling-null-values)
    - [Default NULL Handling](#default-null-handling)
    - [Custom NULL Value](#custom-null-value)
  - [Type Detection](#type-detection)

## Overview

Unlike other JSON parsers that require adaptations to load and dump JSON data, LuaFluidJson leverages Lua's native mechanics to implement the processing. This provides a streamlined and intuitive way to work with JSON in Lua.

The library handles the conversion between Lua tables and JSON objects/arrays automatically, making it extremely easy to integrate into your Lua applications.

## Supported Platforms

- **Linux** (Tested on Fedora and Ubuntu)

## Installation

### Direct Download

The installation doesn't require LuaRocks or any package manager. Simply:

1. Download the [Lib Package](https://github.com/OUIsolutions/LuaFluidJson/releases/download/v0.6.0/src.zip)
2. Extract it into your project's root directory
3. Start using it in your code

### Terminal Installation

If you prefer using the terminal, run this command in your project's root directory:

```shell
wget https://github.com/OUIsolutions/LuaFluidJson/releases/download/v0.6.0/src.zip && unzip src.zip -d .
```

## Building from Source

To build from source, you need [Darwin](https://github.com/OUIsolutions/Darwin/) installed on your machine.

### Installing Darwin

```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.2.0/darwin.out -o darwin.out && chmod +x darwin.out && sudo mv darwin.out /usr/bin/darwin
```

### Building the Library

Build using Docker:
```bash
darwin run_blueprint build/ --mode folder build_release
```

Build locally:
```bash
darwin run_blueprint build/ --mode folder build_local
```

All compiled **releases** will be generated in the **/release** directory.

## Usage

### Dumping JSON

#### To File

Dump a Lua table to a JSON file:

```lua
local json = require("luaFluidJson/luaFluidJson")

local user = {
    name = 'Mateus',
    age = 27,
    married = false,
    children = {
        {name = 'Child1', married = 'null'}
    }
}

-- The second parameter is the file path, third parameter enables indentation
local indent = true
json.dumps_to_file(user, "output.json", indent)
```

#### To String

Convert a Lua table to a JSON string:

```lua
local json = require("luaFluidJson/luaFluidJson")

local user = {
    name = 'Mateus',
    age = 27,
    married = true,
    children = {
        {name = 'Child1', married = false}
    }
}

local indent = true
local jsonString = json.dumps_to_string(user, indent)
print(jsonString)
```

### Loading JSON

#### From File

Parse a JSON file into a Lua table:

```lua
local json = require("luaFluidJson/luaFluidJson")

local parsed = json.load_from_file("data.json")

print("Name: " .. parsed.name)
print("Age: " .. parsed.age)
print("Married: " .. tostring(parsed.married))

for i, child in ipairs(parsed.children) do
    print("Child name: " .. child.name)
end
```

#### From String

Parse a JSON string into a Lua table:

```lua
local json = require("luaFluidJson/luaFluidJson")

local jsonString = '{"name":"Mateus","age":27}'
local parsed = json.load_from_string(jsonString)

print("Name: " .. parsed.name)
print("Age: " .. parsed.age)
```

### Handling NULL Values

#### Default NULL Handling

Since Lua's `nil` doesn't work the same way as `null` in other languages, the library treats the string `"null"` as a JSON null value:

```lua
local json = require("luaFluidJson/luaFluidJson")

local user = {
    name = 'Mateus',
    age = 27,
    married = false,
    children = 'null'  -- This will be parsed as JSON null
}

local indent = true
json.dumps_to_file(user, "output.json", indent)
```

#### Custom NULL Value

You can set a custom string to represent null values:

```lua
local json = require("luaFluidJson/luaFluidJson")

-- Set a custom null identifier
json.set_null_code("custom_null")

local user = {
    name = 'Mateus',
    age = 27,
    married = false,
    children = 'custom_null'  -- This will be parsed as JSON null
}

local indent = true
json.dumps_to_file(user, "output.json", indent)
```

### Type Detection

If you need to ensure that a table is parsed as a JSON object (rather than an array), you can use the `is_table_a_object` function:

```lua
local json = require("luaFluidJson/luaFluidJson")

local array = {1, 2, 3}
print(json.is_table_a_object(array))  -- false (it's an array)

local object = {a = 20, b = 30}
print(json.is_table_a_object(object))  -- true (it's an object)
```
