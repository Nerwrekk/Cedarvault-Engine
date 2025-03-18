---@class Entity
---@field Id number
entity = {}

---@class Vec2
---@field x number
---@field y number
vec2 = {}

---@class Transform
---@field position Vec2
---@field rotation Vec2
---@field scale Vec2
transform = {}

--- Gets the Transform component
---@param entity Entity
---@return Transform
function GetTransformComponent(entity) end

---@class SpriteComponent
---@field Sprite string
---@field Width number
---@field Height number
---@field ZIndex number
---@field SrcRect Vec2
spriteComponent = {}

--- Gets the Sprite component
---@param entity Entity
---@return SpriteComponent
function GetSpriteComponent(entity) end
