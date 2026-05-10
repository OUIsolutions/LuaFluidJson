---@meta

--- JSON library loaded via package.loadlib from the compiled shared object.
--- JSON null values are represented in Lua as the null-code string (default: "null").
---@class LuaFluidJson
local LuaFluidJson = {}

--- Parses a JSON string and returns the corresponding Lua value.
--- JSON null is converted to the current null-code string.
---@param str string   Valid JSON text.
---@return any         Parsed value: table, string, number, boolean, or the null-code string.
function LuaFluidJson.load_from_string(str) end

--- Reads a file and parses its content as JSON.
--- JSON null is converted to the current null-code string.
---@param path string  Path to the JSON file.
---@return any         Parsed value: table, string, number, boolean, or the null-code string.
function LuaFluidJson.load_from_file(path) end

--- Serializes a Lua value to a JSON string.
--- The null-code string is serialized back to JSON null.
---@param entry any         Value to serialize: table, string, number, or boolean.
---@param ident? boolean    Whether to pretty-print the output (default: true).
---@return string           JSON text.
function LuaFluidJson.dumps_to_string(entry, ident) end

--- Serializes a Lua value to a JSON file.
--- The null-code string is serialized back to JSON null.
---@param entry any         Value to serialize: table, string, number, or boolean.
---@param output string     Destination file path.
---@param ident? boolean    Whether to pretty-print the output (default: true).
function LuaFluidJson.dumps_to_file(entry, output, ident) end

--- Returns true if all elements in the table have string keys (JSON object),
--- or false if any element lacks a key (JSON array).
---@param element table
---@return boolean
function LuaFluidJson.is_table_a_object(element) end

--- Changes the string used to represent JSON null in Lua (default: "null").
--- Affects both loading and dumping.
---@param null_code string  New string to use in place of JSON null.
function LuaFluidJson.set_null_code(null_code) end
