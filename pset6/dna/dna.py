"""
dna.py: This program program that identifies a person based on their DNA.
"""
__author__ = "Brice Bartoletti"


# specs:
# args:
#   - arg1 : csv file with str conuts for list of individual
#   - arg2 : txt file with DNA sequence to identify
#   X if incorrect len(arg) print an error message with print
# Open CSV in memory:
#   first row : name, str1, str2
#   next row : name, count1, count2
# Open DNA sequence and read content into memory
# for each STR of first line CSV file:
#   compute the longest run of consecutive repeats of str
# assume one match max
# if match one individual, print the name
# else print "No match"
#

if __name__ == "__main__":
    import sys
    import csv
    # number of args provided
    if len(sys.argv) != 3:
        print("Usage: python ./dna.py path_to_csv path_to_txt")
    # list of args provided
    _, db_path, txt_path, *kwargs = sys.argv

    # open CSV
    with open(db_path, newline='') as csvFile:
        lineReader = csv.reader(csvFile)
        # load CSV into mem
        for csvRow in lineReader:
            print(", ".join(csvRow))


    # close CSV

    # open Txt

    # load Txt into mem

    # scan Txt for strs longest consecutiv count

    # check for match into csv data

    # return match or nothing
