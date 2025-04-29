ilovbee B87 (https://www.amazon.com/iLovBee-Wireless-Mechanical-Bluetooth-Swappable/dp/B0D1XLXGBK)

Wired only (no bluetooth or RF mode). Make sure you have wb32-dfu-updater installed.

Build:
```
# Tested with https://github.com/vial-kb/vial-qmk.git, cab779b912c49c3366b949eb5cbb073bc8ff8822
$ git clone https://github.com/vial-kb/vial-qmk.git qmk_firmware
$ git -C qmk_firmware checkout cab779b912c49c3366b949eb5cbb073bc8ff8822

# Symlink into qmk_firmware folder (or vial-qmk)
$ ln -sr ilovbee_b87/ qmk_firmware/keyboards/

For Vial:
$ qmk compile -kb ilovbee_b87 -km vial
$ qmk flash ./ilovbee_b87_vial.bin

For QMK:
$ qmk compile -kb ilovbee_b87 -km default
$ qmk flash ./ilovbee_b87_default.bin
```

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+R_Shift+Esc will reset the board to bootloader mode if you have flashed the default QMK keymap
