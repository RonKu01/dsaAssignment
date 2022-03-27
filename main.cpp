#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <regex>

using namespace std;
const int depArrSize = 10;

struct User{
  string icPassport;
  string name;
  string address;
  string gender;
};

struct Individual{
  User userDetails;
  string email;
  string phoneNum;
  string password;
  string vacDetails;
  string riskStat;
};

struct Dependants{
  User depDetails;
  string relation;
  int age;
};

struct Establishment{
  int code;
  string venue;
};

struct History{
  Establishment est;
  Individual indi;
  string date;
  string time;
  Dependants dep[depArrSize];
  int totalDep;
  History* nxtHistory;
} *top;

// Single Variable for individual
Individual indi;

// Queue Array - Dependants
Dependants dep[10];
int n = 10, front = - 1, rear = - 1;
int numberOfDependants = 0;

//Individual Declaration for graph
// Individual red;
// Individual blue;
// Individual green;
// Individual pink;

bool is_email_valid(const string& email)
{
   // define a regular expression
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

bool is_phoneNumber_valid(const string& phoneNumber)
{
   // define a regular expression
   const std::regex pattern
      ("[[:digit:]]{3}-[[:digit:]]{3}-[[:digit:]]{4}");

   // try to match the string with the regular expression
   return std::regex_match(phoneNumber, pattern);
}

bool is_icPassport_valid(const string& icPassport)
{
   // define a regular expression
   const std::regex pattern
      ("[[:digit:]]{6}-[[:digit:]]{2}-[[:digit:]]{4}");

   // try to match the string with the regular expression
   return std::regex_match(icPassport, pattern);
}

Establishment* getEstList(){
  Establishment est;
  static Establishment estList[10];

  int i = 0;
  ifstream input("establishment.txt");
  while( input >> est.code >> est.venue)
  {
    estList[i].code = est.code;
    estList[i].venue = est.venue;
    i++;
  }
  input.close();
  return estList;
}

void displayProfile(){
  cout << "---------------------------------" << endl;
  cout << "        Individual Account       " << endl;
  cout << "---------------------------------" << endl;
  cout << "Full Name   : " << indi.userDetails.name << endl;
  cout << "IC/Passport : " << indi.userDetails.icPassport << endl;
  cout << "Address     : " << indi.userDetails.address << endl;
  cout << "Gender      : " << indi.userDetails.gender << endl;
  cout << "Email       : " << indi.email << endl;
  cout << "Phone Num   : " << indi.phoneNum << endl;
  cout << "Vaccination : " << indi.vacDetails << endl;
  cout << "Risk Status : " << indi.riskStat << endl;
}

void displayEst() {

  Establishment* est;
  est = getEstList();

  cout << "----------------" << endl;
  cout << "   Venue List   " << endl;
  cout << "----------------" << endl;
  
  for (int i=0; i <10; i ++){
    cout << est[i].code << "   " << est[i].venue << endl;
  }
  cout << "----------------" << endl;
}

void updateProfile(){
  
  int userOption; string email; string phoneNumber;
  displayProfile();

  do 
  {
    cout << "---------------------------------" << endl; 
    cout << "Please insert options to update  " << endl;
    cout << "1) Email                         " << endl;
    cout << "2) Phone Number                  " << endl;
    cout << "3) Address                       " << endl;
    cout << "4) Return to Home Page           " << endl;
    cout << "---------------------------------" << endl; 
    cout << "Input: ";
    
    cin >> userOption;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(userOption)
      {
        case 1 : {
          cout << "New Email : ";
          getline(cin, email);

          while(!is_email_valid(email)) {
            cout << "-----------------------------" << endl;
            cout << "         Invalid Email       " << endl;
            cout << "   Format 'abc@example.com'  " << endl;    
            cout << "-----------------------------" << endl;
            cout << "Please insert New Email: ";
        		cin.clear();
            getline(cin, email);
          }

          indi.email = email;
          system("cls");
          displayProfile();
          break;
        }
        case 2 : {
          cout << "New Phone Number : ";
          getline(cin, phoneNumber);

          while(!is_phoneNumber_valid(phoneNumber)) {
            cout << "-------------------------------------" << endl;
            cout << "         Invalid Phone Number        " << endl;
            cout << "         Format '000-000-0000'       " << endl; 
            cout << "-------------------------------------" << endl;
            cout << "Please insert New Phone Number: ";
        		cin.clear();
            getline(cin, phoneNumber);
          }

          indi.phoneNum = phoneNumber;

          system("cls");
          displayProfile();
          break;
        }
        case 3 : {
          cout << "New Address : ";
          getline(cin, indi.userDetails.address);
          system("cls");
          displayProfile();
          break;
        }
        case 4 : system("cls"); break;
        default:
          cout << "Please only key in 1, 2, 3, or 4" << endl;
          system("cls");
          break;
      }
  } while (!(userOption == 4));
}

void displayDependants(){

  // Queue is Empty
  if (front == -1){
    cout << "-------------------------------" << endl;
    cout << "You do not have any dependants!" << endl;
    cout << "-------------------------------" << endl;
  } else 
    
  // Display List of Dependant
  { 
    system("cls");
    cout << "-------------------------------" << endl;
    cout << "        Dependants List        " << endl;
    cout << "-------------------------------" << endl;
    
    for (int i = 0; i <= rear; i++) {
      cout << i+1 << "  " 
           << dep[i].depDetails.name << "  " 
           << dep[i].depDetails.icPassport << "  " 
           << dep[i].depDetails.address << "  "
           << dep[i].depDetails.gender << "  " 
           << dep[i].relation << "  " 
           << dep[i].age << "  "
           << endl;
    }

    cout << "-------------------------------" << endl;
  }
}

void addDependants() {
  string depIcPassport, gender; 
  char depGender;
  int userInput, depAge;
  bool isValidAge = false;

   if (rear == n - 1)
     cout<<"Failed : Reached Maximum Dependants (10)"<<endl;
   else {
      if (front == - 1) {
        front = 0; rear = 0; 
        cout << "Dependant Name: ";
        getline(cin, dep[front].depDetails.name);

        cout << "Dependant IC / Passport: ";
        cin >> depIcPassport;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(!is_icPassport_valid(depIcPassport)) {
            cout << "-----------------------------------" << endl;
            cout << "      Invalid IC Passport          " << endl;
            cout << "      Format '000000-00-0000'      " << endl; 
            cout << "-----------------------------------" << endl;
            cout << "Please insert correct IC Passport: ";
            cin.clear();
            cin >> depIcPassport;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          }
        
        dep[front].depDetails.icPassport = depIcPassport;

        cout << "Dependant Address: ";
        cin >> dep[front].depDetails.address;


        cout << "Dependant Gender(M / F): ";
        cin >> depGender;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(depGender != 'M' && depGender != 'm' && depGender != 'F' && depGender != 'f'){
          cin.clear();
          cout << "---------------------------------" << endl;
          cout << "Invalid! Only Enter (M / F) only!" << endl;
          cout << "---------------------------------" << endl;
          cout << "Please insert your Gender (M / F): ";
          cin >> depGender;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (depGender == 'M' || depGender == 'm'){
          gender = "Male";
        } else 
          if (depGender == 'F' || depGender == 'f'){
          gender = "Female";
        }
        dep[front].depDetails.gender = gender;

        
        cout << "---------------------------------" << endl; 
        cout << "          Relationship           " << endl;
        cout << "---------------------------------" << endl;
        cout << "Please Select Relantionship      " << endl;
        cout << "1) Spouse                        " << endl;
        cout << "2) Child                         " << endl;
        cout << "3) Siblings                      " << endl;
        cout << "4) Parents / Parents-in-law      " << endl;
        cout << "5) Grandparents                  " << endl;
        cout << "6) Guardian                      " << endl;
        cout << "7) Others                        " << endl;
        cout << "---------------------------------" << endl;
        cout << "Input: ";
        cin >> userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

       
        while(userInput != 1 && userInput !=2 && userInput !=3 && userInput !=4 && userInput !=5 && userInput !=6 && userInput !=7){
          cin.clear();
          cout << "----------------------------------" << endl;
          cout << "   Fail! Please Reselect Again!   " << endl;
          cout << "----------------------------------" << endl;
          cout << "Input: ";
          cin >> userInput;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      
        if(userInput == 1){
          dep[front].relation = "Spouse";
        }
        else if(userInput == 2){
          dep[front].relation = "Child";
        }
        else if(userInput == 3){
          dep[front].relation = "Siblings";
        }
        else if(userInput == 4){
          dep[front].relation = "Parents / Parents-in-law";
        }
        else if(userInput == 5){
          dep[front].relation = "Grandparents";
        }
        else if(userInput == 6){
          dep[front].relation = "Guardian";
        }
        else if(userInput == 7){
          dep[front].relation = "Others";
        }
        
        
        
      cout << "Dependants Age: ";
        do{
          cin >> depAge;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          
          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please insert integer!" << endl;
            cout << "Dependants Age: ";
          }else {
            if (depAge >= 0 && depAge <= 120){
              isValidAge = true;
            } else {
              cout << "Invalid Age!" << endl;
              cout << "Please insert again: ";
            }
          } 
        }while(!(isValidAge == true));
        
        dep[front].age = depAge;
    
        dep[rear].depDetails.name = dep[front].depDetails.name;
        dep[rear].depDetails.icPassport = dep[front].depDetails.icPassport;
        dep[rear].depDetails.address = dep[front].depDetails.address;
        dep[rear].depDetails.gender = dep[front].depDetails.gender;
        dep[rear].relation = dep[front].relation;
        dep[rear].age = dep[front].age;

        
        system("cls");
        cout << "-------------------------------" << endl;
        cout << "Dependants Successfully Added!" << endl;
        cout << "-------------------------------" << endl;
      } else {
        rear = rear + 1;
        
        cout << "Dependant Name: ";
        getline(cin, dep[rear].depDetails.name);

        cout << "Dependant IC / Passport: ";
        cin >> depIcPassport;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(!is_icPassport_valid(depIcPassport)) {
          cout << "-----------------------------------" << endl;
          cout << "      Invalid IC Passport          " << endl;
          cout << "      Format '000000-00-0000'      " << endl; 
          cout << "-----------------------------------" << endl;
          cout << "Please insert correct IC Passport: ";
          cin.clear();
          cin >> depIcPassport;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        dep[rear].depDetails.icPassport = depIcPassport;

        cout << "Dependant Address: ";
        cin >> dep[rear].depDetails.address;

        cout << "Dependant Gender(M / F): ";
        cin >> depGender;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(depGender != 'M' && depGender != 'm' && depGender != 'F' && depGender != 'f'){
          cin.clear();
          cout << "---------------------------------" << endl;
          cout << "Invalid! Only Enter (M / F) only!" << endl;
          cout << "---------------------------------" << endl;
          cout << "Please insert your Gender (M / F): ";
          cin >> depGender;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (depGender == 'M' || depGender == 'm'){
          gender = "Male";
        } else 
          if (depGender == 'F' || depGender == 'f'){
          gender = "Female";
        }
        
        dep[rear].depDetails.gender = gender;

        cout << "---------------------------------" << endl; 
        cout << "          Relationship           " << endl;
        cout << "---------------------------------" << endl;
        cout << "Please Select Relantionship      " << endl;
        cout << "1) Spouse                        " << endl;
        cout << "2) Child                         " << endl;
        cout << "3) Siblings                      " << endl;
        cout << "4) Parents / Parents-in-law      " << endl;
        cout << "5) Grandparents                  " << endl;
        cout << "6) Guardian                      " << endl;
        cout << "7) Others                        " << endl;
        cout << "---------------------------------" << endl;
        cout << "Input: ";
        cin >> userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while(userInput != 1 && userInput !=2 && userInput !=3 && userInput !=4 && userInput !=5 && userInput !=6 && userInput !=7){
          cin.clear();
          cout << "----------------------------------" << endl;
          cout << "   Fail! Please Reselect Again!   " << endl;
          cout << "----------------------------------" << endl;
          cout << "Input: ";
          cin >> userInput;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      
        if(userInput == 1){
          dep[rear].relation = "Spouse";
        }
        else if(userInput == 2){
          dep[rear].relation = "Child";
        }
        else if(userInput == 3){
          dep[rear].relation = "Siblings";
        }
        else if(userInput == 4){
          dep[rear].relation = "Parents / Parents-in-law";
        }
        else if(userInput == 5){
          dep[rear].relation = "Grandparents";
        }
        else if(userInput == 6){
          dep[rear].relation = "Guardian";
        }
        else if(userInput == 7){
          dep[rear].relation = "Others";
        }

        cout << "Dependants Age: ";
        do{
          cin >> depAge;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          
          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please insert integer!" << endl;
            cout << "Dependants Age: ";
          }else {
            if (depAge >= 0 && depAge <= 120){
              isValidAge = true;
            } else {
              cout << "Invalid Age!" << endl;
              cout << "Please insert again: ";
            }
          } 
        }while(!(isValidAge == true));
        
        dep[rear].age = depAge;

        system("cls");

        cout << "-------------------------------" << endl;
        cout << "Dependants Successfully Added!" << endl;
        cout << "-------------------------------" << endl;
      }
   }
}

void deleteDependants(){
  //Remove Dependants, bring forward

   if (front == - 1) {
     system("cls");
     cout << "-------------------------------" << endl;
     cout << "You do not have any dependants!" << endl;
     cout << "-------------------------------" << endl;
   }else {
      int depDelete;
     
      displayDependants();
      do{
        cout << "--------------------------------------" << endl;
        cout << "Which dependant do you want to delete?" << endl;
        cout << "Note: Enter -1 to go back             " << endl;
        cout << "--------------------------------------" << endl;
        cout << "Number: "; 
        cin >> depDelete;

        if(depDelete == -1)
        {
          system("cls");
          break;
        }else
        {
          int selectedDep = depDelete - 1;
          if (selectedDep > rear) {
            cout << "Please only enter valid dependant Number!" << endl;
          } else {

            for(int i=selectedDep; i<rear; i++) {
              dep[i].depDetails.name = dep[i+1].depDetails.name;
              dep[i].depDetails.icPassport = dep[i+1].depDetails.icPassport;
              dep[i].depDetails.address = dep[i+1].depDetails.address;
              dep[i].depDetails.gender = dep[i+1].depDetails.gender;
              dep[i].relation = dep[i+1].relation;
              dep[i].age = dep[i+1].age;
            }

            system("cls");
            cout << "--------------------------------------" << endl;
            cout << "Delete Succesfully!                   " << endl;
            cout << "--------------------------------------" << endl;
            rear--;

            if (rear == -1) {
              front = -1;
            }
            
            break;
          }
        }
      }while(!(depDelete == -1));
   }
}

void manageDependants(){

  int userOption2;
  displayDependants();
  
  do{
    cout << "-------------------------------" << endl; 
    cout << "Press insert option to continue" << endl;
    cout << "1) Add Dependants              " << endl;
    cout << "2) Display Dependants          " << endl;
    cout << "3) Delete Dependants           " << endl;
    cout << "4) Return to Home Page         " << endl;
    cout << "-------------------------------" << endl; 
    cout << "Input: ";
    cin >> userOption2;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(userOption2) 
    {
      case 1 : { addDependants(); break; }
      case 2 : { displayDependants(); break; }
      case 3 : { deleteDependants(); break; }
      case 4 : { cout << "Return to Home Page" << endl; break; } 
      default: {
        cout << "Please only key in 1, 2, 3, or 4" << endl;   
        break;
      }
    }
  }while(!(userOption2 == 4));
}

void pushHistory
( 
  int estCode,
  string venue,
  string indiName,
  string* depPtr,
  int depNum,
  string vacDetails,
  string risk,
  string date, 
  string time
){
  History* nHistory = new History;

  nHistory->date = date;
  nHistory->time = time;
  nHistory->est.venue = venue;
  nHistory->indi.userDetails.name = indiName;
  nHistory->indi.vacDetails = vacDetails;
  nHistory->indi.riskStat = risk;
  nHistory->totalDep = depNum;

  for (int i=0; i < depNum; i++){
    nHistory->dep[i].depDetails.name = (*(depPtr + i));
  }

  if (depNum == 0) {
    nHistory->dep[0].depDetails.name = "-";
  }

  nHistory->nxtHistory = NULL;
  nHistory->nxtHistory = top;
  top = nHistory;
};

void checkIn(){

  int userOption = 0, userOption2, userOption3;
  int estCode;
  string venue, checkInDate, checkInTime;
  string depName[10];
  bool isConfirm = false; bool isValidVenue = false; bool isValidDep = false;

  Establishment* est;
  est = getEstList();
  
  if (front >= 0) {

    cout << "Do you have dependants with you?" << endl;
    cout << "--------------------------------" << endl;
    cout << "(Yes: Y // No: Press Any Key (Except Y) to continue)" << endl; 

    char input = ' ';
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(input == 'Y' || input == 'y')
    {
      displayDependants();

      do{
        cout << "Keyin the amount of dependants: ";

          do{
            cin >> userOption ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(cin.fail()){
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << "Please insert Integer!" << endl;
              cout << "Keyin the amount of dependants: ";
            }else {
              if ((userOption-1) <= rear){
                isValidDep = true;
              } else {
                cout << "You only have " << (rear+1) << " dependant(s)!" << endl;
                cout << "Keyin the amount of dependants: ";
              }
            }
          }while(!(isValidDep == true));

        int arrDepVisited[userOption]; bool isNew = true;  int x = 0; 

        for (int i = 0; i < userOption; i++){

          cout << "Dependant " << i+1 << ": ";
          cin >> userOption2;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          int selectedDep = userOption2 - 1;

          while(x < i) {
            if (arrDepVisited[x] == selectedDep) {
              isNew = false;
              cout << "Index " << selectedDep + 1 << " dependant has already selected" << endl;
              cout << "RE-enter with ANOTHER dependants again!" << endl;
              cout << "---------------------------------------------------" << endl;
              i--;
              x--;
            }
            x++;
          } 

          if (isNew){
            arrDepVisited[i] = selectedDep;
          }
          isNew = true;
        }
  
        for (int n = 0; n < userOption; n++) {
          cout << "You are with " << dep[arrDepVisited[n]].depDetails.name << "." << endl;
        }
        
        cout << "-----------------------------" << endl;
        cout << "Is this information correct?" << endl;
        cout << "(Yes: Y // No: N)" << endl; 
        char input2 = ' ';
        cin >> input2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (input2 == 'Y' || input2 == 'y'){
          isConfirm = true;
          for (int n = 0; n < userOption; n++) {
            depName[n] = dep[arrDepVisited[n]].depDetails.name;
          }
          system("cls");

        }
      } while (!(isConfirm == true));
    }
  }

  displayEst();

  cout << "Insert Venue Code: "; 

  do{
    cin >> userOption3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      displayEst();
      cout << "Please insert Venue Index!" << endl;
      cout << "Insert Venue Code: ";
    }else {
      if (userOption3 >= 101 && userOption3 <= 110){
        isValidVenue = true;
      } else {
        system("cls");
        displayEst();
        cout << "Please insert valid Venue" << endl;
        cout << "Insert Venue Code: ";
      }
    } 
  }while(!(isValidVenue == true));

  for (int i = 0; i < 10; i ++){
    if (userOption3 == (*(est + i)).code) {
      estCode = (*(est + i)).code;
      venue = (*(est + i)).venue; 

      system("cls");
      cout << "-------------------------------" << endl;
      cout << "     Check IN Successfully!    " << endl;
      cout << "-------------------------------" << endl;
      
      time_t now = time(0);
      tm *ltm = localtime(&now);
      checkInDate = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year);
      checkInTime = to_string(ltm -> tm_hour) + ":" + to_string(ltm -> tm_min) + ":" + to_string(ltm -> tm_sec);

      string depNames = "";

      if (userOption > 0){
        for (int i = 0; i < userOption; i++){
          depNames += (depName[i]+ ",");
        };
        depNames.back() = ' ';
      } else {
        depNames = "-";
      }

      cout << "Venue: " << venue << endl; 
      cout << "Name: " << indi.userDetails.name << endl;
      cout << "Date: " << checkInDate << endl;
      cout << "Time: " << checkInTime << endl;
      cout << "Dependants: " << depNames << endl;
      cout << "Vaccination: " <<indi.vacDetails << endl;
      cout << "Risk: " <<indi.riskStat << endl;
      break;
    }
  }

  pushHistory(estCode, venue, indi.userDetails.name, depName, userOption, indi.vacDetails, indi.riskStat, checkInDate, checkInTime);
}

void displayHistoryList() {

  if (top == NULL)
  {
    cout << "History is empty" << endl;
    return;
  }

  History* nav = top;
  
  cout << "-------------------------------" << endl;
  cout << "          History Log          " << endl;
  cout << "-------------------------------" << endl;
  cout << "Venue \t FullName \t Date \t \t Time \t Dependants \t VacStatus \t RiskStatus" << endl; 

  while (nav != NULL)
  {
    string depNames = "";

    if ((nav->totalDep) > 0){
      for (int i = 0; i < (nav->totalDep); i++){
        depNames += (nav->dep[i].depDetails.name + ",");
      };
      depNames.back() = ' ';
    } else {
      depNames = "-";
    }

    cout  << nav->est.venue << " \t " 
          << nav->indi.userDetails.name << " \t " 
          << nav->date << " \t " 
          << nav->time << " \t " 
          << depNames << " \t " 
          << nav->indi.vacDetails << " \t " 
          << nav->indi.riskStat << endl; 
  
    nav = nav -> nxtHistory;
  }
}; 

void adminFunction(){
  cout << "-------------------------------" << endl;
  cout << "     WELCOME TO ADMIN PAGE     " << endl;
  cout << "-------------------------------" << endl;
}

void indiFunction(){
  int userOption, userInput;
  string icPassport, email, phoneNumber; 
  char gender;
  
  cout << "-------------------------------" << endl;
  cout << "       Register Account        " << endl;
  cout << "(Please insert correct details)" << endl;
  cout << "-------------------------------" << endl;
  
  cout << "Full Name : ";
  getline(cin, indi.userDetails.name);

  cout << "IC / Passport : ";
  cin >> icPassport;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  while(!is_icPassport_valid(icPassport)) {
    cout << "-----------------------------------" << endl;
    cout << "      Invalid IC Passport          " << endl;
    cout << "      Format '000000-00-0000'      " << endl; 
    cout << "-----------------------------------" << endl;
    cout << "Please insert correct IC Passport: ";
    cin.clear();
    cin >> icPassport;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  
  indi.userDetails.icPassport = icPassport;

  cout << "Address : ";
  getline(cin, indi.userDetails.address);

  cout << "Gender (M / F): ";
  cin >> gender;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f'){
    cin.clear();
    cout << "---------------------------------" << endl;
    cout << "Invalid! Only Enter (M / F) only!" << endl;
    cout << "---------------------------------" << endl;
    cout << "Please insert your Gender (M / F): ";
    cin >> gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  if (gender == 'M' || gender == 'm'){
    indi.userDetails.gender = "Male";
  } else 
    if (gender == 'F' || gender == 'f'){
    indi.userDetails.gender = "Female";
  }
  
  cout << "Email : ";
  cin >> email;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(!is_email_valid(email)) {
    cout << "-----------------------------" << endl;
    cout << "         Invalid Email       " << endl;
    cout << "   Format 'abc@example.com'  " << endl;    
    cout << "-----------------------------" << endl;
    cout << "Please insert correct Email: ";
    cin.clear();
    cin >> email;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
    
  indi.email = email;

  cout << "Phone Number : ";
  cin >> phoneNumber;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(!is_phoneNumber_valid(phoneNumber)) {
    cout << "-------------------------------------" << endl;
    cout << "         Invalid Phone Number        " << endl;
    cout << "         Format '000-000-0000'       " << endl; 
    cout << "-------------------------------------" << endl;
    cout << "Please insert correct Phone Number: ";
    cin.clear();
    cin >> phoneNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  
  indi.phoneNum = phoneNumber;

  cout << "---------------------------------" << endl; 
  cout << "        Vaccination Status       " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Please insert options to continue" << endl;
  cout << "1) Never                         " << endl;
  cout << "2) Partial                       " << endl;
  cout << "3) Fully                         " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Please select Vaccination Status: ";
  cin >> userInput;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(userInput != 1 && userInput != 2 && userInput != 3){
    cin.clear();
    cout << "----------------------------------" << endl;
    cout << "Fail! Please Only Enter 1/ 2/ 3!  " << endl;
    cout << "----------------------------------" << endl;
    cout << "Please select Vaccination Status: ";
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  if (userInput == 1){
    indi.vacDetails = "Never";
  }
  else if(userInput == 2)
  {
    indi.vacDetails = "Partial";
  }
  else if(userInput == 3)
  {
    indi.vacDetails = "Fully";
  }
  
  cout << "---------------------------------" << endl; 
  cout << "           Risk Status           " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Please insert options to continue" << endl;
  cout << "1) Low                           " << endl;
  cout << "2) High                          " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Please select Risk Status: ";
  cin >> userInput;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(userInput != 1 && userInput != 2){
    cin.clear();
    cout << "----------------------------------" << endl;
    cout << "Fail! Please Only Enter 1 or 2!   " << endl;
    cout << "----------------------------------" << endl;
    cout << "Please select Risk Status: ";
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  if (userInput == 1){
    indi.riskStat = "Low";
  }
  else if(userInput == 2)
  {
    indi.riskStat = "High";
  }
  system("cls");

  cout << "--------------------------------" << endl; 
  cout << "    Registration Completed      " << endl; 
  cout << "--------------------------------" << endl; 
  cout << "Welcome " << indi.userDetails.name << endl;

  do 
  {
    cout << "---------------------------------" << endl; 
    cout << "            Home Page            " << endl; 
    cout << "---------------------------------" << endl; 
    cout << "Please insert options to continue" << endl;
    cout << "1) Update Individual Profile     " << endl;
    cout << "2) Manage Dependants             " << endl;
    cout << "3) Check in                      " << endl;
    cout << "4) History                       " << endl;
    cout << "5) Exit Application              " << endl;
    cout << "---------------------------------" << endl; 

    cin >> userOption;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");

    switch(userOption)
      {
        case 1 : updateProfile(); break;
        case 2 : manageDependants();  break;
        case 3 : checkIn(); break;
        case 4 : displayHistoryList(); break;
        case 5 : break;
        default:
          cout << "Please only key in 1, 2, 3, 4, or 5" << endl;   
          break;
      }
  } while (!(userOption == 5));

  system("cls");
  cout << "--------------------------------------" << endl;
  cout << "      Individual Logged Out!          " << endl;
  cout << "--------------------------------------" << endl;
}

int main() {

  int userLogin;
  
  cout << "-------------------------------" << endl;
  cout << "     WELCOME TO MYSEJAHTERA    " << endl;
  cout << "-------------------------------" << endl;
  
  do 
  {
    cout << "-------------------------------" << endl; 
    cout << "Please insert options to LOGIN " << endl;
    cout << "1) Individual                  " << endl;
    cout << "2) Admin                       " << endl;
    cout << "3) Exit Application            " << endl;
    cout << "-------------------------------" << endl; 

    cin >> userLogin;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    system("cls");

    switch(userLogin)
      {
        case 1 : indiFunction(); break;
        case 2 : adminFunction(); break;
        case 3 : break;
        default:
          cout << "Please only key in 1 or 2" << endl;   
          break;
      }
  } while (!(userLogin == 3));

  cout << "--------------------------------------" << endl;
  cout << "      Application Exit! Goodbye!      " << endl;
  cout << "--------------------------------------" << endl;

  return 0;
}