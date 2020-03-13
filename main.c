#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned int ns[] = {100,250,500,1000,1500,2500,3500,5000,7000,10000};

// FILL

    void fill_random(int *t, unsigned int n) {
            for (unsigned int i = 0; i < n; i++) {
                t[i] = rand();
            }
        }
    
    void fill_increasing(int *t, unsigned int n) {
            int i;
            for (i = 0; i < n; i++) {
            t[i] = i;
            }
        }
     
    void fill_decreasing(int *t, unsigned int n){
        int j=0;
        for(int i=n; i > 0; i-- ) {   
            t[j]=i;
            j++;}
        }
        
/*    void fill_vshape(int *t, unsigned int n) {
         int i = n/2;
         int licznik = 1;
         int i, x = 1;
         t[i] = 1;
         while(licznik < n)
         {
              if(i - x >= 0)
                   t[i - x] = ++licznik;
              if(i + x < n)
                   t[i + x++] = ++licznik;
         }   
    }    
        
*/        
        
 
// SORT

    //swap to selection and quick sort
    
        void swap(int *first, int *second) { 
                    int temp = *first; 
                    *first = *second; 
                    *second = temp; 
                } 

    //selection sort

        void selection_sort(int *t, unsigned int n) 
        { 
            int i, j, min_idx; 
           
            for (i=0; i< n-1; i++) 
            { 
                min_idx = i; 
                for (j = i+1; j < n; j++) 
                  if (t[j] < t[min_idx]) 
                    min_idx = j; 
                swap(&t[min_idx], &t[i]); 
            } 
        } 

    // insertion sort
 
         void insertion_sort(int *t, unsigned int n) { 
            int i, key, j; 
            for (i = 1; i < n; i++) { 
                key = t[i]; 
                j = i - 1; 
                while (j >= 0 && t[j] > key) { 
                    t[j + 1] = t[j]; 
                    j = j - 1; 
                } 
                t[j + 1] = key; 
            } 
        } 

    // quick sort
    
        int partition(int *t, int low, int high) {
            int j;
            int pivot = t[high];
            int i = (low - 1); 
            for (j = low; j <= high- 1; j++) {  
                if (t[j] <= pivot) { 
                    i++;    
                    swap(&t[i], &t[j]); 
                } 
            } 
            swap(&t[i + 1], &t[high]); 
            return (i + 1); 
        } 
        
        int random_partition(int *t, int low, int high) {
        	int pivot = low + rand()%high;
        	swap(&t[pivot], &t[high]);
        	return partition(t, low, high);
        }
        
        
        void quick(int *t, int low, int high) { 
            if (low < high) { 
                int pi = partition(t, low, high); 
                quick(t, low, pi - 1); 
                quick(t, pi + 1, high); 
            } 
        } 
        
        void quick_sort(int *t, unsigned int n) {
        	quick(t, 0, n-1);
        }
 
    // heap sort
    
  /*      int heap_sort(int *t, unsigned int n) {
            int t[n + 1],i,j,k,m,x;
            for(i = 2; i <= n; i++) {
                j = i; k = j / 2;
                x = t[i];
                while((k > 0) && (t[k] < x)) {
                    t[j] = t[k];
                    j = k; k = j / 2;
                }
                t[j] = x;
            }
                                
        }
 
         for(i = N; i > 1; i--) {
            swap(t[1], t[i]);
            j = 1; k = 2;
            while(k < i) {
                if((k + 1 < i) && (t[k + 1] > t[k]))
                    m = k + 1;
                    else
                    m = k;
                if(t[m] <= t[j]) break;
              swap(t[j], t[m]);
              j = m; k = j + j;
            }
          }
 
 
 */
 
 
void is_random(int *t, unsigned int n) {
    return;
}
 
void is_increasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}
 
void is_decreasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}
 
void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;
 
    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}
 
void is_sorted(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

//


 
void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, /*fill_vshape*/};
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, /*heap_sort*/};
 
char *fill_names[] = { "Random", "Increasing", "Decreasing", "V_shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };
 
int main() {
	FILE *fp=fopen("dane.txt", "w");
    int i,j,k;
    for (i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions) ; i++) {
    void(*sort)(int *, unsigned int) = sort_functions[i];
 
        for (j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];
 
	            for (k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
	            	
	                unsigned int n = ns[k];
	                int *t = malloc(n * sizeof(*t));
	 				
	                fill(t, n);
	                check(t, n);
	                clock_t begin = clock();
	                sort(t, n);
	                clock_t end = clock();
	                is_sorted(t, n);
	                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
	                fprintf(fp, "%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
	       
	                free(t);
	            }
        }
   }

   fclose(fp);
    return 0;
}