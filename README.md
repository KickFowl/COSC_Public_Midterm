**A basic renderer directly interfacing with the Win32API.**

If you work in this codebase I recommend going through drawQueue.h and Canvas.h at most.
I wouldn't recommend touching the window manager.
If you want to do inputs the input Handel class receives **all** keyboard and mouse events from the Win32API just make sure to hand it to your window.
