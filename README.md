echo
==============

Simple text processor written in C++ using the decorator design pattern.

The mainline interpreter loop works as follows:
  
  1. You issue a command of the form source-file text-changes. If source-file
     is stdin, then input should be taken from cin.
  2. The program constructs a custom text processor from text-changes and applies
     the text processor to the words in source-file, printing the resulting words, one per line.
  3. You may then issue another command. An end-of-file signal ends the interpreter loop.

List of text-changes:
  1. dropfirst n: Drop the first n characters of each word.
  2. doublewords: Double up all words in the string.
  3. allcaps: All letters in the string are presented in uppercase. Other characters remain
     unchanged.
  4. count c: The first occurrence of the character c in the string is replaced with 1. The
     second is replaced with 2, ... the tenth is replaced with 10, and so on.
