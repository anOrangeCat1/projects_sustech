import time
import numpy as np
import matplotlib.pyplot as plt
import cv2
import pyautogui as ui
import sys
sys.setrecursionlimit(100000)


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


def neighbors1(p):
    n = [[0, 0]] * 4
    n[0] = [p[0] - 1, p[1]]
    n[1] = [p[0], p[1] - 1]
    n[2] = [p[0], p[1] + 1]
    n[3] = [p[0] + 1, p[1]]
    return n


def neighbors2(p):
    n = [[0, 0]] * 4
    n[0] = [p[0] - 1, p[1] - 1]
    n[1] = [p[0] - 1, p[1] + 1]
    n[2] = [p[0] + 1, p[1] - 1]
    n[3] = [p[0] + 1, p[1] + 1]
    return n


def dfs(i, j, group, path, paths):  # endpoint detect
    if group[i][j] == 0:
        return False
    group[i][j] = 0
    path.append(np.array([i, j]))
    end = True
    for p in neighbors1([i, j]):
        if not end:
            path = []
        a, b = p
        if dfs(a, b, group, path, paths):
            end = False
    for p in neighbors2([i, j]):
        if not end:
            path = []
        a, b = p
        if dfs(a, b, group, path, paths):
            end = False
    if end:
        paths.append(path)
    return True


def path(group):
    paths = []
    height, width = group.shape
    for i in range(height):
        for j in range(width):
            if group[i][j] != 1:
                continue
            path = []
            dfs(i, j, group, path, paths)
            paths.append(path)

    for i in range(height):
        for j in range(width):
            if group[i][j] == 0:
                continue
            path = []
            dfs(i, j, group, path, paths)
            paths.append(path)
    return paths


def show(size, paths):
    can = np.zeros(size, dtype=np.uint8)
    cv2.imshow('path', can)
    cv2.waitKey(0)
    for path in paths:
        for p in path:
            # time.sleep(delay)
            ui.press('enter')
            x, y = p
            can[x][y] = 255
            cv2.imshow('path', can)
            cv2.waitKey(0)
    cv2.destroyAllWindows()


def inv(img):
    img_out = np.zeros(img.shape)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            img_out[i][j] = 255 - img[i][j]
    return img_out


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


def get_paths(flags):
    paths = path(flags)
    for i in range(len(paths)):
        paths[i] = paths[i][::10]
    i = 0
    while i < len(paths):
        if len(paths[i]) <= 5:
            del paths[i]
        else:
            i = i + 1
    return paths


if __name__ == "__main__":
    img = plt.imread('photo.tif')

    height, width = img.shape
    temp = np.zeros(img.shape)
    temp[3:height - 3, 3:width - 3] = img[3:height - 3, 3:width - 3]
    flags = np.zeros(img.shape)

    for i in range(3, height - 3):
        for j in range(3, width - 3):
            if temp[i][j] == 255:
                kernal = temp[i - 1:i + 2, j - 1:j + 2]
                flags[i][j] = classify(kernal)

    paths = path(flags)
    for i in range(len(paths)):
        paths[i] = paths[i][::10]
    i = 0
    while i < len(paths):
        if len(paths[i]) <= 5:
            del paths[i]
        else:
            i = i + 1
    # size = flags.shape
    # show(size, paths)

    # plt.imshow(img, 'gray')
    # plt.show()
