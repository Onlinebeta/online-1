
Debian
====================
This directory contains files used to package onlined/online-qt
for Debian-based Linux systems. If you compile onlined/online-qt yourself, there are some useful files here.

## online: URI support ##


online-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install online-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your online-qt binary to `/usr/bin`
and the `../../share/pixmaps/online128.png` to `/usr/share/pixmaps`

online-qt.protocol (KDE)

