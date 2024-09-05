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