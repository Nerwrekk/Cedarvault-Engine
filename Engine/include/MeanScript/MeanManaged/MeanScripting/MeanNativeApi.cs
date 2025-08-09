using System.Runtime.InteropServices;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;
using MeanScriptEngine.MeanPrimitives;

#nullable disable
namespace MeanScriptEngine
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetEntityPositionDelegate(Entity entity, float x, float y);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetTransformComponentDelegate(Entity entity);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void* GetComponentDelegate(Entity entity, char* typeName);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public unsafe delegate void AddComponentDelegate(Entity entity, char* typeName, void* data, int size);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.I1)] //NOTE! By default, C# marshals bool as a 4-byte int (BOOL), but native C++ bool is a 1-byte value. This mismatch often causes the return value to be misinterpreted, typically always evaluating to true (because the nonzero 4 bytes contain garbage).
    public delegate bool IsKeyPressedDelegate(Key keyCode);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.I1)]
    public delegate bool IsKeyReleasedDelegate(Key keyCode);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.I1)]
    public delegate bool IsKeyRepeatedDelegate(Key keyCode);

    //NOTE!! The order of function pointers MATTERS very much and need to match the cpp struct MeanNativeBindings 1 TO 1!!
    [StructLayout(LayoutKind.Sequential)]
    internal struct MeanNativeBindings
    {
        public nint SetEntityPositionPtr;

        //Keyboard
        public nint IsKeyPressedPtr;
        public nint IsKeyReleasedPtr;
        public nint IsKeyRepeatedPtr;

        //Component
        public nint GetTransformComponentPtr;
        public nint GetComponentPtr;
        public nint AddComponentPtr;

        //MeanString
        public nint GetMeanStringPtr;
        public nint SetMeanStringPtr;
        public nint GetMeanStringSizePtr;
    }

    internal static class MeanNativeApi
    {
        private static SetEntityPositionDelegate SetEntityPositionFn;
        private static GetTransformComponentDelegate GetTransformComponentFn;
        private static IsKeyPressedDelegate IsKeyPressedFn;
        private static IsKeyReleasedDelegate IsKeyReleasedFn;
        private static IsKeyRepeatedDelegate IsKeyRepeatedFn;

        private static GetMeanStringDelegate GetMeanStringFn;
        private static SetMeanStringDelegate SetMeanStringFn;
        private static GetMeanStringSizeDelegate GetMeanStringSizeFn;

        private static GetComponentDelegate GetComponentFn;
        private static AddComponentDelegate AddComponentFn;

        [UnmanagedCallersOnly]
        public static void BindNativeFunctions(MeanNativeBindings mNativeBinds)
        {
            SetEntityPositionFn = Marshal.GetDelegateForFunctionPointer<SetEntityPositionDelegate>(mNativeBinds.SetEntityPositionPtr);
            GetTransformComponentFn = Marshal.GetDelegateForFunctionPointer<GetTransformComponentDelegate>(mNativeBinds.GetTransformComponentPtr);
            IsKeyPressedFn = Marshal.GetDelegateForFunctionPointer<IsKeyPressedDelegate>(mNativeBinds.IsKeyPressedPtr);
            IsKeyReleasedFn = Marshal.GetDelegateForFunctionPointer<IsKeyReleasedDelegate>(mNativeBinds.IsKeyReleasedPtr);
            IsKeyRepeatedFn = Marshal.GetDelegateForFunctionPointer<IsKeyRepeatedDelegate>(mNativeBinds.IsKeyRepeatedPtr);
            GetMeanStringFn = Marshal.GetDelegateForFunctionPointer<GetMeanStringDelegate>(mNativeBinds.GetMeanStringPtr);
            SetMeanStringFn = Marshal.GetDelegateForFunctionPointer<SetMeanStringDelegate>(mNativeBinds.SetMeanStringPtr);
            GetMeanStringSizeFn = Marshal.GetDelegateForFunctionPointer<GetMeanStringSizeDelegate>(mNativeBinds.GetMeanStringSizePtr);

            GetComponentFn = Marshal.GetDelegateForFunctionPointer<GetComponentDelegate>(mNativeBinds.GetComponentPtr);
            AddComponentFn = Marshal.GetDelegateForFunctionPointer<AddComponentDelegate>(mNativeBinds.AddComponentPtr);
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

        public static unsafe T GetComponent<T>(Entity entity)
        {
            IntPtr ptr = Marshal.StringToHGlobalAnsi(typeof(T).Name);
            var nativePtr = (nint)GetComponentFn.Invoke(entity, (char*)ptr.ToPointer());

            Marshal.FreeHGlobal(ptr);

            return (T)Activator.CreateInstance(typeof(T), nativePtr)!;
        }

        public static unsafe void AddComponent<T>(Entity entity, T initComponent)
        where T : unmanaged, IComponentInit
        {
            var compName = typeof(T).Name.Replace("Init", "");
            IntPtr compNamePtr = Marshal.StringToHGlobalAnsi(compName);

            IntPtr dataPtr = Marshal.AllocHGlobal(Marshal.SizeOf<T>());
            Marshal.StructureToPtr(initComponent, dataPtr, false);

            AddComponentFn.Invoke(entity, (char*)compNamePtr.ToPointer(), dataPtr.ToPointer(), Marshal.SizeOf<T>());

            Marshal.FreeHGlobal(compNamePtr);
            Marshal.FreeHGlobal(dataPtr);
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