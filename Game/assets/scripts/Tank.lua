Tank = {}
-- setmetatable(Tank, { __index = LuaBehaviour })

function Tank:OnStart()
    print("inside Tank lua script")
end

function Tank:OnUpdate()
    print("inside OnUpdate Tank lua script")
end
