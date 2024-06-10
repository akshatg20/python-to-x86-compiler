our_variable : int = 10

def main():
  print("We are inside the main function")

if __name__ == "__main__":
  main()
elif our_variable > 10:
  print("Value of the pre-defined variable is greater than 10")
else:
  print("Value of the pre-defined variable is less than or equal to 10")
