# Control MSI RGBs

This is simple tool where API were discovered from `MSI MysticLight` tool.

It allows to control RGBs on:

- MSI Z370 Krait Gaming (the Mystic Light),
- Corsair Vengeance RGB Pro

## Use

Clone this repository, install `i2c-tools` and tinker with the bash scripts in the root.

## Hacking

Look at `helpers/`. There's a XML definition to `API Monitor` application that
allows you to easily inspect the behavior of `MSI Mystic Light` the `LEDKeeper.exe` tool.

Next:
1. Start Mystic Light,
2. Stop Mystic Light Service,
3. Put API Monitor into `API/` folder,
4. Start API Monitor x32 in privileged mode,
5. Terminate `LEDKeeper.exe` from API Monitor,
6. Enable monitoring of functions of `MBAPI_x86.dll` and `SMBus_Engine.dll`
7. From API Monitor start the `LEDKeeper.exe`,
8. Tinker with Mystic Light,
9. Record SMBus calls.

## Author, License

Kamil Trzciński, 2019, MIT
