LuieScript = {}
LuieScript.__index = LuieScript

function LuieScript:new(entity)
    local obj = setmetatable({}, self)
    obj.entity = entity -- Store entity id reference
    obj.transform = GetTransformComponent(entity)
    return obj
end

--Directly sets the entities position
function LuieScript:SetEntityPosition(x, y)
    SetPosition(self.entity, x, y)
end

function LuieScript:GetEntityPosition()
    return GetPosition(self.entity)
end

function LuieScript:SetEntityVelocity(x, y)
    SetVelocity(self.entity, x, y)
end

function LuieScript:GetEntityVelocity()
    return GetVelocity(self.entity)
end
