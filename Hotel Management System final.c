#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Divayang Siddhapura 202451154
//Ronak Rathod        202451143
//Daksh Amalseda      202451012

#define MAX_ROOMS 100
#define FILENAME "hotel_data.txt"
#define logindata "logindata.txt"
#define MAX_LOGIN 300


void loginpage();
void bookRoom();
void checkIn();
void checkOut();
void savecustomerdata(int x);
void loadRooms();
void saveRooms();
void displayRooms();


typedef struct{
    char item[50];
    int price;
} order;
order food[20];
void foodmenu();
void starter();
void gujarati();
void southindian();
void soda();
void dessert();
void bill();

typedef struct
{
    int roomNumber;
    int roomclass;
    int isBooked;
    float price;
    char guestName[50];
    long long int guestaadhar;
    long long int phonenumber;
    int checkindate[3];
} Room;

typedef struct
{   
    char login_name[50];
    long long int phone;
} login;

Room rooms[MAX_ROOMS];
int totalRooms = 0;
login person[MAX_LOGIN];

void loginpage()
{
    int static i = 1;
    int static ID=1001;
    int givenid = 0,choice=0;

    printf("||---------------------------------------------------------||\n");
    printf("||               W   E   L   C   O   M   E                 ||\n\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||---------------------------------------------------------||\n\n");

    printf("Enter 1 to Register.\nEnter 0 to if Already Registered.\n");
    scanf("%d",&choice);
    if(choice==0)
        return;
    printf("||  Enter your Name: ");
    scanf("%s",&person[i].login_name);
    printf("\n|| Enter your Phone number: ");
    scanf("%lld", &person[i].phone);
    printf("\n||  Your ID is: %d \n", ID);
    printf("\n||---------------------------------------------------------||\n\n");

retry:
    printf("||  Enter your ID: ");
    scanf("%d", &givenid);

    if (givenid != ID)
    {
        printf("||  your given ID is incorrect\n||  please enter your ID again: ");
        goto retry;
    }

    printf("||---------------------------------------------------------||\n\n");

    ID++;
    i++;
}

void bookRoom()
{
    int roomNumber;
    char Name[50];
    printf("\n|| Enter room number to book: ");
    scanf("%d", &roomNumber);
    printf("|| Enter Check in Date (DD MM YYYY): ");
    scanf("%d %d %d", &rooms[roomNumber - 1].checkindate[0], &rooms[roomNumber - 1].checkindate[1], &rooms[roomNumber - 1].checkindate[2]);
    if (rooms[roomNumber - 1].checkindate[0] > 30 && rooms[roomNumber - 1].checkindate[1] > 12 && rooms[roomNumber - 1].checkindate[0] < 1 && rooms[roomNumber - 1].checkindate[1] < 1)
    {
        printf("|| please Enter Valid Date");
        return;
    }
    printf("|| Enter Guest name: ");
    scanf("%s", Name);
    strcpy(rooms[roomNumber-1].guestName,Name);
    printf("|| Enter Guest Aadhar number: ");
    scanf("%lld", &rooms[roomNumber - 1].guestaadhar);
    printf("|| Enter Guest Phone number: ");
    scanf("%lld", &rooms[roomNumber - 1].phonenumber);

    if (roomNumber < 1 || roomNumber > totalRooms)
    {
        printf("|| Invalid room number.\n");
        return;
    }

    if (rooms[roomNumber - 1].isBooked)
    {
        printf("|| Room is already booked.\n");
    }
    else
    {
        rooms[roomNumber - 1].isBooked = 1;
        strcpy(rooms[roomNumber - 1].guestName, Name);
        printf("|| Room %d booked successfully for %s.\n", roomNumber, Name);
        saveRooms();
    }
    savecustomerdata(roomNumber);
}

void checkIn()
{
    int roomNumber;
    printf("Enter room number to check in: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > totalRooms)
    {
        printf("Invalid room number.\n");
        return;
    }

    if (rooms[roomNumber - 1].isBooked)
    {
        printf("Room %d is already booked by %s.\n", roomNumber, rooms[roomNumber - 1].guestName);
    }
    else
    {
        printf("Room %d is available for check-in.\n", roomNumber);
    }
}

void checkOut()
{
    int roomNumber;
    printf("Enter room number to check out: ");
    scanf("%d", &roomNumber);
    int i=roomNumber;
    if (roomNumber < 1 || roomNumber > totalRooms)
    {
        printf("Invalid room number.\n");
        return;
    }

    if (!rooms[roomNumber - 1].isBooked)
    {
        printf("Room %d is not booked.\n", roomNumber);
    }
    else
    {
        rooms[roomNumber - 1].isBooked = 0;
        strcpy(rooms[roomNumber - 1].guestName, "");
        printf("Checked out from room %d successfully.\n", roomNumber);
        int amount;
        if (i < 10)
            amount=30000;
        else if (i < 30)
            amount=10000;
        else if (i < 70)
            amount=5000;

        else if (i < 100)
            amount=3000;
        printf("Your Payable Amount for the room is :%d",amount);
        saveRooms();
    }
}

void savecustomerdata(int x){
        FILE *file = fopen(FILENAME, "a");

        fprintf(file,"||D_A_T_A||\n");
        fprintf(file,"||*||\n");
        fprintf(file,"||  Room Number: %d\n",rooms[x].roomNumber);
        fprintf(file,"||  Guest Name: %s\n",rooms[x].guestName);
        fprintf(file,"||  Aadhar number: %lld\n",rooms[x].guestaadhar);
        fprintf(file,"||  Phone number: %d\n",rooms[x].phonenumber);
        fprintf(file,"||  Check In Date: ");
        for (int j = 0; j < 3; j++)
        {
            fprintf(file, "%d ", rooms[x].checkindate[j]);
        }
        fprintf(file,"||*||");
        fprintf(file, "\n\n");
    
    fclose(file);
}

void roominfo()
{
    int i;
    printf("|| Enter Room number: ");
    scanf("%d", &i);
    printf("-------------------------------------------\n");
    printf("\n|| Room number: %d \n", rooms[i - 1].roomNumber);
    printf("|| Name:           %s \n", rooms[i - 1].guestName);
    printf("|| Aadhar no:      %lld \n", rooms[i - 1].guestaadhar);
    printf("|| Check in Date:  %d/%d/%d \n", rooms[i - 1].checkindate[0], rooms[i - 1].checkindate[1], rooms[i - 1].checkindate[2]);
    if (rooms[i - 1].checkindate[0] < 30)
        printf("|| Check out Date: %d/%d/%d\n", rooms[i - 1].checkindate[0] + 1, rooms[i - 1].checkindate[1], rooms[i - 1].checkindate[2]);
    else if (rooms[i - 1].checkindate[0] == 30 && rooms[i - 1].checkindate[1] < 12)
        printf("|| Check out Date: %d/%d/%d\n", 1, rooms[i - 1].checkindate[1] + 1, rooms[i - 1].checkindate[2]);
    else if (rooms[i - 1].checkindate[0] == 30 && rooms[i - 1].checkindate[1] == 12)
        printf("|| Check out Date: %d/%d/%d\n", 1, 1, rooms[i - 1].checkindate[2] + 1);

}

void loadRooms()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Could not open file for reading. Initializing default rooms.\n");
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            rooms[i].roomNumber = i + 1;

            if (i < 10)
            {
                rooms[i].roomclass = 1;
                rooms[i].isBooked = 0;
                rooms[i].price = 30000.0;
            }
            else if (i < 30)
            {
                rooms[i].roomclass = 2;
                rooms[i].isBooked = 0;
                rooms[i].price = 10000.0;
            }
            else if (i < 70)
            {
                rooms[i].roomclass = 3;
                rooms[i].isBooked = 0;
                rooms[i].price = 5000.0;
            }
            else if (i < 100)
            {
                rooms[i].roomclass = 4;
                rooms[i].isBooked = 0;
                rooms[i].price = 3000.0;
            }
        }
        totalRooms = MAX_ROOMS;
        return;
    }

    while (fscanf(file, "%d %d %f %s", &rooms[totalRooms].roomNumber,
                  &rooms[totalRooms].isBooked,
                  &rooms[totalRooms].price,
                  rooms[totalRooms].guestName) != EOF)
    {

        fscanf(file, "%lld", &rooms[totalRooms].guestaadhar);
        for (int i = 0; i < 3; i++)
        {
            fscanf(file, "%d", &rooms[totalRooms].checkindate[i]);
        }
        totalRooms++;
    }
    fclose(file);
}

void saveRooms()
{
    FILE *file = fopen(FILENAME, "w");
    for (int i = 0; i < totalRooms; i++)
    {
        fprintf(file, "%d %d %.2f %s ",
                rooms[i].roomNumber,
                rooms[i].isBooked,
                rooms[i].price,
                rooms[i].guestName);

        fprintf(file, "Aadhar: %lld ", rooms[i].guestaadhar);

        for (int j = 0; j < 3; j++)
        {
            fprintf(file, "%d ", rooms[i].checkindate[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void displayRooms()
{
    printf("Available Rooms:\n");
    for (int i = 0; i < totalRooms; i++)
    {
        if (!rooms[i].isBooked)
        {
            printf("Room Number: %d, Price: %.2f, ", rooms[i].roomNumber, rooms[i].price);
            if (rooms[i].roomclass == 1)
                printf("Presidential suite\n");
            else if (rooms[i].roomclass == 2)
                printf("Deluxe room\n");
            else if (rooms[i].roomclass == 3)
                printf("Standard room\n");
            else if (rooms[i].roomclass == 4)
                printf("Single room\n");
            printf("\n");
        }
    }
}




int main()
{
    loadRooms();
    loginpage();
    int choice;

    do
    { 
        printf("\n||---------------------------------------------------------||\n");
        printf("||      H o t e l      B o o k i n g      S y s t e m      ||\n");
        printf("||---------------------------------------------------------||\n");
        printf("|| 1. Display Available Rooms                              ||\n");
        printf("|| 2. Book Room                                            ||\n");
        printf("|| 3. Check In                                             ||\n");
        printf("|| 4. Check Out                                            ||\n");
        printf("|| 5. For room info                                        ||\n");
        printf("|| 6. To Order Food                                        ||\n");
        printf("|| 7. Exit                                                 ||\n");
        printf("||---------------------------------------------------------||\n\n");
        printf("|| Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            displayRooms();
            break;
        case 2:
            bookRoom();
            break;
        case 3:
            checkIn();
            break;
        case 4:
            checkOut();
            break;
        case 5:
            roominfo();
            break;
        case 6:
            foodmenu();
            break;
        case 7:
            printf("\n||---------------------------------------------------------||\n");
            printf("||               T  H  A  N  K    Y  O  U                  ||\n");
            printf("||                 V I S I T   A G A I N                   ||\n");
            printf("||                   Have a Good Day!!!                    ||\n");
            printf("||---------------------------------------------------------||\n");
            printf("Exiting the system.....");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while(choice!=7);

    return 0;
}
// Some limitations of our code:
// 1.there is only 30 days in every month
// 2.Only first name is compatable

void foodmenu(){
    int choice=0;
    do{
    printf("\n||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("|| 1.  Starters                                            ||\n");
    printf("|| 2.  Gujarati                                            ||\n");
    printf("|| 3.  South Indian                                        ||\n");
    printf("|| 4.  Soda and Milkshakes                                 ||\n");
    printf("|| 5.  Desserts                                            ||\n");
    printf("|| 6.  View your Order                                     ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);

    if(choice==1)
        starter();
    else if(choice==2)
        gujarati();
    else if(choice==3)
        southindian();
    else if(choice==4)
        soda();
    else if(choice==5)
        dessert();
    else if(choice==6)
        bill();
    else if(choice==0)
        return;
    }while(choice!=0);
}

void bill(){
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    B   I   L   L                        ||\n");
    printf("|| Name:                             Price:                ||\n");
    int total=0;
    for(int i=1;i<=20;i++){
    printf("|| %s  -->  %d||\n",food[i].item,food[i].price);
    total+=food[i].price;
    }

    printf("|| Your Total Payable amount = %d rs                       ||\n",total);
    printf("|| press any 0 to go back                                  ||\n");
    printf("||---------------------------------------------------------||\n");
    int back;
    scanf("%d",&back);
    if(back || !back){
        return;
    }
}

int itemnum=1;
void starter(){
    int choice=0;
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("||  **Starters**                                         ||\n");
    printf("|| Name:                                Price:             ||\n");
    printf("|| 1.  Manchurian                       110                ||\n");
    printf("|| 2.  Manchaow Soup                    90                 ||\n");
    printf("|| 3.  Noodles                          120                ||\n");
    printf("|| 4.  Paneer Chilli                    180                ||\n");
    printf("|| 5.  Cheese Momos                     140                ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Manchurian");
        food[itemnum].price=110;
        itemnum++;
        break;
    case 2:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Manchow Soup");
        food[itemnum].price=90;
        itemnum++;
        break;
    case 3:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Noodles");
        food[itemnum].price=120;
        itemnum++;
        break;
    case 4:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Paneer Chilli");
        food[itemnum].price=180;
        itemnum++;
        break;
    case 5:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Cheese Momos");
        food[itemnum].price=140;
        itemnum++;
        break;
    case 0:
        return;
    default:
        printf("Enter valid number");
        break;
    }
}


void gujarati(){
    int choice=0;
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("||  **Gujarati**                                         ||\n");
    printf("|| Name:                                Price:             ||\n");
    printf("|| 1.  Gujarati Thali                   210                ||\n");
    printf("|| 2.  Sev Tomato                       70                 ||\n");
    printf("|| 3.  Plain Roti/rotlo                 20                 ||\n");
    printf("|| 4.  Kadhi kichdi                     170                ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Gujarati Thali");
        food[itemnum].price=210;
        itemnum++;
        break;
    case 2:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Sev Tomato");
        food[itemnum].price=70;
        itemnum++;
        break;
    case 3:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Plain roti/rotlo");
        food[itemnum].price=20;
        itemnum++;
        break;
    case 4:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Kadhi Kichdi");
        food[itemnum].price=170;
        itemnum++;
        break;
    case 0:
        return;
    default:
        printf("Enter valid number");
        break;
    }
}
void southindian(){
    int choice=0;
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("||  **South Indian**                                     ||\n");
    printf("|| Name:                                Price:             ||\n");
    printf("|| 1.  Masala Dosa                     150                 ||\n");
    printf("|| 2.  Utappam                         120                 ||\n");
    printf("|| 3.  Idli                            80                  ||\n");
    printf("|| 4.  Mendu Vada                      80                  ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Dosa");
        food[itemnum].price=150;
        itemnum++;
        break;
    case 2:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Uttapam");
        food[itemnum].price=120;
        itemnum++;
        break;
    case 3:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Idli");
        food[itemnum].price=80;
        itemnum++;
        break;
    case 4:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Mendu Vada");
        food[itemnum].price=80;
        itemnum++;
        break;
    case 0:
        return;
    default:
        printf("Enter valid number");
        break;
    }
}
void soda(){
    int choice=0;
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("||  **Soda and Milkshakes**                              ||\n");
    printf("|| Name:                                Price:             ||\n");
    printf("|| 1.  Mocktail                         150                ||\n");
    printf("|| 2.  Lemon Soda                       30                 ||\n");
    printf("|| 3.  Cold Coco                        60                 ||\n");
    printf("|| 4.  Jeera Soda                       30                 ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Mocktail");
        food[itemnum].price=150;
        itemnum++;
        break;
    case 2:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Lemon Soda");
        food[itemnum].price=30;
        itemnum++;
        break;
    case 3:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Cold Coco");
        food[itemnum].price=60;
        itemnum++;
        break;
    case 4:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Jeera Soda");
        food[itemnum].price=30;
        itemnum++;
        break;
    case 0:
        return;
    default:
        printf("Enter valid number");
        break;
    }
}
void dessert(){
    int choice=0;
    printf("||---------------------------------------------------------||\n");
    printf("||               H O T E L   K R I S H N A                 ||\n");
    printf("||                    F   O   O   D                        ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("||                    M   E   N   U                        ||\n");
    printf("||  **South Indian**                                     ||\n");
    printf("|| Name:                                Price:             ||\n");
    printf("|| 1.  Choco Lava Cake                  180                ||\n");
    printf("|| 2.  Black forest Cake                220                ||\n");
    printf("|| 3.  Cheese Cake(1 piece)             350                ||\n");
    printf("|| 4.  Brownie Icecream                 80                 ||\n");
    printf("|| 0.  Back                                                ||\n");
    printf("||---------------------------------------------------------||\n");
    printf("\nEnter Your Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Choco Lava Cake");
        food[itemnum].price=180;
        itemnum++;
        break;
    case 2:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Black Forest Cake");
        food[itemnum].price=220;
        itemnum++;
        break;
    case 3:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Cheese Cake");
        food[itemnum].price=350;
        itemnum++;
        break;
    case 4:
        printf("Added succesfully");
        strcpy(food[itemnum].item,"Brownie cake");
        food[itemnum].price=80;
        itemnum++;
        break;
    case 0:
        return;
    default:
        printf("Enter valid number");
        break;
    }
}
