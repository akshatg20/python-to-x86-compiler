# Define the function to be tested
def remove_escape_characters(string : str) -> str:
    """
    Remove escape characters from a string.
    """
    return string

class TestRemoveEscapeCharacters:
    def __init__(self) -> None:
        self.passed : int = 0
        self.failed : int = 0
        return

    def assert_equal(self, actual : str, expected : str) -> bool:
        if actual == expected:
            self.passed += 1
            return True
        else:
            self.failed += 1
            print("Test failed!")
            return False

    def run_tests(self) -> None:
        # Test case with escape characters
        input_string1 : str = r'Hello\nWorld!'
        expected_output1 : str = 'Hello\nWorld!'
        val1 : str = remove_escape_characters(input_string1)
        self.assert_equal(val1, expected_output1)

        # Test case without escape characters
        input_string2 : str = r'Hello World!'
        expected_output2 : str = 'Hello World!'
        val2 : str = remove_escape_characters(input_string2)
        self.assert_equal(val2, expected_output2)

        # Return from the test cases
        return

def main():
    # Define a bytes literal representing ASCII characters
    ascii_bytes : str = b'Hello, World!'
    # Print the bytes literal
    print(ascii_bytes)
    # Define a bytes literal representing hexadecimal values
    hex_bytes : str = b'\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21'
    # Print the bytes literal
    print(hex_bytes)
    
    # Run the test cases
    obj : TestRemoveEscapeCharacters = TestRemoveEscapeCharacters()
    obj.run_tests()
    return

if __name__ == "__main__":
    main()
