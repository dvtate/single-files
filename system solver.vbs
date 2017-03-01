
'!!!REBUILD THIS MOTHER_FUCKER FROM SCRATCH


''''''
'version#3
'scripted by: DV Tate Testa
'

Option Explicit

'declarations
 'program vars. (operational)
  Dim type1
  Dim type2
  Dim intloop
  Dim intgoigen
  Dim intstartigen
 'Slope intercept vars.
  Dim m1, m2, b1, b2
 'coordinate holders 
  Dim y, x
 'std. form vars.
  Dim a1, a2, b3, b4, c1, c2


'fyi(purpose)
MsgBox "This program can solve systems of linear equations for their point of intersection", 0, "Tate's System solver"

On Error Resume Next

Do
 '1st equation
 DoDoDoDoDoDoDoDoDo 'dafuq????
	intloop = 7
 	type1 = InputBox("Is the first equation in: (a)-slope-intercept form, or (b)-standard form? (input the correct letter)", "equation type", "equation type")
 	'slope intercept
 	If type1 = "a" Then
 		Do
 			MsgBox "please input the requested values in decimal form (no fractions)", 0, "equation #1 -system solver"
 			intgoigen = 2
 			m1 = InputBox("enter the slope for the first equation (m).")
 			b1 = InputBox("enter the y-intercept for the first equation (b).")
 			If m1 = "" or b1 = "" Then
 				MsgBox "I can't do your math homework if you dont give me the question"
				intgoigen = MsgBox("Try again?", vbYesNo + 32)
				If  intgoigen = 7 Then
					MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
					Wscript.Quit
				End if
			End If
		Loop While intgoigen = 6
	'std. form
	ElseIf type1 = "b" Then
		Do
			MsgBox "please input the requested values in decimal form (no fractions)", 0, "equation #1 -system solver"
			intgoigen = 2
			MsgBox "The requested variables will come from the formula [ax+by=c]", 48, "Equation #1 - standard form - formula"
			a1 = InputBox("Enter the value of a (from formula [ax+by=c])")
			b3 = InputBox("Enter the value of b (from formula [ax+by=c])")
			c1 = InputBox("Enter the value of c (from formula [ax+by=c])")
			m1 = -(a1) / b3
			b1 = c1 / b3
			If a1 = "" Or b3 = "" Or c1 = "" Then
				MsgBox "I can't do your math homework if you dont give me the question"
				intgoigen = MsgBox("Try again?", vbYesNo + 32)
				If  intgoigen = 7 Then	
					MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
					Wscript.Quit
				End if
			End If
		Loop While intgoigen = 6
	Else If type1 = 7 Or 6 Or "" Then
		
	Else
		MsgBox "That is not a valid response"
		
		intloop = MsgBox("Try again?", vbYesNo + 32)
		If  intloop = 7 Then
			MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
			Wscript.Quit		
		End If
	End If
 Loop While intloop <>7
 '2nd Equation
 Do
	intloop = 1
	type2 = InputBox("Is the first equation in: (a)-slope-intercept form, or (b)-standard form?   (input the correct letter)", "Equation Type", "Equation Type")
	MsgBox "please input the requested values in decimal form (no fractions)", 0, "equation #1 -system solver"
	'slope intercept
	If type2 = "a" Then
		Do
			MsgBox "please input the requested values in decimal form (no fractions)", 0, "equation #1 -system solver"
			intgoigen = 2
			m1 = InputBox("enter the slope for the first equation (m).")
			b1 = InputBox("enter the y-intercept for the first equation (b).")
			If m1 = "" or b1 = "" Then
				MsgBox "I can't do your math homework if you dont give me the question"
				intgoigen = MsgBox("Try again?", vbYesNo + 32)
				If  intgoigen = 7 Then
					MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
					Wscript.Quit
				End if
			End If
		Loop While intgoigen = 6
	'std. form
	ElseIf byttype2 = "b" Then
		Do
			MsgBox "please input the requested values in decimal form (no fractions)", 0, "equation #1 -system solver"
			intgoigen = 2
			MsgBox "The requested variables will come from the formula [ax+by=c]", 48, "Equation #1 - standard form - formula"
			a2 = InputBox("Enter the value of a (from formula [ax+by=c])")
			b4 = InputBox("Enter the value of b (from formula [ax+by=c])")
			c2 = InputBox("Enter the value of c (from formula [ax+by=c])")
			m2 = -(a1) / b3
			b2 = c2 / b4
			If a2 = "" Or b3 = "" Or c1 = "" Then
				MsgBox "I can't do your math homework if you dont give me the question"
				intgoigen = MsgBox("Try again?", vbYesNo + 32)
				If  intgoigen = 7 Then
					MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
					Wscript.Quit
				End if
			End If
		Loop While intgoigen = 6
	Else
		MsgBox "That is not a valid response"
		
		intgoigen = MsgBox("Try again?", vbYesNo + 32)
		If  intgoigen = 7 Then
			MsgBox "I see how it is. Have fun doing math the old-fashioned way!", vbExclamation, "Fare Well" 
			Wscript.Quit		
		End If
	End If
 Loop While intloop = 6
 'math
  x = (b2 - b1) / (m1 - m2)
  y = m1 * x + b1
 MsgBox "The two equations intersect at the point (" &dblx& "," &dbly& ")", 48, "solution - Tate's System Solver"
 intstartigen = MsgBox("Would you like to solve another system?", vbYesNo, "Restart program?"
Loop While intstartigen = 6
