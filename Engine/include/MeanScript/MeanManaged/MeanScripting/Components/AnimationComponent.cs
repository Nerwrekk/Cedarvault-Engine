
namespace MeanScriptEngine.Components
{
    public unsafe struct AnimationComponent : IComponent
    {
        private int* _numOfFrames;
        private int* _currentFrame;
        private int* _frameRateSpeed;
        private int* _startTime;
        private bool* _shouldLoop;

        public ref int NumOfFrames => ref *_numOfFrames;
        public ref int CurrentFrame => ref *_currentFrame;
        public ref int FrameRateSpeed => ref *_frameRateSpeed;
        public ref int StartTime => ref *_startTime;
        public ref bool ShouldLoop => ref *_shouldLoop;

        public AnimationComponent(nint nativePtr)
        {
            _numOfFrames = (int*)nativePtr;
            _currentFrame = _numOfFrames + 1;
            _frameRateSpeed = _numOfFrames + 2;
            _startTime = _numOfFrames + 3;
            _shouldLoop = (bool*)_numOfFrames + 4;
        }
    }
}