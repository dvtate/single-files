#! /bin/sh

echo reinstalling all packages

## for each package name we have installed
for pkg in $(pacman -Q | cut -d' ' -f1); do
	pacman -S --noconfirm $pkg # reinstall pkg
done

