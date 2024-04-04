def merge_sort(arr):
    """
    Merge sort implementation.
    
    Parameters:
    - arr (list): List of elements to be sorted.
    
    Returns:
    - None (List is sorted in-place).
    """
    if len(arr) > 1:
        mid = len(arr) // 2  # Find the middle of the array
        left_half = arr[:mid]  # Divide the array into two halves
        right_half = arr[mid:]

        # Recursively sort the two halves
        merge_sort(left_half)
        merge_sort(right_half)

        # Merge the sorted halves
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        # Check for any remaining elements in left_half
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        # Check for any remaining elements in right_half
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

def main():

    print(''' This is a code 
          for merge sort, which
          return a sorted list from an unsorted list\n''')
    
    unsorted_list = [38, 27, 43, 3, 9, 82, 10]
    
    print("Unsorted List:", unsorted_list)

    merge_sort(unsorted_list)

    print("Sorted List:", unsorted_list)

if __name__ == "__main__":
    main()
