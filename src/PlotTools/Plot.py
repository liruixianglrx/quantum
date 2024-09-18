import matplotlib.pyplot as plt

# x = []
# y = []

# with open("./plot_data.txt", "r") as file:
#     for line in file:
#         values = line.split()
#         x.append(float(values[0]))
#         y.append(float(values[1]))

# plt.plot(x, y)
# plt.title("Array Plot Example")
# plt.show()


def PlotYValue(filePath):
    x = []
    y = []

    with open(filePath, "r") as file:
        for line in file:
            values = line.split()
            x.append(float(values[0]))
            y.append(float(values[1]))

    mean_y = sum(y) / len(y)

    plt.plot(x, y)
    plt.axhline(y=mean_y, color='r', linestyle='--', label=f'Mean: {mean_y:.2f}')
    plt.title("Array Plot Example")
    plt.legend()
    plt.show()

def PlotYValueWithColor(filePath):
    x = []
    y = []
    color = []

    with open(filePath, "r") as file:
        for line in file:
            values = line.split()
            x.append(float(values[0]))
            y.append(float(values[1]))
            color.append(float(values[2]))

    mean_y = sum(y) / len(y)

    # Plot segments based on color value
    for i in range(1, len(x)):
        if color[i-1] == 1:
            plt.plot(x[i-1:i+1], y[i-1:i+1], color='r')  # Green line segment when color is 1
        elif color[i-1] == -1:
            plt.plot(x[i-1:i+1], y[i-1:i+1], color='g')  # Green line segment when color is 1
        else:
            plt.plot(x[i-1:i+1], y[i-1:i+1], color='b')  # Blue line segment otherwise

    # Plot the mean line
    plt.axhline(y=mean_y, color='r', linestyle='--', label=f'Mean: {mean_y:.2f}')
    plt.title("Array Plot Example")
    plt.legend()
    plt.show()