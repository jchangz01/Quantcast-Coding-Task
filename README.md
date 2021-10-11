# Quantcast Software Engineer Internship Summer 2022 Coding Task (Most Active Cookie)

C++ program that prints the most active cookies given a cookie log file and a specified date

## Building 

To compile most_active_cookie.cpp, run `make`

## Running 
To run, format the command as `./most_active_cookie [file] -d [date]` <br />
**Example 1:** ` ./most_active_cookie cookie_log.csv -d 2018-12-09` <br />
**Output:** <br />
> AtY0laUfhglK3lC7
    
**Example 2:** ` ./most_active_cookie cookie_log.csv -d 2018-12-08` <br />
**Output:** <br />
> fbcn5UAVanZf6UtG <br />
> 4sMM2LxV07bPJzwf <br />
> SAZuXPGUrfbcn5UA <br />

## Cleaning up
To remove all binary files, run `make clean` in the current directory
