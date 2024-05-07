# Define a bytes literal representing ASCII characters
ascii_bytes = b'Hello, World!'

# Print the bytes literal
print(ascii_bytes)

# Iterate over the bytes and print their corresponding ASCII values
for byte in ascii_bytes:
    print(byte, end=' ')
print()

# Define a bytes literal representing hexadecimal values
hex_bytes = b'\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21'

# Print the bytes literal
print(hex_bytes)

# Decode the bytes to a string using ASCII encoding
decoded_string = hex_bytes.decode('ascii')

# Print the decoded string
print(decoded_string)


class TestRemoveEscapeCharacters:
    def __init__(self):
        self.passed = 0
        self.failed = 0

    def assert_equal(self, actual, expected):
        if actual == expected:
            self.passed += 1
        else:
            self.failed += 1
            print(f"Test failed! Expected: {expected}, Actual: {actual}")

    def run_tests(self):
        # Test case with escape characters
        input_string = r'Hello\nWorld!'
        expected_output = 'Hello\nWorld!'
        self.assert_equal(remove_escape_characters(input_string), expected_output)

        # Test case without escape characters
        input_string = r'Hello World!'
        expected_output = 'Hello World!'
        self.assert_equal(remove_escape_characters(input_string), expected_output)

# Define the function to be tested
def remove_escape_characters(string):
    """
    Remove escape characters from a string.
    """
    return string.replace('\\', '')

# Run the test cases
TestRemoveEscapeCharacters().run_tests()
