Tank = setmetatable({}, { __index = LuieScript })
Tank.__index = Tank

function Tank:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    obj.x = 0
    obj.y = 0
    return obj
end

function Tank:OnStart()
    print("inside Tank lua script")
end

function Tank:OnUpdate(deltaTime)
    -- print("DeltaTime is: " .. deltaTime)
    -- print("inside OnUpdate Tank lua script attached to entity: " .. self.entity:GetID())
    self:SetEntityPosition(self.x, self.y)
    self.x = self.x + 1
    self.y = self.y + 1
    -- print("Entity x: " .. self.x .. " y: " .. self.y)
end
