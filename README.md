UNT Sustainability Text Parsing Project
=======================================

Text parsing project for the UNT Sustainability department. This program is used for formatting the data from 
the Texas Industry Employer Contact Information website. All of the data on this website is formatted using 
low quality HTML and is nearly impossible to use and search through. The program format.c takes chunks of this 
database one at a time and formats them for importing into Microsoft Excel. This project reduces a year's worth 
of manual copying down to a few hours worth of running the program.

format.c first strips out the unnecessary tabs and [ Yahoo! Maps ] block, and prints each piece of data onto
a separate line. Following this, it takes the separated data and loads in one business at a time. It will then 
see which data the business has and does not have, printing every business on a separate line with semicolons
separating each data piece for importing directly into Excel.
