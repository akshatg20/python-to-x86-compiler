def array_sum(array : list[int], size : int) -> int:
    sum : int = 0
    i : int = 0
    for i in range(size):
        sum = sum + array[i]
    return sum

def main():
    array : list[int] = [1, 2, 3, 4, 7, 20, -4, 5]
    length : int = 8
    sum : int = array_sum(array, length)
    print("The array is given by")
    i : int = 0
    for i in range(length):
        print(array[i])
    print("The sum of array elements is ", sum)
    return

if __name__ == "__main__":
    main()
