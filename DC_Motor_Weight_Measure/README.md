# A Weight Measurement Device Based on a DC Motor

This project was a weight measurement project with a range of 100g to 1.5kg, and the premise was not to use traditional weight sensors, such as strain gauges.

Other students' approaches were often more conventional, mainly using **_spring method (mg=kx)_** or **_acceleration method (F=ma)_**. Since I hadn't previously worked with motor control, 
I wanted to use a motor for weight measurement and utilized Arduino as controller, which was a very innovative approach that has never been attempted before.

I employed the principle of **torque balance**. When the motor lifts the weight to a horizontal position, it is balanced in my hand, and the torque exerted by the motor equals the torque produced by the weight.The process is illustrated in the following diagram:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/cc83fe9c-b649-4e13-859e-d2b9e765320e"  />
</div>

When the torque is balanced, **$\tau$ = MgL**, where $\tau$ represents the motor's torque, **M** is the mass of the object to be measured, **g** is the acceleration due to gravity, and **L** is the length of the lever. $\tau$ can be considered proportional to the motor current, **g** is known, and **L** is known, so we can get: **M = $\tau$/gL**. Therefore, through calibration, we can deduce the mass of the object.

**_Below are the relevant files:_**
|folder_name/file_name|content&function|
|------|-----|
|_openloop_test_|**Using open-loop control for the motor primarily aims to become familiar with motor control methods and to accomplish basic functions.**|
|_pid_control_|**Using PID control for position control,Ensuring that the motor reaches a level position during each measurement. Due to motor accuracy issues, PD control is actually used.**|
|_pid_speed_|**Speed control using PD control was attempted to lift the weight at a constant speed, but the results were unsatisfactory, so it was eventually abandoned.**|
|_Opening_report_ppt.pptx_|**The opening presentation PPT.The initial plan and the final solution had some differences.**|
|_calibration_data.xlsx_|**The calibration results of the sensors indicate that there is a roughly linear relationship between the motor torque and the mass of the object being measured.**|
|_final_pre.pdf_|**The final project presentation PPT**|

In this project, **the motor's encoder** was used, and a **PID control algorithm** was employed to control the motor to lift the object to the same position.

Due to the limitations of the motor's performance and its encoder precision, if the integral **(I)** term was added, the motor could not immediately reached the desired position, resulting in accumulated error, causing the motor to oscillate and preventing it from converging. So, in the end, instead of PID, a **PD** control algorithm was used.

After completing the motor position control, I used a known mass weight to **calibrate** this novel sensor, establishing a relationship between mass and motor torque (actually current value, but **in this project, torque was assumed to be directly proportional to current**). This formula allowed for the measurement of unknown mass weights once calibration was complete. The calibration results are as follows:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/155dbee1-3c9e-4018-8d35-9488185f5e35"  />
</div>

In the end, this new sensor exhibits excellent performance: measurement error within 2%, response time within 5s, and calibration data indicating a near-linear relationship between input and output.
The final project is shown as following:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/90598a63-a220-4ba8-bf82-85281c23a164"  />
</div>

**_video link:_**

_youtube:_ https://www.youtube.com/watch?v=4rZR-NxtF5Q

_bilibili:_ https://www.bilibili.com/video/BV1Gu4y1p77T

