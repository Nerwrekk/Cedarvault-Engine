Chopper = setmetatable({}, { __index = LuieScript })
Chopper.__index = Chopper

function Chopper:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    obj.moveSpeed = 100
    return obj
end

function Chopper:OnStart()
end

function Chopper:OnUpdate(deltaTime)
    local xVel, yVel = self:GetEntityVelocity()
    if IsKeyRepeated(Keys.A) then
        xVel = xVel - (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.D) then
        xVel = xVel + (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.W) then
        yVel = yVel - (self.moveSpeed * deltaTime)
    end
    if IsKeyRepeated(Keys.S) then
        yVel = yVel + (self.moveSpeed * deltaTime)
    end

    if IsKeyPressed(Keys.Space) then
        print("Space was pressed")
    end

    if IsKeyReleased(Keys.Space) then
        print("Space was Released")
    end

    self:SetEntityVelocity(xVel, yVel)
end
