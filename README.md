# String Sorter for the Poem "Eugene Onegin"

A console application written in C that reads a text file (Alexander Pushkin's poem *"Eugene Onegin"*), splits it into individual lines, and performs three types of sorting, saving each result to an HTML file with styled output.

---

## Table of Contents

- [Introduction](#introduction)
- [Key Features](#key-features)
- [Project Structure](#project-structure)
- [Usage](#usage)
- [Algorithm](#algorithm)
- [Notes](#notes)
- [License](#license)

---

## Introduction

This project is a console application written in C, designed to read a text file (Alexander Pushkin's poem "Eugene Onegin"), split it into individual lines, and perform three types of sorting:

1. **Alphabetical sorting** — comparing lines by their first letter (ignoring non-alphabetic characters and case).
2. **Reverse alphabetical sorting** — comparing lines by their last letter (from the end of the line, also ignoring case and non-alphabetic characters).
3. **Memory address sorting** — restoring the original line order by sorting pointers in ascending address order.

The results of each sorting stage are saved to an output file in HTML format with styling elements (headings, horizontal rules, gradient text).

---

## Key Features

- **Flexible file reading**: the text is loaded into a dynamic buffer, after which lines are parsed by the `\n` delimiter.
- **Index array**: pointers to the beginning of each line are used for sorting, avoiding the need to copy the strings themselves.
- **Custom comparators**:
  - `CompareAlpha` — alphabetical comparison from the beginning of the line;
  - `CompareAlphaReverse` — alphabetical comparison from the end of the line;
  - `CompareUpPtr` — comparison of pointers by their numeric addresses.
- **Quick sort**: a custom `QuickSort` function is implemented for the first stage (presumably defined in `header.h`), while the standard `qsort` is used for the remaining stages.
- **Formatted output**: generation of an HTML file with CSS styles for a clear presentation of the results.
- **Error handling**: handling of file opening errors, validation of input/output file formats (`.txt`, `.htm`, `.html`), and error reporting via `errno`.

---

## Project Structure

| Component | Purpose |
|-----------|---------|
| `main()` | Entry point, controls sorting stages and output. |
| `struct FileStat` | Stores all file information: text, pointer array, size, number of lines, file paths. |
| `GetFilenameStd()` | Parses command-line arguments. |
| `CheckFileFormat()` | Validates the file extension. |
| `ReadFile()` | Reads the file into a buffer and fills the indexes. |
| `FillIndexes()` | Counts lines and creates the pointer array. |
| `StringsParser()` | Splits the buffer into lines by replacing delimiters with `\0`. |
| `CountElems()` | Counts occurrences of a character in a string. |
| `PrintStrings()` | Outputs the array of strings to a stream. |
| `PrintBeautyText()` | Generates HTML output with a title and styles. |
| `CompareAlpha()` | Comparator for sorting by the beginning of the line. |
| `CompareAlphaReverse()` | Comparator for sorting by the end of the line. |
| `CompareUpPtr()` | Comparator for sorting pointers by address. |
| `CompareUp()` | Helper function for comparing unsigned numbers. |
| `PrintErrno()` | Prints an error message using `strerror`. |

---

## Usage

The application is launched from the command line with the following arguments:

```bash
>>> ./sort --readfile <input_file> --printfile <output_file>

### Example
>>> ./sort --readfile onegin.txt --printfile result.html
```
You should use only 4 arguments.
## Algorithms
1. Parse command-line arguments and validate file extensions.
2. Read the input file into a dynamic buffer.
3. Split the buffer into lines: each \n character is replaced with \0, and pointers to the beginning of each line are stored in the index array.
4. First stage: sort index using QuickSort and the CompareAlpha comparator.
5. Output the sorted lines to the output file in HTML format with the title "Sorted Onegin".
6. Second stage: sort index using qsort and the CompareAlphaReverse comparator.
7. Output with the title "Reverse-sorted Onegin".
8. Third stage: sort index using qsort and the CompareUpPtr comparator (restoring the original order).
9. Output with the title "Standard Onegin"

## Notes
- All strings in the buffer are separated by the \0 character, allowing them to be treated as ordinary C strings.

- The CompareAlpha and CompareAlphaReverse comparators ignore non-alphabetic characters and convert letters to lowercase.

- CompareUpPtr compares the numeric values of pointers, guaranteeing restoration of the original line order.

- The output is formatted as an HTML document using inline CSS styles.

- Building the project requires including the header.h header file, which presumably defines the ASSERT, BOLR_RED (and another colors), RESET macros and the QuickSort function.
