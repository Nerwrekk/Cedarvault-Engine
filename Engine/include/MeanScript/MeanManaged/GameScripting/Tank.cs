using MeanScriptEngine;

public class Tank : MeanScriptBehaviour
{
    private float xPos = 100f;
    private float yPos = 100f;

    private float moveSpeed = 100f;
    public override void OnStart()
    {
        Console.WriteLine($"[Tank] OnStart, is bound to entity with id: {Entity.Id}");
        MeanNativeApi.SetEntityPosition(Entity, 100, 100);
    }

    public override void OnUpdate(float deltaTime)
    {
        xPos = xPos + (moveSpeed * deltaTime);
        MeanNativeApi.SetEntityPosition(Entity, xPos, 100);
    }
}