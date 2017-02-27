;The Problem:
; I love the hotcorner(s) in GNOME & KDE, and kept finding myself 
; trying to use them since I've been forced to use windows 10 (winshit).

;My solution:
; download & install: https://autohotkey.com/
; save this script with the extension ".ahk" 
; click on the script to start it and/or set it to launch automatically.

#Persistent
SetTimer, HotCorners, 0
return

taskOverview := false

HotCorners:
	CoordMode, Mouse, Screen

	; get desktop size
	WinGetPos, X, Y, Xmax, Ymax, Program Manager

	; adjust tolerance value if desired
	T = 2

	MouseGetPos, MouseX, MouseY

	; any of these can be used to have a different hot corner
	Corner := (MouseY < T and MouseX < T)			; top left
	;Corner := (MouseY < T and MouseX > Xmax - T)		; top right
	;Corner := (MouseY > Ymax - T and MouseX < T)		; bottom left
	;Corner := (MouseY > Ymax - T and MouseX > Xmax - T) 	; bottom right


	; top-left hot-corner-hit => send super + tab
	if Corner {
	
		; press <super> + <tab>
		Send, {LWin down}{tab down}
		
		taskOverview := !taskOverview
		
		; move mouse to center of screen towards apps
		if taskOverview {
			;MouseMove, Xmax/2, Ymax/2
		}
		
		; unpress <super> + <tab>
		Send, {LWin up}{tab up}
		

		; prevent retriggering
		Sleep, 250

	}

	return
