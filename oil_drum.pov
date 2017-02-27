#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 

#include "colors.inc"


light_source {
  <50, 20, 10>
  color White
}
camera {
    location <5, 25, -40>
    look_at <2.5, 2.5, 0>
}                        


lathe {
    linear_spline
    16,
    <0, 0>
    <4,0>
    <4.1,0.5>
    <4, 1>
    <4, 3>
    <4.1, 3.5>
    <4, 4>
    <4, 6>
    <4.1, 6.5>
    <4, 7>
    <4, 9>
    <4.1, 9.5>
    <4, 10>
    <3.8, 10>
    <3.8, 9.5>
    <0, 9.5>
        
    pigment { White }
}
                                 
                                 
                                 
                                 
