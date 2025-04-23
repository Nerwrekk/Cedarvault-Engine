using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Tank : MeanScriptBehaviour
{
    private float moveSpeed = 100f;
    public override void OnStart()
    {
        Console.WriteLine($"[Tank] OnStart, is bound to entity with id: {Entity.Id}");
        Console.WriteLine($"Tank starting position is: x: {Transform.Position.X}, y:{Transform.Position.Y}");
    }

    public override void OnUpdate(float deltaTime)
    {
        // Console.WriteLine($"Transform pos at x: {transform.Position.X} and y: {transform.Position.Y}");

        if (MeanNativeApi.IsKeyPressed(Key.A))
        {
            Console.WriteLine("A was pressed");
        }

        if (MeanNativeApi.IsKeyReleased(Key.A))
        {
            Console.WriteLine("A was released");
        }

        if (MeanNativeApi.IsKeyRepeated(Key.Space))
        {
            Console.WriteLine("Space is being repeated");
            Console.WriteLine($"Deltatime is: {deltaTime}");
        }
    }
}