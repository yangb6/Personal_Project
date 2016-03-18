HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME:  < Bing Yang >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
First, I asked my classmates Yushi Xiao and Zhuoyi Li for some problem about homework_9.
Second, in the class, classmates who sit near me  give me some helpful suggestions and help me to solve some problems about the homework_9. 
Third, I used the google to search some information.
Finally, I also use the website cplusplus.com for some information.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 hours >


ALGORITHM ANALYSIS: 
Assume v_0 vertices, e_0 edges, and t_0 triangles in the initial mesh,
reduced to t_final triangles using the -shortest criteria.  What is
the overall order notation for the program?  Analyze the separate
compoenents of the program to justify your answer.

ALGORITHM ANALYSIS -- LINEAR:
Collapse times: In order to get t_final triangles, the worst situation(all edges are on the boundary),we need to do (t_0-t_final) times.

FindEdge Function: we have to traversal the edges map, so the worst situation is O(e_0).

Traversal the triangle about b(Assume that k to be the number of edges connected to a vertex.): So the order notation is O(k).

Triangle Hasvertex Function: O(1).

RemoveEdge Function: 
1.Find the edge: O(log(e_0))
2.Priority Queue Remove Function:O(log(e_0)).
3.Vertex RemoveEdge Funtion: O(log(k))
So the total order notation is O(log(k*e_0^2))

CollectEdgesWithVertex Function:O(k)

RemoveTriangle Function:
1.Vertex RemoveTriangle Function:O(log(k))
So total order notation is O(log(k*t_0))

ReCalculateEdges Function:O(k).

So one time collapse:  order notation is O(e_0+k*((log(k*e_0^2))+k+log(k*t_0)))

Finally, the total order notation is O((t_0-t_final)*(e_0+k*((log(k*e_0^2))+k+log(k*t_0))))



ALGORITHM ANALYSIS -- PRIORITY QUEUE:
The difference between PRIORITY QUEUE and LINER function is on the FindEdge Function.
The PRIORITY QUEUE would use constant time to find the next edge, so the whole order notation:
O((t_0-t_final)*(k*((log(k*e_0^2))+k+log(k*t_0))))

So the time between them should be (t_0-t_final)*(e_0).
If we have to collapse a lot of times and the picture is huge which has a lot of edges, it would significantly affect the performance of the program.

！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
Picture: Sunflowers.ppm |  default | preserve_area| target:100 | target:50 | target:25|
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
Linear			 | 0.328s   | 0.437s       | 0.337s     | 0.345s    |  0.369s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
PRIORITY QUEUE		 | 0.327s   | 0.374s	    | 0.332s     |  0.342    |  0.355s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-

！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
Picture: deer.ppm      |  default | preserve_area| target:100 | target:50 | target:25
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
Linear			 | 0.174s   | 0.185s       | 0.337s     | 0.210s    |  0.349s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
PRIORITY QUEUE		 | 0.174s   | 0.215s	    | 0.205s     |  0.185s    |  0.191s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-

！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
Picture: cats.ppm       |  default | preserve_area| target:100 | target:50 | target:25
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
Linear			 | 0.347s   | 0.379s       | 0.399s     | 0.490s    |  0.576s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-
PRIORITY QUEUE		 | 0.324s   | 0.367s	    | 0.400s     |  0.422s    |  0.439s  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！-

From the table before, we can see that, the more times collapse, the Performance of the PRIORITY QUEUE would be better. So it can improve the performance successfully.





EXTRA CREDIT:  COLOR & OVERALL APPERANCE
Discuss the quality of your results in your README.txt and include
screenshots of your more impressive results.  If you have submitted
screenshots, give the file names and describe the results.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






