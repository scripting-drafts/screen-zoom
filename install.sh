#!/bin/sh
set -eu
here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
command -v cc >/dev/null 2>&1 || {
    echo "cc is required (build-essential and libxrandr-dev)" >&2
    exit 1
}
mkdir -p "$HOME/bin" "$HOME/.config/systemd/user"
install -m 0755 "$here/screen-zoom" "$HOME/bin/screen-zoom"
install -m 0755 "$here/screen-zoom-fence" "$HOME/bin/screen-zoom-fence"
cc -O2 -o "$HOME/bin/xrandr-nopan" "$here/xrandr-nopan.c" -lXrandr -lX11
install -m 0644 "$here/zoom-secondary-screen.service" "$HOME/.config/systemd/user/zoom-secondary-screen.service"
systemctl --user daemon-reload
systemctl --user enable zoom-secondary-screen.service
echo "Installed. Start with: systemctl --user start zoom-secondary-screen.service"
