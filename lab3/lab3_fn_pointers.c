// Credit: Shudong Hao
// Collaberator: Joseph Vasallo
#include <stdio.h>

// TODO: addone() must accept parameters that include a function pointer,
// the number of elements in the array and the size of each element
// it must NOT accept any parameters directly revealing the data type

void* addInt(const void* elem_ptr){
    int* elem = (int*)elem_ptr;
    *elem_ptr = *elem_ptr + 1;
    
}

void addDouble(){

}

void addChar(){

}

void* addone(void *array_inp, size_t len, size_t elem_sz, void*(*fun)(const void*)){

}

int main() {

    int test1[] = {1,2,3,4,5};
    addone(test1, 5, 8, addInt);
    for (size_t i = 0; i < 5; i ++) printf("%d\n", test1[i]);
        
    double test2[] = {0.3, -0.2, 1.34};
    
    for (size_t i = 0; i < 3; i ++) printf("%lf\n", test2[i]);

    char test3[] = {'3', 'a', 'Z', '?'};
    
    for (size_t i = 0; i < 4; i ++) printf("%c\n", test3[i]);

    return 0;
}
