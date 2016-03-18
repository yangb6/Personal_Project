HOMEWORK 7: MINIBLAST


NAME:  < BingYang >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

First, I asked my classmates Yushi Xiao and Zhuoyi Li for some problem about homework_7.
Second, I used the google to search some information about the conversion between cahr* and string.
Finally, I also use the website cplusplus.com for some information.


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 4 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?
The memory for data structure depend on the number of the k_mer. In my code, I set k_mer(string type) as key and a vector as the value. The worse situation is that there is no duplicate k_mer. The total number of positions store in the different vector wouldn¡¯t be affected by the duplicate k_mer.So the total memory of the map would be O(L-K).

What is the order notation for performance (running time) of each of
the commands?
Reading the genome:
a.Traversal the the genome sequence, the order notation is O(L-k).
b.Add the k_mer to the map, it would run (L-k) times, and each time would take log(n) to add the new k_mer to the map and take p to add the position, so the total time should be £¨log1+log2+log3+¡­.logn£©* p = log(n!)*p, and the worse situation is that there is no duplicate k_mer, so n = L-K.
c. So the total order notation is O((L-K)+log(N!)*p).->O(log((L-K)!)*p)

Comparing each query: 
For each position, it would take O(q) to compare the query and genome sequence. It take logn to find the seed in the map. so the total order notation is O(p*q*logn),where n is the number of the keys.




EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

In my extra credit part, I use a vector to store the k_mer and the other two-dimensional vector to store the position. So every time when we want to find a k_mer in the vector, it would take O(N),where N is the number of the k_mer.

So for reading the genome:
The order notation is O((L-K)^2*p).
For comparing each query:
The order notation is O(p*q*N),where N is the number of the keys.

The new command should be added in the input file,take the input_small.txt for exams
le, the command should be "new_method¡±, the position is before the ¡°quit¡± and last query line,just like this:

genome genome_small.txt
kmer 10
query 2 TATTACTGCCATTTTGCAGATAAGAAATCAGAAGCTC
query 2 TTGACCTTTGGTTAACCCCTCCCTTGAAGGTGAAGCTTGTAAA
query 2 AAACACACTGTTTCTAATTCAGGAGGTCTGAGAAGGGA
query 2 TCTTGTACTTATTCTCCAATTCAGTCACAGGCCTTGTGGGCTACCCTTCA
query 5 TTTTTTTTTTTTTTTCTTTTTT
new_method
quit


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


