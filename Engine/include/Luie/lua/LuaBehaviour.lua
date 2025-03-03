LuaBehaviour = {}

function LuaBehaviour:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function LuaBehaviour:OnStart()
    print("default start call")
end

function LuaBehaviour:OnUpdate()
    print("default update call")
end
