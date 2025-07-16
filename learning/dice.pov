#version 3.7
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 

#include "colors.inc"


light_source {
  <50, 20, 10>
  color White
}


camera {
    location <4, 5, 6>
    look_at <1, 1, 1>     
}

#declare dice = difference {
    intersection {
        box {
            <0,0,0> <2,2,2>
            pigment { color White }
            finish {
                roughness 0.1
                reflection {
                    .01
                    metallic
                }       
            }
          
        }    
        
        sphere {
            <1,1,1>, 1.385                  
            pigment { color White }
            finish {
                roughness 0.1
                reflection {
                    .05
                    metallic
                }       
                phong 10
            }
        }          
    }
    
    // 3
    sphere {<2,1,1> 0.1}  
    sphere {<2,0.5,1.5> 0.1}
    sphere {<2,1.5,0.5> 0.1}
    
    // 2    
    sphere {<0.5,1.5,2> 0.1}
    sphere {<1.5,0.5,2> 0.1}
        
    // 1
    sphere {<1,2,1> 0.1}  
}                       
                
dice

object {
    dice 
    translate<-3, 0, -3>
}
object {
    dice 
    translate<-3, 0, 0>
}
object {
    dice 
    translate<0, 0, -3>
}
                
plane { 
    <0,1,0>, 0 
    texture { 
        pigment { 
            checker 
                color rgb <1,1,1>*1.3 
                color rgb <0,0,0>*0
        }
        finish { phong 0.1}
    }
}
