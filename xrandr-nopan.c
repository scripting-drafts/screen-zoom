#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "usage: %s OUTPUT\n", argv[0]); return 2; }
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) return 1;
    Window root = DefaultRootWindow(dpy);
    XRRScreenResources *res = XRRGetScreenResourcesCurrent(dpy, root);
    if (!res) { XCloseDisplay(dpy); return 1; }
    int ret = 1;
    for (int i = 0; i < res->noutput; i++) {
        XRROutputInfo *oi = XRRGetOutputInfo(dpy, res, res->outputs[i]);
        if (!oi) continue;
        if (strcmp(oi->name, argv[1]) == 0) {
            RRCrtc crtc = oi->crtc;
            if (crtc != None) {
                XRRCrtcInfo *ci = XRRGetCrtcInfo(dpy, res, crtc);
                XRRPanning p;
                memset(&p, 0, sizeof p);
                if (ci) { p.left = ci->x; p.top = ci->y; XRRFreeCrtcInfo(ci); }
                ret = (XRRSetPanning(dpy, res, crtc, &p) == Success) ? 0 : 1;
            }
            XRRFreeOutputInfo(oi);
            break;
        }
        XRRFreeOutputInfo(oi);
    }
    XRRFreeScreenResources(res);
    XCloseDisplay(dpy);
    return ret;
}
