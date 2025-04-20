using System.Runtime.InteropServices;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

namespace MeanScriptEngine
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetEntityPositionDelegate(Entity entity, float x, float y);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetTransformComponentDelegate(Entity entity);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate bool IsKeyPressedDelegate(Key keyCode);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate bool IsKeyReleasedDelegate(Key keyCode);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate bool IsKeyRepeatedDelegate(Key keyCode);

    [StructLayout(LayoutKind.Sequential)]
    public struct MeanNativeBindings
    {
        public nint SetEntityPositionPtr;
        public nint GetTransformComponentPtr;
        public nint IsKeyPressedPtr;
        public nint IsKeyReleasedPtr;
        public nint IsKeyRepeatedPtr;
    }

    public static class MeanNativeApi
    {
        private static SetEntityPositionDelegate? SetEntityPositionFn;
        private static GetTransformComponentDelegate? GetTransformComponentFn;
        private static IsKeyPressedDelegate IsKeyPressedFn;
        private static IsKeyReleasedDelegate IsKeyReleasedFn;
        private static IsKeyRepeatedDelegate IsKeyRepeatedFn;

        [UnmanagedCallersOnly]
        public static void BindNativeFunctions(MeanNativeBindings mNativeBinds)
        {
            SetEntityPositionFn = Marshal.GetDelegateForFunctionPointer<SetEntityPositionDelegate>(mNativeBinds.SetEntityPositionPtr);
            GetTransformComponentFn = Marshal.GetDelegateForFunctionPointer<GetTransformComponentDelegate>(mNativeBinds.GetTransformComponentPtr);
            IsKeyPressedFn = Marshal.GetDelegateForFunctionPointer<IsKeyPressedDelegate>(mNativeBinds.IsKeyPressedPtr);
            IsKeyReleasedFn = Marshal.GetDelegateForFunctionPointer<IsKeyReleasedDelegate>(mNativeBinds.IsKeyReleasedPtr);
            IsKeyRepeatedFn = Marshal.GetDelegateForFunctionPointer<IsKeyRepeatedDelegate>(mNativeBinds.IsKeyRepeatedPtr);
        }

        public static void SetEntityPosition(Entity entity, float x, float y)
        {
            SetEntityPositionFn?.Invoke(entity, x, y);
        }

        public static unsafe TransformComponent GetTransformComponent(Entity entity)
        {
            var nativePtr = (nint)GetTransformComponentFn.Invoke(entity);

            return new TransformComponent(nativePtr);
        }

        public static bool IsKeyPressed(Key keyCode)
        {
            return IsKeyPressedFn(keyCode);
        }

        public static bool IsKeyReleased(Key keyCode)
        {
            return IsKeyReleasedFn(keyCode);
        }

        public static bool IsKeyRepeated(Key keyCode)
        {
            return IsKeyRepeatedFn(keyCode);
        }
    }
}