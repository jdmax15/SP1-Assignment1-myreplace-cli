================================================================================
COMP2019 - Systems Programming 1
Assignment 1 - myreplace
================================================================================

Name:           Joel Maxwell
Student ID:     22173818

--------------------------------------------------------------------------------
PSEUDO-CODE
--------------------------------------------------------------------------------

- Check Args:

	If no args provided:
		print error and exit.
	
	Check for a '-f' as the 2nd argument (argv[1]):
		If present, remember it was used.

	If '-f' was used:
		Store the filename from the 3rd arg used.
		Note that pairs will start from 4th arg used.
	Else:
		Store the filename from 2nd arg used.
		Note that pairs will start from the 3rd arg used.

	If there are an odd number of args remaining after pair start position:
		print error and exit.

	For each pair of args:
		Store the first arg as 'from' in a Pair struct.
		Store the 2nd arg as 'to' in the Pair struct.
		Set the replace flag to 0. 
		Keep count the amount of pairs structs created.

- Open File:

	Open the filename provided as read/write, print error and quit if failure.

- Read and Replace:

	While there are up to 1024 bytes to read into a buffer:
		For every byte in the buffer:
			For every pair struct:
				Check the chars the from the 'from' field, to the same amount of chars at the
				current position ahead in the buffer.
				If they are the same:
					If the '-f' arg was used and it has been replaced all ready:
						Skip replacement.
					Else:
						If the 'from' and 'to' are different:
							Overwrite the 'to' chars at the current buffer position.
							Set the current pair struct 'replace' flag to 1.
					Advance the buffer pointer forward the amount of chars it replaced - 1.

		Seek back to the start of the buffer.
		Write the modified buffer back into the file.
		Display the contents of the buffer to STDOUT.
		
	Repeat until end of file.

- Report if changed:
	If any pair 'replace' flag was set to 1:
		Print "File was modified."
	Else:
		Print "File was not modified."

- Close File:

	Close the file.
		

	
--------------------------------------------------------------------------------
TEST PLAN
--------------------------------------------------------------------------------

Test No | Description                          | Command
--------|--------------------------------------|----------------------------------------
1       | No arguments                         | ./myreplace
2       | Missing from/to pairs                | ./myreplace File.txt
3       | Odd number of from/to args           | ./myreplace File.txt a
4       | File does not exist                  | ./myreplace file_.txt a A
5       | Single pair, all occurrences         | ./myreplace File.txt jumps JUMPS
6       | Multiple pairs, all occurrences      | ./myreplace File.txt jumps JUMPS lazy LAZY dog DOG
7		| Same from and to					   | ./myreplace File.txt dog dog
8       | Single pair, first occurrence (-f)   | ./myreplace -f File.txt jumps JUMPS
9       | Multiple pairs, first occurrence(-f) | ./myreplace -f File.txt fox FOX dog DOG
10      | Multi-char string replacement        | ./myreplace File.txt jumps RAN

--------------------------------------------------------------------------------
TEST RUN AND OUTPUT
--------------------------------------------------------------------------------

1.
./myreplace
Usage: "myreplace [-f] filename from to [from to] ..." 

2.
./myreplace File.txt
Usage: "myreplace [-f] filename from to [from to] ..." 

3.
./myreplace File.txt a
ERROR: Enter "from" and "to" as pairs. Odd number detected.

4.
./myreplace file_.txt a A

ERROR: Could not open file_.txt

5.
./myreplace File.txt jumps JUMPS
The quick brown fox JUMPS over the lazy dog
The quick brown fox JUMPS over the lazy dog
The quick brown fox JUMPS over the lazy dog

File was modified.

6.
./myreplace File.txt jumps JUMPS lazy LAZY dog DOG
The quick brown fox JUMPS over the LAZY DOG
The quick brown fox JUMPS over the LAZY DOG
The quick brown fox JUMPS over the LAZY DOG

File was modified.

7.
./myreplace File.txt jumps jumps
The quick brown fox jumps over the lazy dog
The quick brown fox jumps over the lazy dog
The quick brown fox jumps over the lazy dog

File was not modified.

8.
./myreplace -f File.txt jumps JUMPS
The quick brown fox JUMPS over the lazy dog
The quick brown fox jumps over the lazy dog
The quick brown fox jumps over the lazy dog

File was modified.

9.
./myreplace -f File.txt fox FOX dog DOG
The quick brown FOX jumps over the lazy DOG
The quick brown fox jumps over the lazy dog
The quick brown fox jumps over the lazy dog

File was modified.

10.
./myreplace File.txt jumps RAN
The quick brown fox RANps over the lazy dog
The quick brown fox RANps over the lazy dog
The quick brown fox RANps over the lazy dog

File was modified.

--------------------------------------------------------------------------------
LIMITATIONS
--------------------------------------------------------------------------------

The program can handle everything except the multi-char string replacement.

I would need to shift the bytes when 'from' and 'to' are of different lengths. The buffer would
need to be truncated if 'to' < 'from' and the 'buffer' would need to be expanded if 'to' > 'from'.
When reading through the file two different points of the original buffer would need to be 
maintained, as the current point of writing would start to differ once changes are made.

The entire file could also be read into memory, the amount of changes to the filesize could be
tracked, then a new buffer of that new size could be written to, before writing the whole buffer
back to the new file.


================================================================================
