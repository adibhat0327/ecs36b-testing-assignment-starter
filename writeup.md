# Google Test And Debugging Writeup

## Things I Thought To Test

1. `swap`: swapping two values results in each variable holding the other's original value
2. `swap`: swapping values inside an array only changes the two swapped positions, not others
3. `swap`: swapping a value with itself leaves it unchanged
4. `copy_array`: the copy contains the same values as the original
5. `copy_array`: modifying the copy does not change the original (independent memory)
6. `copy_array`: the pointer returned is different from the input pointer (actual new allocation)
7. `min_index_of_array`: returns 0 when the minimum is at the front
8. `min_index_of_array`: returns the last index when the minimum is at the end
9. `min_index_of_array`: returns the correct index when the minimum is in the middle
10. `min_index_of_array`: returns the first occurrence when there are duplicate minimums
11. `min_index_of_array`: does not modify the contents of the array
12. `make_sorted`: correctly sorts an already-sorted array (no-op)
13. `make_sorted`: correctly sorts a reverse-sorted array
14. `make_sorted`: correctly sorts an array with random order
15. `make_sorted`: correctly sorts an array with duplicate values
16. `get_sorted`: returns a sorted copy without modifying the original array
17. `get_sorted`: the returned pointer is different from the input pointer
18. `parse_args`: correctly converts string arguments to integers and sets len_out
19. `parse_args`: sets ar_out to NULL and len_out to 0 when no arguments are given

## Bugs

### Bug 1

### Location

`src/sorting.cpp`, lines 66–68 (`swap` function)

```c++
int* temp = a;
a = b;
b = temp;
```

### How the bug was located

The `SimpleSwapTwoValues` test failed — after calling `swap`, both variables still held their original values. Inspecting the implementation revealed the issue immediately.

### Description

The function swaps the pointer variables `a` and `b` themselves (which are local copies of the caller's pointers), rather than swapping the integer values they point to. Since C passes arguments by value, reassigning `a` and `b` locally has no effect on the caller.

### Fix

Dereference `a` and `b` to swap the values at those addresses, not the addresses themselves.

```c++
int temp = *a;
*a = *b;
*b = temp;
```

---

### Bug 2

### Location

`src/sorting.cpp`, lines 52 and 56 (`min_index_of_array` function)

```c++
if (ar[i] > ar[min_index]) {
    min_index = i;
}
return ar[min_index];
```

### How the bug was located

The `SimpleMinIndexAtFrontOfArray` test failed — the function returned a wrong index. Reading the code showed two problems: the comparison finds the *maximum*, not the minimum, and the return value is the array *value* rather than the *index*.

### Description

Two bugs:
1. The comparison `ar[i] > ar[min_index]` updates `min_index` when a *larger* value is found, so the function finds the maximum index, not the minimum.
2. `return ar[min_index]` returns the value stored at that index rather than the index itself, which is what the function is supposed to return.

### Fix

Change `>` to `<` so we track the minimum, and return `min_index` instead of `ar[min_index]`.

```c++
if (ar[i] < ar[min_index]) {
    min_index = i;
}
return min_index;
```

---

### Bug 3

### Location

`src/sorting.cpp`, lines 36–37 (`copy_array` function)

```c++
int* copy = ar;
return copy;
```

### How the bug was located

The `SimpleCopyWasMade` test failed — the returned pointer was the same as the input pointer. Reading the code confirmed that no allocation was being done at all.

### Description

The function sets `copy` equal to `ar`, which just copies the pointer value. No new memory is allocated and no data is duplicated. The "copy" is simply an alias for the original array, so any modification to it also modifies the original.

### Fix

Allocate a new block of memory with `malloc` and copy each element from the original into it.

```c++
int* copy = (int*)malloc(len * sizeof(int));
for (int i = 0; i < len; ++i) {
    copy[i] = ar[i];
}
return copy;
```
