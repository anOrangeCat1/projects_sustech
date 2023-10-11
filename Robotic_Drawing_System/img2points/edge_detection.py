import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate


def nearest_color(img0, dim):
    r = dim[0]
    c = dim[1]
    # new row and column numbers
    rr = (img0.shape[0] - 1) / (r - 1)
    cr = (img0.shape[1] - 1) / (c - 1)
    # computation of one step of new pixel on behalf of the old ones
    img = np.zeros([r, c, 3], dtype=np.uint8)  # initiation of a new image
    for i in range(0, c):
        for j in range(0, r):
            if np.ceil(i * cr) - i * cr > i * cr - np.floor(i * cr):
                if np.ceil(j * rr) - j * rr > j * rr - np.floor(j * rr):
                    img[j][i] = img0[int(np.floor(j * rr))][int(np.floor(i * cr))]
                else:
                    img[j][i] = img0[int(np.ceil(j * rr))][int(np.floor(i * cr))]
            else:
                if np.ceil(i * cr) - i * cr > i * cr - np.floor(i * cr):
                    img[j][i] = img0[int(np.floor(j * rr))][int(np.ceil(i * cr))]
                else:
                    img[j][i] = img0[int(np.ceil(j * rr))][int(np.ceil(i * cr))]
            # find the nearest pixel
    return img


def linear(x0, x, a, b):
    return a * (1 - x + x0) + b * (x - x0)  # computation of linear interpolation


def bicubic_12012103(img0, dim):
    if dim[0] >= img0.shape[0]:
        r = dim[0] -1
    else:
        r = dim[0]
    if dim[1] >= img0.shape[1]:
        c = dim[1] -1
    else:
        c = dim[1]
    # when the image is enlarged, the function will generate an image with 1 more column and 1 nore row.
    # in this case, compensation is needed.
    r0 = img0.shape[0]
    c0 = img0.shape[1]
    # old row and column numbers
    rs0 = range(r0)
    cs0 = range(c0)
    f = interpolate.interp2d(cs0, rs0, img0, kind='cubic')
    # generate the interpolation function
    rr = (r0 - 1) / (r - 1)
    cr = (c0 - 1) / (c - 1)
    rs = np.arange(0, r0, rr)
    cs = np.arange(0, c0, cr)
    img = f(cs, rs)
    # generate the new image using the interpolation function
    img = img.astype(np.uint8)
    # data type transformation
    return img


def dilate2(img_in):
    kernalInt = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
    img_out = cv.dilate(img_in, kernalInt, iterations=2, borderType=cv.BORDER_CONSTANT, borderValue=0)
    return img_out


def erode2(img_in):
    kernalInt = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
    img_out = cv.erode(img_in, kernalInt, iterations=1, borderType=cv.BORDER_CONSTANT, borderValue=0)
    return img_out


def dilate(img_in):
    kernalInt = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
    img_out = cv.dilate(img_in, kernalInt, iterations=5, borderType=cv.BORDER_CONSTANT, borderValue=0)
    return img_out


def erode(img_in):
    kernalInt = cv.getStructuringElement(cv.MORPH_RECT, (3, 3))
    img_out = cv.erode(img_in, kernalInt, iterations=5, borderType=cv.BORDER_CONSTANT, borderValue=0)
    return img_out


def color2gray(img):
    img_out = np.zeros(img.shape[0:2], dtype=np.uint8)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            img_out[i][j] = int(sum(img[i][j]) / 3)
    return img_out


def get_edge(img):
    img_gray = color2gray(img)
    img_b = cv.GaussianBlur(img_gray, [31, 31], 1, 1)
    edge = cv.Canny(img_b, 50, 120)
    return edge


if __name__ == "__main__":
    img = plt.imread('ID photo\\photo.jpg')
    edge = get_edge(img)
