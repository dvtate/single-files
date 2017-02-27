<!DOCTYPE html>
<html>
<head>
<style type="text/css">
	body { 			
		color: black;
		background: white;
		white-space: nowrap;
	}
	h3 {
		font-style: bold;
	}
	h5 {
		text-decoration: underline;
	}
	h6 {
		text-decoration: italicize;
		text-decoration: line-through;
	}	
</style>
<title>Tate's Triangle Area Calculator (coordiates)</title>
<!--Project started 7-2-2014 (conversion to asp)-->
<!--Version # 10 -->
<span style="text-decoration: underline; ">
	<h1>Triangle Area from Coordinates</h1>
</span>
<ul id="aboutwebpage">
	<li><span style="text-decoration: underline;">Developed By</span>: (Dustin Van) Tate Testa</li>
	<li><span style="text-decoration: underline;">Purpose</span>: To find the area between any 3 coordinates.</li>
</ul>
<h5>input the required data into the text fields</h5><hr>
</head>
<body>
<%@ language="vbscript" %>
<%
	 'slope intercept vars.
	Dim x, m1, m2, b1, b2, y
	 'coordinates (input) (holding vars.)
	Dim ax, ay, bx, by, cx, cy
	 'triangle area formula vars 
	Dim base, height, area2
	 'other (operational)
	Dim runValue 'forces cooperation
	Dim runval 'forces cooperation
	Dim strnone
	Dim goja 
	goja = 0
%>
<form action="triangle_area_coordinates_web.asp" method="post">
	<p>
	-<span style="text-decoration: underline;">
		1st Coordinate
	</span>
	:   (<input type="text" name="ax" value="<%=ax%>" required="true" /> 
	, <input type="text" name="ay" value="<%=ay%>" required="true" /> ) </p>
	<p>
	-<span style="text-decoration: underline;">
		2nd Coordinate
	</span>
	:   (<input type="text" name="bx" value="<%=bx%>" required="true" /> 
	, <input type="text" name="by" value="<%=by%>" required="true" /> ) </p>
	<p>
	-<span style="text-decoration: underline;">
		3rd Coordinate
	</span>
	:   (<input type="text" name="cx" value="<%=cx%>" required="true" /> 
	, <input type="text" name="cy" value="<%=cy%>" required="true" /> ) </p>
	<input type="submit" name="areafinder" value="Find Area" onClick="<% goja = 1 %>" />
</form>
<%
If goja = 1 Then
	ax = Request.Form("ax")
	ay = Request.Form("ay")
	bx = Request.Form("bx")	
	by = Request.Form("by")
	cx = Request.Form("cx")
	cy = Request.Form("cy")
	ax = Eval(ax)
	ay = Eval(ay)
	bx = Eval(bx)
	by = Eval(by)
	cx = Eval(cx)
	cy = Eval(cy)
	If ax = "" Or ay = "" Or bx = "" Or by = "" Or cx = "" Or cy = "" Then
		response.write("<p>something is missing</p> ")
	End If
	runval = by - ay
	runValue = bx - ax 'Forces computer to cooperate
	If ax = bx And bx = cx And cx = ax Xor ay = by And by = cy And cy = ay Then
		response.write("<p></p>")
		Call noarea("There is no area between the entered points.<br> They formed a line")
	ElseIf ax = bx And bx = cx And cx = ax And ay = by And by = cy And cy = ay Then
		response.write("<p></p>")
		Call noarea("There is no area between the entered points.<br> (They Are all the same)")
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
		response.write("<br>")
		response.write("<h6>Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...</h6>")
		response.write("<h3>The area of the triangle is " &area2& " square units.</h3>")
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
		response.write("<br>")
		response.write("<h6>Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...</h6>")
		response.write("<h3>The area of the triangle is " &area2& " square units.</h3>")
	'process(normal)
	Else
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
		response.write("<h6>Please ignore this message::" &base& "::" &m1& "::" &m2& "::" &b1& "::" &b2& "::" &x& "::" &y& "::" & height & "::...</h6>")
		response.write("<h3>The area of the triangle is " &area2& " square units.</h3>")
	End If
	goja = 0
End If
Sub noarea(strnone)
	response.write("<h3>" &strnone& "</h3>")
End Sub
%>
</body>
</html>
