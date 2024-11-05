# cppinterception
This is a C++ **wrapper** for [interception][c_ception], a low level input device driver.

> The Interception API aims to build a portable programming interface that allows one to intercept and control a range of input devices.

If your're a Python developer, also check out the [Python Port & Wrapper][pyinterception] for the interception api!
In comparison, this project is far more work in progress so any contributions are much appreciated as long as the style of the project is maintained!

## Installing
Clone the repository and build the static / dynamic library using CMake or copy the required source files into your project.

## Why use the interception device driver?
Some people are under the impression that windows doesnt differentiate between *fake* inputs and *real* inputs, but that is **wrong**!

Take a look at [KBDLLHOOKSTRUCT][kbdllhook], specifically the `flags` field:
> Testing LLKHF_INJECTED (bit 4) will tell you whether the event was injected. If it was, then testing LLKHF_LOWER_IL_INJECTED (bit 1) will tell you whether or not the event was injected from a process running at lower integrity level.

This flag will **always** be set when sending an input through the windows API and there is nothing you can do about it. Programs may not pick up on this flag through the `KBDLLHOOKSTRUCT`, but it certainly proves that the OS clearly differentiates between inputs. 

If whatever you're sending inputs to currently works fine, and you are not worried about getting flagged by heuristic input detection, then by all means its totally fine to stick to pyautogui / pydirectinput.
At this point it is worth noting that alot of the more advanced anti-cheats including vanguard and some versions of EAC **will not boot** while the driver is loaded on your system, it is a very well known piece of software after all.
And if you're going to ask me how to bypass that detection - write your own driver.

## Why use this port?
- Very simple interface the low-level communication is abstracted away.
- Dynamically obtains scancodes, thus doesnt depend on the order of your keyboard layout.
- Well documented for anyone who is interested in implementing any functionality themselves.
- Supports keys that are extended or require a shift / alt / ctrl modifier to work.
- Supports 'human' movement by generating configurable [Bezier Curves][curve].

[c_ception]: https://github.com/oblitum/Interception
[pyclick]: https://github.com/patrikoss/pyclick
[curve]: https://en.wikipedia.org/wiki/B%C3%A9zier_curve
[kbdllhook]: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-kbdllhookstruct?redirectedfrom=MSDN
[pyinterception]: https://github.com/kennyhml/pyinterception
