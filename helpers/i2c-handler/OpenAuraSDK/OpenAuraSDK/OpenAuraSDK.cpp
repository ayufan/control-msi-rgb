// OpenAuraSDK.cpp : Defines the exported functions for the DLL application.
//

#include "i2c_smbus.h"
#include "i2c_smbus_piix4.h"
#include "i2c_smbus_i801.h"
#include "AuraController.h"
#include "OpenAuraSDK.h"
#include <memory>
#include <vector>

std::vector<AuraController *> controllers;

void DbgPrintf(const char *fmt, ...)
{
	va_list marker;
	char szBuf[256];

	va_start(marker, fmt);
	vsprintf(szBuf, fmt, marker);
	va_end(marker);

	OutputDebugStringA(szBuf);
	fprintf(stdout, "%s", szBuf);
}

i2c_smbus_interface * CreateAuraBus(AuraBusDriverType driver, unsigned int base)
{
	switch (driver)
	{
	case I2C_DRIVER_SMBUS_PIIX4:
		{
			auto bus = new i2c_smbus_piix4();
			bus->piix4_smba = base;
			return bus;
		}

	case I2C_DRIVER_SMBUS_I801:
		{
			auto bus = new i2c_smbus_i801();
			bus->i801_smba = base;
			return bus;
		}

	default:
		return NULL;
	}
}

void CreateAuraDevice(AuraBusDriverType driver, unsigned int base, aura_dev_id dev)
{
    AuraController * aura;

    aura = new AuraController();
    aura->bus = CreateAuraBus(driver, base);
    aura->dev = dev;

    controllers.push_back(aura);
}

//code adapted from i2c-tools i2cdetect.c
#define MODE_AUTO   0
#define MODE_QUICK  1
#define MODE_READ   2
#define MODE_FUNC   3

std::vector<int> DetectI2C(AuraBusDriverType driver, unsigned int base, int mode)
{
    int i, j;
    int res;
    int slave_addr;

	std::vector<int> slaves;

	std::auto_ptr<i2c_smbus_interface> bus(CreateAuraBus(driver, base));

	DbgPrintf("DetectI2C: %04x, mode: %d\n", base, mode);
    DbgPrintf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

    for (i = 0; i < 128; i += 16)
    {
        DbgPrintf("%02x: ", i);

        for (j = 0; j < 16; j++)
        {
            /* Set slave address */
            slave_addr = i + j;

			if (slave_addr == 0x08)
			{
				int a = 0;
			}
            /* Probe this address */
            switch (mode)
            {
            case MODE_QUICK:
                res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            case MODE_READ:
                res = bus->i2c_smbus_read_byte(slave_addr);
                break;
            default:
                if ((i + j >= 0x30 && i + j <= 0x37)
                 || (i + j >= 0x50 && i + j <= 0x5F))
                    res = bus->i2c_smbus_read_byte(slave_addr);
                else
                    res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            }

            if (res < 0)
            {
                DbgPrintf("-- ");
            }
            else
            {
                DbgPrintf("%02x ", i + j);
				slaves.push_back(i + j);
            }
        }
        DbgPrintf("\n");
    }
	DbgPrintf("\n");
	return slaves;
}

#define WRITE_COLOR(bus, dev, r,g,b,a) do { \
	bus->i2c_smbus_write_byte_data(dev, 32, r); \
	bus->i2c_smbus_write_byte_data(dev, 32, g); \
	bus->i2c_smbus_write_byte_data(dev, 32, b); \
	bus->i2c_smbus_write_byte_data(dev, 32, a); \
} while(0)

void ControlCorsairProDRAMLED(AuraBusDriverType driver, unsigned int base, aura_dev_id dev, int style, int colorType, int direction, int r, int g, int b, int bright, int speed)
{
	std::auto_ptr<i2c_smbus_interface> bus(CreateAuraBus(driver, base));
	DbgPrintf("ControlCorsairProDRAMLED: %04x, dev: %02x\n", base, dev);
	DbgPrintf("style: %d, colorType: %d, direction: %d, r: %d, g: %d, b: %d, bright: %d, speed: %d\n",
		style, colorType, direction, r, g, b, bright, speed);

	bus->i2c_smbus_write_byte_data(dev, 16, 50); // bright

#if 1
	bus->i2c_smbus_write_byte_data(dev, 33, 0);

#if 1
	for(int i = 0; i<10; ++i) {
		WRITE_COLOR(bus, dev, 0, 0, 128, 255);
	}
#else
	WRITE_COLOR(bus, dev, 255, 255, 255, 255);
	WRITE_COLOR(bus, dev, 255, 0, 0, 255);
	WRITE_COLOR(bus, dev, 0, 255, 0, 255);
	WRITE_COLOR(bus, dev, 0, 0, 255, 255);
	WRITE_COLOR(bus, dev, 255, 255, 0, 255);
	WRITE_COLOR(bus, dev, 255, 0, 255, 255);
	WRITE_COLOR(bus, dev, 0, 255, 255, 255);
	WRITE_COLOR(bus, dev, 128, 128, 128, 255);
	WRITE_COLOR(bus, dev, 0, 128, 0, 255);
	WRITE_COLOR(bus, dev, 0, 128, 0, 255);
#endif
#endif

#if 1
	bus->i2c_smbus_write_byte_data(dev, 130, 2);
	bus->i2c_smbus_write_byte_data(dev, 33, 0);

	bus->i2c_smbus_write_byte_data(dev, 32, 3); // style
	bus->i2c_smbus_write_byte_data(dev, 32, 2); // speed
	bus->i2c_smbus_write_byte_data(dev, 32, 1); // color type
	bus->i2c_smbus_write_byte_data(dev, 32, 0); // ?

	WRITE_COLOR(bus, dev, 99, 33, 129, 255);
	WRITE_COLOR(bus, dev, 99, 33, 129, 255);
	WRITE_COLOR(bus, dev, 0, 0, 0, 0);
	WRITE_COLOR(bus, dev, 0, 0, 0, 0);
#endif

	bus->i2c_smbus_write_byte_data(dev, 130, 1);
	bus->i2c_smbus_write_byte_data(dev, 192, 0);
}

void DumpI2CDev(AuraBusDriverType driver, unsigned int base, aura_dev_id dev)
{
	int i, j;

	std::auto_ptr<i2c_smbus_interface> bus(CreateAuraBus(driver, base));

	DbgPrintf("DumpI2CDev: %04x, dev: %02x\n", base, dev);

	DbgPrintf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

	for (i = 0; i < 256; i += 16)
	{
		DbgPrintf("%02x: ", i);

		for (j = 0; j < 16; j++)
		{
			auto res = bus->i2c_smbus_read_byte_data(dev, i + j);

			if (res >= 0) {
				DbgPrintf("%02x ", res);
			}
			else {
				DbgPrintf("-- ", res);
			}
		}
		DbgPrintf("\n");
	}
	DbgPrintf("\n");
}

void DumpAuraDevices()
{
    for (unsigned int i = 0; i < controllers.size(); i++)
    {
        unsigned char dcolor0 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x00 );
        unsigned char dcolor1 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x01 );
        unsigned char dcolor2 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x02 );
        unsigned char dcolor3 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x03 );
        unsigned char dcolor4 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x04 );
        unsigned char dcolor5 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x05 );
        unsigned char dcolor6 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x06 );
        unsigned char dcolor7 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x07 );
        unsigned char dcolor8 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x08 );
        unsigned char dcolor9 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x09 );
        unsigned char dcolorA = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0A );
        unsigned char dcolorB = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0B );
        unsigned char dcolorC = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0C );
        unsigned char dcolorD = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0D );
        unsigned char dcolorE = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_DIRECT + 0x0E );

        unsigned char ecolor0 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x00 );
        unsigned char ecolor1 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x01 );
        unsigned char ecolor2 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x02 );
        unsigned char ecolor3 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x03 );
        unsigned char ecolor4 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x04 );
        unsigned char ecolor5 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x05 );
        unsigned char ecolor6 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x06 );
        unsigned char ecolor7 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x07 );
        unsigned char ecolor8 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x08 );
        unsigned char ecolor9 = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x09 );
        unsigned char ecolorA = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0A );
        unsigned char ecolorB = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0B );
        unsigned char ecolorC = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0C );
        unsigned char ecolorD = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0D );
        unsigned char ecolorE = controllers[i]->AuraRegisterRead( AURA_REG_COLORS_EFFECT + 0x0E );

        unsigned char direct  = controllers[i]->AuraRegisterRead( AURA_REG_DIRECT               );
        unsigned char mode    = controllers[i]->AuraRegisterRead( AURA_REG_MODE                 );

        DbgPrintf("Controller %d\n", i);
        DbgPrintf("Direct Mode:    %d \n", direct  );
        DbgPrintf("Mode Value:     %d \n", mode    );
        DbgPrintf("Direct Color 0: %d \n", dcolor0);
        DbgPrintf("Direct Color 1: %d \n", dcolor1);
        DbgPrintf("Direct Color 2: %d \n", dcolor2);
        DbgPrintf("Direct Color 3: %d \n", dcolor3);
        DbgPrintf("Direct Color 4: %d \n", dcolor4);
        DbgPrintf("Direct Color 5: %d \n", dcolor5);
        DbgPrintf("Direct Color 6: %d \n", dcolor6);
        DbgPrintf("Direct Color 7: %d \n", dcolor7);
        DbgPrintf("Direct Color 8: %d \n", dcolor8);
        DbgPrintf("Direct Color 9: %d \n", dcolor9);
        DbgPrintf("Direct Color A: %d \n", dcolorA);
        DbgPrintf("Direct Color B: %d \n", dcolorB);
        DbgPrintf("Direct Color C: %d \n", dcolorC);
        DbgPrintf("Direct Color D: %d \n", dcolorD);
        DbgPrintf("Direct Color E: %d \n", dcolorE);
        DbgPrintf("Effect Color 0: %d \n", ecolor0);
        DbgPrintf("Effect Color 1: %d \n", ecolor1);
        DbgPrintf("Effect Color 2: %d \n", ecolor2);
        DbgPrintf("Effect Color 3: %d \n", ecolor3);
        DbgPrintf("Effect Color 4: %d \n", ecolor4);
        DbgPrintf("Effect Color 5: %d \n", ecolor5);
        DbgPrintf("Effect Color 6: %d \n", ecolor6);
        DbgPrintf("Effect Color 7: %d \n", ecolor7);
        DbgPrintf("Effect Color 8: %d \n", ecolor8);
        DbgPrintf("Effect Color 9: %d \n", ecolor9);
        DbgPrintf("Effect Color A: %d \n", ecolorA);
        DbgPrintf("Effect Color B: %d \n", ecolorB);
        DbgPrintf("Effect Color C: %d \n", ecolorC);
        DbgPrintf("Effect Color D: %d \n", ecolorD);
        DbgPrintf("Effect Color E: %d \n", ecolorE);
    }
}

int main()
{
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x77);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x71);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x73);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B00, 0x74);
    //CreateAuraDevice(I2C_DRIVER_SMBUS_PIIX4, 0x0B20, 0x4E);
    CreateAuraDevice(I2C_DRIVER_SMBUS_I801, 0xf040, 0x02);

    //DumpAuraDevices();

    auto slaves = DetectI2C(I2C_DRIVER_SMBUS_I801, 0xf040, MODE_AUTO);
	slaves.clear();
	slaves.push_back(82>>1);
	slaves.push_back(182 >> 1);
	for (auto slave_addr : slaves) {
		DumpI2CDev(I2C_DRIVER_SMBUS_I801, 0xf040, slave_addr);
	}

	ControlCorsairProDRAMLED(I2C_DRIVER_SMBUS_I801, 0xf040, 178 >> 1,
		0, 0, 0, 255, 255, 255, 255, 2);
	ControlCorsairProDRAMLED(I2C_DRIVER_SMBUS_I801, 0xf040, 182 >> 1,
		0, 0, 0, 255, 255, 255, 255, 2);
	for (auto slave_addr : slaves) {
		DumpI2CDev(I2C_DRIVER_SMBUS_I801, 0xf040, slave_addr);
	}

    //for (unsigned int i = 0; i < controllers.size(); i++)
    //{
    //    controllers[i]->AuraRegisterWrite(AURA_REG_COLORS_EFFECT, 255);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_DIRECT, 0);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_MODE, AURA_MODE_RAINBOW);
    //    controllers[i]->AuraRegisterWrite(AURA_REG_APPLY, AURA_APPLY_VAL);
    //}

    return TRUE;
}