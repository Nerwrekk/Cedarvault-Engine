using System;
using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Tank : MeanScriptBehaviour
{
    private float moveSpeed = 130f;
    private SpriteComponent spriteComponent;
    public override void OnStart()
    {
        Console.WriteLine($"[Tank] OnStart, is bound to entity with id: {Entity.Id}");
        Console.WriteLine($"Tank starting position is: x: {Transform.Position.X}, y:{Transform.Position.Y}");

        spriteComponent = GetComponent<SpriteComponent>();
        Console.WriteLine($"SpriteComponent width: {spriteComponent.Width}");
        Console.WriteLine($"SpriteComponent height: {spriteComponent.Height}");
        Console.WriteLine($"SpriteComponent zindex: {spriteComponent.Zindex}");
        Console.WriteLine($"SpriteComponent sdl.x: {spriteComponent.SrcRect.x}");
        Console.WriteLine($"SpriteComponent sdl.y: {spriteComponent.SrcRect.y}");
        Console.WriteLine($"SpriteComponent sdl.w: {spriteComponent.SrcRect.w}");
        Console.WriteLine($"SpriteComponent sdl.h: {spriteComponent.SrcRect.h}");
        Console.WriteLine($"SpriteComponent Texture id: {spriteComponent.TextureId}");

        spriteComponent.TextureId = "tank-panther-left";
    }

    public override void OnUpdate(float deltaTime)
    {
        // Console.WriteLine($"Transform pos at x: {transform.Position.X} and y: {transform.Position.Y}");
        var xPos = Transform.Position.X;
        var yPos = Transform.Position.Y;

        if (MeanNativeApi.IsKeyRepeated(Key.A))
        {
            xPos = xPos - (this.moveSpeed * deltaTime);
            spriteComponent.TextureId = "tank-panther-left";
        }

        if (MeanNativeApi.IsKeyRepeated(Key.D))
        {
            xPos = xPos + (this.moveSpeed * deltaTime);
            spriteComponent.TextureId = "tank-panther-right";
        }

        if (MeanNativeApi.IsKeyRepeated(Key.W))
        {
            yPos = yPos - (this.moveSpeed * deltaTime);
            spriteComponent.TextureId = "tank-panther-up";
        }

        if (MeanNativeApi.IsKeyRepeated(Key.S))
        {
            yPos = yPos + (this.moveSpeed * deltaTime);
            spriteComponent.TextureId = "tank-panther-down";
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

        MeanNativeApi.SetEntityPosition(Entity, xPos, yPos);
    }
}