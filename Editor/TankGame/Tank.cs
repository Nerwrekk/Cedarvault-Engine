using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Tank : MeanScriptBehaviour
{
    private float moveSpeed = 130f;
    private SpriteComponent spriteComponent;
    public override void OnStart()
    {
        Log.Warn($"[Tank] OnStart, is bound to entity with id: {Entity.Id}");
        Log.Warn($"Tank starting position is: x: {Transform.Position.X}, y:{Transform.Position.Y}");

        spriteComponent = GetComponent<SpriteComponent>();
    }

    public override void OnUpdate(float deltaTime)
    {
        // Log.Warn($"Transform pos at x: {transform.Position.X} and y: {transform.Position.Y}");
        var xPos = Transform.Position.X;
        var yPos = Transform.Position.Y;

        if (Input.IsKeyRepeated(Key.A))
        {
            xPos = xPos - (this.moveSpeed * deltaTime);
        }

        if (Input.IsKeyRepeated(Key.D))
        {
            xPos = xPos + (this.moveSpeed * deltaTime);
        }

        if (Input.IsKeyRepeated(Key.W))
        {
            yPos = yPos - (this.moveSpeed * deltaTime);
        }

        if (Input.IsKeyRepeated(Key.S))
        {
            yPos = yPos + (this.moveSpeed * deltaTime);
        }

        if (Input.IsKeyReleased(Key.A))
        {
            Log.Warn("A was released");
        }

        if (Input.IsKeyRepeated(Key.Space))
        {
            Log.Warn("Space is being repeated");
            Log.Warn($"Deltatime is: {deltaTime}");

            Log.Warn($"Transform pos at x: {Transform.Position.X} and y: {Transform.Position.Y}");
        }

        SetEntityPosition(xPos, yPos);
    }
}