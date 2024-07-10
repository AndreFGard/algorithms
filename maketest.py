import random
import sys 
global test_filename
test_filename = ((sys.argv[2] + "/") if len(sys.argv) >= 2 else "") + ("test_int")

def randomints():
    f = open("test_int", "w")
    a = [n*13 for n in range(0, 500000 )]
    random.shuffle(a)
    f.write(f"{len(a)}\n")
    f.write(" ".join(map(str, a)) )
    f.write("\n")
    f.write("2\n3 40\n")
    f.close()

    a.sort()

def list_to_str(l: list): 
    return " ".join(map(str, l))

def write_test(a, file):
    file.write(str(a) + "\n")



def discounts():
    n = 9*10**4 - 1000
    precos = [random.randint(0,10**7) for i in range(n)]
    n_cups = n -1
    cups = [i for i in range(n-1)]

    random.shuffle(precos)
    precos = list_to_str(precos)
    cups = list_to_str(cups)

    f = open(test_filename, "w")
    for i in [len(precos), precos, len(cups) -1, cups]:
        write_test(i, f)

def generate(max_letra, n_geradas,size):
    return [[(max_letra-j)//(i+1) for i in range(0,size)] for j in range(n_geradas)]
def hash_it():
    n_geradas = 30
    max_letra = 120
    letras = list(range(1,max_letra))
    geradas = generate(max_letra,n_geradas,4) + generate(max_letra,n_geradas,5) + generate(max_letra,n_geradas,6)
    geradas_strs = list(filter(lambda x: ' ' not in x and x.strip() == x, ["".join(list(map(chr, i))) for i in geradas]))
    print("\n".join(geradas_strs))

def random_string(size=4):
    letters = [i for i in ('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'*10 + 8*"e")] 
    #letters might be repeated. e has a high frequency because that _might_ increase collisions
    import random
    random.shuffle(letters)
    return "".join(letters[:size])

def make_hashit_tests(cases=3, n_operations=3, words_min_size=1, words_max_size=6) ->list[list[str]]:
    tests = []

    import random
    possible_lengths = list(range(words_min_size,words_max_size+1))
    random.shuffle(possible_lengths)

    operations = ["ADD:"] #removeed "DEL:"

    for i in range(cases):
        words = [random_string(random.choice(possible_lengths)) for i in range(n_operations)]
        operations = [random.choice(operations) for i in range(n_operations)]

        testcase = [f"{cases}\n{n_operations}"] + [(operations[i % len(operations)]) + words[i]
                                                    for i in range(n_operations)]
        #testcase = "\n".join(testcase)
        tests.append(testcase)

    return tests

def test_hashit(test, correct, cases=3, n_operations=3, words_min_size=1, words_max_size=6, get_tests=make_hashit_tests):
    import subprocess
    testcases = get_tests(cases=3, n_operations=3, words_min_size=1, words_max_size=6)

    out_test = []
    out_correct = []
    
    inp = ""
    inp_log = []
    for case in testcases:
        inp +=  "\n".join(case)
        inp_log.append("\n".join(case) + "\n#########################\n#########################\n")

    out_test.append(subprocess.check_output(test, text=True, input=inp))
    out_correct.append(subprocess.check_output(correct, text=True, input=inp))
    

    for fname, outlist in zip(["test_out.txt", "correct_out.txt"], [out_test, out_correct]):
        with open(fname, 'w') as f:

            [f.write(out + "\n#########################\n#########################\n") for out in outlist]
    
    with open("input_cases.txt", 'w') as f:
        f.write('\n'.join(inp_log))
        f.write(inp)

import sys
#test_hashit("./a", "./gab",cases=3, n_operations=3, words_min_size=1, words_max_size=6)



def test_Contest_Rankings_basic(cases=100, teams = 102, z_teams=6):
    ADDER_STRING = ""
    print(cases)
    for _ in range(cases):
        print(teams)
        z_teams = 6
        names =["Ahmad"]
        for i in range(1, (teams -z_teams+1)):
            names.extend( [f"a" +f"{i}".zfill(2) + ADDER_STRING] + [f"b" +f"{i}".zfill(2) +  ADDER_STRING] + [f"b" +f"{i}".zfill(2) +  ADDER_STRING])
        
        for i in range((teams+1- z_teams), (teams+1)):
            names.extend( [f"zzzz" +f"{i}".zfill(2) + ADDER_STRING] + [f"zzz" +f"{i}".zfill(2) +  ADDER_STRING] + [f"zz" +f"{i}".zfill(2) +  ADDER_STRING])
            #names.sort()
        
        #print(len(names))
        
        ss = ""
        histo=[]
        for i in range(0,3*(teams),3):
            ss = " ".join(names[i:i+3])
            print(ss)
            histo.extend(names[i:i+3])

    #print(len(set(histo)))

test_Contest_Rankings_basic()