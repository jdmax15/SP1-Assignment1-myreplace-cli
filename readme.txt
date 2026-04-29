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
4       | File does not exist                  | ./myreplace nofile.txt a A
5       | Single pair, all occurrences         | ./myreplace File.txt [from] [to]
6       | Multiple pairs, all occurrences      | ./myreplace File.txt [from] [to] [from] [to]
7       | Single pair, first occurrence (-f)   | ./myreplace -f File.txt [from] [to]
8       | Multiple pairs, first occurrence(-f) | ./myreplace -f File.txt [from] [to] [from] [to]
9       | Identical from and to                | ./myreplace File.txt a a
10      | Multi-char string replacement        | ./myreplace File.txt [from] [to]

--------------------------------------------------------------------------------
TEST RUN AND OUTPUT
--------------------------------------------------------------------------------

[Paste your actual test run output here, with screenshots or terminal output
for each test case above.]

--------------------------------------------------------------------------------
LIMITATIONS
--------------------------------------------------------------------------------

[Describe any known limitations or cases where your program does not produce
the expected result.]

================================================================================
