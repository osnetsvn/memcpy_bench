/*
 * Author: Roja Eswaran <reswara1@binghamton.edu>
 * Purpose: Microbenchmark to measure the memcpy overhead
 */


#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include <string.h>

void *mem_1,*mem_2;


/*
 * Function: num_repeats
 * Purpose: To avoid any cold penalty and ensure accuracy, this function runs for over a second for the given working set and returns the total iteration(let's say X). 
 */


long num_repeats(long s){
        long rep=10;
        long go_on=1;
        struct timeval st,et;
        while(go_on){
                gettimeofday(&st,NULL);
                for (long i = 0; i < rep; i++) { // I omit warm-ups.
                        memcpy(mem_2, mem_1, s); // Read-write. Write only can be done by memset. 
                }
                gettimeofday(&et,NULL);
                double total_elapsed_seconds=(et.tv_sec - st.tv_sec) + ((et.tv_usec - st.tv_usec)*0.000001);
                if(total_elapsed_seconds>=1)
                        return rep;
                else
                        rep=rep*2;
        }
}


/*
 *Function: read_write_memcpy 
 *
 *Purpose: The cache is warmed up by performing memcpy for X/10 iterations and then the final Memcpy is performed X times.  (Unit:ms)
 */

void read_write_memcpy(long total_size){
                long n = num_repeats(total_size); // num_repeats depends on "s
                long warmup = n/10;
                void *mem_1,*mem_2;     
                struct timeval st,et;
                double total_elapsed_time;
                double average_time;
                mem_1 = malloc(total_size); // or you can use malloc() and run the application with "numactl"
                mem_2 = malloc(total_size);
//                printf("warmup:%ld iterations:%ld\n",warmup, n);
                if(mem_1!=NULL && mem_2!=NULL){
                         for (long iteration = 0; iteration < warmup; iteration++) { // Warmup Phase
                                 memcpy(mem_2, mem_1, total_size);
                         }


                         gettimeofday(&st, NULL);
                         for(long iteration = 0;iteration < n; iteration++){ // Final Phase
                                 memcpy(mem_2, mem_1, total_size);
                         }
                         gettimeofday(&et, NULL);

                         total_elapsed_time = ((et.tv_sec - st.tv_sec)*1000000) + ((et.tv_usec - st.tv_usec));
                     //    printf("Total time:%lf N:%ld\n",total_elapsed_time, n);
                      
       	                 average_time = (total_elapsed_time / (double)n) * 0.001;
                         printf("%lf\t", average_time);
                         
                         free(mem_1);
                         free(mem_2);
                }
                else{
                        printf("Cannot alloc\n");
                        exit(0);
                }
}

int main(int argc, char*argv[]) {
        int thread_count;
        long total_size;
        long total_rep;
        if(argc!= 2){
                printf("Two arguments required\n");
                exit(1);
        }
        else{
                total_size=atoi(argv[1]);
		total_size = total_size * (1024*1024); 
//		printf("total_size:%ld\n",total_size);
                mem_1 = malloc(total_size); // or you can use malloc() and run the application with "numactl"
                mem_2 = malloc(total_size);
                if(mem_1!=NULL && mem_2!=NULL){
                        read_write_memcpy(total_size);
                        free(mem_1);
                        free(mem_2);

                }

                else{
                        printf("Cannot allocate memory\n");
                        exit(0);
                }
        }
        return 0;
}
