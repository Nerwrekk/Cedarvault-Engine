Tank = setmetatable({}, { __index = EntityScript })
Tank.__index = Tank

function Tank:new(entity)
    local obj = EntityScript.new(self, entity) -- Call base constructor
    return obj
end

function Tank:OnStart()
    print("inside Tank lua script")
end

function Tank:OnUpdate()
    print("inside OnUpdate Tank lua script attached to entity: " .. self.entity:GetID())
end
