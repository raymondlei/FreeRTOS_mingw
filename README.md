# FreeRTOS

This repository contains the FreeRTOS kernel and the WIN32-MingW simulator demo.

## Functional example (based on Example004/main.c)

A new simulator demo mode is available in [WIN32-MingW/main_functional_example.c](./WIN32-MingW/main_functional_example.c).  
It creates two tasks with different priorities, each printing its own message every 250 ms, matching the behavior of the attached Example004 `main.c`.

### Build and run

From [WIN32-MingW/](./WIN32-MingW):

```powershell
mingw32-make EXAMPLE004_DEMO=1
..\build_functional\RTOSDemo.exe
```

The existing modes remain available:
- `mingw32-make BLINKY_DEMO=1` for the blinky demo
- `mingw32-make` for the full demo