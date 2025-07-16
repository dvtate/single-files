Dim objIE, objWSH, intSC


MsgBox "Welcome to SearchBot 0.2" &vbNewLine& "-By: DV Tate Testa", 0, "Welcome - SearchBot 0.2"
'Get Info
strQ = InputBox("What do you want to search for?", "Query - SearchBot 1.2")
intSC = InputBox("How many times?", "SearchBot 1.2")
strQ = trim(strQ)
'Create IE obj
Set objIE = CreateObject("InternetExplorer.Application")
Set objWSH = CreateObject("WScript.Shell")
objIE.Visible = True

Do
	objIE.navigate "http://www.google.com/?q=" & strQ, CLng(2048)
	WScript.Sleep 1000
	objWSH.SendKeys "~"
	WScript.Sleep 1500
	
	
	intSC = intSC- 1
Loop While intSC > 0

'End
Set objIE = Nothing
WScript.Quit
