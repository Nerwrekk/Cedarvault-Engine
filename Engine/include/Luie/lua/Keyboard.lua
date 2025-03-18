---@class Keys
---@field x number
---@field y number
---@field Space number,
---@field Apostrophe number
---@field Comma  number
---@field Minus number
---@field Period  number
---@field Slash  number
---@field Num_0 number
---@field Num_1 number
---@field Num_2  number
---@field Num_3  number
---@field Num_4 number
---@field Num_5 number
---@field Num_6 number
---@field Num_7 number
---@field Num_8 number
---@field Num_9 number
---@field Semicolon number
---@field Equal number
---@field A number
---@field B number
---@field C number
---@field D number
---@field E number
---@field F number
---@field G number
---@field H number
---@field I number
---@field J number
---@field K number
---@field L number
---@field M number
---@field N number
---@field O number
---@field P number
---@field Q number
---@field R number
---@field S number
---@field T number
---@field U number
---@field V number
---@field W number
---@field X number
---@field Y number
---@field Z number
Keys = {}

--- returns true if key is being held down
---@param key number
---@return boolean
function IsKeyRepeated(key) end

--- returns true if key is being pressed once
---@param key number
---@return boolean
function IsKeyPressed(key) end

--- returns true if key is being released
---@param key number
---@return boolean
function IsKeyReleased(key) end
