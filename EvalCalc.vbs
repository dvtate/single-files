'''EvalCalc
'By: Dustin Van Tate Testa
'Summary: A calculator slightly better than the default Windows calculator
'Date: 28-12-2014
'''This is a reproduction of the file lost in my programming drive
Dim ans
Dim intigen
Dim pi

intigen = MsgBox("This is a calculator program by DV Tate Testa." &vbNewLine& "Here are the rules::" &vbNewLine & vbTab& "-Put a space between operators & what they effect" &vbNewLine & vbTab & "-you can use parentheses " &chr(34)& "()" &chr(34)&" for order of operations" &vbNewLine & vbTab & "-Your standard operators are: +, -, *, /, and ^" &vbNewLine & vbTab& "-You also hve these operators:"  &vbNewLine & vbTab & vbTab& "+" &chr(34)& "Mod" &chr(34)& ": your modulus/remainder operator" &vbNewLine & vbTab & vbTab& "+" &chr(34)& "Sqr()" &chr(34)& ": your square route operator" &vbNewLine & vbTab & vbTab& "+" &chr(34)& "pi"  &chr(34)&": The value of pi", 0 + vbOKCancel, "EvalCalc - A basic Windows calculator")'intro/documentation
If intigen = 2 Then
	Wscript.Quit
End If
On Error Resume Next
Do
	pi = 4 * Atn(1)
	intigen = 7
	ans = InputBox("Expression:","EvalCalc - A basic Windows calculator")
	ans = Eval(ans)
	intigen = MsgBox("ans =" &vbNewLine & ans & vbNewLine & vbNewLine& "Go another cycle?", vbYesNo, "Answer - EvalCalc - A basic Windows calculator")
	If intigen = 7 Then
		Wscript.Quit
	End If
Loop While intigen <>7