import os


def test(file, arg1, arg2, expected_answer):
    answer = os.popen(f"python {file} {arg1} {arg2}").read().strip()
    print(
        "Test succeed" if expected_answer == answer else f"test failed expected: {expected_answer} instead of {answer}")


def test_less_args(args, expected_answer):
    test(args, "", "", expected_answer)


test_less_args("./dna.py databases/small.csv sequences/1.txt", "Bob")
test_less_args("./dna.py databases/small.csv sequences/1.txt", "Bob")
test_less_args("./dna.py databases/small.csv sequences/2.txt", "No match")
test_less_args("./dna.py databases/small.csv sequences/3.txt", "No match")
test_less_args("./dna.py databases/small.csv sequences/4.txt", "Alice")
test_less_args("./dna.py databases/large.csv sequences/5.txt", "Lavender")
test_less_args("./dna.py databases/large.csv sequences/6.txt", "Luna")
test_less_args("./dna.py databases/large.csv sequences/7.txt", "Ron")
test_less_args("./dna.py databases/large.csv sequences/8.txt", "Ginny")
test_less_args("./dna.py databases/large.csv sequences/9.txt", "Draco")
test_less_args("./dna.py databases/large.csv sequences/10.txt", "Albus")
test_less_args("./dna.py databases/large.csv sequences/11.txt", "Hermione")
test_less_args("./dna.py databases/large.csv sequences/12.txt", "Lily")
test_less_args("./dna.py databases/large.csv sequences/13.txt", "No match")
test_less_args("./dna.py databases/large.csv sequences/14.txt", "Severus")
test_less_args("./dna.py databases/large.csv sequences/15.txt", "Sirius")
test_less_args("./dna.py databases/large.csv sequences/16.txt", "No match")
test_less_args("./dna.py databases/large.csv sequences/17.txt", "Harry")
test_less_args("./dna.py databases/large.csv sequences/18.txt", "No match")
test_less_args("./dna.py databases/large.csv sequences/19.txt", "Fred")
test_less_args("./dna.py databases/large.csv sequences/20.txt", "No match")
