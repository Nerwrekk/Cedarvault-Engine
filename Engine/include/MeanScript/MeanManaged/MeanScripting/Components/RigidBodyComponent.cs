namespace MeanScriptEngine.Components
{
    public unsafe struct RigidBodyComponent : IComponent
    {
        private Vector2* _velocity;

        public ref Vector2 Velocity => ref *_velocity;

        public RigidBodyComponent(nint nativePtr)
        {
            _velocity = (Vector2*)nativePtr;
        }
    }
}