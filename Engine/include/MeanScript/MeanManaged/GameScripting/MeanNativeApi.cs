using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetEntityPositionDelegate(Entity entity, double x, double y);

    [StructLayout(LayoutKind.Sequential)]
    public struct MeanNativeBindings
    {
        public nint SetEntityPositionPtr;
    }

    public static class MeanNativeApi
    {
        private static SetEntityPositionDelegate? SetEntityPositionFn;

        [UnmanagedCallersOnly]
        public static void BindNativeFunctions(MeanNativeBindings mNativeBinds)
        {
            SetEntityPositionFn = Marshal.GetDelegateForFunctionPointer<SetEntityPositionDelegate>(mNativeBinds.SetEntityPositionPtr);
        }

        public static void SetEntityPosition(Entity entity, double x, double y)
        {
            SetEntityPositionFn?.Invoke(entity, x, y);
        }
    }
}