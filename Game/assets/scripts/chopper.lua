Chopper = setmetatable({}, { __index = LuieScript })
Chopper.__index = Chopper

function Chopper:new(entity)
    local obj = LuieScript.new(self, entity) -- Call base constructor
    return obj
end

function Chopper:OnStart()
    self.moveSpeed = 100
    print("Chopper position: x = " .. self.transform.position.x .. " y = " .. self.transform.position.y)
    self.sprite = GetSpriteComponent(self.entity)
    self.sprite.Sprite = "chopper-spritesheet"
    -- print(self.spriteComponent.Sprite)
end

function Chopper:OnUpdate(deltaTime)
    local xVel, yVel = self:GetEntityVelocity()
    if IsKeyRepeated(Keys.A) then
        xVel = xVel - (self.moveSpeed * deltaTime)
        self.sprite.SrcRect.y = self.sprite.Height * 3
    end
    if IsKeyRepeated(Keys.D) then
        xVel = xVel + (self.moveSpeed * deltaTime)
        self.sprite.SrcRect.y = self.sprite.Height * 1
    end
    if IsKeyRepeated(Keys.W) then
        yVel = yVel - (self.moveSpeed * deltaTime)
        self.sprite.SrcRect.y = self.sprite.Height * 0
    end
    if IsKeyRepeated(Keys.S) then
        yVel = yVel + (self.moveSpeed * deltaTime)
        self.sprite.SrcRect.y = self.sprite.Height * 2
    end

    if IsKeyPressed(Keys.Space) then
        print("Space was pressed")
    end

    if IsKeyReleased(Keys.Space) then
        print("Space was Released")
    end

    self:SetEntityVelocity(xVel, yVel)
end
