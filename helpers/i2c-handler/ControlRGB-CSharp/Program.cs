using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlRGB
{
    class Program
    {
        static void Main(string[] args)
        {
            var result = MBAPI.CheckMBVersion("MSI-7B46", "1", "Z370 KRAIT GAMING", "T");
            if (!result)
            {
                Console.WriteLine("Failed to initialize MB");
                Environment.Exit(1);
            }

            result = MBAPI.InitialDDRTIMING();
            if (!result)
            {
                Console.WriteLine("Failed to initialize DDR");
                Environment.Exit(1);
            }

            result = MBAPI.ControlCorsairProDRAMLED(1, 0, 0, 99, 33, 129, 80, 2);
            Console.WriteLine("CorsairPRODRAMLED: {0}", result);
        }
    }
}
