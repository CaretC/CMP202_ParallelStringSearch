CMP 202 Coursework - Parallel String Search
===========================================
> | Disclaimer: | This is the coursework that was sumitted for an assessment, feel free to be inspired or get in touch with me about the code base. Please do not plaigarise as you'll likely get caught which is not a good look for anyone. |
> |-------------|:--------------------|

```
Author - Joseph Lee
Student Number - 1903399
Date - 10/05/2021
```
> If you have any questions about this project then [contact me](mailto:1903399@uad.ac.uk?subject=[Github]%20-%20Parallel%20String%20Search%20Contact) and I would be happy to answer any queries. 

Summary
-------
This program uses the Boyer-Moore-Horspool algorithm to search for a list of string patterns in a search text. 

Notes On Directories
--------------------
There are 3 required directories within the application directory. These are:
* `PatternLists` - This should contain the search pattern list .txt file.
* `SearchTextx` - This should contain the seach text .txt file.
* `Results` - This directory is used to store the .csv timing results.

Notes On Compilation
--------------------
This application takes advantage of the std::barrier avaliable in C++20. This requires the solution C++ Language Standard to be set use the **Preview - Features from the Latest CPP Working Draft.**. Shown below. This is accessed by right-clicking the colution and navigating to the drop down in C/C++ => Language => C++ Language Standard.

![Required C++ Standard](ReadmeImgs/RequiredCppLanguage.png)

