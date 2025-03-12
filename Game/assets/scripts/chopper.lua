Chopper = setmetatable({}, { __index = LuieScript })
Chopper.__index = Chopper

function Chopper:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    obj.moveSpeed = 5
    return obj
end

function Chopper:OnStart()
    print("OnStart chopper" .. self.entity:GetID())
end

function Chopper:OnUpdate()
    local xPos, yPos = self:GetEntityPosition()
    if IsKeyRepeated(Keys.A) then
        self:SetEntityPosition(xPos - self.moveSpeed, yPos)
    end
    if IsKeyRepeated(Keys.D) then
        self:SetEntityPosition(xPos + self.moveSpeed, yPos)
    end
    if IsKeyRepeated(Keys.W) then
        self:SetEntityPosition(xPos, yPos - self.moveSpeed)
    end
    if IsKeyRepeated(Keys.S) then
        self:SetEntityPosition(xPos, yPos + self.moveSpeed)
    end
end
