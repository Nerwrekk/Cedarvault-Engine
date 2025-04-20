using System.Runtime.InteropServices;
using MeanScriptEngine.Components;

namespace MeanScriptEngine
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetEntityPositionDelegate(Entity entity, double x, double y);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetTransformComponentDelegate(Entity entity);

    [StructLayout(LayoutKind.Sequential)]
    public struct MeanNativeBindings
    {
        public nint SetEntityPositionPtr;
        public nint GetTransformComponentPtr;
    }

    public static class MeanNativeApi
    {
        private static SetEntityPositionDelegate? SetEntityPositionFn;
        private static GetTransformComponentDelegate? GetTransformComponentFn;

        [UnmanagedCallersOnly]
        public static void BindNativeFunctions(MeanNativeBindings mNativeBinds)
        {
            SetEntityPositionFn = Marshal.GetDelegateForFunctionPointer<SetEntityPositionDelegate>(mNativeBinds.SetEntityPositionPtr);
            GetTransformComponentFn = Marshal.GetDelegateForFunctionPointer<GetTransformComponentDelegate>(mNativeBinds.GetTransformComponentPtr);
        }

        public static void SetEntityPosition(Entity entity, double x, double y)
        {
            SetEntityPositionFn?.Invoke(entity, x, y);
        }

        public static unsafe TransformComponent GetTransformComponent(Entity entity)
        {
            var nativePtr = (nint)GetTransformComponentFn.Invoke(entity);
            return new TransformComponent(nativePtr);
        }
    }
}