#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
    char* cName;
    double balance;
    int order;
} Item;

int leftChild(int i)
{
    return (2*i)+1;
}

int rightChild(int i)
{
    return (2*i)+2;
}

/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item *arr, int n, int i)
{
    Item temp;
    int left,right;
    left = leftChild(i);
    right = rightChild(i);
    if(left<(n+1) && arr[left].balance > arr[i].balance)
    {
        temp = arr[i];
        arr[i] = arr[left];
        arr[left] = temp;
        max_heapify(arr, n, left);

    }
    else if(left<(n+1) && arr[i].balance==arr[left].balance)
    {
        if(arr[left].order < arr[i].order)
        {
            temp=arr[i];
            arr[i]=arr[left];
            arr[left]=temp;
            max_heapify(arr, n, left);

        }
    }

    if(right<(n+1) && arr[right].balance > arr[i].balance)
    {
        temp = arr[i];
        arr[i] = arr[right];
        arr[right] = temp;
        max_heapify(arr,n,right);

    }
    else if(right<(n+1) && arr[i].balance==arr[right].balance)
    {
        if(arr[right].order < arr[i].order)
        {
            temp = arr[i];
            arr[i] = arr[right];
            arr[right] = temp;
        max_heapify(arr,n,right);

        }
    }

}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
    int x;
    for(x=n/2; x>=0; x--)
        max_heapify(arr,n,x);
}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    if(!n)
        printf("\nQueue is empty");
    Item max = arr[0];
    arr[0]=arr[n];
    n=n-1;
    max_heapify(arr,n,0);
    return max;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    FILE *f;
    //  char ch[50];
//   double Balance;
    int i;
    int counter=0;
    f=fopen("PriorityQueue.txt","r");
    if (f!=NULL)
    {
        for(i=0; i<20; i++)
        {
            fscanf(f,"%s %lf\n",&arr[i].cName,&arr[i].balance);
            arr[i].order=i;
            //     printf("\n %s %lf\n",&arr[i].cName,arr[i].balance);
            counter++;
        }
        fclose(f);

    }
    return counter;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    int i;
    printf("**************************************");
    printf("\n Customers Sorted in descending order: ");
    printf("\n**************************************");
    printf("\n\nName   Balance   Order\n-------------------------\n");

    for(i=n; i>0; i--)
    {
        Item item=extract_maximum(arr,n--);
        printf("\n%s   %0.2lf   %d",&item.cName,item.balance,item.order);

    }
}
/*
 *
 */
int main(int argc, char**argv)
{

    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
