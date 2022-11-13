
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct monom{
    int coefficient;
    int power;
} Monom;

void printMonom(int coefficient, int power, bool isFirst) {
    if(!isFirst) {
        if(coefficient < 0) {
            printf("-");
            coefficient *= -1;
        }
        else {
            printf("+");
        }
        printf(" %d", coefficient);
        if(power == 1) printf("x ");
        else if(power != 0) printf("x^%d ", power);
    }
    else {
        printf("%dx^%d ", coefficient, power);
    }
}

void printPolynom(Monom * pol, int size) {
    for(int i = 0; i < size; i++) {
        if(i != 0) {
            printMonom(pol[i].coefficient, pol[i].power, false);
        }
        else {
            printMonom(pol[i].coefficient, pol[i].power, true);
        }
    }
}

void swapMonom(Monom *m1, Monom *m2)
{
    Monom temp = *m1;
    *m1 = *m2;
    *m2 = temp;
}

void insertToMonomArrayAndSort(Monom ** polynom, int coefficient, int power, int * size) {
    
    int lastPowerIndex = 0;
    while((lastPowerIndex < *size) && ((*polynom)[lastPowerIndex].power > power)) {
        lastPowerIndex++;
    }
    if((lastPowerIndex >= 0) && (lastPowerIndex != *size) && ((*polynom)[lastPowerIndex].power == power)) {
       (*polynom)[lastPowerIndex].coefficient += coefficient;
    }
    else {
        (*size)++;
        lastPowerIndex = (*size) - 1;
        (*polynom) = (Monom*)realloc((*polynom) ,(*size) * sizeof(Monom));
        
        (*polynom)[lastPowerIndex].coefficient = coefficient;
        (*polynom)[lastPowerIndex].power = power;
    
    
        while((lastPowerIndex > 0) && ((*polynom)[lastPowerIndex].power > (*polynom)[lastPowerIndex-1].power)) {
            swapMonom(&((*polynom)[lastPowerIndex]), &((*polynom)[lastPowerIndex - 1]));
            lastPowerIndex--;
        }   
    }

}

void printPolySum(Monom * polynom1, int polynom1Size, Monom * polynom2, int polynom2Size) {
    int i=0, j=0;
    bool isFirst = true;
    while(polynom1Size > i && polynom2Size > j) {
        if(!(i == 0 && j == 0)) isFirst = false; 
        if(polynom1[i].power == polynom2[j].power) {
            printMonom((polynom1[i].coefficient + polynom2[j].coefficient), polynom1[i].power, isFirst);
            i++;
            j++;
        }
        else if(polynom1[i].power > polynom2[j].power) {
            printMonom(polynom1[i].coefficient, polynom1[i].power, isFirst);
            i++;
        }
        else {
            printMonom(polynom2[j].coefficient, polynom2[j].power, isFirst);
            j++;
        }
    }
    
    while(polynom1Size > i) {
        printMonom(polynom1[i].coefficient, polynom1[i].power, isFirst);
        i++;
    }
    while(polynom2Size > j) {
        printMonom(polynom2[j].coefficient, polynom2[j].power, isFirst);
        j++;
    }
}

void printPolyMul(Monom * polynom1, int polynom1Size, Monom * polynom2, int polynom2Size) {
    Monom * p;
    int size = 0;
    p = (Monom*)malloc(sizeof(Monom*));
    for(int i = 0; i < polynom1Size; i++) {
        for(int j = 0; j < polynom2Size; j++) {
            insertToMonomArrayAndSort
            (&p, polynom1[i].coefficient * polynom2[j].coefficient ,polynom1[i].power + polynom2[j].power, &size);
        }  
    }
    printPolynom(p, size);
    free(p);
}

Monom * getPolynom(unsigned int * size) {
    
    int coefficient;
    int power;
    Monom *polynom;
    polynom = (Monom*)malloc(sizeof(Monom));
    
    bool inputFlag = true;
    *size = 0;
    while(inputFlag) {
        scanf("%d %d", &coefficient, &power);
        if(coefficient != 0) {
            
            insertToMonomArrayAndSort(&polynom, coefficient, power, size);
        }
        if (getchar() == '\n') {
            inputFlag = false;
        }
    }
    
    return polynom;

    
}

int main()
{
    Monom *polynom1, *polynom2;             // The input polynoms
    unsigned int polynom1Size,polynom2Size; // The size of each polynom
     
    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size);   // get polynom 1
     
    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size);   // get polynom 2
    
    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");
     
    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");
     
    free(polynom1); // releasing all memory allocations
    free(polynom2);
}
