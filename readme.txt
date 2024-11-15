This program is designed to input a file from the command line when it's run
and build a database with the data from the input file. It will skip any entry that has a space
in the first or last name field, and skip any line that has a salary <30000 and >150000.
It can read out and count the number of entries it imported. Search for someone based on ID.
Search for someone based on the last name. And, finally, it will add an entry into the db
by prompting the user for the first name, last name, and salary and perform the same data validation
techniques mentioned above. It will then auto assign an ID based on the highest ID number
in the db and increment by 1 from there for each additional entry.

To run this program unzip the package
Open the command line in Windows and cd to the appropriate folder
Then, run "gcc workerDB.c workerfunctions.c readfile.c -o workerDB" without the quotes
Once it's compiled run "workerdb small.txt" without the quotes
