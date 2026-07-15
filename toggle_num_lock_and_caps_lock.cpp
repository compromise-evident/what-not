/*Run it: "apt install g++ geany libx11-dev". Open the .cpp in Geany.
Go to Build >> Set Build Commands. Where it says "Compile" and "Build", append " -lX11".
Hit F9 once. F5 to run. */

#include <chrono>
#include <thread>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
int main()
{	Display* dpy = XOpenDisplay(nullptr); if(!dpy) {return 1;}
	const unsigned int CAPS_MASK = LockMask;
	const unsigned int NUM_MASK = Mod2Mask;
	
	//Turns off Num Lock and Caps Lock.
	XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK | NUM_MASK, 0); XFlush(dpy);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	//Blinks.
	for(int a = 0; a < 5; a++)
	{	//Num Lock on.
		XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, NUM_MASK); XFlush(dpy);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		//Num Lock off.
		XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, 0); XFlush(dpy);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		//Caps Lock on.
		XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, CAPS_MASK); XFlush(dpy);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		//Caps Lock off.
		XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, 0); XFlush(dpy);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	XCloseDisplay(dpy);
}
