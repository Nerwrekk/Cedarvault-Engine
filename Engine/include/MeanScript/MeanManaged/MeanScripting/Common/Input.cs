namespace MeanScriptEngine.Input
{
    public static class Input
    {
        //Returns true when the user presses the key
        public static bool IsKeyPressed(Key key)
        {
            return MeanNativeApi.IsKeyPressed(key);
        }

        //Returns true when the user releases the key
        public static bool IsKeyReleased(Key key)
        {
            return MeanNativeApi.IsKeyReleased(key);
        }

        //Returns true while the user holds down the key
        public static bool IsKeyRepeated(Key key)
        {
            return MeanNativeApi.IsKeyRepeated(key);
        }
    }
}