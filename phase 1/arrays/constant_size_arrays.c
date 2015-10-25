/***************************
 * Name: Tyler Nivin
 *
 * Description: A very basic intoduction to arrays in c. As with most things in this repository, the largest benefit will come from reading this source file and trying to understand what is happening. 
 *
 * Last Modified: Sun Oct 25, 2015  02:22AM
 **************************/
#include <stdlib.h>
#include <stdio.h>

//Here are functions to print the contents of an integer array with the length passed to the function. 
//It's worth your time to look at it and understand what's happening. 
//The implementation for arrays of different primitive data types is very similar, and is suggested as a learning exercise. 
void print_int_array(int array[], int size);

int main(int argc, char* argv[]) {
    //In c, there are (basically) two kinds of arrays that we can use when it comes to handling the size of the array.
    //The two types i'm referring to are constant-size arrays, that is, where the size of the area is known at compile-time and 
    //variable size arrays that will get there size from some input source during run-time. 
    ////First, let's look at a few constant-size arrays. Here are a few examples of constant-size int arrays.

    int x = 30;

    int array1[5];
    int array2[x];
    int array3[5] = {1,2,3,4,5};
    int array4[5] = {1};
    int array5[5] = {0};
    int array6[5] = {3,3,3,3,3};
    

    print_int_array(array1, 5);
    print_int_array(array2, x);
    print_int_array(array3, 5);
    print_int_array(array4, 5);
    print_int_array(array5, 5);
    print_int_array(array6, 5);


    return 0;

    /*	Let's recap what happened when we ran the above code.. 
     *	First, let's talk about the five between the brackets. As you are probably aware, or realized, that is how many elements you want the array to be able to hold.
     *	But what about array 2? It has a variable! 
     *	Well, since C99, one of the C standards, was released, C has had support for variable length arrays. Now, how "variable" this array is is a point of discussion,
     *	however in the proceeding examples we'll read in an array size from the user using scanf, and actually make the array at run-time. Exciting! 
     *	More on that later though. 
     *
     *	There is one other VERY important thing I want to point out before we move on. When you ran the code above, did you randomly see very large numbers? 
     *	Seriously, I don't know if you did; it depends. You see, when you allocate space for an array, the operating system kindly 
     *	hands you (incomplete explanation warning) a way to work with that array. A reference to that array, if you will. This is not much different than if 
     *	you had declared any primitive data type, e.g. int, char, float. JUST LIKE with primitive types, if you don't assign the variable a value and then USE
     *	that variable, still never having given it a value, then you have no way of know what the value of the variable is. Sometimes we get lucky and it happens
     *	to be 0 or some other value that is useful to us, but there is NO guarantee what the values stored in array 1 and array 2 are. 
     *
     *	Now, there is a difference between the first two and the last three arrays, and you can readily see it; We use the syntax above to initialize
     *	arrays 3, 4, and 5 with some value that we want. What did you notice about each of the last three arrays? 
     *
     *	array 3 has size 5, and we gave 5 values to initialize the array with. Therefore, array 3 had only the values we gave it, and it was fully initialized.
     *
     *	array 4 has size 5, but we only gave it one initial value so only the first element was initialized with the value we gave. 
     *	But, there is something I wanted to point out, and that is the fact that the other elements ARE guaranteed to be 0. 
     *
     *	Array 5 we initialize the first element to 0 explicitly, and because of ther behavior we mentioned with array 4, ALL elements will be initialied to 0.
     *
     *	Array 6 is another example of initializing all elements to some number, here 3. We can't shortcut the initialization like we can with array5, for the same reason that
     *	array 4 is not initialized with all 1s. 
     *
     **/
}
void print_int_array(int array[], int size){
    printf("PRINTING INTEGER ARRAY OF LENGTH: %d\n", size);

    int i;
    for (i=0; i<size; i++){
	printf("%d ", array[i]);		
    }
    printf("\n");

    //return here is not STRICTLY needed, because the function is void, but I like to explicitly say when I am done. 
    return;
}
