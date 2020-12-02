"""
dna.py: This program program that identifies a person based on their DNA.
"""
__author__ = "Brice Bartoletti"

if __name__ == "__main__":
    import sys
    import csv
    import re

    # number of args provided
    if len(sys.argv) != 3:
        print("Usage: python ./dna.py path_to_csv path_to_txt")
    # list of args provided
    _, db_path, txt_path, *kwargs = sys.argv

    # Load CSV data in memory then close
    with open(db_path, newline='') as csvFile:
        dnaSeqs, *data = csv.reader(csvFile)
        csvFile.close()

    # Create dictionary where key are DNA Sequence combination and value = name
    dictDnaKeyPeopleValue = {}
    for line in data:
        key = []
        for i, colVal in enumerate(line):
            if i == 0:
                name = colVal
            else:
                key.append(int(colVal))
        key = tuple(key)
        dictDnaKeyPeopleValue[key] = name

    # Load Txt data into memory then close
    with open(txt_path) as txtFile:
        dnaToAnalyse = txtFile.readline()
        txtFile.close()

    # remove the "name" value to only keep the dna sequences
    dnaSeqs.pop(0)
    # Analyse dna
    dnaKey = []
    # for each sequence in the database
    for dnaSeq in dnaSeqs:
        # find all repetition of this sequence
        seqSize = len(dnaSeq)
        continueSequences = re.compile(f"({dnaSeq})+").finditer(dnaToAnalyse)
        dnaKey.append(max([int(len(cs.group())/seqSize) for cs in continueSequences] or [0]))
    # create the key
    dnaKey = tuple(dnaKey)

    # get a result
    print(dictDnaKeyPeopleValue.get(dnaKey) or "No match")
