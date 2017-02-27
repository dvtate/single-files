''''''''''!'TriProg
'Author: Dustin Van Tate Testa
'Purpose: To find the area between any three points on a coordinate plane
'Original production date: 1-2-2014
'This is one of the many files lost on my programming drive which I have rebuilt
'Rebuild date: 12-28-2014
'
'TODO:
'	Rebuild based on an ASP classic page I made based on this program
'	Replace math process with heron's formula(like in website)
''''''''''!'

Option Explicit
'slope intercept vars.
	Dim x, m1, m2, b1, b2, y
'coordinates (input) (holding vars.)
	Dim ax, ay, bx, by, cx, cy
'triangle area formula vars 
	Dim base, height, area2
'other (operational)
	DIm intigen
	Dim runValue 'forces cooperation
	Dim runval 'forces cooperation
	Dim strnone

Do'Attempt to get data
	intigen=7'clear previous user stupidity
	ax = InputBox( "A(*, y) B(x, y) C(x, y)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	ay = InputBox( "A(#, *) B(x, y) C(x, y)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	bx = InputBox( "A(#, #) B(*, y) C(x, y)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	by = InputBox( "A(#, #) B(#, *) C(x, y)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	cx = InputBox( "A(#, #) B(#, #) C(*, y)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	cy = InputBox( "A(#, #) B(#, #) C(#, *)" &vbNewLine& "X-value for the first coordinate", "Input - Tate's Triangle Program")
	ax = Eval(ax)'evaluate in case a math expression is given 
	ay = Eval(ay)
	bx = Eval(bx)
	by = Eval(by)
	cx = Eval(cx)
	cy = Eval(cy)
	If ax = "" Or ay = "" Or bx = "" Or by = "" Or cx = "" Or cy = "" Then
		intigen = MsgBox("Somthing is missing..." &vbNewLine& "I can't do your math homework if you don't give me the question!" &vbNewLine& "Try again", vbYesNo & 32, "User Error - Tate's Triangle Program")
		If intigen = 7 Then 'if they say 'no'
			MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Good Bye" 
			Wscript.Quit
		End If
	End If
Loop While intigen <>7	
runval = by - ay'errors occured by direct testing
runValue = bx - ax 'Forces computer to cooperate
If (ax = bx And bx = cx And cx = ax) Xor (ay = by And by = cy And cy = ay) Then
	MsgBox "There is no area between the entered points" &vbNewLine& "They formed a line", 0, "No Area - Tate's Triangle program"
	Wscript.Quit
ElseIf ax = bx And bx = cx And cx = ax And ay = by And by = cy And cy = ay Then
	MsgBox "There is no area between the entered points." &vbNewLine& " (They Are all the same)", 0, "No Area - Tate's Triangle program"
	Wscript.Quit
ElseIf runval = 0 & by <> "" & ay <> "" Then   'error handleing2
	On Error Resume Next
	'process data (variable relationships)
	'Change order (ABC to CBA)
	base = Sqr(((cy - by) ^ 2) + ((cx - bx) ^ 2)) 
	m1 = (by - cy) / (bx - cx)
	m2 = 0 - (1 / m1)
	b1 = by - (m1 * bx)
	b2 = ay - (m2 * ax)
	x = (b2 - b1) / (m1 - m2)
	y = m1 * x  + b1
	height = Sqr(((y - ay) ^ 2) + ((x - ax) ^ 2))
	area2 = 0.5 * base * height
		'execution(forced) & output 
	MsgBox "Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...A", 0, "Scratch work (Ignore) - Tate's Triangle Program"
	MsgBox "The area of the triangle is " &area2& " square units.", 0, "Area/Answer - Tate's Triangle program"
	Wscript.Quit
ElseIf runValue = 0 Then   'error handleing
	On Error Resume Next
	'process data (variable relationships)
	'Change order (ABC to CBA)
	base = Sqr(((cy - by) ^ 2) + ((cx - bx) ^ 2)) 
	m1 = (by - cy) / (bx - cx)
	m2 = 0 - (1 / m1)
	b1 = by - (m1 * bx)
	b2 = ay - (m2 * ax)
	x = (b2 - b1) / (m1 - m2)
	y = m1 * x  + b1
	height = Sqr(((y - ay) ^ 2) + ((x - ax) ^ 2))
	area2 = 0.5 * base * height
	'execution(forced) & output 
	MsgBox "Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...a", 0, "Scratch work (Ignore) - Tate's Triangle Program"
	MsgBox "The area of the triangle is " &area2& " square units.", 0, "Area/Answer - Tate's Triangle program"
	Wscript.Quit
Else'process(normal)
	On Error Resume Next	
	'Math process(variable relationships)
	base = Sqr(((ay - by) ^ 2) + ((ax - bx) ^ 2))
	m1 = (by - ay) / (bx - ax)
	m2 = 0 - (1 / m1)
	b1 = by - (m1 * bx)
	b2 = cy - (m2 * cx)
	x = (b2 - b1) / (m1 - m2)
	y = m1 * x  + b1
	height = Sqr(((y - cy) ^ 2) + ((x - cx) ^ 2))
	area2 = 0.5 * base * height
	'execution(forced) & output 
	response.write("<br>")
	MsgBox "Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...B", 0, "Scratch work (Ignore) - Tate's Triangle Program"
	MsgBox "The area of the triangle is " &area2& " square units.", 0, "Area/Answer - Tate's Triangle program"
	Wscript.Quit
End If
