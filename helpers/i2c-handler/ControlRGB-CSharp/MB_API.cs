using System.Runtime.InteropServices;

namespace ControlRGB
{
    internal static class MBAPI
    {
        internal const string DLL_FileName = @"C:\Program Files (x86)\MSI\MysticLight\Lib\MBAPI_x86.dll";

        [DllImport(DLL_FileName)]
        public static extern bool CheckBTLED();
        [DllImport(DLL_FileName)]
        public static extern bool CheckECRAM(out bool data);
        [DllImport(DLL_FileName)]
        public static extern bool CheckLANLED();
        [DllImport(DLL_FileName, CharSet = CharSet.Auto)]
        public static extern bool CheckMBVersion(string _csMB, string _csMBVer, string _csMBMarket, string _csMBSIOInit);
        [DllImport(DLL_FileName)]
        public static extern bool CloseLEDControl(bool bBackToDefault);
        [DllImport(DLL_FileName)]
        public static extern bool ControlBTLED(int value);
        [DllImport(DLL_FileName)]
        public static extern bool ControlCorsairDRAMLED(int changetime, int darktime, int colornum, int r, int g, int b, int brightN, int brightD);
        [DllImport(DLL_FileName)]
        public static extern bool ControlCorsairProDRAMLED(int style, int colorType, int direction, int r, int g, int b, int bright, int speed);
        [DllImport(DLL_FileName)]
        public static extern bool ControlFANLED(int value);
        [DllImport(DLL_FileName)]
        public static extern bool ControlGALAXDRAMLED(int style, int r, int g, int b);
        [DllImport(DLL_FileName)]
        public static extern bool ControlGALAXDRAMLED_Byte(int data0, int data1, int data2, int data3);
        [DllImport(DLL_FileName)]
        public static extern bool ControlKingStonDRAMLED(int r, int g, int b, int speed, int style);
        [DllImport(DLL_FileName)]
        public static extern bool ControlKingStonDRAMLED_X299(int offset, int data);
        [DllImport(DLL_FileName)]
        public static extern bool ControlLANLED(int value);
        [DllImport(DLL_FileName)]
        public static extern bool ControlMICRONDRAMLED(int style, int r, int g, int b);
        [DllImport(DLL_FileName)]
        public static extern bool CorsairProDRAMSync();
        [DllImport(DLL_FileName)]
        public static extern bool GetCPU_GameBoostSec(ref int sec);
        [DllImport(DLL_FileName)]
        public static extern bool GetCPU_MaxRatio(ref int ratio);
        [DllImport(DLL_FileName)]
        public static extern bool GetCPUTemp(ref int Temp);
        [DllImport(DLL_FileName, CharSet = CharSet.Unicode)]
        public static extern bool GetDRAMInfo(int slot, [MarshalAs(UnmanagedType.BStr)] out string manufac, [MarshalAs(UnmanagedType.BStr)] out string partnum);
        [DllImport(DLL_FileName, CharSet = CharSet.Unicode)]
        public static extern bool GetDRAMInfo2(int slot, [MarshalAs(UnmanagedType.BStr)] out string manufac, [MarshalAs(UnmanagedType.BStr)] out string size, [MarshalAs(UnmanagedType.BStr)] out string width);
        [DllImport(DLL_FileName)]
        public static extern bool GetECSpace(int Page, int Index, out int data);
        [DllImport(DLL_FileName)]
        public static extern bool GetSIO_DefaultWhite(ref bool defWhite);
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_Change(int iStyle, int iR = 0, int iG = 0, int iB = 0, int iInterval = 0);
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_Initial();
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_MarqueeStop();
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_MeteorStop();
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_ONOFF(int ledmode);
        [DllImport(DLL_FileName)]
        public static extern bool GSKDDR_RainbowStop();
        [DllImport(DLL_FileName)]
        public static extern bool InitialDDRTIMING();
        [DllImport(DLL_FileName)]
        public static extern bool IT8295QFN_OP(int mode, int r, int g, int b, int addr);
        [DllImport(DLL_FileName)]
        public static extern bool KeepRenesasLED();
        [DllImport(DLL_FileName)]
        public static extern bool LEDAudioControl(int ledmode);
        [DllImport(DLL_FileName)]
        public static extern bool LEDBOTControl(int ledmode);
        [DllImport(DLL_FileName)]
        public static extern bool LEDControl(int ledmode);
        [DllImport(DLL_FileName)]
        public static extern bool LEDMysticControl(int ledmode);
        [DllImport(DLL_FileName)]
        public static extern bool ReleaseDll();
        [DllImport(DLL_FileName)]
        public static extern bool RenesasLEDControlV3(int index70, int index71, int index80, int index81, int index82, int index83, int cmd, int data, int r, int g, int b, int e0, int e1, int e2, int e3, int e5);
        [DllImport(DLL_FileName)]
        public static extern bool ResetLED();
        [DllImport(DLL_FileName)]
        public static extern bool SetAudioBreathingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetAudioDualBlinkingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetAudioFlashingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetBreathingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetColorMode(int R, int G, int B);
        [DllImport(DLL_FileName)]
        public static extern bool SetCorsairDRAMLED(int mode);
        [DllImport(DLL_FileName)]
        public static extern bool SetDualBlinkingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetECRAM_Color(byte r, byte g, byte b);
        [DllImport(DLL_FileName)]
        public static extern bool SetECRAM_Mode(int mode);
        [DllImport(DLL_FileName)]
        public static extern bool SetECSpace(int Page, int Index, int Data);
        [DllImport(DLL_FileName)]
        public static extern bool SetExtendSequence(int mode);
        [DllImport(DLL_FileName)]
        public static extern bool SetFlashingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetLEDModelName(int model);
        [DllImport(DLL_FileName)]
        public static extern bool SetMusicLED(bool mystic, bool on, int mode);
        [DllImport(DLL_FileName)]
        public static extern bool SetMusicVolumeV2(int left, int right);
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticBreathingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticDualBlinkingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticFlashingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticLEDColor(int R, int G, int B);
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticLightningMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticMarqueeMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticMeteorMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticRainbowMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetMysticSequenceMode(int mode);
        [DllImport(DLL_FileName)]
        public static extern bool SetRainbowBreathingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetRainbowFlashingMode();
        [DllImport(DLL_FileName)]
        public static extern bool SetRainbowMode();
        [DllImport(DLL_FileName)]
        public static extern bool SMBusControl(int addr, int offset, int data);
        [DllImport(DLL_FileName)]
        public static extern bool SupportLED();
    }
}
