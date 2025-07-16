#version 3.7
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 

#include "colors.inc"
#include "glass.inc"
         /*
light_source {
  <50, 20, 10>
  color White
}
       */

camera {
    location <10, 25, 40>
    look_at <0, 10, 0>     
    
    
    //location <5, 50, 0>
    //look_at <10, 0 ,0>
    
    //location <2, 18, 0>
    //look_at <0, 20, 0>
}                        
    
    
// lamp pole
lathe {
    linear_spline
    8,
    <0, 0>
    <4,0>
    <4, 0.1>
    <0.25, 0.1>
    <0.25, 16>
    <0.75, 16>
    <0.75, 18>
    <0.5, 18>

    pigment { color rgb <0.4, 0.4, 0.4> }
    finish {        
        roughness .001
        reflection {
            .75
            metallic
        }       
    }
}
                                 
                                 
                                 
// lamp shade
lathe {
    linear_spline
    2,
    <5, 16>
    <3, 22>                                 
    pigment { White filter 0.2 }
    finish {
        diffuse 0.9
        ambient 0.2 
        roughness 10
    }
    
}   

// light bulb
light_source {
    <0,0,0> color rgb <5,5,5>
    looks_like { 
        sphere { 
            <0,0,0>, 1           
            
            material {
                texture { 
                    pigment{ color rgb< 1, 1, 1> filter 0.9 }
                    finish { 
                        diffuse 0.1 
                        reflection 0.2  
                        specular 0.8 
                        roughness 0.0003 
                        phong 1 
                        phong_size 400
                        ambient 1
                    }
                }
                
                interior{ior 1.333}
            }
            
        }
    }       
    
    translate <0,20,0>
}                         

/*
sphere { <0, 18, 0>, 1
    pigment { color White} 
    finish {
        ambient 1
        specular 0.75
        

    } 

}*/
/*
light_source {
    <0, 18, 0>
    color White
}               
  */
plane { 
    <0,1,0>, 0 
    texture { 
        pigment { 
            checker 
                color rgb<0, 0, 0> 
                color rgb<0.5, 0.5, 0.5> *2
        }
        finish { phong 0.1}
    }
}
