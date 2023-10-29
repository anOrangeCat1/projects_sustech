# Age-Changing Camera Based on GANs

This project is based on GANs(Generative Adversarial Networks). To make the task simple, I use **PaddleGAN** frame work. When you input a photo, this project will output a photo that looks both younger and older.

Though this project, I can learn some about GANs. The folder _GAN_try_ is try to realize a simple GAN. Two papers were read, which were _HyperStyle_StyleGAN_Inversion_with_HyperNetworks_for_Real_Image_Editing_ and
_Age and Gender Classification using Convolutional Neural Networks_.

**_Below are the relevant files:_**
|folder_name/file_name|content&function|
|------|------|
|_Aging_Camera_Based_on_Paddle_|**Codes based on PaddleGAN, which can change age of photo.**|
|_GAN_try_|**basic codes trying to GAN using random data**|
|_results_|**the results of changing aging portrait photograph**|
|_Basic_Survey.pdf_|**the PPT of primary survey to find some age changing software**|
|_age-changing_camera_final_pre.pdf_|**final project PPT**|

The folder _Aging_Camera_Based_on_Paddle_ contains my Python script, but if you want to run them, you must download PaddleGan framework first. Link: https://github.com/PaddlePaddle/PaddleGAN . 
Once you have successfully deployed Paddle locally, put all things of _"Aging_Camera_Based_on_Paddle"_ in same directory, then you can run it successfully.

- **Generative Adversarial Networks(GAN)**

GAN, Generative Adversarial Networks, is a deep learning architecture used for various tasks such as image generation, style transfer, and more. The primary idea behind GAN is to train two neural networks, one called the generator and the other called the discriminator, and have them compete with each other. The generator is trained to create new images that resemble the training dataset, while the discriminator is trained to distinguish between the generated images and real ones. As training progresses, the generator can generate images that are closer to real images, and the discriminator becomes better at distinguishing between real and generated images."

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/81e10bb2-4593-4032-b5ca-36eae328fb01"  />
</div>

- **Style Transfer Tasks of GANs** 

The goal is to generate a new image that retains the content of a given image while changing some of the stylistic aspects to obtain the desired target image. In style transfer tasks, the generator produces two images: a content image and a style image. Both of these images are used as input, and the generator produces an output image that combines the content of the content image (e.g., a person's likeness) and the stylistic features of the style image (e.g., age).

The frame of this project is shown as follows:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/a8b1ba60-c840-4447-ae25-49b89ffed1a4" width="70%" height="70%"/>
</div>


The results are shown as following, which are fun:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/eb97bea6-7e6b-4fe7-9bde-f69e27156d6d"  />
</div>

**Donald Trump and Andy Lau, who are famous.**

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/e3bc58a8-4adf-4449-887b-c8bbbd26d33e"  />
</div>

**They are both my friends.**

**video link:**

youtube: https://www.youtube.com/watch?v=hzoAII0tOl0

bilibili: https://www.bilibili.com/video/BV1GH4y1R7hG



