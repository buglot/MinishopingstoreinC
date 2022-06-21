#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//เรื่องที่ใช้
// input output   *scanf *printf
// variable
// Operator
// Conditional    *if *else if *else
// Loop           *for loop *while loop
// function       *Read_File *Print_stock
// Array
// Pointer        *maxline *stock *maxUser
// File           *fopen *fclose *fgets
// Structure      *Product_type *Clint_user

typedef struct Product_type
{
    char name[30];
    int amount;
    double price;
} Product;
Product *stock_i;
typedef struct Clint_user
{
    int id;
    char name[50];
    char password[100];
} Clint;
Clint *data_User;
typedef struct time_buy
{
    char name[50];
    double price;//total
    int month;
    int years;
    int day;
} buyHistory;
buyHistory *history;
int Lastbuy;//42
int t_year,t_month,t_day;//2022y/5 m/5d
void time_buy(int *t_year,int *t_month,int *t_day){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *t_year=tm.tm_year + 1900;
    *t_month=tm.tm_mon + 1;
    *t_day =tm.tm_mday;
}
void Write_Sale(char *FILENAME,int Lastbuy,char *name,double price){
    FILE *FIles;
    FIles = fopen(FILENAME,"a+");
    if(Lastbuy!=0){
        fprintf(FIles,"%s","\n");
    }
    fprintf(FIles,"%s,",name);
    fprintf(FIles,"%.2f,",price);
    fprintf(FIles,"%d,",t_day);
    fprintf(FIles,"%d,",t_month);
    fprintf(FIles,"%d",t_year);
    fclose(FIles);
}
void Read_line_sale(char *FILENAME,int *buy){
    FILE *FIles;
    //history.txt 
    //https://www.programiz.com/c-programming/c-file-input-output
    FIles = fopen(FILENAME,"a+");
    char t[300];//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa....aa
    int count=0;
    while (fgets(t,300,FIles)!=NULL){
        count++; 
    }
    *buy = count;//42
    fclose(FIles);
}
void print_View(buyHistory *history,int*buy){
    int day;
    int month;
    int year;
    int runloop=1;
    int choice;
    double price=0;
    while (runloop){
        printf("1.View sales Years\n");
        printf("2.View sales Month\n");
        printf("3.View sales day\n");
        printf("...other key be EXIT\n");
        printf(":");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("what years!\n");
                printf(":");
                scanf("%d",&year);
                int loopRun1=1;
                int month_year=1;
                price=0;
                while(loopRun1){
                    printf("-------------------------------------------\n");
                    printf("Year: %d month : %d \n",year,month_year);
                    printf("%-6s|%-12s|%9s|\n","DAY","NAME","PRICE");
                    for(int i=0;i<*buy;i++){
                        if(history[i].month == month_year && history[i].years == year){
                            printf("%-6d|%-12s|%9.2f|\n",history[i].day,history[i].name,history[i].price);
                            price+=history[i].price;
                        }
                    }
                    printf("-------------------------------------------\n");
                    month_year++;
                    if(month_year>12){
                        printf("%4d total  :%.2f \n",year,price);
                        printf("-------------------------------------------\n");
                        loopRun1=0;
                    }
                }
                break;
            case 2:
                price=0;
                printf("what years!\n");
                printf(":");
                scanf("%d",&year);
                printf("what month!\n");
                printf(":");
                scanf("%d",&month);
                printf("-------------------------------------------\n");
                printf("Year: %d month : %d \n",year,month);
                printf("%-6s|%-12s|%9s|\n","DAY","NAME","PRICE");
                for(int i=0;i<*buy;i++){
                    if(history[i].month == month && history[i].years == year){
                        printf("%-6d|%-12s|%9.2f|\n",history[i].day,history[i].name,history[i].price);
                        price+=history[i].price;
                    }
                }
                printf("%2d/%4d total  :%.2f \n",month,year,price);
                printf("-------------------------------------------\n");
                break;   
            case 3:
                price=0;
                printf("what years!\n");
                printf(":");
                scanf("%d",&year);
                printf("what month!\n");
                printf(":");
                scanf("%d",&month);
                printf("what day!\n");
                printf(":");
                scanf("%d",&day);
                printf("-------------------------------------------\n");
                printf("Year: %d month : %d day: %d \n",year,month,day);
                printf("%-12s|%-9s|\n","NAME","PRICE");
                for(int i=0;i<*buy;i++){
                    if(history[i].day == day && history[i].month == month && history[i].years == year){
                        printf("%-12s|%-9.2f|\n",history[i].name,history[i].price);
                        price+=history[i].price;
                    }
                }
                printf("%2d/%4d total  :%.2f \n",month,year,price);
                printf("-------------------------------------------\n");
                break;
            default:
                runloop=0;
                break;
        }
    }     
}
 

void View_Read_Sale_s(char *FILENAME,int *buy){
    FILE *FIles;
    int countbuy=0;
    buyHistory histo[500];
    char data_In_File[300];
    char *Split;
    FIles = fopen(FILENAME,"a+");
    while (fgets(data_In_File,300,FIles)!=NULL){
        Split = strtok(data_In_File,",");
        int Index_Txt_Comma = 0;
        while (Split != NULL){
            if (Index_Txt_Comma == 0){
                strcpy(histo[countbuy].name, Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else if (Index_Txt_Comma == 1){
                histo[countbuy].price = strtod(Split, NULL);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else if (Index_Txt_Comma == 2){
                histo[countbuy].day = atoi(Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else if (Index_Txt_Comma == 3){
                histo[countbuy].month =atoi(Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else if (Index_Txt_Comma == 4){
                histo[countbuy].years =atoi(Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }
        }
        countbuy++;
    }
    history = histo;
    *buy = countbuy;
    fclose(FIles);
    print_View(history,buy);
}

void Read_File(char *FILENAME, int *count){
    //stock.txt
    FILE *ReadFile;
    char TxtInFile[50];//aaaaaaaaaaa...a 50
    int countLINE = 0;//นับบรรทัด
    int count_repeat=0;//ซ้ำ
    char *Split;//แยก
    ReadFile = fopen(FILENAME, "a+");
    if (NULL == ReadFile){
        printf("file can't be opened \n");
    }
    Product stock[500]; //กำหนดเต็มที่ 500
    while (fgets(TxtInFile, 50, ReadFile) != NULL){
        Split = strtok(TxtInFile, ",");
        int Index_Txt_Comma = 0;
        while (Split != NULL){
            int repeat=0;
            int index_repeat=0;
            for(int i =0;i<countLINE;i++){
                if (strcmp(stock[i].name,Split)==0){
                    index_repeat=i;
                    repeat=1;
                    count_repeat=1;
                    break;
                }
                
            }
            //if== true
            if(repeat){//true 1 false 0
                if (Index_Txt_Comma == 0){
                    Split = strtok(NULL, ",");
                    stock[index_repeat].amount += atoi(Split);
                    Index_Txt_Comma++;
                    
                }
            }else{
                //true
                if (Index_Txt_Comma == 0){
                    strcpy(stock[countLINE].name, Split);
                    Split = strtok(NULL, ",");//แยกตัวถัดไป
                    Index_Txt_Comma++;//+1 =1 
                }else if (Index_Txt_Comma == 1){
                    stock[countLINE].amount = atoi(Split);
                    Split = strtok(NULL, ",");
                    Index_Txt_Comma++;//2
                }else{
                    stock[countLINE].price = strtod(Split, NULL);
                    Split = strtok(NULL, ",");
                    Index_Txt_Comma++;
                }
            }
            
        }
        countLINE-=count_repeat;
        count_repeat=0;
        countLINE++;//0+1 //1
    }
    countLINE-=count_repeat;
    stock_i = stock;
    *count = countLINE;
    fclose(ReadFile);
}
void Print_Stock(Product stock[], int maxline){
    int i;
    printf("%-4s|%-15s|%8s|%12s\n", "ID", "Product Name", "Amount", "Price");
    for (i = 0; i < maxline; i++){
        if(stock[i].amount!=0){
            printf("%-4d|%-15s|%8d|%12.2f \n", i, stock[i].name, stock[i].amount, stock[i].price);
        }else{
            printf("%-4d|%-15s|%8s|%12.2f \n", i, stock[i].name, "sold out", stock[i].price);
        }
    }
    printf("-------------------------------------------\n");
}
void bill(int *item, int maxAddItem, int idClint, Clint user[], Product *stock, int maxline,double price){
    char name[50];
    for (int i = 0; i < maxline; i++){
        if (user[i].id == idClint){
            strcpy(name, user[i].name);
            break;
        }
    }
    Product stock_for_bill[500];
    int item_bill[500];
    int maxAddItem_bill = 0;
    for (int i = 0; i < maxAddItem; i++){
        if (strcmp(stock_for_bill[item[i]].name, stock[item[i]].name) == 0){
            
            stock_for_bill[item[i]].amount += 1;
            stock_for_bill[item[i]].price = stock[item[i]].price * stock_for_bill[item[i]].amount;
        }else{
            strcpy(stock_for_bill[item[i]].name, stock[item[i]].name);
            stock_for_bill[item[i]].amount = 1;
            stock_for_bill[item[i]].price = stock[item[i]].price;
            item_bill[maxAddItem_bill] = item[i];
            maxAddItem_bill++;
        }
        
    }
    printf("-------------------------------------------\n");
    printf("%25s \n", "BILL");
    printf("Name : %s \n", name);
    printf("%-15s|%-13s|%12s|\n", "Product", "   Amount", "Prire");
    for (int i = 0; i < maxAddItem_bill; i++){
        if (stock_for_bill[item_bill[i]].amount > 1){
            printf("%-15s|%-3d*%-9.2f|%12.2f|\n", stock_for_bill[item_bill[i]].name, stock_for_bill[item_bill[i]].amount, stock[item_bill[i]].price, stock_for_bill[item_bill[i]].price);
            stock[item_bill[i]].amount -= stock_for_bill[item_bill[i]].amount;
        }else{
            printf("%-15s|%-13d|%12.2f|\n", stock_for_bill[item_bill[i]].name, stock_for_bill[item_bill[i]].amount, stock_for_bill[item_bill[i]].price);
            stock[item_bill[i]].amount -= stock_for_bill[item_bill[i]].amount;
        }
        stock_for_bill[item_bill[i]].amount = 0;
        strcpy(stock_for_bill[item[i]].name, "");
    }
    Write_Sale("history.txt",Lastbuy,name,price);
}
void loop_Purchase(int maxline, Clint user[], Product *stock, int idClint){
    char choice[300];
    int countbuy = 0;
    double price = 0;
    int sort_ITEM[500];
    int sort_ITEM_for_amount[500];
    int amountData[maxline-1];
    for(int i=0;i<maxline;i++){
        amountData[i]=stock[i].amount;
    }
    while (1){
        printf("What do you want? select with ID:0-%d  ( View Stock: v ) ( View You select: s )  ( Exit: e ) ( Confirm: c )\n :", maxline - 1);
        scanf("%s", &choice);
        if (strcmp(choice, "c") == 0){
            if(countbuy == 0){
                printf("Product ID has not been selected!\n");
                printf("-------------------------------------------\n");
            }else{
                bill(sort_ITEM, countbuy, idClint, user, stock, maxline,price);
                printf("%-12s %25.2f BTH| \n", "Total Price", price);
                printf("-------------------------------------------\n");
                break;
            }
            
        }else if (strcmp(choice, "v") == 0){
            Print_Stock(stock, maxline);
        }else if(strcmp(choice, "s")==0){
            printf("%-4s|%-4s|%-15s|\n","Time","id","Name Product");
            for(int i=0;i<countbuy;i++){
                printf("%-4d|%-4d|%-15s|\n",i+1,sort_ITEM[i],stock[sort_ITEM[i]].name);
            }
        }else{
            if (strcmp(choice, "e") != 0){
                if (maxline - 1 >= atoi(choice) && atoi(choice) >= 0){
                    if(amountData[atoi(choice)]>=1){
                        price += stock[atoi(choice)].price;
                        amountData[atoi(choice)]-=1;
                        sort_ITEM[countbuy] = atoi(choice);
                        countbuy++;
                    }else{
                        printf("this you select is limit of stock!\n");
                        printf("-------------------------------------------\n");
                    }
                    
                }else{
                    printf("Not Found id you enter!\n");
                    printf("-------------------------------------------\n");
                }
            }else{
                break;
            }
        }
    }
}
void Read_File_user(char *FILENAME, int *maxUser){
    FILE *ReadFile,*white;
    char TxtInFile[50],t[0];
    int countLINE = 0;
    char *Split;
    ReadFile = fopen(FILENAME, "a+");
    Clint user[500]; //กำหนดเต็มที่ 500
    while (fgets(TxtInFile, 50, ReadFile) != NULL){
        Split = strtok(TxtInFile, ",");
        int Index_Txt_Comma = 0;
        while (Split != NULL){
            if (Index_Txt_Comma == 0){
                strcpy(user[countLINE].name, Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else if (Index_Txt_Comma == 1){
                strcpy(user[countLINE].password, Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }else{
                user[countLINE].id = atoi(Split);
                Split = strtok(NULL, ",");
                Index_Txt_Comma++;
            }
        }
        countLINE++;
    }

    data_User = user;
    *maxUser = countLINE;
    fclose(ReadFile);
}
//0 0
void Menu(int admin_show, int bool_login){
    printf("Welcome to shop store\n");
    printf("select Menu\n");
    printf("1. View Stock\n");
    printf("2. Purchase\n");
    if (bool_login){
        printf("3. Logout-->\n");
    }else{
        printf("3. Login<--\n");
        printf("4. Register\n");
    }
    if (admin_show){
        printf("5. View Sales\n");
        printf("6. Add Amount of stock\n");
        printf("...\n9. And orther key Exit \n");
    } 
}
void login(Clint *user, int maxUser, int *bool_login, char name[], int *index){
    char username[50];
    int count_have_user = 0;
    while (1){
        printf("Enter your Username\n");
        printf(":");
        scanf("%s", &username);
        for (int y = 0; y < maxUser; y++){
            if (strcmp(user[y].name, username) == 0){
                count_have_user = 1;
                char passwordss[100];
                int countWong5TimePassword = 5;
                int loopRun = 1;
                strcpy(name, user[y].name);
                while (loopRun){
                    printf("Enter your Password\n");
                    printf(":");
                    scanf("%s", passwordss);
                    if (strcmp(user[y].password, passwordss) == 0) {
                        *bool_login = 1;
                        *index = user[y].id;
                        loopRun = 0;
                        printf("Login Succeed!\n");
                        printf("-------------------------------------------\n");
                        break;
                    }else{
                        printf("Password Wrong try again %d \n", countWong5TimePassword);
                        printf("-------------------------------------------\n");

                        if (countWong5TimePassword < 1){
                            count_have_user == 2;
                            loopRun = 0;
                        }
                        countWong5TimePassword--;
                    }
                }
            }
        }
        if (count_have_user == 0){
            printf("NO Have username\n");
            printf("-------------------------------------------\n");
            break;
        }
        else if (count_have_user == 1){
            break;
        }else if (count_have_user == 2){
            *bool_login = 0;
            printf("your Password Wrong more than 5 time!");
            break;
        }
    }
}
void writeFile_registers(char userNameInput[],char passwordInput[],int *maxUser){   
    FILE *fptr;
    if ((fptr = fopen("data_user.txt", "a+")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    if(*maxUser !=0){
        fprintf(fptr, "%s", "\n");
    }
    fprintf(fptr, "%s", userNameInput);
    fprintf(fptr, ",");
    fprintf(fptr, "%s",passwordInput);
    fprintf(fptr, ",");
    fprintf(fptr, "%d",*maxUser);
    *maxUser=*maxUser+1;
    fclose(fptr);
}

void registers(Clint *user, int *maxUser){
    int existUser = 0;
    int loopWhileRun = 1;
    char userNameInput[50];
    char passwordInput[100];
    char Re_passwordInput[100];
    while (loopWhileRun){
        printf("Enter Username\n");
        printf(":");
        scanf("%s", &userNameInput);
        for (int i = 0; i < *maxUser; i++){
            if (strcmp(user[i].name, userNameInput) == 0){
                existUser = 1;
                break;
            }
        }
        if (existUser){
            printf("-------------------------------------------\n");
            printf("Username Already Exists!\n");
            printf("Please Enter New Username Again!\n");
            printf("-------------------------------------------\n");
            existUser = 0;
        }else{
            while (1){
                printf("Enter password\n");
                printf(":");
                scanf("%s", &passwordInput);
                printf("Enter re-password\n");
                printf(":");
                scanf("%s", &Re_passwordInput);
                if (strcmp(Re_passwordInput, passwordInput) == 0){
                    writeFile_registers(userNameInput,passwordInput,maxUser);
                    strcpy(user[*maxUser-1].name,userNameInput);
                    strcpy(user[*maxUser-1].password,passwordInput);
                    user[*maxUser-1].id =*maxUser-1;
                    loopWhileRun = 0;
                    break;
                }else{
                    printf("-------------------------------------------\n");
                    printf("password & re_password not samething\n");
                    printf("try again Please!\n");
                    printf("-------------------------------------------\n");
                }
            }
        }
    }
}
void update_Stock(char *FILENAME,int maxline,Product *stock){
    FILE *fptr;
    if ((fptr = fopen(FILENAME, "w")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    for(int i=0;i<maxline;i++){
        if(i !=0){
            fprintf(fptr, "%s", "\n");
        }   
        fprintf(fptr,"%s,",stock[i].name);
        fprintf(fptr,"%d,",stock[i].amount);
        fprintf(fptr,"%.2f",stock[i].price);
    }
    fclose(fptr);
}
void Add_Astock(int *maxline,Product *stock){
    int runloop=1;
    char Name[50];
    int Amount,choice;
    char price[10];
    int ids=0;
    int Emounts=0;
    int c=0;
    while (runloop){
        printf("1.Add Amount\n");
        printf("2.View Stock\n");
        printf("...other ket be Exit\n");
        printf(":");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("%d\n",*maxline);
                Print_Stock(stock,*maxline);
                printf("ID product: ");
                scanf("%d",&ids);
                if(0<=ids && ids<*maxline){
                    printf("Amount Add: ");
                    scanf("%d",&Emounts);
                    printf("confirm Add! (yes: 1, no: 0)\n");
                    scanf("%d",&c);
                    if(c){
                        stock[ids].amount+=Emounts;
                        printf("Succeed!\n");
                    }
                }else{
                    printf("%d",ids);
                    printf("No have ID!\n");
                }
                break;
            case 2:
                Print_Stock(stock,*maxline);
                break;
            default:
                runloop=0;
                break;
        }

    }
    
}

void Font_loop(int *maxline, int *maxUser, Clint *user, Product *stock){
    int choice = 0;
    int runLoop = 1;//true =1 //false=0
    int bool_login = 0;
    char Name[50];
    int idClint;
    int admin_show = 0;
    while (runLoop){
        if (bool_login){
            printf("Hello %s\n", Name);
            if (strcmp(Name, "admin") == 0){
                admin_show = 1;
            }else{
                admin_show = 0;
            }
        }
        Menu(admin_show, bool_login);
        printf(":");
        scanf("%d", &choice);
        printf("-------------------------------------------\n");
        switch (choice){
        case 1:
            Print_Stock(stock, *maxline);
            break;
        case 2:
            if (bool_login){
                loop_Purchase(*maxline, user, stock, idClint);
            }else{
                printf("Please Login first\n");
                printf("-------------------------------------------\n");
            }
            break;
        case 3:
            if (bool_login){
                bool_login = 0;
                strcpy(Name, "");
                admin_show = 0;
            }else{
                login(user, *maxUser, &bool_login, Name, &idClint);
            }
            break;
        case 4:
            if (bool_login){
                printf("No commands!\n");
                printf("-----------------------------------------\n");
            }else{
                registers(user, maxUser);
            }
            
            break;
        case 5:
            if (admin_show){
                View_Read_Sale_s("history.txt",&Lastbuy);
            }else{
                printf("No commands!\n");
                printf("-----------------------------------------\n");
            }
            break;
        case 6:
            if (admin_show){
                Add_Astock(maxline,stock);
            }else{
                printf("No commands!\n");
                printf("-------------------------------------------\n");
            }
            break;
        case 9:
            if (admin_show){
                runLoop = 0;
                update_Stock("stock.txt",*maxline,stock);
            }else{
                printf("No commands!\n");
                printf("-------------------------------------------\n");
            }
            break;
        default:
            if (admin_show){
                update_Stock("stock.txt",*maxline,stock);
                runLoop = 0;
            }else{
                printf("No commands!\n");
                printf("-------------------------------------------\n");
            }
            break;
        }
    }
}
void main(){
    int maxline = 0;
    int maxUser = 0;
    Read_line_sale("history.txt",&Lastbuy);//อ่านบรรทัด history.txt
    time_buy(&t_year,&t_month,&t_day);//วันเวลาของคอม
    Read_File("stock.txt", &maxline);//อ่านไฟล์ stock.txt
    Read_File_user("data_user.txt", &maxUser);//อ่านไฟล์ data_user.txt
    Font_loop(&maxline, &maxUser, data_User, stock_i);
}