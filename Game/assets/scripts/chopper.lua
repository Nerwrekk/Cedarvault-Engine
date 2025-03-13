Chopper = setmetatable({}, { __index = LuieScript })
Chopper.__index = Chopper

function Chopper:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    obj.moveSpeed = 100
    return obj
end

function Chopper:OnStart()
    print("OnStart chopper" .. self.entity:GetID())
end

function Chopper:OnUpdate(deltaTime)
    local xPos, yPos = self:GetEntityPosition()
    if IsKeyRepeated(Keys.A) then
        xPos = xPos - (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.D) then
        xPos = xPos + (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.W) then
        yPos = yPos - (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.S) then
        yPos = yPos + (self.moveSpeed * deltaTime)
    end

    self:SetEntityPosition(xPos, yPos)
end
