### Main Task
The user enters the name of the folder with text files. The program calculates the frequency dictionary of words, documents found in this folder. The words from the frequency dictionary are saved in a separate file, sorted by frequency. The word frequency is the number of times a word is repeated.

### Additional Tasks
#### Task #1
The task is solve by 1 thread and the solution time is traced.

#### Task #2
The task is solve by 2 independent streams, each has its own half of the files for processing and its own separate frequency dictionary. The streams work independently of each other and at the end of the work the frequency dictionaries are combined. Only then the timer stops.

#### Task #3
The task is solve by 2 independent streams, each has its own half of the files for processing and one common frequency dictionary, access to which is protected by the critical section. Opening hours stop when both threads finish their work.
