# projects_sustech
This repository is to record my all undergraduate projects in sustech.

You can click on specific folders to view detailed information about the projects. Some are code of prjects and some of them are code exercises during the learning process. 

I have also uploaded some reports and PowerPoint presentations. Some of them are in English, and others are in Chinese.

If you are interested in these projects and find them helpful, feel free to download and use them.

**_Below are the projects corresponding to the folders:_**

|folder_name|project_name|
|------|-----|
|_AI_ML_Projects_|**Artificial Intelligent and Machine Learning Projects**|
|_Age-Changing_Camera_|**Age-Changing Camera Based on GANs**|
|_Bluetooth_Glittering_Speaker_|**Bluetooth Glittering Speaker**|
|_DC_Motor_Weight_Measure_|**A Weight Measurement Device Based on a DC Motor**|
|_Drawing_Board_|**Drawing Board Based on Hand Recognization Based by OpenCV**|
|_Flow_Detection_System_|**A Multi-Scene Flow Intelligence Detection System Based on Raspberry Pi**|
|_Hair_Transplnt_Robot_|**Hair Transport Robot**|
|_Mobile_Robot_Labs_|**Mobile Robot Navigation and Control Labs**|
|_Robotic_Drawing_System_|**A Robotic Arm-Based Portrait Drawing System**|
|_Smart_Speaker_|**A Smart Speaker Based on Raspberry Pi**|
|_Vending_Machine_|**Implementing an Automatic Vending Machine Using Logic Circuits**|

Here are overviews of these projects, and if you want to know more details, you can click on the respective folders.

## A Robotic Arm-Based Portrait Drawing System
**_2023.4~2023.6_**

_Team Project of 3 members_

**_Discription of project:_** This is a project for a robot control course. It involves using a robotic arm to draw portrait sketches. The process begins with inputting a real portrait photograph. Image processing techniques are then applied to extract the outline of the portrait, which is transformed into a series of ordered coordinate points. These points serve as the path for the robotic arm to follow. Finally, the robotic arm is controlled to move along the generated path, ultimately completing the portrait drawing.

**_Individual contribution:_** I formed a path for the robotic arm by using the sorted pixel coordinates and became proficient in utilizing the **ROS** package provided by the robotic arm manufacturer for basic control. I applied the **PID control algorithm** to control the robotic arm for the purpose of creating artwork. 

The final result is depicted in the following image:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/0e1ae695-f4aa-4b16-98c6-d66303c3f6a0"  />
</div>

**_video link_**

_youtube:_ https://www.youtube.com/shorts/PwJzDzVUQ28

_bilibili:_

## A Weight Measurement System Based on DC Motor
**_2023.3~2023.6_**

_Team Project of 2 members_

**_Discription of project:_** This is a project for a sensor course. The requirement was to design an innovative weight sensor without using any strain gauges. It needed to measure random weights in the range of 0-1.5 kg with high accuracy and relatively fast response time. We adopted the principle of torque balance and used the PD control algorithm to control a DC motor to raise the object being weighed to its balanced position. By measuring the motor torque at equilibrium and conducting calibration, we completed the design of the Innovative sensor.

**_Individual contribution:_** Mastered the basic principles of DC motors and implemented position control using the **PD control algorithm**. It was approximated that the motor torque was linearly related to the current magnitude, and **calibration** allowed us to measure the weight of objects using this method.

The final project looked like the following image:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/da7862ec-6811-43cc-aff6-6c664bafd607" width="20%" height="20%" />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/6892484b-8b30-4f06-87dd-0d1114085b7b" width="36%" height="36%" />
</div>



**_video link_**

_youtube:_

_bilibili:_


## A Hair Transplant Robot Based on Han’s Collaborative Robot
**_2023.6~2023.7_**

_Team Project of 9 members_

**_Discription of project:_** This is a project with a focus on business. The Grand Robotics Company wanted to explore the use of robotic arms in the beauty and hairdressing industry. They required a product proposal based on their current collaborative robotic arm technology. After investigating the market size and assessing user needs, we proposed a product concept for a hair transplant robot. We designed the configuration of the robotic arm, conducted a feasibility analysis, and obtained approval from the Grand Robotics Company.

**_Individual contribution:_** Participated in market research, contributed to the design of the robotic arm configuration, prepared weekly reports and the final presentation, and collaborated with team members to advance the entire project.


The final configuration of the hair transplant robot is shown in the following image:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/3ba1483a-c0ef-470e-a5a0-75ee96d54e8e" width="50%" height="50%"/>
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/3fd0e27e-bbe6-40fe-8423-effb3e1b9192" width="32%" height="32%"/>
</div>


**_video link_**

_youtube:_

_bilibili:_



## A Smart Speaker Based on Raspberry Pi
**_2022.10~2023.1_**

_Team Project of 2 members_

**_Discription of project:_** 
This is a project for the Microcomputer Principles course. We used a Raspberry Pi as a development board and, based on it, connected various hardware components to develop a smart speaker. We mainly accomplished the following functions:
- Implemented a **wake-up function** using the Wukong open-source project.
- Integrated Baidu Intelligent Cloud API for voice recognition and synthesis, enabling **voice interactions**.
- Utilized web scraping to fetch weather information for **voice weather reports**.
- Integrated with the Turing Robot, enabling **basic conversations** (at that time, ChatGPT had not yet been released).
- Connected various hardware components and established a communication network for **smart home control**, such as voice-controlled light switches and remote control of air conditioning and so on.


**_Individual contribution:_** 
Completed the setup of the main program framework, implemented voice wake-up function, achieved voice interaction, enabled voice weather reporting, integrated with the Turing Robot and accomplished light control.


The following image shows a physical representation of the voice interaction component (left) and the system diagram (right):

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/45a4b741-42db-4953-b83c-d8d44e5561a9" width="31%" height="31%"/>
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/c6c27131-5520-4af8-a51e-7ec29d0a8496" width="27%" height="27%"/>
</div>

The following images depict the physical components of the smart home section (left and center) and the system diagram (right):

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/d28cf865-8e07-4ad6-82dd-a178dae5e6db" width="26%" height="26%" />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/70992164-7c35-4ffb-a6ff-266bcd2ee28c" width="15%" height="15%"/>
   <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/c463842a-6c0b-4b7f-81fd-25363f971efe" width="35%" height="35%"/>
</div>




**_video link_**

_youtube:_

_bilibili:_


## Artificial Intelligent and Machine Learning Projects
**_2022 fall   2 weeks for each project_**

_Individual Project_

**_Discription of project:_** 
There are 2 projects for the Machine Learning and Artificial Intelligence course. The mid-term project focused on using **sklearn** to implement **linear regression** and the **K-Nearest Neighbors (KNN)** algorithm to solve a Kaggle problem, addressing the issue of imbalanced training samples. For the final project, **pytorch** was used to implement **Multi-Layer Perceptrons (MLP), Convolutional Neural Networks (CNN), Recurrent Neural Networks (RNN), and Attention** to solve another Kaggle problem.



## Mobile Robot Navigation and Control Labs
**_2022.9~2023.1_**

_Team Project of 2 members_

**_Discription of labs:_** 
These are labs for mobile robots. Each lab involves using the **TurtleBot** to complete specific tasks, including **line following by visual method, recognizing ArUco markers, mapping,navigation, SMACH and so on.** I became familiar with various tools and basic packages in ROS, and I wrote C++ and Python programs to accomplish specific tasks. Click to enter the folder to see more detailed information. Each lab is accompanied by code and usage instructions.

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/84be5c14-6811-431f-8cd1-d7a5c8c9eaf1" width="40%" height="40%"/>
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/4d351bb7-8b8d-483a-a0a5-937997da1129" width="37%" height="37%"/>
</div>

## Age-Changing Camera Based on GANs
**_2022.9~2023.1_**

_Team Project of 3 members_



## A Multi-Scene Flow Intelligence Detection System Based on Raspberry Pi
**_2022.7~2022.8_**

_Team Project of 3 members_



## A Drawing Board Based on Hand Recognization Based by OpenCV
**_2022.4~2022.6_**

_Team Project of 3 members_




## Implementing an Automatic Vending Machine Using Logic Circuits
**_2022.3~2022.6_**

_Team Project of 5 members_



## Bluetooth Glittering Speaker
**_2021.10~2022.1_**

_Team Project of 5 members_


