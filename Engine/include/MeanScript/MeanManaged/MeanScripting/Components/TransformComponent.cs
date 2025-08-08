
namespace MeanScriptEngine.Components
{
    public unsafe struct TransformComponent
    {
        private Vector2* _position;
        private Vector2* _scale;
        private double* _rotation;

        public ref Vector2 Position => ref *_position;
        public ref Vector2 Scale => ref *_scale;
        public ref double Rotation => ref *_rotation;

        public TransformComponent(nint nativePtr)
        {
            // Assumes TransformComponent starts with position/scale/rotation in order
            _position = (Vector2*)nativePtr;
            _scale = _position + 1;
            _rotation = (double*)_position + 2;
        }
    }
}