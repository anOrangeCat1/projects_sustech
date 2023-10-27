# A Smart Speaker Based on Raspberry Pi

**_Function List:_**
- Wake-up and voice interaction
- Voice-controlled light on/off
- Weather inquiry
- Chat with the Turing robot
- Remote/local server
- Infrared device control
- Indoor temperature and humidity query
- Mobile control of home devices


**_Below are the relevant files:_**
|file_name|content&function|
|------|-----|
|_demo.py_|****|
|_easy.py_|****|
|_main.py_|****|
|_project_pre.pdf_|****|
|_system_frame.png_|****|



In this project, I developed a Raspberry Pi-based microsystem inspired by smart voice assistants. I completed the setup of the main program framework, implemented voice wake-up function, achieved voice interaction, enabled voice weather reporting, integrated with the Turing Robot and accomplished light control.

**_Throughout the entire project process, there are some points:_**

- **Sound Card Configuration**
  
Before using an external USB audio device, you need to configure the sound card in advance. You should enter the Raspberry Pi configuration to specify the device's built-in sound card (not using the Raspberry Pi's onboard sound card).

- **Audio recording parameters**

After completing the relevant configuration, you can use the system's built-in command:

`arecord -d 3 -r 16000 -c 1 -f S16_LE listen_word.wav`

`d 3` indicates recording for 3 seconds.

`r 16000` indicates a sampling rate of 16,000 samples per second.

`c 1` indicates 1 channel.

`f S16_LE` indicates recording in 16-bit format.

In this project, it's essential to strictly use a 16,000 Hz sampling rate, 1 channel, and 16-bit format for audio recording; otherwise, speech recognition won't work (Baidu Intelligent Cloud strictly requires this audio format). Initially, you might think that using 32-bit audio quality would yield better recognition results, but after multiple experiments, it was found to be unrecognizable. (Baidu Intelligent Cloud documentation does not specify 16-bit, but after numerous parameter adjustments, it was discovered that this is necessary.)

- **Voice Wake-up and Snowboy**

Many products feature voice wake-up functionality, such as Siri on the iPhone, Xiaomi's Xiao Ai, and more.

1. Snowboy is an artificial intelligence software toolkit developed by KITT.AI. With Snowboy, developers can add "voice hotword detection" to various hardware devices.
2. Snowboy can be used for real-time embedded systems and continuously listens (even offline). Currently, it can run on systems like Raspberry Pi, (Ubuntu) Linux, and Mac OS X.
3. Snowboy is now open-source. This project uses Snowboy as the voice wake-up framework.

- **Snowboy Callback Function (call_back)**

The main functions that execute various tasks are written within Snowboy's callback function. Each time the wake word is detected, the main function is executed to accomplish various tasks, achieving human-computer interaction.








<div align=center>
<img src=""  />
</div>

![image](https://github.com/anOrangeCat1/projects_sustech/assets/99580008/09866319-dd67-4345-868a-65e39d49b617)

![system_frame](https://github.com/anOrangeCat1/projects_sustech/assets/99580008/61792e10-50d5-47d0-97ed-899e03825490)

![image](https://github.com/anOrangeCat1/projects_sustech/assets/99580008/1740ab2f-bc60-49a1-be60-1c60104ec86d)

