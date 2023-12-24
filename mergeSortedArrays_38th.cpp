#include <iostream>

/*
                    Q. merge sorted arrays w/o extra space

                explanation -  we will be given 2 sorted arrays
                            arr1[] = {1, 3, 5, 7},      arr2[] = {0, 2, 6, 8, 9}

                            our desired o/p -  {0, 1, 2, 3, 5, 6, 7, 8, 9},     w/o using any extra space
                                                in order to do this firstly we have to arrange arr1[] & arr2[] and then merge it

                            in other words we have to - arr1[] = {0, 1, 2, 3},      arr2[] = {5, 6, 7, 8, 9}
                                    then merge it -  {0, 1, 2, 3, 5, 6, 7, 8, 9}

                    Brute force -  we will create a 3rd array 'arr3[]', we will also be 2 pointers in arr1[] & arr2[] to iterate
                                    through elements and feed into arr3[] in sorted order

                                    arr1[] = {1, 3, 5, 7}       arr2[] = {0, 2, 6, 8, 9}
                                    by iterating through arr1 and arr2 we will feed in arr3
                                            arr3[] = {0, 1, 2, 3, 5, 6, 7, 8, 9}

                                    there are 4 indexes in arr1 and 5 indexes in arr2, so we will feed 4 indexes in arr1 from arr3
                                    and feed nxt 5 indexes in arr2 from arr3
                                            in order to do that we put '0'th index of arr3 in '0'th index of arr1,  till '3'rd index
                                            to put elements in arr2 what we do is - index of arr3 'minus' length of arr1
                                            i.e,  4 - 4 = 0
                                                        4th index of arr3 - length of arr1 = '0'th index of arr2
                                            similarly               5 - 4 = 1
                                                                    6 - 4 = 2
                                                                    7 - 4 = 3
                                                                    8 - 4 = 4
                                                                    9 - 4 = 5

        Actual code
void merge(long long arr1[], long long arr2[], int n, int m)        // n = size of arr1, m = size of arr2
{
    long long arr3[n + m];
    int left = 0;                           // pointer which will point to '0'
    int right = 0;                          // pointer which will point to '0' again
    int index = 0;

    while(left < n && right < m)            // we will move until we have elements in first and second array
    {
        if(arr1[left] <= arr2[right])
        {
            arr3[index] = arr1[left];       // we are comparing elements of arr1 & arr2 (which is smaller) and
            left++, index++;                // and putting the smaller one in arr3
        }
        else
        {
            arr3[index] = arr2[right];      // we are comparing elements of arr1 & arr2 (which is smaller) and
            right++, index++;               // and putting the smaller one in arr3
        }
    }

    while(left < n)                         // if arr1 has still lest element
    {
        arr3[index++] = arr1[left++];
    }

    while(right < m)                        // if arr2 has still lest element
    {
        arr3[index++] = arr2[right++];
    }

    for(int i = 0; i < n + m; i++)          
    {
        if(i < n)
            arr1[i] = arr3[i];
        else
            arr2[i - n] = arr3[i];
    }
}

            TC - O(N + M) + O(N + M)        // putting from arr1 & arr2 in arr3  +  putting in arr1 & arr2 from arr3
            SC - O(N + M)


                1. Optimal sol -  we will take last element of arr1 (i.e, 7) & first element of arr2 (i.e, 0), by comparing
                                them we get that 7 is bigger than 0 so we interchange it. 0 goes to arr1 and 7 to arr2

                               then moving to element 5 of arr1 & 2 of arr2, by comparing them we get that 5 is bigger 
                                than 2 so we interchange them, 2 to arr1 and 5 to arr2

                               then moving to element 3 of arr1 & 6 of arr2, by comparing them we get 6 is already bigger 
                                than 3, so we leave them be

                               and rest of the elements are in their respective place in arr1 & arr2
                                after that we got -  arr1[] = {1, 3, 2, 0}      arr2[] = {7, 5, 6, 8, 9}
                                we have to sort them  arr1[] = {0, 1, 2, 3}     arr2[] = {5, 6, 7, 8, 9}

        Actual code
void merge(long long arr1[], long long arr2[], int n, int m)
{
    int left = n - 1;                           // left pointer is the last place
    int right = 0;                              // right pointer is at the first place

    while(left >= 0 && right < m)               // we wil move till left pointer is greater than equal to 0 and right pointer is less than m
    {
        if(arr1[left] > arr2[right])
        {
            swap(arr1[left], arr2[right]);
            left--, right++;                    // after swaping pointers are moving backward and forward
        }
        else
        {
            break;
        }
    }
    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);
}

            TC - O(min(n, m)) + O(n logn) + O(m logm)           // we moving minimum of n or m (which array length is less)
                                                                // + to sort arr1 + to sort arr2
            SC - O(1)                                       // we are not using anything extra


                2. Optimal sol -  we will be using 'gap' method
                                    'gap' method comes from shell sorting method

                                for that we will take length of arr1 and arr2, which is n = 4 & m = 5
                                    take the ceiling value of the average of those two  ->  (n + m)/2
                                                                                         =  (4 + 5)/2
                                                                                         =   4.5
                                                                        ceiling value    =   5
                                            we will take gap as '5'

                                            arr1[] = {1, 3, 5, 7}       arr2[] = {0, 2, 6, 8, 9}
                                    we take first pointer at '0'th index and 2nd pointer will at the 'gap' distance
                                    means 1st pointer(left) will be at element 1 and 2nd pointer(right) will be at element 2
                                    by comparing both '1' and '2', 1 should stay on the arr1 and 2 should stay on the arr2
                                then move both the pointers in forward direction to 3 & 6, by comparing both , 3 should stay
                                on the arr1 and 6 should atay on arr2
                                and similarly.. (5 & 6), (7, 8)
                                when left pointers moves to '0' (in arr2), the right pointer moves outside the arr2

                                                arr1[] = {1, 3, 5, 7}       arr2[] = {0, 2, 6, 8, 9}

                                after this, we again apply the 'gap' method in 5 -  5/2
                                                                                 =  2.5
                                                                   ceiling value =  3

                                the left pointer will be at element '1' and right pointer will be at element '7', by comparing
                                both of them should stay on their places
                                then move both the pointers fwd 3 & 0 , by comparing them we will interchange their places - 0 & 3
                                then move both the pointers fwd 5 & 2 , by comparing them we will interchange their places - 2 & 5
                                then move both the pointers fwd 7 & 6 , by comparing them we will interchange their places - 6 & 7
                                then move both the pointers fwd 3 & 8 , by comparing them both of them stay in their places
                                then move both the pointers fwd 5 & 9 , by comparing them both of them stay in their places
                                then move both the pointers fwd, left will be at 6 and right willgo to the end of arr2 

                                                arr1[] = {1, 0, 2, 7}       arr2[] = {3, 5, 6, 8, 9}

                                again applying 'gap' method = 3/2
                                                            = 1.5
                                                ceiling value = 2

                                the left will be at 1 and right will be at 2, by comparing they both stays at their place
                                then move both the pointers fwd 0 & 7 , by comparing them both of them stay in their places
                                then move both the pointers fwd 2 & 3 , by comparing them both of them stay in their places
                                then move both the pointers fwd 7 & 5 , by comparing them we interchange their places - 5 & 7
                                then move both the pointers fwd 3 & 6 , by comparing them both of them stay in their places
                                then move both the pointers fwd 7 & 8 , by comparing them both of them stay in their places
                                then move both the pointers fwd 6 & 9 , by comparing them both of them stay in their places

                                                arr1[] = {1, 0, 2, 5}       arr2[] = {3, 7, 6, 8, 9}

                                        again applying 'gap' method = 2/2
                                                                    = 1

                                then move both the pointers fwd 1 & 0 , by comparing them both interchange their places - 0 & 1
                                then move both the pointers fwd 1 & 2 , by comparing them both of them stay in their places
                                then move both the pointers fwd 2 & 5 , by comparing them both of them stay in their places
                                then move both the pointers fwd 5 & 3 , by comparing them both interchange their places - 3 & 5
                                then move both the pointers fwd 5 & 7 , by comparing them both stays in their places - 5 & 7
                                then move both the pointers fwd 7 & 6 , by comparing them both interchange their places - 6 & 7
                                then move both the pointers fwd 7 & 8 , by comparing them both stay in their places - 7 & 8
                                then move both the pointers fwd 8 & 9 , by comparing them both stay in their places - 8 & 9

                                                arr1[] = {0, 1, 2, 3}       arr2[] = {5, 6, 7, 8, 9}

                                        we can stop the iteration after iterating once with the gap value of 1

        Actual code
private:
void swapIfGreater(long long arr1[], long long arr2[], int ind1, int ind2)
{
    if(arr1[ind1] > arr2[ind2])
    {
        swap(arr[ind1], arr2[ind2]);
    }
}

public:
void merge(long long arr1[], long long arr2[], int n, int m)
{
    int len = (n + m);
    int gap = (len/2) + (len % 2);                      // exa -  gap = (9/2) + (9 % 2) => 4 + 1 => 5

    while(gap > 0)                                  // O(log 2 (n+m))  -> log base 2 of (n+m)
    {
        int left = 0;                                   // left always started from '0'th index of arr1 and 
        int right = left + gap;                         // right is always 'gap' ahead

        while(right < len)                              // we are going till length bcz after length it crosses the boundary        // O(n + m) 
        {
            // ar1 and arr2
            if(left < n && right >= n)                  // this condition means we are in arr1 and arr2
            {
                swapIfGreater(arr1, arr2, left, right - n);     // declared in private,  right index = 
            }
            // arr2 and arr2
            else if(left >= n)                          // both of them are in arr2
            {
                swapIfGreater(arr1, arr2, left - n, right - n);
            }
            // arr1 and arr1
            else                                        // both are in arr1
            {
                swapIfGreater(arr1, arr2, left, right);
            }
            left++, right++;
        }
        if(gap == 1)
            break;

        gap = (gap / 2) + (gap % 2);
    }
}

            TC - O(log 2 (n+m) * O(n+m)
            SC - O(1)
*/

int main()
{
    std::cout << "Hello World!\n";
}