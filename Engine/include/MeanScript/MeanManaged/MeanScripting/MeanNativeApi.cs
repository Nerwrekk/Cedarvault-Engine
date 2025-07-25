using System.Runtime.InteropServices;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;
using MeanScriptEngine.MeanPrimitives;

namespace MeanScriptEngine
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetEntityPositionDelegate(Entity entity, float x, float y);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetTransformComponentDelegate(Entity entity);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetSpriteComponentDelegate(Entity entity);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate IntPtr GetSpriteTextureIdDelegate(Entity entity);

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
        public nint GetSpriteComponentPtr;
        public nint GetSpriteTextureIdPtr;
        public nint GetMeanStringPtr;
        public nint SetMeanStringPtr;
        public nint GetMeanStringSizePtr;
    }

    public static class MeanNativeApi
    {
        private static SetEntityPositionDelegate? SetEntityPositionFn;
        private static GetTransformComponentDelegate? GetTransformComponentFn;
        private static IsKeyPressedDelegate IsKeyPressedFn;
        private static IsKeyReleasedDelegate IsKeyReleasedFn;
        private static IsKeyRepeatedDelegate IsKeyRepeatedFn;
        private static GetSpriteComponentDelegate GetSpriteComponentFn;
        private static GetSpriteTextureIdDelegate GetSpriteTextureIdFn;

        private static GetMeanStringDelegate GetMeanStringFn;
        private static SetMeanStringDelegate SetMeanStringFn;
        private static GetMeanStringSizeDelegate GetMeanStringSizeFn;

        [UnmanagedCallersOnly]
        public static void BindNativeFunctions(MeanNativeBindings mNativeBinds)
        {
            SetEntityPositionFn = Marshal.GetDelegateForFunctionPointer<SetEntityPositionDelegate>(mNativeBinds.SetEntityPositionPtr);
            GetTransformComponentFn = Marshal.GetDelegateForFunctionPointer<GetTransformComponentDelegate>(mNativeBinds.GetTransformComponentPtr);
            IsKeyPressedFn = Marshal.GetDelegateForFunctionPointer<IsKeyPressedDelegate>(mNativeBinds.IsKeyPressedPtr);
            IsKeyReleasedFn = Marshal.GetDelegateForFunctionPointer<IsKeyReleasedDelegate>(mNativeBinds.IsKeyReleasedPtr);
            IsKeyRepeatedFn = Marshal.GetDelegateForFunctionPointer<IsKeyRepeatedDelegate>(mNativeBinds.IsKeyRepeatedPtr);
            GetSpriteComponentFn = Marshal.GetDelegateForFunctionPointer<GetSpriteComponentDelegate>(mNativeBinds.GetSpriteComponentPtr);
            GetSpriteTextureIdFn = Marshal.GetDelegateForFunctionPointer<GetSpriteTextureIdDelegate>(mNativeBinds.GetSpriteTextureIdPtr);
            GetMeanStringFn = Marshal.GetDelegateForFunctionPointer<GetMeanStringDelegate>(mNativeBinds.GetMeanStringPtr);
            SetMeanStringFn = Marshal.GetDelegateForFunctionPointer<SetMeanStringDelegate>(mNativeBinds.SetMeanStringPtr);
            GetMeanStringSizeFn = Marshal.GetDelegateForFunctionPointer<GetMeanStringSizeDelegate>(mNativeBinds.GetMeanStringSizePtr);
        }

        public static void SetMeanStringPtr(nint meanStringPtr, [MarshalAs(UnmanagedType.LPUTF8Str)] string value)
        {
            if (meanStringPtr == IntPtr.Zero)
            {
                return;
            }

            SetMeanStringFn(meanStringPtr, value);
        }

        public static nint GetMeanStringPtr(nint meanStringPtr)
        {
            if (meanStringPtr == IntPtr.Zero)
            {
                return IntPtr.Zero;
            }

            return GetMeanStringFn(meanStringPtr);
        }

        public static nuint GetMeanStringSizePtr(nint meanStringPtr)
        {
            if (meanStringPtr == IntPtr.Zero)
            {
                return (nuint)IntPtr.Zero;
            }

            return GetMeanStringSizeFn(meanStringPtr);
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

        public static unsafe SpriteComponent GetSpriteComponent(Entity entity)
        {
            var nativePtr = (nint)GetSpriteComponentFn.Invoke(entity);

            return new SpriteComponent(nativePtr);
        }

        public static unsafe string GetSpriteTextureId(Entity entity)
        {
            var textureId = GetSpriteTextureIdFn.Invoke(entity);

            return Marshal.PtrToStringUTF8(textureId);
        }
    }
}