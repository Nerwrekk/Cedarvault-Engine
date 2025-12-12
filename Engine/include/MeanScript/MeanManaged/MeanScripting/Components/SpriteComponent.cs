
using MeanScriptEngine.MeanPrimitives;

namespace MeanScriptEngine.Components
{
    public unsafe struct SpriteComponent : IComponent
    {
        private UInt32* _zIndex;
        private MeanString _textureId;

        public string TextureId { get => _textureId.Text; set { _textureId.Text = value; } }
        public ref UInt32 Zindex => ref *_zIndex;

        public SpriteComponent(nint nativePtr)
        {
            _zIndex = (uint*)nativePtr;
            //we need to increment by 8 because MeanString starts with an uint64
            //and since zIndex is an uint32 which means only 4 bytes, an additional 4 bytes are added 
            //beforehand as padding
            _textureId = new MeanString(nativePtr + 8);
        }
    }
}