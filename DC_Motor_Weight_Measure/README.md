# A Weight Measurement Device Based on a DC Motor

This project was a weight measurement project with a range of 100g to 1.5kg, and the premise was not to use traditional weight sensors, such as strain gauges.

Other students' approaches were often more conventional, mainly using the displacement method or acceleration method. Since I hadn't previously worked with motor control, 
I wanted to use a motor for weight measurement.

![image](https://github.com/anOrangeCat1/projects_sustech/assets/99580008/cc83fe9c-b649-4e13-859e-d2b9e765320e)


In this project, we used the principle of torque balance with the motor and measured the motor current. Typically, current and torque are directly proportional under normal circumstances. 
After calibration, we can determine the relationship between the sensor's output and the weight.

![image](https://github.com/anOrangeCat1/projects_sustech/assets/99580008/155dbee1-3c9e-4018-8d35-9488185f5e35)

I tried both velocity control and position control loops, but due to accuracy issues, we ultimately used PD control in the position loop.
