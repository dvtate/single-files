#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 


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
  <50, 5, 10> // position of the light source
  color rgb 1.0 // color of the light
}


camera {
    perspective angle 75               // front view
    location  <10.0 , 6.0, 15.0>
    right     x*image_width/image_height
    look_at   <0.0 , 0 , 0.0>
}


plane { 
    <0,1,0>, 0  hollow // normal vector, distance to zero ----

    texture{ 
        pigment{ color rgb<1,0, 0.00> }
        finish { phong 1 }
    }

    rotate< 0,0,0>

}



plane { 
    <0,1,0>, 0  hollow // normal vector, distance to zero ----

    texture{ 
        pigment{ color rgb<0,1, 0.00> }
        finish { phong 1 }
    }

    rotate< 0,0,90>

}


plane { 
    <0,1,0>, 0  hollow // normal vector, distance to zero ----

    texture{ 
        pigment{ color rgb<0,0, 1.00> }
        finish { phong 1 }
    }

    rotate< 90,0,0>

}

#declare compass = object {
    union {
        // y arrows
        cone { 
            <3, 5,3>,0.5,<3, 6, 3>,0 
        
            pigment{ color Blue }
        }        
        cone {// cylinder...               
            <3,5,3>, 0.25, <3,1,3>, 0.25
            pigment { color Blue }
        
        }                
        cone { 
            <3, 1, 3>,0.5,<3, 0, 3>,0 
        
            pigment{ color Blue }
        }                 
               
               
        // x arrows       
        cone { 
            <5, 3, 3>,0.5,<6, 3, 3>,0 
        
            pigment{ color Red }
        }        
        cone {// cylinder...               
            <5,3,3>, 0.25, <1,3, 3>, 0.25
            pigment { color Red }
        
        }                
        cone { 
            <1, 3, 3>,0.5,<0, 3, 3>,0 
        
            pigment{ color Red }
        }          
        
        // z arrows       
        cone { 
            <3, 3, 5>,0.5,<3, 3, 6>,0 
        
            pigment{ color Green }
        }        
        cone {// cylinder...               
            <3,3,1>, 0.25, <3,3, 5>, 0.25
            pigment { color Green }
        
        }                
        cone { 
            <3, 3, 1>,0.5,<3, 3, 0>,0 
        
            pigment{ color Green }
        }     
                       
        sphere {
            <3,3,3>, 0.75
            
            material {
                texture { 
                    pigment{ color rgb< 1, 1, 1>*0.75 }
                    finish { 
                        diffuse 0.1 
                        reflection 0.2  
                        specular 0.8 
                        roughness 0.0003 
                        phong 1 
                        phong_size 400
                    }
                }
                interior{ I_Glass }
            }
        
        }                                 
    }
}

object { compass
    //translate <-3,-3,-3>
    //rotate<90,0,0>
    //translate <3,3,3>
    
}
    
