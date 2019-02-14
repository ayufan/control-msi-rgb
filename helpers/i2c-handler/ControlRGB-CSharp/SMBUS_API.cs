using System;
using System.Runtime.InteropServices;

namespace ControlRGB
{
    internal static class SMBUSAPI
    {
        internal const string DLL_FileName = @"C:\Program Files (x86)\MSI\MysticLight\Lib\SMBus_Engine.dll";

        [DllImport(DLL_FileName)]
        public static extern bool SMBusInitialization(int a, int b);
        [DllImport(DLL_FileName)]
        public static extern bool SMBusReload();
        [DllImport(DLL_FileName)]
        public static extern bool SMBusRelease();
        [DllImport(DLL_FileName)]
        public static extern Int32 SMBusGetAddress();
        [DllImport(DLL_FileName)]
        public static extern Int32 SMB_ByteRead(Int32 dev, Int32 addr, Int32 mode = 30);
        [DllImport(DLL_FileName)]
        public static extern bool SMB_ByteWrite(Int32 dev, Int32 addr, Int32 data, Int32 mode = 30);
    }
}
