if __name__ == "__main__":

    # Recursive drawing
    def draw(n, height):
        # Base case
        if n == 0:
            return
        # Draw previous line
        draw(n - 1, height)
        # Draw if not base case
        k = height - n
        line = k * " " + n * "#" + 2 * " " + n * "#"
        print(line)

    # get correct input
    height = int()
    while height < 1 or height > 8:
        try:
            height = int(input("Height: "))
        except ValueError:
            continue

    draw(height, height)

