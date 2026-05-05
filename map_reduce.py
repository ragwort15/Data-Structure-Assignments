import os
from collections import defaultdict

def get_filename(word):
    c = word[0].lower()
    
    if 'a' <= c <= 'e':
        return "a-e.txt"
    elif 'f' <= c <= 'j':
        return "f-j.txt"
    elif 'k' <= c <= 'o':
        return "k-o.txt"
    elif 'p' <= c <= 't':
        return "p-t.txt"
    else:
        return "u-z.txt"


def map_function(input_files):
    word_count = defaultdict(int)

    for file in input_files:
        if not os.path.exists(file):
            print(f"File not found: {file}")
            continue
        
        with open(file, 'r') as f:
            for line in f:
                words = line.strip().split()
                for word in words:
                    word = word.lower()
                    # check if first insertion starts from 0
                    word_count[word] += 1

    
    file_handles = {}

    for word, count in word_count.items():
        filename = get_filename(word)

       
        if filename not in file_handles:
            file_handles[filename] = open(filename, 'w')

        # word,frequency
        file_handles[filename].write(f"{word} {count}\n")

    
    for f in file_handles.values():
        f.close()


def reduce_function(input_files, output_file="final_output.txt"):
    final_count = defaultdict(int)

   
    for file in input_files:
        if not os.path.exists(file):
            continue

        with open(file, 'r') as f:
            for line in f:
                # split with coma
                parts = line.strip().split()
                if len(parts) != 2:
                    continue
                
                word, count = parts
                final_count[word] += int(count)

    
    with open(output_file, 'w') as out:
        for word, count in sorted(final_count.items()):
            # word,frequency
            out.write(f"{word} {count}\n")        