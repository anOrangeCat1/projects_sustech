import tkinter as tk
from tkinter import messagebox
from tkinter.ttk import *
from tkinter import filedialog
from tkinter.filedialog import askdirectory

import webbrowser
import os

from PIL import Image
import numpy as np
import functools
import threading
from download import *


def work_mkdir():
    if os.path.exists('D:\素描图生成器'):
        pass
    else:
        os.mkdir('D:\素描图生成器')
        os.mkdir('D:\素描图生成器\程序配置文件（请不要更改）')
        down_image()


work_mkdir()
os.chdir('D:\素描图生成器')
path = os.getcwd()
path_image = '{0}\输出----图片'.format(path)
path_most = ' 工作目录位置：  {0} \n 输出图片位置：  {1}\输出----图片'.format(path, path)


def images_re(numbers):
    screen2.delete(1.0, tk.END)

    startss = os.listdir(image_paths)
    image_numbers = len(startss)
    screen2.insert('insert', '共 ' + str(image_numbers) + ' 张： ' + '\n')
    for i, starts in enumerate(startss):
        start = ''.join(starts)
        print('正在转化--图片：  ' + start)
        U = '第 ' + str(i + 1) + '张： ' + '正在转化--图片：  ' + start
        screen2.insert('insert', U + '\n')
        sta = image_paths + '/' + start
        end = './' + '输出----图片/' + 'HD_20' + start

        a = np.asarray(Image.open(sta).convert('L')).astype('float')
        depth = numbers
        grad = np.gradient(a)
        grad_x, grad_y = grad
        grad_x = grad_x * depth / 100.
        grad_y = grad_y * depth / 100.
        A = np.sqrt(grad_x ** 2 + grad_y ** 2 + 1.)
        uni_x = grad_x / A
        uni_y = grad_y / A
        uni_z = 1. / A
        vec_el = np.pi / 2.2
        vec_az = np.pi / 4.
        dx = np.cos(vec_el) * np.cos(vec_az)
        dy = np.cos(vec_el) * np.sin(vec_az)
        dz = np.sin(vec_el)
        b = 255 * (dx * uni_x + dy * uni_y + dz * uni_z)
        b = b.clip(0, 255)
        im = Image.fromarray(b.astype('uint8'))
        im.save(end)
    screen2.insert('insert', '程序运行成功，图片都已转化为素描图。')


def one_image_re(numbers):
    screen2.delete(1.0, tk.END)
    start = image_path
    screen2.insert('insert', '共 ' + str(1) + ' 张： ' + '\n')
    print('正在转化--图片：  ' + start)
    U = '第 ' + str(1) + '张： ' + '正在转化--图片：  ' + start
    screen2.insert('insert', U + '\n')
    sta = image_path
    end = './' + '输出----图片/' + 'HD_20' + str(start[-5:])
    a = np.asarray(Image.open(sta).convert('L')).astype('float')
    depth = numbers
    grad = np.gradient(a)
    grad_x, grad_y = grad
    grad_x = grad_x * depth / 100.
    grad_y = grad_y * depth / 100.
    A = np.sqrt(grad_x ** 2 + grad_y ** 2 + 1.)
    uni_x = grad_x / A
    uni_y = grad_y / A
    uni_z = 1. / A
    vec_el = np.pi / 2.2
    vec_az = np.pi / 4.
    dx = np.cos(vec_el) * np.cos(vec_az)
    dy = np.cos(vec_el) * np.sin(vec_az)
    dz = np.sin(vec_el)
    b = 255 * (dx * uni_x + dy * uni_y + dz * uni_z)
    b = b.clip(0, 255)
    im = Image.fromarray(b.astype('uint8'))
    im.save(end)
    screen2.insert('insert', '程序运行成功，图片都已转化为素描图。')


def exists_mkdir():
    if os.path.exists('输出----图片'):
        pass
    else:
        os.mkdir('输出----图片')


def print_selection(v):
    global v1
    l.config(text='你所选择的参数是：   ' + v)
    v1 = v


def print_image_path(image_path):
    l2.config(text='图片路径是：   ' + image_path)


def print_images_path(image_paths):
    l3.config(text='图片文件夹路径是：   ' + image_paths)


def main_images():
    print(v1)
    if int(v1) == 0:
        c["text"] = "程序出错，原因是没有选择参数"
        pass
    else:
        try:

            next_work = tk.messagebox.askyesno(title='提示', message='是否开始下一步，可能要等待几秒')
            print(next_work)
            if next_work == True:
                numbers = int(v1)
                image_1 = functools.partial(images_re, numbers=numbers)
                p = threading.Thread(target=image_1)
                p.start()
                print((threading.activeCount() - 1))
                tk.messagebox.showinfo(title='提示', message='程序运行成功了')
                if image_paths is True:
                    c["text"] = c["text"] = "程序运行出错了,可能是没有选择路径或者缺少了配置文件"
                else:
                    c["text"] = "我们的程序运行成功了" + '\n' + '请到 ' + path_image + '\n' + '文件夹下找到图片'
            else:
                pass
        except (NameError, Exception):
            c["text"] = "程序运行出错了,可能是没有选择路径或者缺少了配置文件"


def main_one_images():
    print(v1)
    if int(v1) == 0:
        c["text"] = "程序出错，原因是没有选择参数"
        pass

    else:
        try:
            next_work = tk.messagebox.askyesno(title='提示', message='是否开始下一步，可能要等待几秒')
            print(next_work)
            if next_work == True:
                numbers = int(v1)
                image_1 = functools.partial(one_image_re, numbers=numbers)
                p = threading.Thread(target=image_1)
                p.start()
                print((threading.activeCount() - 1))
                tk.messagebox.showinfo(title='提示', message='程序运行成功了')
                if image_path is True:
                    c["text"] = c["text"] = "程序运行出错了,可能是没有选择路径或者缺少了配置文件"
                else:
                    c["text"] = "我们的程序运行成功了" + '\n' + '请到 ' + path_image + '\n' + '文件夹下找到图片'
            else:
                pass

        except (NameError, Exception):
            c["text"] = "程序运行出错了,可能是没有选择路径或者缺少了配置文件"


def window_1():
    tk.messagebox.showinfo(title='工作目录', message=path_most)


def window_2():
    tk.messagebox.showinfo(title='使用手册', message=text_1)


def window_3():
    url_3 = ''
    webbrowser.open(url_3, new=2, autoraise=True)


def window_4():
    tk.messagebox.showinfo(title='', message=text_2)


def open_image():
    global image_path
    image_path = filedialog.askopenfilename()
    print_image_path(image_path)
    print(image_path)


def open_images():
    global image_paths
    image_paths = askdirectory()
    print_images_path(image_paths)
    print(image_paths)


def open_images_path():
    webbrowser.open(os.getcwd() + '\输出----图片')


window = tk.Tk()
window.geometry('600x600+80+60')

if os.path.exists('.\程序配置文件（请不要更改）\log.ico'):
    window.iconbitmap('.\\程序配置文件（请不要更改）\\log.ico')
else:
    pass

window.resizable(False, False)

exists_mkdir()

if os.path.exists(r'.\程序配置文件（请不要更改）\background.gif'):
    canvas = tk.Canvas(window, width=600, height=100)
    image_file = tk.PhotoImage(file=r'.\程序配置文件（请不要更改）\background.gif')
    image = canvas.create_image(0, 0, anchor='nw', image=image_file)
    canvas.create_text(300, 80, text="素描图生成器", fill="blue", font=("Times", 24))
    canvas.pack(side='top')
else:
    p = tk.Label(window, text="这的程序少了一个图片配置文件", background="green")
    p.place(x=150, y=50)
    pass

menubar = tk.Menu(window)

filemenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label=' 菜单 ', menu=filemenu)
filemenu.add_command(label='工作目录', command=window_1)
filemenu.add_command(label='退出程序', command=window.quit)

editmenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='', menu=editmenu)
editmenu.add_command(label='', command=window_2)

makemenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='', menu=makemenu)
makemenu.add_command(label='', command=window_3)

freemenu = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label='', menu=freemenu)
freemenu.add_command(label='', command=window_4)

window.config(menu=menubar)

window.title('素描图生成器')
w = tk.Label(window, text='工作目录： ' + path)
w_ = tk.Label(window, text='使用说明：')
w3 = tk.Label(window, text='步骤一：选择图片文件或者文件夹（二选一）')
w4 = tk.Label(window, text='步骤二：选择 0-100的数值，数值越大，颜色越深。--------标准参数是 10 ')
w5 = tk.Label(window, text='步骤三：点击确认 确定单图/确定文件夹（对应前面的选择） 等待几秒后出现的提示')
w6 = tk.Label(window, text='点击“打开图片存放文件夹” 到输入----图片  文件夹找到素描图')
w_.place(x=0, y=100)
w.place(x=0, y=200)
w3.place(x=0, y=120)
w4.place(x=0, y=140)
w5.place(x=0, y=160)
w6.place(x=0, y=180)

b = Button(window, text='单图片选择', command=open_image)
b.place(x=15, y=240)
b = Button(window, text='多图片： 文件夹选择', command=open_images)
b.place(x=15, y=270)

l2 = tk.Label(window, fg='blue', width=70, text='')
l2.place(x=130, y=240)
l3 = tk.Label(window, fg='blue', width=70, text='')
l3.place(x=150, y=270)

l = tk.Label(window, bg='yellow', width=20, text='empty')
l.place(x=220, y=300)

s = tk.Scale(window, label='try：', from_=0, to=100, orient=tk.HORIZONTAL,
             length=580, showvalue=0, tickinterval=10, resolution=1, command=print_selection)
s.place(x=0, y=320)

b = Button(window, text='确定文件夹', command=main_images)
b.place(x=490, y=400)

b = Button(window, text='确定单图', command=main_one_images)
b.place(x=380, y=400)

c = tk.Label(window, text="", background="yellow")
c.place(x=180, y=430)

b = Button(window, text='打开图片存放文件夹', command=open_images_path)
b.place(x=460, y=465)

screen2 = tk.Text(window, height=4, width=75)
screen2.place(x=30, y=500)

window.mainloop()
