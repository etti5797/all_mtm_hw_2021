
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*definitions*/
#define INVALID_NUM -1
#define MODULO_EVEN 2
void printSizeNotValid();
bool checkIfSizeValid(double size);
void printNumNotValid();
bool checkIfNumWhole(double num);
int calculatePowerOfTwo(int num);
void printNumAndPower(int num_list[],int num_power_list[],int size);
void printExponentSum(int num_power_list[],int size);
void initializeArrayToZeros(int array[],int size);

/*program*/
int main()  //is size a whole? can be double?the nums too ? ?
{
    printf("Enter size of input:\n");
    double input_size=0;
    if((scanf("%lf",&input_size)!=1)||(!checkIfSizeValid(input_size)))
    {
        printSizeNotValid();
        return 0;
    }
    int size=input_size; //if we are here input size is an integer
    int* num_list=malloc(sizeof(*num_list)*size);
    if(num_list==NULL)
    {
        return 0;
    }
    initializeArrayToZeros(num_list,size);
    int* num_power_list=malloc(sizeof(*num_power_list)*size);
    if(num_power_list==NULL)
    {
        free(num_list);
        return 0;
    } 
    initializeArrayToZeros(num_power_list,size);
    printf("Enter numbers:\n");
    int more_to_recive=0, array_index=0,possibility=0;
    double temp=0;
    while(more_to_recive<size)
    {
        if((scanf("%lf",&temp)!=1)||(!checkIfNumWhole(temp)))
        {
            printNumNotValid();
            return 0;
        }
        int integer=(int)temp;
        possibility=calculatePowerOfTwo(integer);
        if(possibility!=INVALID_NUM)
        {
            num_list[array_index]=integer;
            num_power_list[array_index]=possibility;
            array_index++;
        }
        more_to_recive++;
    }
    printNumAndPower(num_list,num_power_list,size);
    printExponentSum(num_power_list,size);
    free(num_list);
    free(num_power_list);
    return 0;
}

void printSizeNotValid(){
    printf("Invalid size\n");
}

bool checkIfSizeValid(double size){
    if(size<=0)
    {
        return false;
    }
    return checkIfNumWhole(size);
}

void printNumNotValid(){
    printf("Invalid number\n");
}

bool checkIfNumWhole(double num){
    if(num<0)
    {
        num=-num;
    }
    int int_num=(int)num;
    if(num-int_num>0)
    {
        return false;
    }
    return true;
}

int calculatePowerOfTwo(int num){
    if(num==1)
    {
        return 0;
    }
    if((num<=0)||(num% MODULO_EVEN!=0))
    {
        return INVALID_NUM;
    }
    int power=0;
    while(num!=1)
    {
        num=num/MODULO_EVEN;
        if((num!=1)&&(num % MODULO_EVEN !=0))
        {
            return INVALID_NUM;
        }
        power++;
    }
    return power;
}

void printNumAndPower(int num_list[],int num_power_list[],int size)
{
    for(int i=0;i<size;i++)
    {
        if(num_list[i]==0)
        {
            break; //zero is not powered by two so if there is zero in the array 
           // it's from initialization so we didn't fill the array since this point
        }  
        printf("The number %d is a power of 2: %d = 2^%d\n",num_list[i],num_list[i],num_power_list[i]);
    }
}
void printExponentSum(int num_power_list[],int size){
    int sum=0;
    for(int i=0;i<size;i++)
    {
        sum+=num_power_list[i];
    }
    printf("Total exponent sum is %d\n", sum);
}

void initializeArrayToZeros(int array[],int size)
{
    for(int i=0;i<size;i++)
    {
        array[i]=0;
    }
}


