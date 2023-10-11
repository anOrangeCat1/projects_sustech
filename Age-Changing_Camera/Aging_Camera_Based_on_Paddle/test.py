# coding:utf-8
import cv2
import numpy as np
import os
from playsound import playsound
cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)
flag = cap.isOpened()
index = 1
playsound('sound/welcome.mp3')
while (flag):
    ret, frame = cap.read()
    cv2.imshow("Capture_Paizhao", frame)
        
    k = cv2.waitKey(1) & 0xFF
    
    if k == ord('s'):  # 按下s键，进入下面的保存图片操作
        playsound('sound/wait.mp3')
        cv2.imwrite("./inputs/" + str(index) + ".jpg", frame)
        print("save" + str(index) + ".jpg successfuly!")
        print("-------------------------")
        print("现在使用时光照相机！")
        os.system("python -u applications/tools/pixel2style2pixel.py \
                  --input_image inputs/"+str(index)+".jpg \
                  --output_path outputs/"+str(index)+" \
                  --model_type ffhq-inversion ")  # 预处理
        os.system("python -u applications/tools/styleganv2editing.py \
                  --latent outputs/"+str(index)+"/dst.npy \
                  --output_path outputs/"+str(index)+"/young \
                  --model_type ffhq-config-f \
                  --size 1024 \
                  --style_dim 512 \
                  --n_mlp 8 \
                  --channel_multiplier 2 \
                  --direction_name age \
                  --direction_offset -5")  # 年轻化
        os.system("python -u applications/tools/styleganv2editing.py \
                  --latent outputs/"+str(index)+"/dst.npy \
                  --output_path outputs/"+str(index)+"/old \
                  --model_type ffhq-config-f \
                  --size 1024 \
                  --style_dim 512 \
                  --n_mlp 8 \
                  --channel_multiplier 2 \
                  --direction_name age \
                  --direction_offset +5")  # 年老化
        young = cv2.imread("outputs/"+str(index)+"/young/dst.editing.png")
        old = cv2.imread("outputs/"+str(index)+"/old/dst.editing.png")    
        img1 = cv2.resize(young,(640,640))
        img2 = cv2.resize(old,(640,640))
        new_img = np.hstack([img1,img2])
        playsound('sound/over.mp3')
        cv2.namedWindow("时光照相机",0)
        cv2.resizeWindow("时光照相机",(1280,640))
        cv2.moveWindow("时光照相机",100,50)
        cv2.imshow("时光照相机",new_img)
        cv2.waitKey(0)
        index += 1
    elif k == ord('q'):  # 按下q键，程序退出
        playsound('sound/bye.mp3')
        break
cap.release()  # 释放摄像头
cv2.destroyAllWindows()  # 释放并销毁窗口
