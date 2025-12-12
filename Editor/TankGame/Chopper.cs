using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Chopper : MeanScriptBehaviour
{
    private RigidBodyComponent _rigidBodyComponent;
    private AnimationComponent _animComp;
    private SpriteComponent _spriteComponent;

    private float _movespeed = 100;
    public override void OnStart()
    {
        _rigidBodyComponent = AddComponent<RigidBodyComponent>();
        _rigidBodyComponent.Velocity = new Vector2(500, 0);


        _animComp = GetComponent<AnimationComponent>();
        _spriteComponent = GetComponent<SpriteComponent>();

        Log.Info($"NumOfFrames: {_animComp.NumOfFrames}");
        Log.Info($"StartTime: {_animComp.StartTime}");
        Log.Info($"FrameRateSpeed: {_animComp.FrameRateSpeed}");
        Log.Info($"CurrentFrame: {_animComp.CurrentFrame}");
        Log.Info($"ShouldLoop: {_animComp.ShouldLoop}");
    }

    public override void OnUpdate(float deltaTime)
    {
        if (Transform.Position.X >= 600)
        {
            _rigidBodyComponent.Velocity.X = -50 * (_movespeed * deltaTime);
        }
        else if (Transform.Position.X <= 100)
        {
            _rigidBodyComponent.Velocity.X = 50 * _movespeed * deltaTime;
        }

        if (Input.IsKeyPressed(Key.P))
        {
            _spriteComponent.TextureId = "player_walk_left_strip";
            _animComp.FrameRateSpeed = 100;
        }
        else if (Input.IsKeyReleased(Key.P))
        {
            _spriteComponent.TextureId = "player_walk_right_strip";
            _animComp.FrameRateSpeed = 10;
        }
    }
}