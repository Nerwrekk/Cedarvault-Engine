using MeanScriptEngine;
using MeanScriptEngine.Components;

public class Tank : MeanScriptBehaviour
{
    private float xPos = 100f;
    private float yPos = 100f;

    private float moveSpeed = 100f;
    private TransformComponent transform;
    public override void OnStart()
    {
        transform = MeanNativeApi.GetTransformComponent(Entity);
        Console.WriteLine($"[Tank] OnStart, is bound to entity with id: {Entity.Id}");
        // MeanNativeApi.SetEntityPosition(Entity, 100, 100);
    }

    public override void OnUpdate(float deltaTime)
    {
        // Console.WriteLine($"Transform pos at x: {transform.Position.X} and y: {transform.Position.Y}");

        if (MeanNativeApi.IsKeyPressed(0x04)) //TODO: Fix keycode bindings in csharp
        {
            Console.WriteLine("A was pressed");
        }
    }
}