#include<stdio.h>
#include<string.h>
#include<math.h>

#define DEBUG

//do you want to manual enter all other users information or a text file? 
//overleaf for latex


struct user_t{
    float time;//nanoseconds since ref
    char name[50];
    float lat, lng, alt;//meters south, west, above reference
}our_user, other_user[50]; //add to report placement of variable in function or global
struct user_t *user_ptr;
struct user_t *other_ptr;

int n = 0;// number of other_users initiallized to zero
int *nptr = &n;//pointer to number of other users

struct distance{
    char name [50];
    float dist_to_our_user;
}other_dist[50];


void scan_user(struct user_t *dest_ptr,struct user_t source_user);
void input();//Function for step 2 of requirements.  Calls scan_user() to fill our_user & other_users array
void distance();
int closest();
void print_user(struct user_t *ptr);
void user_entry();
void manual();
void auto_file();

int main()
{   
    //manuel entry funcion called for our_user & for manual other_users takes a pointer for the user
    //auto_file();
    
    input();
    distance();
    
    print_user(user_ptr = &our_user);//print our users data

    print_user(user_ptr = &other_user[closest()]);//print other users data

    return 0;
}

void input(){   
    
    struct user_t entering_user;//struct for storing manual entries
       
    printf("\nPlease enter your information.");
    printf("\nName: ");
    scanf("%s",&entering_user.name);//string stops at a space and crashes function.  Seems within scope of project
    printf("Time: ");
    scanf("%f",&entering_user.time);
    printf("Latitude: ");       //ASSUMPTION THAT  NAMES ARE SINGLE WORD
    scanf("%f",&entering_user.lat);
    printf("Longitude: ");
    scanf("%f",&entering_user.lng);
    printf("Altitude: ");
    scanf("%f",&entering_user.alt);  

    user_ptr = &our_user;//set user pointer to our_user

    scan_user(user_ptr,entering_user);//scan in our user

    printf("\nEnter other users. Select 0 for manual entry, 1 for file: ");
    int auto_manual=0;
    scanf("%d",&auto_manual);

    if(auto_manual == 1)  
        auto_file();
    else
        manual();  
    
    
    
}

void scan_user(struct user_t *dest_ptr,struct user_t scan_user){ //assign struc of source to destination struct. like strcpy()for struct;
     *dest_ptr = scan_user;
}

void print_user(struct user_t *print_ptr){
    
    struct user_t print_user;
    print_user = *print_ptr;//assign user in function call to struct used by print function
    
    printf("\nUser name: %s",print_user.name);
    printf("\nTime: %.2f",print_user.time);
    printf("\nLatitude: %.2f",print_user.lat);
    printf("\nLongitude: %.2f",print_user.lng);
    printf("\nAltitude: %.2f\n",print_user.alt);    
}

void manual (){
    /////////  MANUALLY ENTER OTHER USERS  /////////////

    struct user_t entering_user;//struct for storing manual entries
    
    printf("\nHow many other users would you like to manually enter?: ");
    scanf("%i",nptr);//scan number of users to global variable n

    for(int i=0;i<n;i++){
        printf("\nPlease enter your information.");
        
        printf("\nName: ");//string stops at a space and crashes function.  Seems within scope of project
        scanf("%s",&entering_user.name);//ASSUMPTION THAT  NAMES ARE SINGLE WORD
        printf("Time: ");
        scanf("%f",&entering_user.time);
        printf("Latitude: ");       
        scanf("%f",&entering_user.lat);
        printf("Longitude: ");
        scanf("%f",&entering_user.lng);
        printf("Altitude: ");
        scanf("%f",&entering_user.alt); 
        user_ptr = &other_user[i];
        scan_user(user_ptr,entering_user);//scan in our user
    }
}

void auto_file (){
    char file_name[50]={};
    printf("Enter file to load: ");
    scanf("%s",file_name);
    printf("The file %s will be opened.",file_name);

    FILE *input_file;
    input_file = fopen(file_name,"r");
    
    fscanf(input_file,"%i",nptr);//scan first line to global number of other users
    printf("\nNumber of other users scanned: %i\n",*nptr);//print the number of other users

    struct user_t entering_user;//struct for storing manual entries

    for(int i=0;i<*nptr;i++){
        fscanf(input_file,"%s", &entering_user.name);// printf("\nName: %s", entering_user.name);
        fscanf(input_file, "%f",&entering_user.time);// printf("\nTime: %d", entering_user.time);
        fscanf(input_file, "%f",&entering_user.lat); //printf("\nLat: %d", entering_user.lat);
        fscanf(input_file, "%f",&entering_user.lng); //printf("\nLng: %d", entering_user.lng);
        fscanf(input_file, "%f",&entering_user.alt); //printf("\nalt: %d", entering_user.alt);
            
        user_ptr = &other_user[i];

        scan_user(user_ptr,entering_user);//scan in our user
        print_user(user_ptr);
    }
   
    fclose(input_file);
}

void distance(){
      
    
    for(int i=0;i<n;i++)

    {
        float calc_dist = sqrt(pow((our_user.lat - other_user[i].lat),2)+pow((our_user.lng - other_user[i].lng),2)+pow((our_user.alt-other_user[i].alt),2));
        //printf("\ncalculated distance: %.2f",calc_dist);//Testing
        
        strcpy(other_dist[i].name, other_user[i].name);
        other_dist[i].dist_to_our_user = calc_dist;
        printf("\nother_dist[%d] name: %s",i,other_dist[i].name);
        printf("\nother_dist[%d] distance: %.2f",i,other_dist[i].dist_to_our_user);
    }
}

int closest (){
    int closest_user = 0;

    for(int i=0;i<n-1;i++){
        if(other_dist[i].dist_to_our_user < other_dist[closest_user].dist_to_our_user)//find smallest distance
            closest_user = i;
    }
    printf("\nClosest user is other_user[%d]",closest_user);
    return closest_user;

}