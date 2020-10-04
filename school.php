<?php
	// Function to get the client IP address
	function getClientIP(){
		if ($_SERVER['HTTP_CLIENT_IP'])
			return $_SERVER['HTTP_CLIENT_IP'];
		else if($_SERVER['HTTP_X_FORWARDED_FOR'])
			return $_SERVER['HTTP_X_FORWARDED_FOR'];
		else if($_SERVER['HTTP_X_FORWARDED'])
			return $_SERVER['HTTP_X_FORWARDED'];
		else if($_SERVER['HTTP_FORWARDED_FOR'])
			return $_SERVER['HTTP_FORWARDED_FOR'];
		else if($_SERVER['HTTP_FORWARDED'])
			return $_SERVER['HTTP_FORWARDED'];
		else if($_SERVER['REMOTE_ADDR'])
			return $_SERVER['REMOTE_ADDR'];
		else return 'UNKNOWN';
	}

	function cURLgetSrc($url){
		$ch = curl_init();// create curl resource
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);//return the transfer as a string
		curl_setopt($ch, CURLOPT_URL, $url);//set url
		$output = curl_exec($ch);//$output contains the output string
		curl_close($ch);//close curl resource to free up system resources
		return $output;

	}
	$latlon=explode(",",cURLgetSrc("ipinfo.io/".getClientIP()."/loc"));
?><!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
		<meta name="description" content="DV Tate's personal Website homepage"/>
		<meta name="author" content="Dustin Van Tate Testa"/><title>College-Tate's Website</title>
		<meta name="keywords" content="tate testa dustin van freshman college programming Dustin Van Tate Testa"/>
		<meta name="start-date" id="new-style" content="6-4-2015"/>
		<link href="http://fonts.googleapis.com/css?family=Ubuntu" rel="stylesheet" type="text/css">
		<link rel="stylesheet" type="text/css" href="//dvtate.com/styles/nyental.css" />
		<style type="text/css">#logo_img{width:400px;}body{min-width:800px;}
			h4{font-family:'Ubuntu', 'Lucida Sans Unicode', 'Lucida Grande', Helvetica, sans-serif;}
			a#showhide_txt:active{color:red;}div#google_canvas h1 {font-size:16px;}
			div#google_canvas h2 {font-size:14px;font-weight:300;}div#showhide{cursor:pointer;}
			a#showhide_txt{color:#0000EE;margin-left:15px;text-decoration:none;}
			div#how_container{border:1px solid #000;border-radius:5px;margin:5px;}
			p.ind,h4,h3{margin-left:5px;}div#google_canvas{height:600px;}
		</style><script src="https://apis.google.com/js/platform.js" async defer></script><!--Google+1 btn-->
		<script type="text/javascript"><!--//Google Analytics
			(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
			(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
			m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
			})(window,document,'script','//www.google-analytics.com/analytics.js','ga');
			ga('create', 'UA-59746939-2', 'auto');ga('send', 'pageview');//-->
		</script>
	</head>
	<body onload="redrawmap">
		<script>alert("<?php echo cURLgetSrc("ipinfo.io".getClientIP()."/loc"); ?>"); </script>
		<ul class="pages"><!--page-link menu-->
			<li class="page" id="home"><a class="here" href="http://dvtate.com/">Home</a></li>
			<li class="page" id="icategory" onclick=""><a class="page">Hobbies</a>
				<ul class="dpages" id="hob">
					<li class="dpage"><a class="page" href="http://dvtate.com/prog/" >Programming</a></li>
					<li class="dpage"><a class="page" href="http://dvtate.com/3d/" >3d modelling</a></li>
					<li class="dpage"><a class="page" href="http://dvtate.com/forge/" >Blacksmithing</a></li>
					<li class="dpage"><a class="page" href="http://dvtate.com/lab/" >The Lab</a></li>
					<li class="dpage"><a class="page" href="http://dvtate.com/tanks/" >My Aquariums</a></li>
					<li class="dpage"><a class="page" href="http://dvtate.com/os/" >Operating Systems</a></li>
				</ul>
			</li>&nbsp;<li class="page" id="category"><a class="page" href="http://dvtate.com/chat/">Chat</a></li>
			<li class="page" id="category"><a class="page" href="http://dvtate.com/calc/">Calculators</a></li>
			<li class="page" id="category"><a class="page" href="http://dvtate.com/school/">College</a></li>
		</ul><div class="main">
			<h1><b>I'm Thinking About</b>:</h1><ul>
				<table id="skole_choice"><tr><td id="skole_logo"></td><td><p class="ind" id="om_skole">Waiting for your location</p></td></tr></table>
			</ul><div id="how_container"><div id="showhide" onclick="showhidehow()"><h3>How I chose <a id="showhide_txt"></a></h3></div>
				<div id="how"><hr/>
					<p class="ind">This page doesn't give a uniform result about which college I want to attend. This page first gets your location, and picks a college I've chosen for your location. The default is Georgia tech. If you're in New England (USA), you should see MIT, if you are in Europe, you should see DTU, if you are on the gulf coast (Alabama through Louisiana), you should see Auburn, if you are near the west coast, you should see CalTech. If you are anywhere else, Georgia tech should appear. Because Google's geolocation API isn't perfect the map below will show you where my page thinks you are and not your exact location.</p>
					<div id="google_canvas"></div><!--becomes the map-->
					<h4><b>Override Location</b>:<input type="button" value="CalTech" onclick="caltech()" /><input type="button" value="dtu" onclick="dtu()" /><input type="button" value="mit" onclick="mit()" />
					<input type="button" value="auburn" onclick="auburn()" /><input type="button" value="gatech" onclick="gatech()" /></h4>
				</div>
			</div>
		</div><center>
			<h6 hidden="true">IP: <span hidden="true" <a id="hostbtn" class="ad" href="http://www.000webhost.com/" target="_blank" align="center">
				<img src="http://www.000webhost.com/images/80x15_powered.gif" alt="Web Hosting" width="80" height="15" border="0" /><!--host ad-->
			</a><div class="g-follow" data-href="https://plus.google.com/+Tatetesta" data-height='15' data-rel="{relationshipType}"></div><!--g+-->
			<div class="g-plusone" data-size="small" data-annotation="inline" data-width="300" data-href="http://www.dvtate.com/school/"></div><!--g+1-->
		</center><script src="//maps.googleapis.com/maps/api/js?v=3.exp&sensor=true"></script>
		<script type="text/javascript"><!--//geolocation script.
			var lat,lon,open=false;
			function gatech(){document.getElementById('om_skole').innerHTML=
				"Located in Atlanta, Georgia, the Georgia Institute of Technology is a leading research university committed to improving the human condition through advanced science and technology.";
				document.getElementById('skole_logo').innerHTML="<a href=\"http://gatech.edu/\" target=\"_blank\"><img id=\"logo_img\" src=\"http://dvtate.com/school/logos/gt.png\" alt=\"logo\"/></a>";
			}function mit(){document.getElementById('om_skole').innerHTML=
				"The Massachusetts Institute of Technology (MIT) is a private research university in Cambridge, Massachusetts. One of the most prestigious universities in the field of engineering.";
				document.getElementById('skole_logo').innerHTML="<a href=\"http://mit.edu/\" target=\"_blank\"><img id=\"logo_img\" src=\"http://dvtate.com/school/logos/mit.png\" alt=\"logo\"/></a>";
			}function dtu(){document.getElementById('om_skole').innerHTML=
				"For almost two centuries DTU, Technical University of Denmark, has been dedicated to fulfilling the vision of H.C. &#216;rsted - the father of electromagnetism - who founded the university in 1829 to develop and create value using the natural sciences and the technical sciences to benefit society.</p><p class=\"ind\">Today, DTU is ranked as one of the foremost technical universities in Europe, continues to set new records in the number of publications, and persistently increase and develop our partnerships with industry, and assignments accomplished by DTU\'s public sector consultancy.";
				document.getElementById('skole_logo').innerHTML="<a href=\"http://www.dtu.dk/\" target=\"_blank\"><img id=\"logo_img\" src=\"http://dvtate.com/school/logos/dtu.jpg\" alt=\"logo\"/></a>";
			}function auburn(){document.getElementById('om_skole').innerHTML=
				"Auburn University has developed into one of the largest universities in the South, remaining in the educational forefront with its traditional blend of arts and applied science, and changing with the needs of today while living with a respect for the traditions and spirit that are Auburn.";
				document.getElementById('skole_logo').innerHTML="<a href=\"http://auburn.edu/\" target=\"_blank\"><img id=\"logo_img\" src=\"http://dvtate.com/school/logos/au.jpg\" alt=\"logo\"/></a>";
			}function caltech(){document.getElementById('om_skole').innerHTML=
				"Caltech is a world-renowned and pioneering research and education institution dedicated to advancing science and engineering.";
				document.getElementById('skole_logo').innerHTML="<a href=\"http://caltech.edu/\" target=\"_blank\"><img id=\"logo_img\" src=\"http://dvtate.com/school/logos/cali.png\" alt=\"logo\"/></a>";
			}
			function redrawmap(){
				if(!!navigator.geolocation){var map;
					var mapOptions={zoom:15, mapTypeId:google.maps.MapTypeId.ROADMAP};
					map=new google.maps.Map(document.getElementById('google_canvas'),mapOptions);
					var geolocate=new google.maps.LatLng(lat,lon);

					if(typeof(lat)==="undefined"||typeof(lon)==="undefined"){//location not given
						pickcollegeIP();/*
						var infowindow=new google.maps.InfoWindow({
							map:map,position:geolocate,content:"<h1>Why won\'t you share your location</h1>"+
							"<h2>Thats not very nice</h2><h2>ERROR: no location given</h2>"
						});map.setCenter(geolocate);*/
					}else{
						var infowindow=new google.maps.InfoWindow({
							map:map,position:geolocate,content:"<h1>I think you\'re here</h1><h2>Latitude: "+
							lat+"</h2><h2>Longitude: "+lon+"</h2>"
						});map.setCenter(geolocate);
					}
				}else{alert("\tERROR!\nThis browser doesn't support geolocation.\nYou should get a better one.");
					document.getElementById('google_canvas').innerHTML='ERROR: Couldn\'t get location';
				}
			}
			function pickcollege(position){
				lat=position.coords.latitude;lon=position.coords.longitude;
				if(lat>38&&lat<48&&lon<-66&&lon>-84)mit();//NE-US
				else if(lat<72&&lat>32&&lon>-24&&lon<30)dtu();//Europe
				else if(lat<48&&lat>30&&lon>-132&&lon<-114)caltech();//west coast -US
				else if(lat<38&&lat>28&&lon>-95&&lon<-85)auburn();//gulf coast -US
				else if(typeof(lat)=="number"&&typeof(lon)=="number")gatech();//any other real coordinates
				else getLocation();//undefined(no location)
			}(function getLocation(){
				if(!!navigator.geolocation)navigator.geolocation.getCurrentPosition(pickcollege);
				else alert("ERROR:\n Geolocation is not supported by this browser");
			})();


			function pickcollegeIP(){
				lat=<?php //echo latlon[0]; ?>;//[approximate]
				lon=<?php //echo latlon[1]; ?>;//
				if(lat>38&&lat<48&&lon<-66&&lon>-84)mit();//NE-US
				else if(lat<72&&lat>32&&lon>-24&&lon<30)dtu();//Europe
				else if(lat<48&&lat>30&&lon>-132&&lon<-114)caltech();//west coast -US
				else if(lat<38&&lat>28&&lon>-95&&lon<-85)auburn();//gulf coast -US
				else if(typeof(lat)=="number"&&typeof(lon)=="number")gatech();//any other real coordinates
				else redrawmap();//undefined(no location)
			}
			function showhidehow(){
				if(open){document.getElementById('how').style.display="block";
					document.getElementById('showhide_txt').innerHTML="[hide]";redrawmap();
				}else{document.getElementById('how').style.display="none";
					document.getElementById('showhide_txt').innerHTML="[show]";
				}open=!open;
			}showhidehow();//-->
		</script>
	</body>
</html>
