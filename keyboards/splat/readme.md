# splat

![splat](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Kirby Banman](https://github.com/kdbanman)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

```
qmk flash -kb splat -km default -bl uf2-split-left
qmk flash -kb splat -km default -bl uf2-split-right
```

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
