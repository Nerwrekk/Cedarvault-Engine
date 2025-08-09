using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    namespace MeanPrimitives
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate nint GetMeanStringDelegate(nint ptr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SetMeanStringDelegate(nint ptr, string meanString);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate nuint GetMeanStringSizeDelegate(nint ptr);

        public unsafe class MeanString
        {
            private unsafe char** _nativeString;
            private UInt64* _size;
            private UInt64* _capacity;
            private nint nativePtr;

            public string Text
            {
                get
                {
                    return ToString();
                }

                set
                {
                    Set(value);
                }
            }

            public MeanString(nint ptr)
            {
                nativePtr = ptr;
                _size = (UInt64*)nativePtr;
                _capacity = (UInt64*)nativePtr + 1;
                _nativeString = (char**)(((ulong*)nativePtr) + 2);
            }

            public override string ToString()
            {
                if (nativePtr == IntPtr.Zero)
                {
                    return string.Empty;
                }

                IntPtr dataPtr = MeanNativeApi.GetMeanStringPtr(nativePtr);
                int length = (int)MeanNativeApi.GetMeanStringSizePtr(nativePtr);

                if (dataPtr == IntPtr.Zero || length == 0)
                {
                    return string.Empty;
                }

                return Marshal.PtrToStringUTF8(dataPtr, length) ?? string.Empty;
            }

            public void Set(string value)
            {
                if (nativePtr == IntPtr.Zero)
                {
                    throw new ObjectDisposedException(nameof(MeanString));
                }

                MeanNativeApi.SetMeanStringPtr(nativePtr, value);
            }
        }
    }
}