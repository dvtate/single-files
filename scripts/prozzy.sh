#!/bin/sh

# configure the system proxy in gnome settings
gnome_sys_proxy () {
        # $1 - 'enable' | 'disable' 

        # toggle proxy
        if [ $1 -eq 'status' ]
        then
                gsettings get org.gnome.system.proxy mode
        elif [ $1 -eq 'enable']
        then
                gsettings set org.gnome.system.proxy.socks host 127.0.0.1
                gsettings set org.gnome.system.proxy.socks port 1080
                gsettings set org.gnome.system.proxy mode 'manual'
        elif [ $1 -eq 'disable']
        then
                gsettings set org.gnome.system.proxy mode 'none'
        fi

}
