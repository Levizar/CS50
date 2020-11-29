if __name__ == "__main__":

    # Recursiv drawing
    def draw(n, height):
        # Base case
        if n == 0:
            return
        # Draw previous line
        draw(n - 1, height)
        # Draw if not base case
        k = height - n
        line = ""
        for i in range(k):
            line += " "
        for i in range(n):
            line += "#"
        for i in range(2):
            line += " "
        for i in range(n):
            line += "#"
        print(line)

    # get correct input
    height = int()
    while (height < 1 or height > 8):
        try:
            height = int(input("Height: "))
        except:
            continue

    draw(height, height)

