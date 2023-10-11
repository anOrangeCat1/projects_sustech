import cv2
import numpy as np
import onnxruntime as ort
import time
import random
import RPi.GPIO as GPIO
import lirc
import socket
from time import ctime
HOST = '43.142.161.117'
PORT = 9001
ADDR = (HOST, PORT)
ENCODING = 'utf-8'
BUFFSIZE = 1024

# 默认mode = 0 检测人
# 初始化时mode = 0
# mode = 1 检测车
# mode = 2 检测人和车
# mode = 3 检测所有类别
mode = 0

# 模型参数
model_h = 320
model_w = 320
nl = 3
na = 3
stride = [8., 16., 32.]
anchors = [[10, 13, 16, 30, 33, 23], [30, 61, 62, 45, 59, 119], [116, 90, 156, 198, 373, 326]]
anchor_grid = np.asarray(anchors, dtype=np.float32).reshape(nl, -1, 2)
thred_nms = 0.4
thred_cond = 0.5

# 标签字典 一共可以识别80个物体 0-79
# 数字就是id 不同的id代表不同的物体
coco_dic = {
    0: "person",
    1: "bicycle",
    2: "car",
    3: "motorbike",
    4: "aeroplane",
    5: "bus",
    6: "train",
    7: "truck",
    8: "boat",
    9: "traffic light",
    10: "fire hydrant",
    11: "stop sign",
    12: "parking meter",
    13: "bench",
    14: "bird",
    15: "cat",
    16: "dog",
    17: "horse",
    18: "sheep",
    19: "cow",
    20: "elephant",
    21: "bear",
    22: "zebra",
    23: "giraffe",
    24: "backpack",
    25: "umbrella",
    26: "handbag",
    27: "tie",
    28: "suitcase",
    29: "frisbee",
    30: "skis",
    31: "snowboard",
    32: "sports ball",
    33: "kite",
    34: "baseball bat",
    35: "baseball glove",
    36: "skateboard",
    37: "surfboard",
    38: "tennis racket",
    39: "bottle",
    40: "wine glass",
    41: "cup",
    42: "fork",
    43: "knife",
    44: "spoon",
    45: "bowl",
    46: "banana",
    47: "apple",
    48: "sandwich",
    49: "orange",
    50: "broccoli",
    51: "carrot",
    52: "hot dog",
    53: "pizza",
    54: "donut",
    55: "cake",
    56: "chair",
    57: "sofa",
    58: "pottedplant",
    59: "bed",
    60: "diningtable",
    61: "toilet",
    62: "tvmonitor",
    63: "laptop",
    64: "mouse",
    65: "remote",
    66: "keyboard",
    67: "cell phone",
    68: "microwave",
    69: "oven",
    70: "toaster",
    71: "sink",
    72: "refrigerator",
    73: "book",
    74: "clock",
    75: "vase",
    76: "scissors",
    77: "teddy bear",
    78: "hair drier",
    79: "toothbrush", }

# 颜色字典
color_dic = {
    0: [255, 0, 0],
    1: [50, 75, 99],
    2: [0, 0, 255],
    3: [137, 14, 254],
    4: [190, 71, 201],
    5: [212, 3, 11],
    6: [210, 151, 79],
    7: [0, 125, 134],
    8: [212, 111, 212],
    9: [247, 49, 38],
    10: [30, 30, 49],
    11: [63, 251, 227],
    12: [182, 215, 35],
    13: [73, 58, 55],
    14: [94, 67, 147],
    15: [129, 71, 103],
    16: [128, 41, 233],
    17: [248, 217, 153],
    18: [224, 62, 86],
    19: [200, 170, 69],
    20: [43, 21, 3],
    21: [239, 223, 137],
    22: [190, 214, 78],
    23: [83, 192, 25],
    24: [248, 148, 220],
    25: [71, 158, 194],
    26: [119, 184, 243],
    27: [214, 85, 185],
    28: [155, 222, 104],
    29: [125, 156, 120],
    30: [27, 46, 71],
    31: [207, 250, 78],
    32: [5, 249, 55],
    33: [57, 165, 129],
    34: [134, 176, 205],
    35: [250, 244, 106],
    36: [47, 173, 5],
    37: [128, 198, 178],
    38: [72, 202, 65],
    39: [240, 86, 40],
    40: [184, 250, 169],
    41: [229, 120, 113],
    42: [245, 67, 251],
    43: [113, 220, 16],
    44: [94, 128, 197],
    45: [17, 254, 77],
    46: [79, 173, 188],
    47: [192, 208, 123],
    48: [184, 99, 180],
    49: [115, 10, 249],
    50: [222, 150, 29],
    51: [58, 37, 240],
    52: [129, 247, 229],
    53: [155, 99, 192],
    54: [202, 207, 96],
    55: [163, 3, 102],
    56: [98, 5, 86],
    57: [82, 138, 213],
    58: [46, 82, 226],
    59: [10, 235, 225],
    60: [141, 198, 93],
    61: [112, 130, 124],
    62: [215, 33, 162],
    63: [56, 117, 201],
    64: [81, 75, 127],
    65: [64, 94, 111],
    66: [97, 227, 50],
    67: [80, 183, 6],
    68: [71, 88, 54],
    69: [143, 188, 204],
    70: [19, 51, 107],
    71: [251, 236, 192],
    72: [190, 237, 58],
    73: [186, 165, 2],
    74: [87, 235, 248],
    75: [19, 102, 24],
    76: [41, 90, 160],
    77: [174, 98, 145],
    78: [222, 214, 144],
    79: [28, 157, 234]}

makerobo_Rpin = 16
makerobo_Gpin = 20
makerobo_Bpin = 21
makerobo_blocking = 0
rgb_Lv = [100, 1, 0]
rgb_color = [00, 00, 00]


def makerobo_ledColorset(color):
    p_R.ChangeDutyCycle(100 - color[0])
    p_G.ChangeDutyCycle(100 - color[1])
    p_B.ChangeDutyCycle(100 - color[2])


def makerobo_setup():
    global p_R, p_G, p_B
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(makerobo_Rpin, GPIO.OUT)
    GPIO.setup(makerobo_Gpin, GPIO.OUT)
    GPIO.setup(makerobo_Bpin, GPIO.OUT)
    p_R = GPIO.PWM(makerobo_Rpin, 2000)
    p_G = GPIO.PWM(makerobo_Gpin, 2000)
    p_B = GPIO.PWM(makerobo_Bpin, 2000)
    p_R.start(0)
    p_G.start(0)
    p_B.start(0)
    lirc.init("pylirc", "/etc/lirc/conf", makerobo_blocking)


def makerobo_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


def RGB_control(config):
    global color

    if config == 'KEY_CHANNELDOWN':
        rgb_color[0] = rgb_Lv[0]
        print('Makerobo Red OFF')

    if config == 'KEY_CHANNEL':
        rgb_color[0] = rgb_Lv[1]
        print('Makerobo Light Red')

    if config == 'KEY_CHANNELUP':
        rgb_color[0] = rgb_Lv[2]
        print('Makerobo Red')

    if config == 'KEY_PREVIOUS':
        rgb_color[1] = rgb_Lv[0]
        print('Makerobo Green OFF')

    if config == 'KEY_NEXT':
        rgb_color[1] = rgb_Lv[1]
        print('Makerobo Light Green')

    if config == 'KEY_PLAYPAUSE':
        rgb_color[1] = rgb_Lv[2]
        print('Makerobo Green')

    if config == 'KEY_VOLUMEDOWN':
        rgb_color[2] = rgb_Lv[0]
        print('Makerobo Blue OFF')

    if config == 'KEY_VOLUMEUP':
        rgb_color[2] = rgb_Lv[1]
        print('Makerobo Light Blue')

    if config == 'KEY_EQUAL':
        rgb_color[2] = rgb_Lv[2]
        print('Makerobo BLUE')


def makerobo_loop():
    while True:
        s = lirc.nextcode()
        while s:
            for code in s:
                print("Command: ", code)

                RGB_control(code)
                makerobo_ledColorset(rgb_color)
            if (not makerobo_blocking):
                s = lirc.nextcode()
            else:
                s = []


def destroy():
    p_R.stop()
    p_G.stop()
    p_B.stop()
    GPIO.output(makerobo_Rpin, GPIO.LOW)
    GPIO.output(makerobo_Gpin, GPIO.LOW)
    GPIO.output(makerobo_Bpin, GPIO.LOW)
    GPIO.cleanup()
    lirc.exit()


def plot_one_box(x, img, color=None, label=None, line_thickness=None):
    """
    description: Plots one bounding box on image img,
                 this function comes from YoLov5 project.
    param:
        x:      a box likes [x1,y1,x2,y2]
        img:    a opencv image object
        color:  color to draw rectangle, such as (0,255,0)
        label:  str
        line_thickness: int
    return:
        no return

    """
    tl = (
            line_thickness or round(0.002 * (img.shape[0] + img.shape[1]) / 2) + 1
    )  # line/font thickness
    color = color or [random.randint(0, 255) for _ in range(3)]
    c1, c2 = (int(x[0]), int(x[1])), (int(x[2]), int(x[3]))
    cv2.rectangle(img, c1, c2, color, thickness=tl, lineType=cv2.LINE_AA)
    if label:
        tf = max(tl - 1, 1)  # font thickness
        t_size = cv2.getTextSize(label, 0, fontScale=tl / 3, thickness=tf)[0]
        c2 = c1[0] + t_size[0], c1[1] - t_size[1] - 3
        cv2.rectangle(img, c1, c2, color, -1, cv2.LINE_AA)  # filled
        cv2.putText(
            img,
            label,
            (c1[0], c1[1] - 2),
            0,
            tl / 3,
            [225, 255, 255],
            thickness=tf,
            lineType=cv2.LINE_AA,
        )


def _make_grid(nx, ny):
    xv, yv = np.meshgrid(np.arange(ny), np.arange(nx))
    return np.stack((xv, yv), 2).reshape((-1, 2)).astype(np.float32)


def cal_outputs(outs, nl, na, model_w, model_h, anchor_grid, stride):
    row_ind = 0
    grid = [np.zeros(1)] * nl
    for i in range(nl):
        h, w = int(model_w / stride[i]), int(model_h / stride[i])
        length = int(na * h * w)
        if grid[i].shape[2:4] != (h, w):
            grid[i] = _make_grid(w, h)

        outs[row_ind:row_ind + length, 0:2] = (outs[row_ind:row_ind + length, 0:2] * 2. - 0.5 + np.tile(
            grid[i], (na, 1))) * int(stride[i])
        outs[row_ind:row_ind + length, 2:4] = (outs[row_ind:row_ind + length, 2:4] * 2) ** 2 * np.repeat(
            anchor_grid[i], h * w, axis=0)
        row_ind += length
    return outs


def post_process_opencv(outputs, model_h, model_w, img_h, img_w, thred_nms, thred_cond):
    conf = outputs[:, 4].tolist()
    c_x = outputs[:, 0] / model_w * img_w
    c_y = outputs[:, 1] / model_h * img_h
    w = outputs[:, 2] / model_w * img_w
    h = outputs[:, 3] / model_h * img_h
    p_cls = outputs[:, 5:]
    if len(p_cls.shape) == 1:
        p_cls = np.expand_dims(p_cls, 1)
    cls_id = np.argmax(p_cls, axis=1)

    p_x1 = np.expand_dims(c_x - w / 2, -1)
    p_y1 = np.expand_dims(c_y - h / 2, -1)
    p_x2 = np.expand_dims(c_x + w / 2, -1)
    p_y2 = np.expand_dims(c_y + h / 2, -1)
    areas = np.concatenate((p_x1, p_y1, p_x2, p_y2), axis=-1)

    areas = areas.tolist()
    ids = cv2.dnn.NMSBoxes(areas, conf, thred_cond, thred_nms)
    if len(ids) > 0:
        return np.array(areas)[ids], np.array(conf)[ids], cls_id[ids]
    else:
        return [], [], []


def infer_img(img0, net, model_h, model_w, nl, na, stride, anchor_grid, thred_nms=0.4, thred_cond=0.5):
    # 图像预处理
    img = cv2.resize(img0, [model_w, model_h], interpolation=cv2.INTER_AREA)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = img.astype(np.float32) / 255.0
    blob = np.expand_dims(np.transpose(img, (2, 0, 1)), axis=0)

    # 模型推理
    outs = net.run(None, {net.get_inputs()[0].name: blob})[0].squeeze(axis=0)

    # 输出坐标矫正
    outs = cal_outputs(outs, nl, na, model_w, model_h, anchor_grid, stride)

    # 检测框计算
    img_h, img_w, _ = np.shape(img0)
    boxes, confs, ids = post_process_opencv(outs, model_h, model_w, img_h, img_w, thred_nms, thred_cond)

    return boxes, confs, ids


if __name__ == "__main__":

    # 模型加载
    model_pb_path = "v5Lite-e-sim-320.onnx"
    so = ort.SessionOptions()
    net = ort.InferenceSession(model_pb_path, so)
    makerobo_setup()

    # 调用摄像头
    video = 0
    cap = cv2.VideoCapture(video)

    # 设置是否开始检测 初始化为否
    start_detect = False

    # 设置是否退出 初始化为否
    quit_detect = False

    # 进入循环 开始显示画面
    with socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM) as s:
        # 尝试连接服务器
        s.connect(ADDR)
        # Note0=open('person.txt', mode='w')
        # Note1=open('car.txt', mode='w')
        # Note2=open('cp.txt', mode='w')
        while True:

            # 读取摄像头图像
            success, img0 = cap.read()
            if success:



                # 开始检测
                if start_detect:

                    # 计时开始
                    t1 = time.time()
                    # 传入图片和模型 进行推理
                    inf_boxes, inf_scores, inf_ids = infer_img(img0, net, model_h, model_w, nl, na, stride, anchor_grid,
                                                               thred_nms=0.4, thred_cond=0.5)

                    # mode 0 检测人
                    # in coco_dic: 0: "person"
                    if mode == 0:
                        print("mode0")
                        # 只有红灯亮
                        rgb_color[0] = rgb_Lv[2]
                        rgb_color[1] = rgb_Lv[0]
                        rgb_color[2] = rgb_Lv[0]
                        makerobo_ledColorset(rgb_color)


                        # 计算人数
                        num_person = np.count_nonzero(inf_ids == 0)
                        print("persons: %d" % num_person)
                        inData = str(num_person)
                        Note0.write(inData)
                        inData = inData + 'p'
                        # 画框
                        for Box, Score, Id in zip(inf_boxes, inf_scores, inf_ids):

                            # mode 0
                            if Id == 0:
                                label = '%s:%.2f' % (coco_dic[Id], Score)
                                plot_one_box(Box.astype(np.int16), img0, color=color_dic[Id], label=label,
                                             line_thickness=None)

                    # mode 1 检测车
                    # in coco_dic: 2: "car"
                    elif mode == 1:
                        # 只有绿灯亮
                        rgb_color[1] = rgb_Lv[2]
                        rgb_color[0] = rgb_Lv[0]
                        rgb_color[2] = rgb_Lv[0]
                        makerobo_ledColorset(rgb_color)


                        # 计算车数
                        num_car = np.count_nonzero(inf_ids == 2)
                        print("persons: %d" % num_car)
                        inData = str(num_car)
                        Note0.write(inData)
                        inData = inData + 'c'
                        # 画框
                        for Box, Score, Id in zip(inf_boxes, inf_scores, inf_ids):

                            # mode 1
                            if Id == 2:
                                label = '%s:%.2f' % (coco_dic[Id], Score)
                                plot_one_box(Box.astype(np.int16), img0, color=color_dic[Id], label=label,
                                             line_thickness=None)

                    # mode 2 检测人和车
                    elif mode == 2:
                        # 红绿灯亮
                        rgb_color[1] = rgb_Lv[2]
                        rgb_color[0] = rgb_Lv[2]
                        rgb_color[2] = rgb_Lv[0]
                        makerobo_ledColorset(rgb_color)

                        # 计算人数和车数
                        num_person = np.count_nonzero(inf_ids == 0)
                        num_car = np.count_nonzero(inf_ids == 2)
                        print("persons: %d" % num_person)
                        print("persons: %d" % num_car)
                        inData = str(num_car + num_person)
                        inData = inData + 't'
                        # 画框
                        for Box, Score, Id in zip(inf_boxes, inf_scores, inf_ids):

                            # mode 2
                            if Id == 0 or Id == 2:
                                label = '%s:%.2f' % (coco_dic[Id], Score)
                                plot_one_box(Box.astype(np.int16), img0, color=color_dic[Id], label=label,
                                             line_thickness=None)

                    # mode 3 检测所有
                    elif mode == 3:
                        # 蓝灯亮
                        rgb_color[2] = rgb_Lv[2]
                        rgb_color[0] = rgb_Lv[0]
                        rgb_color[1] = rgb_Lv[0]
                        makerobo_ledColorset(rgb_color)


                        # 画框
                        for Box, Score, Id in zip(inf_boxes, inf_scores, inf_ids):
                            # mode 3
                            label = '%s:%.2f' % (coco_dic[Id], Score)
                            plot_one_box(Box.astype(np.int16), img0, color=color_dic[Id], label=label,
                                         line_thickness=None)

                    # 计时结束
                    t2 = time.time()  # t2 - t1 为推理一帧所需要的时间 FPS = 1 / (t2 - t1) 帧率
                    if i % 20 == 0 and (mode == 0 or mode == 1 or mode == 2):
                        s.send(inData.encode(ENCODING))
                        print('发送成功！')
                    str_FPS = "FPS: %.2f" % (1. / (t2 - t1))

                    # 显示模式信息
                    cv2.putText(img0, "detection mode: " + str(mode), (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 3)
                    cv2.putText(img0, str_FPS, (450, 450), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 3)
                    print("mode: %d" % mode)
                else:
                    # 没有灯亮
                    rgb_color[0] = rgb_Lv[0]
                    rgb_color[1] = rgb_Lv[0]
                    rgb_color[2] = rgb_Lv[0]
                    makerobo_ledColorset(rgb_color)
                    cv2.putText(img0, "observation mode", (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 3)

                cv2.imshow("video", img0)

            cv2.waitKey(1)

            # 遥控器控制
            s = lirc.nextcode()

            while s:
                for code in s:
                    print("Command: ", code)
                    # 按EQ退出
                    if code == 'KEY_EQUAL':
                        quit_detect = not quit_detect
                        print('EQ')

                    # 按0开始检测
                    elif code == 'KEY_PLAYPAUSE':
                        mode = 0

                        start_detect = not start_detect
                        print('0')

                        # 退出检测后返回默认值
                        if not start_detect:
                            mode = 0
                        # 打印 True 开始检测
                        # 打印 False 未检测
                        print(start_detect)

                    # 在开始检测后才能开始调整检测模式
                    # mode = 0 人 按p
                    # mode = 1 车 按c
                    # mode = 2 人和车 按b
                    if start_detect:
                        # 按1检测人 person
                        if code == 'KEY_NUMERIC_0':
                            mode = 0


                            print('1')

                        # 按c检测车 car
                        elif code == 'KEY_NUMERIC_1':
                            mode = 1
                            print('2')

                        # 按b检测人和车 both
                        elif code == 'KEY_NUMERIC_2':
                            mode = 2
                            print('3')

                        # 按a检测所有类别 all
                        elif code == 'KEY_NUMERIC_3':
                            mode = 3
                            print('4')



                    makerobo_ledColorset(rgb_color)
                if (not makerobo_blocking):
                    s = lirc.nextcode()
                else:
                    s = []

            if quit_detect:
                break
            # # 键盘控制
            # # 按q退出
            # key = cv2.waitKey(1) & 0xFF
            # if key == ord('q'):
            #     break
            #
            # # 按s开始检测
            # elif key & 0xFF == ord('s'):
            #     mode = 0
            #     start_detect = not start_detect
            #
            #     # 退出检测后返回默认值
            #     if start_detect:
            #         mode = 0
            #     # 打印 True 开始检测
            #     # 打印 False 未检测
            #     print(start_detect)
            #
            # # 在开始检测后才能开始调整检测模式
            # # mode = 0 人 按p
            # # mode = 1 车 按c
            # # mode = 2 人和车 按b
            # if start_detect:
            #     # 按p检测人 person
            #     if key == ord('p'):
            #         mode = 0
            #
            #     # 按c检测车 car
            #     elif key == ord('c'):
            #         mode = 1
            #
            #     # 按b检测人和车 both
            #     elif key == ord('b'):
            #         mode = 2
            #
            #     # 按a检测所有类别 all
            #     elif key == ord('a'):
            #         mode = 3
    s.close()
    cap.release()
    cv2.destroyAllWindows()
    destroy()

