# Define a bytes literal representing ASCII characters
ascii_bytes : str = b'Hello, World!'

def main():
    # Print the bytes literal
    print(ascii_bytes)

    # Iterate over the bytes and print their corresponding ASCII values
    for byte in ascii_bytes:
        print(byte, end=' ')
    print()

if __name__ == "__main__":
    main()
