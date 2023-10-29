# A Smart Speaker Based on Raspberry Pi

In this project, I developed a Raspberry Pi-based microsystem inspired by smart voice assistants. I completed the setup of the main program framework, implemented voice wake-up function, achieved voice interaction, enabled voice weather reporting, integrated with the Turing Robot and accomplished light control.

**_Below are the relevant files:_**
|file_name|content&function|
|------|-----|
|_demo.py_|**Wake-up Function Code**|
|_easy.py_|**Voice Interaction Function Code**|
|_main.py_|**Complete Code**|
|_project_pre.pdf_|**The final project presentation PPT**|
|_system_frame.png_|**picture of system frame**|


**_The entire project is as follows:_**
<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/09866319-dd67-4345-868a-65e39d49b617"  /> 
</div>


**_Function List:_**
- Wake-up and voice interaction
- Voice-controlled light on/off
- Weather inquiry
- Chat with the Turing robot
- Remote/local server
- Infrared device control
- Indoor temperature and humidity query
- Mobile control of home devices








**_Throughout the entire project process, there are some points:_**

- **Sound Card Configuration**
  
Before using an external USB audio device, you need to configure the sound card in advance. You should enter the Raspberry Pi configuration to specify the device's built-in sound card (not using the Raspberry Pi's onboard sound card).

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/ec32270d-5587-414a-8f16-c3960b6aaec8"  />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/40a3e33c-1175-4d90-9a12-aa164201e251"  />
</div>



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
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/abdaf5c6-a990-404d-b7d7-66f115e14c2f"  />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/de21d8e1-01aa-45c0-bcbd-3f988deea76f"  />
</div>

- **Speech Recognition**

Speech recognition technology refers to the automatic conversion of spoken language content into text, also known as Automatic Speech Recognition (ASR) technology. 

With the emergence of deep learning, Recurrent Neural Network Language Models (RNNLM) began to be widely used in this field. 

The early applications of speech recognition technology were primarily in speech transcription, where a user speaks a sentence, and the machine transcribes it into text. As AI has developed, speech recognition has become an integral part of intelligent interactive applications. 

In this project, we used Baidu Intelligent Cloud's ASR API to achieve speech recognition functionality.

The effects of speech recognition were shown as following:


<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/ff4ded00-0dd2-414b-acfd-d16574e03ff0"  />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/2b95a6f5-c9c4-4e58-b661-3ed4129f5865" width="45%" height="45%" />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/95c08da6-6d4f-4764-bd13-d019de7f7a27" width="45%" height="45%" />
</div>

- **Speech Synthesis**

Speech synthesis is the technology used to generate artificial speech through mechanical or electronic means. 

TTS (Text-to-Speech) technology falls under the category of speech synthesis. It involves transforming textual information, generated by a computer or entered externally, into understandable and fluent spoken language output, such as Mandarin Chinese in this case. 

In this project, the Baidu Intelligent Cloud's speech synthesis API is utilized to achieve Text-to-Speech (TTS) functionality. For specific results, please refer to the demonstration video.

- **Cloud-Edge Structure**

In this project, the computational power of the Raspberry Pi is not sufficient to perform deep learning for speech recognition. Therefore, we used the Baidu Cloud API for speech recognition. The recognition is done in the cloud, and the results are then returned to the Raspberry Pi for further processing.

This approach highlights the architecture of edge-cloud computing, showcasing the advantages of lightweight and flexible embedded systems.

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/61792e10-50d5-47d0-97ed-899e03825490" width="45%" height="45%" />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/1740ab2f-bc60-49a1-be60-1c60104ec86d" width="45%" height="45%" />
</div>

**video link:**

youtube: https://www.youtube.com/watch?v=xWRJxR4BXoA

bilibili: https://www.bilibili.com/video/BV1WC4y157by



