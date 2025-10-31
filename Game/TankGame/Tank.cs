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
        Log.Warn($"SpriteComponent width: {spriteComponent.Width}");
        Log.Warn($"SpriteComponent height: {spriteComponent.Height}");
        Log.Warn($"SpriteComponent zindex: {spriteComponent.Zindex}");
        Log.Warn($"SpriteComponent sdl.x: {spriteComponent.SrcRect.x}");
        Log.Warn($"SpriteComponent sdl.y: {spriteComponent.SrcRect.y}");
        Log.Warn($"SpriteComponent sdl.w: {spriteComponent.SrcRect.w}");
        Log.Warn($"SpriteComponent sdl.h: {spriteComponent.SrcRect.h}");
        Log.Warn($"SpriteComponent Texture id: {spriteComponent.TextureId}");

        spriteComponent.TextureId = "tank-panther-left";
    }

    public override void OnUpdate(float deltaTime)
    {
        // Log.Warn($"Transform pos at x: {transform.Position.X} and y: {transform.Position.Y}");
        var xPos = Transform.Position.X;
        var yPos = Transform.Position.Y;

        UpdateSprite();

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

        }

        SetEntityPosition(xPos, yPos);
    }

    private void UpdateSprite()
    {
        if (Input.IsKeyPressed(Key.A))
        {
            spriteComponent.TextureId = "tank-panther-left";
        }

        if (Input.IsKeyPressed(Key.D))
        {
            spriteComponent.TextureId = "tank-panther-right";
        }

        if (Input.IsKeyPressed(Key.W))
        {
            spriteComponent.TextureId = "tank-panther-up";
        }

        if (Input.IsKeyPressed(Key.S))
        {
            spriteComponent.TextureId = "tank-panther-down";
        }
    }
}