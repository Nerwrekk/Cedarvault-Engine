using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using MeanScriptEngine.MeanPrimitives;

namespace MeanScriptEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        public float X, Y;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SDL_Rect
    {
        public int x, y;
        public int w, h;
    }

    namespace Components
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

        public unsafe struct SpriteComponent
        {
            private int* _width;
            private int* _height;
            private UInt32* _zIndex;
            private SDL_Rect* _srcRect;
            private MeanString _textureId;

            public string TextureId { get => _textureId.Text; set { _textureId.Text = value; } }
            public ref int Width => ref *_width;
            public ref int Height => ref *_height;
            public ref UInt32 Zindex => ref *_zIndex;
            public ref SDL_Rect SrcRect => ref *_srcRect;

            public SpriteComponent(nint nativePtr)
            {
                byte* basePtr = (byte*)nativePtr;
                _width = (int*)(basePtr + 0);
                _height = (int*)(basePtr + sizeof(int));
                _zIndex = (uint*)(basePtr + sizeof(int) * 2);
                _srcRect = (SDL_Rect*)(basePtr + 12);
                _textureId = new MeanString((nint)((byte*)_width + 32));

                // _width = (int*)nativePtr;
                // _height = _width + 1;
                // _zIndex = (UInt32*)_width + 2;
                // _srcRect = (SDL_Rect*)_width + 3;
                // _textureId = new MeanString((nint)_width + sizeof(SDL_Rect));
            }
        }
    }

}