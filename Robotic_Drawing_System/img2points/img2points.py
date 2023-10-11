import matplotlib.pyplot as plt
import classify
import edge_detection
import path_planning

if __name__ == '__main__':
    img = plt.imread('photo.jpg')
    edge = edge_detection.get_edge(img)
    flags = classify.get_flags(edge)
    paths = path_planning.get_paths(flags)
    # path_planning.show(flags.shape, paths)
