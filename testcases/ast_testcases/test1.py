def main():
    # Define a bytes literal representing ASCII characters
    ascii_bytes : str = b'Hello, World!'

    # Print the bytes literal
    print(ascii_bytes)

    # Iterate over the bytes and print their corresponding ASCII values
    byte : bool = True
    for byte in ascii_bytes:
        print(byte)

    print()
    return

if __name__ == "__main__":
    main()
