
using MeanScriptEngine.MeanPrimitives;

namespace MeanScriptEngine.Components
{
    public unsafe struct SpriteComponent : IComponent
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