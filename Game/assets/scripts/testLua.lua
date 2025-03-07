Some_variable = 1
testVar = 4;

test = LuaBehaviour:new()
test:OnStart()
-- This is a Lua table
-- it is the only data structure in lua that we are allowed to use/create
Config = {
    title = "Test",
    fullscreen = false,
    resolution = {
        width = 800,
        height = 600
    }
}
while Some_variable < 100 do
    print("damn some variable is: " .. Some_variable)
    Some_variable = Some_variable + 1
end

--placement matters when declaring functions in lua!
function printName(name)
    print("Hello! " .. name)
end

printName("Bert")
printName("Gandalf")
printName("Gondor")
