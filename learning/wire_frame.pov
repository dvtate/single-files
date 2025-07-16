#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 


// libraries
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"
#include "stones.inc"
#include "woods.inc"
#include "shapes.inc"
#include "shapes2.inc"
#include "functions.inc"
#include "math.inc"
#include "transforms.inc"

                 
                 
light_source {
  //<50, 20, 10> // position of the light source
  <0,0,0>
  color rgb 1.0 // color of the light
}
    
light_source {
  <50, 20, 10> // position of the light source
  color rgb 1.0 // color of the light
}

camera {
    perspective angle 75
    location  <10.0 , 6.0, 15.0>
    right     x * image_width / image_height
    look_at   <0.0 , 0 , 0.0>
}


// vertices
sphere { <4,4,4>, 0.5 
    pigment { color rgb <1,1,1> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
sphere { <4,4,-4>, 0.5 
    pigment { color rgb <1,1,0> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
sphere { <4,-4,-4>, 0.5 
    pigment { color rgb <1,0,0>}
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}  
}
sphere { <-4,-4,-4>, 0.5 
    pigment { color rgb <0,0,0> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
        }
	}  
}
sphere { <4,-4,4>, 0.5 
    pigment { color rgb <1,0,1> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}  
}
sphere { <-4,-4,4>, 0.5 
    pigment { color rgb <0,0,1> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
sphere { <-4,4,4>, 0.5 
    pigment { color rgb <0,1,1> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}      
}
sphere { <-4,4,-4>, 0.5 
    pigment { color rgb <0,1,0> }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}    
}

           
// edges
cone {      
    <4,4,4>, 0.25, <4,4,-4>, 0.25
    pigment { color rgb<0,1,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <4,4,4>, 0.25, <4,-4,4>, 0.25
    pigment { color rgb<1,0,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <4,4,4>, 0.25, <-4,4,4>, 0.25
    pigment { color rgb<1,1,0> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}                

  
cone {      
    <-4,-4,-4>, 0.25, <4,-4,-4>, 0.25
    pigment { color rgb<1,1,0> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <-4,-4,-4>, 0.25, <-4,4,-4>, 0.25
    pigment { color rgb<1,0,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <-4,-4,-4>, 0.25, <-4,-4,4>, 0.25
    pigment { color rgb<0,1,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}

cone {      
    <4,4,-4>, 0.25, <-4,4,-4>, 0.25
    pigment { color rgb<1,1,0> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <4,4,-4>, 0.25, <4,-4,-4>, 0.25
    pigment { color rgb<1,0,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <4,-4,-4>, 0.25, <4,-4,4>, 0.25
    pigment { color rgb<0,1,1> filter 0.75 }
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
                                     
cone {      
    <-4,-4,4>, 0.25, <4,-4,4>, 0.25
    pigment { color rgb<1,1,0> filter 0.75}
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <-4,-4,4>, 0.25, <-4,4,4>, 0.25
    pigment { color rgb<1,0,1> filter 0.75}
    interior{ ior 1.5 }
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}
}
cone {      
    <-4,4,-4>, 0.25, <-4,4,4>, 0.25
    pigment { color rgb<0,1,1> filter 0.75}
    interior{ ior 1.5 }                
    finish {
    	roughness 0.1
    	reflection {
    		.05
    		metallic
    	}
	}		
}




box { <-4, -4, -4>, <4, -4, 4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<0,1,0,0.75>}                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		
    }
}

box { <-4, -4, -4>, <-4, 4, 4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<0,0,1,0.75> }                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		
		
	}
                
}                              

box { <-4, -4, -4>, <4, 4, -4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<1,0,0,0.75> }                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		
    }
}                                                     


box { <-4, 4, -4>, <4, 4, 4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<0,1,0,0.75> transmit 0.2 }                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		
    }
}

box { <4, -4, -4>, <4, 4, 4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<0,0,1,0.75> transmit 0.2 }                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		
    }
}

box { <-4, -4, 4>, <4, 4, 4>      
    texture { 
        pigment { checker color rgbf <1,1,1,1> color rgbf<1,0,0,0.75> transmit 0.2 }                             
        finish {
    		roughness 0.1
    		reflection {
    			.05
    			metallic
    		}
		}		finish { phong 0.1 }
    }                       
    interior {}
}
