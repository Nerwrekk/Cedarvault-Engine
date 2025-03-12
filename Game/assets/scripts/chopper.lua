Chopper = setmetatable({}, { __index = LuieScript })
Chopper.__index = Chopper

function Chopper:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    return obj
end

function Chopper:OnStart()
    print("OnStart chopper" .. self.entity:GetID())
end

function Chopper:OnUpdate()
    print("OnUpdate chopper")
end
