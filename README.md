# screen-zoom

X11 per-monitor zoom: USB-C-0 at 150% (1280x800 logical), HDMI-0 untouched.
Pointer fence, pan watchdog, and RandR panning clearer included.
Tailored to HDMI-0 (1920x1080 at 0,0) and USB-C-0 (1920x1200 at 1920,280).
Edit the geometry in screen-zoom and screen-zoom-fence for other layouts.

Install: ./install.sh && systemctl --user start zoom-secondary-screen.service
Use: screen-zoom on|off|status|toggle
