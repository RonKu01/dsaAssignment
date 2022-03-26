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
    cout << "4) Exit                          " << endl;
    cout << "---------------------------------" << endl; 
    
    cin >> userOption;
    cin.ignore();
    
    switch(userOption)
      {
        case 1 : {
          cout << "New Email : ";
          getline(cin, email);

          while(!is_email_valid(email)) {
            cout << "Invalid Email" << endl;
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
            cout << "Invalid Phone Number" << endl;
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

   if (rear == n - 1)
     cout<<"Failed : Reached Maximum Dependants (10)"<<endl;
   else {
      if (front == - 1) {
        front = 0; rear = 0; 
        cout << "Dependant Name: ";
        cin >> dep[front].depDetails.name;

        cout << "Dependant IC / Passport: ";
        cin >> dep[front].depDetails.icPassport;

        cout << "Dependant Address: ";
        cin >> dep[front].depDetails.address;

        cout << "Dependant Gender: ";
        cin >> dep[front].depDetails.gender;

        cout << "Relationship: ";
        cin >> dep[front].relation;

        cout << "Dependants Age: ";
        cin >> dep[front].age;
        
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
        cin >> dep[rear].depDetails.name;

        cout << "Dependant IC / Passport: ";
        cin >> dep[rear].depDetails.icPassport;

        cout << "Dependant Address: ";
        cin >> dep[rear].depDetails.address;

        cout << "Dependant Gender: ";
        cin >> dep[rear].depDetails.gender;

        cout << "Relationship: ";
        cin >> dep[rear].relation;

        cout << "Dependants Age: ";
        cin >> dep[rear].age;
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
        cout << "Note: Enter -1 to go back " << endl;
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
              cout << "Delete Succesfully! " << endl;
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
    cout << "3) Delete Dependants          " << endl;
    cout << "4) Exit                        " << endl;
    cout << "-------------------------------" << endl; 

    cin >> userOption2;
    
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
  string risk
){
  History* nHistory = new History;

  numberOfDependants = depNum;
  time_t now = time(0);
  tm *ltm = localtime(&now);

  nHistory->date = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year);

  nHistory->time = to_string(8+ltm -> tm_hour) + ":" + to_string(ltm -> tm_min) + ":" + to_string(ltm -> tm_sec);
  
  nHistory->est.venue = venue;
  nHistory->indi.userDetails.name = indiName;
  nHistory->indi.vacDetails = vacDetails;
  nHistory->indi.riskStat = risk;

  for (int i=0; i < depNum; i++){
    nHistory->dep[i].depDetails.name = (*(depPtr + i));
  }

  nHistory->nxtHistory = NULL;
  nHistory->nxtHistory = top;
  top = nHistory;
};

void checkIn(){

  int userOption = 0, userOption2, userOption3;
  int estCode;
  string venue;
  string depName[10];
  bool isConfirm = false;

  Establishment* est;
  est = getEstList();
  
  if (front >= 0) {

    cout << "Do you have dependants with you?" << endl;
    cout << "--------------------------------" << endl;
    cout << "(Yes: Y // No: N)" << endl; 

    char input = ' ';
    cin >> input;
    char upperInput = toupper(input);

    if(upperInput == 'Y')
    {
      displayDependants();

      do{
        cout << "Keyin the amount of dependants: ";
        cin >> userOption ;
        int arrDepVisited[userOption];
  
        //Validation Needed here for userOption
        for (int i=0; i < userOption; i++){
            cout << "Dependant " << i+1 << ": ";
            cin >> userOption2;
            arrDepVisited[i] = userOption2 - 1;
        }
  
        for (int n : arrDepVisited) {
          cout << "You are with " << dep[n].depDetails.name << "." << endl;

        }
        
        cout << "-----------------------------" << endl;
        cout << "Is this information correct?" << endl;
        cout << "(Yes: Y // No: N)" << endl; 
        char input2 = ' ';
        cin >> input2;
        char upperInput2 = toupper(input2);

        if (upperInput2 == 'Y'){
          isConfirm = true;
          for (int n : arrDepVisited) {
            depName[n] = dep[n].depDetails.name;
          }

          system("cls");
        }
        
      } while (!(isConfirm == true));
    }
  }

  // display est venue
  cout << "----------------" << endl;
  cout << "   Venue List   " << endl;
  cout << "----------------" << endl;
  
  for (int i=0; i <10; i ++){
    cout << est[i].code << "   " << est[i].venue << endl;
  }
  
  cout << "----------------" << endl;

  //Check In - Enter Code
  cout << "Insert Venue Code: "; 
  cin >> userOption3; 

  for (int i = 0; i < 10; i ++){
    if (userOption3 == (*(est + i)).code) {
      estCode = (*(est + i)).code;
      venue = (*(est + i)).venue; \

      system("cls");
      cout << "-------------------------------" << endl;
      cout << "     Check IN Successfully!    " << endl;
      cout << "-------------------------------" << endl;
      break;
      
    }
  }

  pushHistory(estCode, venue, indi.userDetails.name, depName, userOption, indi.vacDetails, indi.riskStat);

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
    if (numberOfDependants > 0){
      for (int i = 0; i < numberOfDependants; i++){
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
  cin.ignore();
  
  while(!is_icPassport_valid(icPassport)) {
    cout << "-----------------------------------" << endl;
    cout << "      Invalid IC Passport          " << endl;
    cout << "      Format '000000-00-0000'      " << endl; 
    cout << "-----------------------------------" << endl;
    cout << "Please insert correct IC Passport: ";
    cin.clear();
    cin >> icPassport;
    cin.ignore();
  }
  
  indi.userDetails.icPassport = icPassport;

  cout << "Address : ";
  getline(cin, indi.userDetails.address);

  cout << "Gender (M / F): ";
  cin >> gender;
  cin.ignore(100, '\n');

  while(gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f'){
    cin.clear();
    cout << "---------------------------------" << endl;
    cout << "Invalid! Only Enter (M / F) only!" << endl;
    cout << "---------------------------------" << endl;
    cout << "Please insert your Gender (M / F): ";
    cin >> gender;
    cin.ignore(100, '\n');
  }

  if (gender == 'M' || gender == 'm'){
    indi.userDetails.gender = "Male";
    cout << indi.userDetails.gender << endl;
  } else 
    if (gender == 'F' || gender == 'f'){
    indi.userDetails.gender = "Female";
  }
  
  cout << "Email : ";
  cin >> email;
  cin.ignore();

  while(!is_email_valid(email)) {
    cout << "-----------------------------" << endl;
    cout << "         Invalid Email       " << endl;
    cout << "   Format 'abc@example.com'  " << endl;    
    cout << "-----------------------------" << endl;
    cout << "Please insert correct Email: ";
    cin.clear();
    cin >> email;
    cin.ignore();
  }
    
  indi.email = email;

  cout << "Phone Number : ";
  cin >> phoneNumber;
  cin.ignore();

  while(!is_phoneNumber_valid(phoneNumber)) {
            cout << "-------------------------------------" << endl;
            cout << "         Invalid Phone Number        " << endl;
            cout << "         Format '000-000-0000'       " << endl; 
            cout << "-------------------------------------" << endl;
            cout << "Please insert correct Phone Number: ";
        		cin.clear();
            cin >> phoneNumber;
            cin.ignore();
          }
  
  indi.phoneNum = phoneNumber;

    cout << "Vaccination Status : ";
  getline(cin, indi.vacDetails);
  
//   do{
//     cout << "Vaccination Status :             " << endl;
//     cout << "---------------------------------" << endl; 
//     cout << "Please insert options to continue" << endl;
//     cout << "1) Never                         " << endl;
//     cout << "2) Partial                       " << endl;
//     cout << "3) Fully                         " << endl;
//     cout << "---------------------------------" << endl; 
//     cin >> userInput;

//     if(userInput == 1)
//     {
//       indi.vacDetails = "Never";
//     }
//     else if(userInput == 2)
//     {
//       indi.vacDetails = "Partial";
//     }
//     else if(userInput == 3)
//     {
//       indi.vacDetails = "Fully";
//     }
//     else{
//       cout << "Please only keyin 1,2 or 3 !" << endl; 
//     }
    
//   }while(!(userInput == 3));
  
//   getline(cin, indi.vacDetails);

  cout << "Risk Status : ";
  getline(cin, indi.riskStat);
  system("cls");

  cout << "--------------------------------" << endl; 
  cout << "    Registration Completed      " << endl; 
  cout << "--------------------------------" << endl; 
  cout << "Welcome " << indi.userDetails.name << endl;


  do 
  {
    cout << "---------------------------------" << endl; 
    cout << "Please insert options to continue" << endl;
    cout << "1) Update Individual Profile     " << endl;
    cout << "2) Manage Dependants             " << endl;
    cout << "3) Check in                      " << endl;
    cout << "4) History                       " << endl;
    cout << "5) Exit Application              " << endl;
    cout << "---------------------------------" << endl; 

    cin >> userOption;
    cin.ignore();
    system("cls");

    switch(userOption)
      {
        case 1 : updateProfile(); break;
        case 2 : manageDependants(); system("cls"); break;
        case 3 : checkIn(); break;
        case 4 : displayHistoryList(); break;
        case 5 : break;
        default:
          cout << "Please only key in 1, 2, 3, 4, or 5" << endl;   
          break;
      }
  } while (!(userOption == 5));

  // system("cls");
  cout << "--------------------------------------" << endl;
  cout << "      Application Ended! Goodbye!     " << endl;
  cout << "--------------------------------------" << endl;
}

int main() {
  
  //Add admin at the start
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
    cout << "-------------------------------" << endl; 

    cin >> userLogin;
    cin.ignore();
    
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

  return 0;
}