Tank = setmetatable({}, { __index = LuieScript })
Tank.__index = Tank

function Tank:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    return obj
end

function Tank:OnStart()
    self.moveSpeed = 130
end

function Tank:OnUpdate(deltaTime)
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

    if IsKeyPressed(Keys.Space) then
        print("Space was pressed")
    end

    if IsKeyReleased(Keys.Space) then
        print("Space was Released")
    end

    self:SetEntityPosition(xPos, yPos)
end
