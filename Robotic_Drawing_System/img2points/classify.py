import cv2
import numpy as np
import math
import time
from matplotlib import pyplot as plt


def neighbors(p):
    n = [[0, 0]] * 8
    n[0] = [p[0] - 1, p[1] - 1]
    n[1] = [p[0] - 1, p[1]]
    n[2] = [p[0] - 1, p[1] + 1]
    n[3] = [p[0], p[1] + 1]
    n[4] = [p[0] + 1, p[1] + 1]
    n[5] = [p[0] + 1, p[1]]
    n[6] = [p[0] + 1, p[1] - 1]
    n[7] = [p[0], p[1] - 1]
    return n


def classify(kernal):
    state = 0
    for p in neighbors([1, 1]):
        i, j = p
        if kernal[i][j] == 255:
            if state == 0:
                state = 3
            elif state == 1 or state == 4:
                state = 2
            elif state == 3:
                state = 4
        else:
            if state == 3 or state == 4:
                state = 1
    if state == 3 or state == 4:
        state = 1
    return state


def bi(img, thre):
    img_out = np.zeros(img.shape)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            if img[i][j] >= thre:
                img_out[i][j] = 255
    return img_out


def get_flags(img):
    img = bi(img, 127)
    height, width = img.shape
    temp = np.zeros(img.shape)
    temp[2:height - 2, 2:width - 2] = img[2:height - 2, 2:width - 2]
    flags = np.zeros(img.shape)
    for i in range(height):
        for j in range(width):
            if temp[i][j] == 255:
                kernal = temp[i - 1:i + 2, j - 1:j + 2]
                flags[i - 1][j - 1] = classify(kernal)
    return flags


if __name__ == "__main__":
    img = plt.imread('test.tif')
    flags = get_flags(img)
