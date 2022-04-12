/*
  * Diffile Hellman programming
 */


#include <iostream>
#include <cstdlib>
#include <ctime>

void User_input();
void Random_input();
bool Check_Pvalue(int number);
bool Check_Gvalue(int number, int pValue);
bool Check_Xvalue(int number, int pValue);

bool PrimitiverootValue(int number, int pValue);
bool Check_prime_value(int number);

int Method_Operation(int a, int dec, int n);
int calculate_number(int input);
void Decimal_to_Binary(int Decimal, int *Binary);


struct db{
    int pValue, gValue, xValue, yValue, kValue;
};

using namespace std;

void calculate_key(db *Alice, db *Bob);

int main() {
    int option;
    unsigned seed = time(nullptr);
    srand(seed);
   while(true){
        cout<<"This is Diffie-Hellman key exchange programing."<<endl;
        cout<<"Option 1. choose the input method."<<endl;               //user input option
        cout<<"Option 2. choose the random method."<<endl;              //random input option
        cout<<"Option 3. Exit the programming."<<endl;                  //stop the programming
        cin>>option;
        switch (option) {
            case 1:
                User_input();                                           //if user select 1, then go to the user input function
                break;
            case 2:
                Random_input();                                         //if user select 2, then go to the random input function
                break;
            case 3:
                cout<<"Exit the programming";
                exit(1);
            default:                                                    //if user select 3, then stop the function
                cout<<"Just only input the option 1, 2 and 3\n";
                cout<<"Please try again\n";
                cout<<"\n";
                break;
        }
   }
}

//This is user input function, user need to input p,g,xa and xb value
void User_input(){
    db Alice{}, Bob{};
    int num;
    bool flag= true;
    cout<<"The input number should be integer number:"<<"\n";
    do{
        cout<<"P value should be the prime number and the number is between 3 and 100"<<"\n";
        cout<<"P value is :";
        cin >> num;
        flag = Check_Pvalue(num);                       //check enter p value number is correct or not correct
    } while(flag);
    Alice.pValue = Bob.pValue = num;

    do{
        cout<<"G value should be the prime number and the number is between 1 and "<<  Alice.pValue -1 <<"\n";
        cout<<"G value is :";
        cin>>num;
        flag = Check_Gvalue(num, Alice.pValue);         //check enter p value number is correct or not correct
    } while (flag);
    Alice.gValue = Bob.gValue = num;

    do {
        cout<<"Xa value is between 2 and "<<Alice.pValue -1<<"\n";
        cout<<"Xa value is :";
        cin>>num;
        flag = Check_Xvalue(num, Alice.pValue);         //check enter xa value number is correct or not correct
    } while (flag);
    Alice.xValue = num;          //alice get the xavalue

    do {
        cout<<"Xb value is between 2 and "<<Alice.pValue -1<<"\n";
        cout<<"Xb value is :";
        cin>>num;
        flag = Check_Xvalue(num, Bob.pValue);           //check enter xb value number is correct or not correct
    } while (flag);
    Bob.xValue = num;           //Bob get the xbvalue

    calculate_key(&Alice, &Bob);                    //find the key function

}

//this is random input function, get the correct random number and show the answer
void Random_input(){
    db Alice{},Bob{};
    int num;
    bool flag = true;

    do{
        num = 3 + rand()%98;                    //get the random number  between 3 and 100
        flag = Check_Pvalue(num);
    } while (flag);
    Alice.pValue = Bob.pValue=num;

    do {
        num = 1+ rand()%(Alice.pValue-1);       //get the random number between 1 and the p value
        flag = Check_Gvalue(num,Alice.pValue);
    } while (flag);
    Alice.gValue=Bob.gValue=num;

    do {
        num = 2 + rand()%(Alice.pValue-2);      //get the random number between 2 and the value of p
        flag = Check_Xvalue(num,Alice.pValue);
    }while(flag);
    Alice.xValue=num;

    do {
        num=2+rand()%(Alice.pValue-2);          //get the random number between 2 and the value of p
        flag= Check_Xvalue(num,Alice.pValue);
    } while (flag);
    Bob.xValue=num;

    //print all the value
    cout<<"The random method like this :"<<"\n";
    cout<<"The random P value is : "<<Alice.pValue<<"\n";
    cout<<"The random G value is : "<<Alice.gValue<<"\n";
    cout<<"The random Xa value is : "<<Alice.xValue<<"\n";
    cout<<"The random Xb value is : "<<Bob.xValue<<"\n";

    calculate_key(&Alice, &Bob);
}

//This is checking the P value function
bool Check_Pvalue(int number){
    //check the value , the number should be between 3 and 100
    if (number < 3 || number > 100)
        return true;
        if (!Check_prime_value(number))              //check the input number p value is prime number or not prime number
        return true;
    return false;
};

//this is checking the g value function
bool Check_Gvalue(int number, int pValue){
    //check the value, make sure the number is between 1 and p value
    if (number<1||number>pValue-1)
        return true;
    //check the primitive root element g must be in p
    if (!PrimitiverootValue(number, pValue))
        return false;
    return true;
}

//check the x value function
 bool Check_Xvalue(int number, int pValue){
    //make sure the xa value and xb value are rang 2 and pvalue
    if (number <2 || number > pValue - 1)
        return true;
    return false;
}

//check the value is primitive root or not
bool PrimitiverootValue(int g, int pValue){
    bool check[pValue-1];
    int root;
    //initiality all set to flase
    memset(check, false, sizeof(check));
    for (int i = 1; i < pValue; ++i) {
        //get array number , if all numbers just use the one time that means primitive root, if is not that not the primitive root
        root = Method_Operation(g, i, pValue)-1;
        if (!check[root]){
            check[root]= true;
        } else
            return true;
    }
    return false;
}

//find the key function (Diffie-Hellman Key Exchange in lecture 7 Page 22)
void calculate_key(db *Alice, db *Bob){
    Alice->yValue = Method_Operation(Alice->gValue,Alice->xValue,Alice->pValue);
    Bob->yValue = Method_Operation(Bob->gValue,Bob->xValue,Bob->pValue);
    Alice->kValue =Method_Operation(Bob->yValue,Alice->xValue,Alice->pValue);
    Bob->kValue =Method_Operation(Alice->yValue,Bob->xValue,Bob->pValue);
    cout<<"The key is  "<< Alice->kValue<<"\n ";                                     //a and b shared secret key together
    cout<<endl;
}

//This function is about the lecture 7 Page 13
int Method_Operation(int a, int dec, int n ){
    int c = 0, d = 1, indexnum;                                     // create c =0, d=1
    indexnum = calculate_number(dec);                             //find how about the size of the array is
    int bin[indexnum];                                            //create the binary size

    Decimal_to_Binary(dec, bin);                                       //covert decimal to the binary
    for (indexnum = indexnum -1 ; indexnum >= 0; indexnum--) {      // use the code form lecture 7 Page 13
        c *=2;                                                      //
        d = d * d % n;                                              //
        if (bin[indexnum]==1){
            c +=1;
            d = d*a%n;
        }
    }
    return  d;
}


//translate the Decimal to Binary
void Decimal_to_Binary(int Decimal, int *Binary){      //if the decimal is 150
    int i = 0;                                  //150 %2 =0     0
    while (Decimal){                            //75 %2= 1      1
        Binary[i]= Decimal%2;                   //37 %2 =1      1
        Decimal =Decimal/2;                     //18% 2 =0      0
        i++;                                    //              1
    }                                           //              0
}                                               //              0
                                                //              1  so is 10010110


//calculate the digits
int calculate_number(int inputnum){             //inputnum is 150
    int value = 0;                              //150/2 = 75  in this time the value is 1
    while (inputnum){                           //75/2 = 37                             2
        inputnum =inputnum/2;                   //37/2 = 18                             3
        value++;                                //18/2 = 9                              4
    }                                           //9/2  = 4                              5
    return value;                               //       2                              6
}                                               //      1                               7
                                                //       0                              8  then we can know the size value is 8


//this is checking the prime number function
bool Check_prime_value(int value){
    for (int i = 2; i <=value ; ++i) {
        if (value%i == 0 && i!= value)
            return false;
    }
    return true;
}



 *
 */
