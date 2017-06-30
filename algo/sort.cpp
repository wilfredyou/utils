template<typename T> 
void swap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}

template<typename T> 
void bubble_sort(T list[], int length) {

    int N = length - 1;
    bool sorted;

    for (int i = 0; i < N; i++) {
        sorted= true;
        
        for (int j = 0; j < N - i; j++) {
            if (list[j] > list[j + 1]) {
                swap(list[j], list[j+1]);
                sorted= false;
            }
        }

        if(sorted) break;
    }
}
