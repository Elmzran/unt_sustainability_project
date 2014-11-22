UNT Sustainability Text Parsing Project
=======================================

Text parsing project for the UNT Sustainability department. This project consists of two programs, which work
together for formatting the data from the Texas Industry Employer Contact Information website. All of the data
on this website is formatted using low quality HTML and is nearly impossible to use and search through. The two
programs, strip.c and format.c, work together to take chunks of this database one at a time and format them for
importing into Microsoft Excel. This project reduces a year's worth of manual copying down to a few hours worth
of running the program.

strip.c first takes the data and strips out unnecessary tabs and the [ Yahoo! Maps ] block. All data will then be
on separate lines.

format.c takes the separated data and loads in one business at a time. It willl then see which data the business has
and does not have, and format all of it into a file using delineators on each line for importing directly into Excel.
