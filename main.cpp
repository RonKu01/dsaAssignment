#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <regex>
#include <iomanip>

using namespace std;
const int depArrSize = 10;

struct User{
  string icPassport;
  string name;
  string address;
  string gender;
  int age; 
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

struct Person {
  string venue;
  string name;
  string date;
  string time;
  string dependants;
  string vacStatus;
  string riskStatus;
  int timeDiff;
};

Individual indi;
Dependants dep[10];
int n = 10, front = - 1, rear = - 1;
int numberOfDependants = 0; int amountOfVictimHistory = 0; int amountOfContact = 0;

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

bool is_date_valid(const string& date)
{
   // define a regular expression
    const std::regex pattern
    ("\\b\\d{2}[-]\\d{2}[-]\\d{4}\\b");

   // try to match the string with the regular expression
   return std::regex_match(date, pattern);
}

bool is_time_valid(const string& time)
{
   // define a regular expression
    const std::regex pattern
    ("(?:[01]\\d|2[0-3]):(?:[0-5]\\d):(?:[0-5]\\d)");

   return std::regex_match(time, pattern);
}

Establishment* getEstList(){
  Establishment est;
  static Establishment estList[10];

  int i = 0;
  ifstream file("establishment.txt");
  while( file >> est.code >> est.venue)
  {
    estList[i].code = est.code;
    estList[i].venue = est.venue;
    i++;
  }
  file.close();
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
  cout << "Age         : " << indi.userDetails.age << endl;
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
  cout << "Venue   List    " << endl; 
  cout << "----------------" << endl;
  
  for (int i=0; i <10; i ++){
    cout << left << setw(7) << setfill(' ') << est[i].code 
         << left << setw(8) << setfill(' ') << est[i].venue << endl;
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
    cout << "----------------------------------------------------" << endl;
    cout << "          You do not have any dependants!           " << endl;
    cout << "----------------------------------------------------" << endl;
  } else 
    
  // Display List of Dependant
  { 
    system("cls");
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "                               Dependants List                           " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "No  Name      IC/Passport    Address          Gender  Dependants     Age " << endl; 
    
    
    for (int i = 0; i <= rear; i++) {
      cout << left << setw(4) << setfill(' ') << i+1   
           << left << setw(10) << setfill(' ') << dep[i].depDetails.name  
           << left << setw(15) << setfill(' ') << dep[i].depDetails.icPassport 
           << left << setw(17) << setfill(' ') << dep[i].depDetails.address
           << left << setw(8) << setfill(' ') << dep[i].depDetails.gender  
           << left << setw(15) << setfill(' ') << dep[i].relation 
           << left << setw(4) << setfill(' ') << dep[i].depDetails.age 
           << endl;
    }

    cout << "-------------------------------------------------------------------------" << endl;
  }
}

void addDependants() {
  string depIcPassport, gender; 
  char depGender;
  int userInput, depAge;
  bool isValidAge = false;
  bool isValidDep = false; 

   if (rear == n - 1)
     cout<<"Failed : Reached Maximum Dependants (10)"<<endl;
   else {
      if (front == - 1) {
        front = 0; rear = 0; 
        cout << "-----------------------------------" << endl;
        cout << "         Dependants Details        " << endl; 
        cout << "-----------------------------------" << endl;
        cout << "Dependant Name         : ";
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

        cout << "Dependant Address      : ";
        getline(cin, dep[front].depDetails.address);


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
        cout << "4) Parents                       " << endl;
        cout << "5) Grandparents                  " << endl;
        cout << "6) Guardian                      " << endl;
        cout << "7) Others                        " << endl;
        cout << "---------------------------------" << endl;
        cout << "Input                  : ";

       do{
          cin >> userInput;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---------------------------" << endl;
            cout << "Please insert number only! " << endl;
            cout << "---------------------------" << endl; 
            cout << "Input: ";
          }else{
                if(userInput == 1){
                  dep[front].relation = "Spouse";
                  isValidDep = true;
                }
                else if(userInput == 2){
                  dep[front].relation = "Child";
                  isValidDep = true;
                }
                else if(userInput == 3){
                  dep[front].relation = "Siblings";
                  isValidDep = true;
                }
                else if(userInput == 4){
                  dep[front].relation = "Parents";
                  isValidDep = true;
                }
                else if(userInput == 5){
                  dep[front].relation = "Grandparents";
                  isValidDep = true;
                }
                else if(userInput == 6){
                  dep[front].relation = "Guardian";
                  isValidDep = true;
                }
                else if(userInput == 7){
                  dep[front].relation = "Others";
                  isValidDep = true;
                }
                else if(userInput != 1 && userInput !=2 && userInput !=3 && userInput !=4 && userInput !=5 && userInput !=6 && userInput !=7){
                  cin.clear();
                  cout << "----------------------------------" << endl;
                  cout << "   Fail! Please Reselect Again!   " << endl;
                  cout << "----------------------------------" << endl;
                  cout << "Input: ";
                }
            } 
       }while(!(isValidDep == true));       

      cout << "Dependants Age         : ";
        do{
          cin >> depAge;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          
          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---------------------------" << endl;
            cout << "Please insert number only! " << endl;
            cout << "---------------------------" << endl;
            cout << "Dependants Age: ";
          }else {
            if (depAge >= 0 && depAge <= 120){
              isValidAge = true;
            } else {
              cout << "---------------------------" << endl;
              cout << "        Invalid Age!       " << endl;
              cout << "---------------------------" << endl; 
              cout << "Please insert again: ";
            }
          } 
        }while(!(isValidAge == true));
        
        dep[front].depDetails.age = depAge;
    
        dep[rear].depDetails.name = dep[front].depDetails.name;
        dep[rear].depDetails.icPassport = dep[front].depDetails.icPassport;
        dep[rear].depDetails.address = dep[front].depDetails.address;
        dep[rear].depDetails.gender = dep[front].depDetails.gender;
        dep[rear].relation = dep[front].relation;
        dep[rear].depDetails.age = dep[front].depDetails.age;

        
        system("cls");
        cout << "-------------------------------" << endl;
        cout << "Dependants Successfully Added!" << endl;
        cout << "-------------------------------" << endl;
      } else {
        rear = rear + 1;
        cout << "-----------------------------------" << endl;
        cout << "         Dependants Details        " << endl; 
        cout << "-----------------------------------" << endl;
        cout << "Dependant Name         : ";
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

        cout << "Dependant Address      : ";
        getline(cin, dep[rear].depDetails.address);

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
        cout << "4) Parents                       " << endl;
        cout << "5) Grandparents                  " << endl;
        cout << "6) Guardian                      " << endl;
        cout << "7) Others                        " << endl;
        cout << "---------------------------------" << endl;
        cout << "Input: ";
        
        do{
          cin >> userInput;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---------------------------" << endl;
            cout << "Please insert number only! " << endl;
            cout << "---------------------------" << endl; 
            cout << "Input: ";
          }else{
                if(userInput == 1){
                  dep[rear].relation = "Spouse";
                  isValidDep = true;
                }
                else if(userInput == 2){
                  dep[rear].relation = "Child";
                  isValidDep = true;
                }
                else if(userInput == 3){
                  dep[rear].relation = "Siblings";
                  isValidDep = true;
                }
                else if(userInput == 4){
                  dep[rear].relation = "Parents";
                  isValidDep = true;
                }
                else if(userInput == 5){
                  dep[rear].relation = "Grandparents";
                  isValidDep = true;
                }
                else if(userInput == 6){
                  dep[rear].relation = "Guardian";
                  isValidDep = true;
                }
                else if(userInput == 7){
                  dep[rear].relation = "Others";
                  isValidDep = true;
                }
                else if(userInput != 1 && userInput !=2 && userInput !=3 && userInput !=4 && userInput !=5 && userInput !=6 && userInput !=7){
                  cin.clear();
                  cout << "----------------------------------" << endl;
                  cout << "   Fail! Please Reselect Again!   " << endl;
                  cout << "----------------------------------" << endl;
                  cout << "Input: ";
                }
            } 
       }while(!(isValidDep == true));  
        
        cout << "Dependants Age         : ";
        do{
          cin >> depAge;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          
          if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---------------------------" << endl;
            cout << "Please insert number only! " << endl;
            cout << "---------------------------" << endl; 
            cout << "Dependants Age: ";
          }else {
            if (depAge >= 0 && depAge <= 120){
              isValidAge = true;
            } else {
              cout << "---------------------------" << endl;
              cout << "        Invalid Age!       " << endl;
              cout << "---------------------------" << endl; 
              cout << "Please insert again: ";
            }
          } 
        }while(!(isValidAge == true));
        
        dep[rear].depDetails.age = depAge;

        system("cls");

        cout << "-------------------------------" << endl;
        cout << "Dependants Successfully Added!" << endl;
        cout << "-------------------------------" << endl;
      }
   }
}

void deleteDependants(){
   if (front == - 1) {
     system("cls");
     cout << "-------------------------------" << endl;
     cout << "You do not have any dependants!" << endl;
     cout << "-------------------------------" << endl;
   }else {
      int depDelete;
      do{
        displayDependants();
        cout << "--------------------------------------" << endl;
        cout << "Which dependant do you want to delete?" << endl;
        cout << "Note: Enter -1 to go back             " << endl;
        cout << "--------------------------------------" << endl;
        cout << "Number: "; 
        cin >> depDelete;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "---------------------------" << endl;
            cout << "Err : Please insert number! " << endl;
            cout << "---------------------------" << endl; 
        } else {
            if(depDelete == -1)
            {
              system("cls");
              break;
            } else {
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
                  dep[i].depDetails.age = dep[i+1].depDetails.age;
                }

                system("cls");
                cout << "--------------------------------------" << endl;
                cout << "         Delete Succesfully!          " << endl;
                cout << "--------------------------------------" << endl;
                rear--;

                if (rear == -1) {
                  front = -1;
                }
                
                break;
              }
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
    system("cls");
    
    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      cout << "Please only key in 1, 2, 3, or 4" << endl;
    } else {
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

void writeFile(){

  History* nav = top;
  ofstream vFile("covid_victim.txt", ofstream::trunc);

  if (vFile.is_open()){

    vFile << "KFC Green 01-04-2022 11:20:00 Ryzen Fully Low" << endl 
          << "Campus Green 25-02-2022 08:00:00 Ryzen Fully Low" << endl
          << "KFC Blue 01-04-2022 11:00:00 Peter Fully Low" << endl
          << "MCD Blue 25-02-2022 10:56:00 - Fully Low" << endl
          << "Campus Blue 25-02-2022 08:00:00 Peter Fully Low" << endl
          << "KFC Pink 01-04-2022 12:30:00 Kelvin Fully Low" << endl
          << "MCD Pink 25-02-2022 10:30:00 Kelvin Fully Low" << endl
          << "Campus Pink 25-02-2022 08:00:00 Kelvin Fully Low" << endl;

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

      string indiNames = nav->indi.userDetails.name;
      indiNames.erase(remove(indiNames.begin(), indiNames.end(), ' '), indiNames.end());
      depNames.erase(remove(depNames.begin(), depNames.end(), ' '), depNames.end());

      string strDate = nav->date;

      std::vector<int> vect;
      std::stringstream ss(strDate);

      for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == '-')
            ss.ignore();
      }

      string writeDay = ""; string writeMonth = ""; string writeYear = "";

      if (vect[0] < 10) {
        writeDay = "0" + to_string(vect[0]);
      } else {
        writeDay = to_string(vect[0]);
      }

      if (vect[1] < 10) {
        writeMonth = "0" + to_string(vect[1]);
      } else {
        writeMonth = to_string(vect[1]);
      }

      if (vect[2] < 10) {
        writeYear = "0" + to_string(vect[2]);
      } else {
        writeYear = to_string(vect[2]);
      }


    string strTime = nav->time;

    std::vector<int> vect2;
    std::stringstream ss2(strTime);

    for (int i; ss2 >> i;) {
      vect2.push_back(i);
      if (ss2.peek() == ':')
          ss2.ignore();
    }

    string writeSec = ""; string writeMin = ""; string writeHour = "";

    if (vect2[0] < 10) {
      writeHour = "0" + to_string(vect2[0]);
    } else {
      writeHour = to_string(vect2[0]);
    }

    if (vect2[1] < 10) {
      writeMin = "0" + to_string(vect2[1]);
    } else {
      writeMin = to_string(vect2[1]);
    }

    if (vect2[2] < 10) {
      writeSec = "0" + to_string(vect2[2]);
    } else {
      writeSec = to_string(vect2[2]);
    }

      vFile << nav->est.venue << " "
            << indiNames << " "
            << writeDay << "-" << writeMonth << "-" << writeYear << " "
            << writeHour << ":" << writeMin << ":" << writeSec << " "
            << depNames << " " 
            << nav->indi.vacDetails << " "
            << nav->indi.riskStat << endl;

      nav = nav -> nxtHistory;
    }

    vFile.close();
  }
}

void checkIn(){

  int userOption = 0, userOption2, userOption3;
  int estCode;
  string venue, checkInDate, checkInTime;
  string depName[10];
  bool isConfirm = false; bool isValidVenue = false;

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
         bool isValidDep = false; bool NoDep = false;
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
              // User Option > amount of dependants 
              if ((userOption-1) <= rear){
                isValidDep = true;
              } else if ((userOption-1) <= 0) {
                NoDep = true;
                break;
              } else {
                cout << "You only have " << (rear+1) << " dependant(s)!" << endl;
                cout << "Keyin the amount of dependants: ";
              }
            }
          }while(!(isValidDep == true));

          if (NoDep == true) {
            system("cls");
            break;
          } else {
            int arrDepVisited[userOption]; bool isNew = true;  int x = 0; 

            for (int i = 0; i < userOption; i++){
              x=0;
              cout << "Dependant " << i+1 << ": ";
              cin >> userOption2;
              cin.ignore(numeric_limits<streamsize>::max(), '\n');

              if (cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                i--;
                cout << "Please insert Dependant Index!" << endl;
              } else {
                int selectedDep = userOption2 - 1;

                while(x < i) {
                  if (arrDepVisited[x] == selectedDep) {
                    isNew = false;
                    cout << "Index " << selectedDep + 1 << " dependant has already selected" << endl;
                    cout << "RE-enter with ANOTHER dependants again!" << endl;
                    cout << "---------------------------------------------------" << endl;
                    i--;
                  }
                  x++;
                } 

                if (isNew){
                  arrDepVisited[i] = selectedDep;
                }
                isNew = true;
              }
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
          }
      } while (!(isConfirm == true));
    }
  }
  system("cls");
  displayEst();
  cout << "(Press -1 to cancel CheckIN) " << endl; 
  cout << "Insert Venue Code: "; 

  do{
    cin >> userOption3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      displayEst();
      cout << "(Press -1 to cancel login) "; 
      cout << "Please insert Venue Index!" << endl;
      cout << "Insert Venue Code: ";
    }else {
      if (userOption3 >= 101 && userOption3 <= 110){
        isValidVenue = true;
      } else {
        if (userOption3 == -1){
          return;
        } else {
          system("cls");
          displayEst();
          cout << "Please insert valid Venue" << endl;
          cout << "Insert Venue Code: ";
        }
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

      cout << "Venue      : " << venue << endl; 
      cout << "Name       : " << indi.userDetails.name << endl;
      cout << "Date       : " << checkInDate << endl;
      cout << "Time       : " << checkInTime << endl;
      cout << "Dependants : " << depNames << endl;
      cout << "Vaccination: " <<indi.vacDetails << endl;
      cout << "Risk       : " <<indi.riskStat << endl;
      break;
    }
  }

  pushHistory(estCode, venue, indi.userDetails.name, depName, userOption, indi.vacDetails, indi.riskStat, checkInDate, checkInTime);
  writeFile();
}

void displayHistoryList() {

  if (top == NULL)
  {
    cout << "History is empty" << endl;
    return;
  }

  History* nav = top;
  
  cout << "------------------------------------------------------------------------------------" << endl;
  cout << "                                      History Log                                   " << endl;
  cout << "------------------------------------------------------------------------------------" << endl;
  cout << "Venue   FullName     Date       Time      Dependants          VacStatus   RiskStatus" << endl; 

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

    cout << left << setw(8) << setfill(' ') << nav->est.venue 
         << left << setw(13) << setfill(' ') << nav->indi.userDetails.name
         << left << setw(11) << setfill(' ') << nav->date
         << left << setw(10) << setfill(' ') << nav->time
         << left << setw(20) << setfill(' ') << depNames
         << left << setw(12) << setfill(' ') << nav->indi.vacDetails
         << left << setw(10) << setfill(' ') << nav->indi.riskStat << endl; 
  
    nav = nav -> nxtHistory;
  }
  cout << "------------------------------------------------------------------------------------" << endl;
}; 

void indiFunction(){
  int userOption, userInput, age;
  string icPassport, email, phoneNumber; 
  char gender;
  bool isValidAge = false; 
  bool isValidVaccine = false;
  bool isValidRisk = false;
  
  cout << "-------------------------------" << endl;
  cout << "       Register Account        " << endl;
  cout << "(Please insert correct details)" << endl;
  cout << "-------------------------------" << endl;

  cout << "Full Name     : ";
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

  cout << "Address       : ";
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
  
  cout << "Age           : ";
  do{
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "---------------------------" << endl;
      cout << "Please insert number only! " << endl;
      cout << "---------------------------" << endl; 
      cout << "Input: ";
    }else{
      if (age >=0 && age <= 120){
        isValidAge = true;
      }
      else{
        cout << "---------------------------" << endl;
        cout << "        Invalid Age!       " << endl;
        cout << "---------------------------" << endl; 
        cout << "Input: ";
      }
    }
  }while(!(isValidAge == true));
  
  indi.userDetails.age = age;

  cout << "Email         : ";
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
 
  cout << "Phone Number  : ";
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
  cout << "Vaccination Status: ";

  do{
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "---------------------------" << endl;
      cout << "Please insert number only! " << endl;
      cout << "---------------------------" << endl; 
      cout << "Input: ";
    }else{
      if (userInput == 1){
        indi.vacDetails = "Never";
        isValidVaccine = true;
      }
      else if(userInput == 2)
      {
        indi.vacDetails = "Partial";
        isValidVaccine = true;
      }
      else if(userInput == 3)
      {
        indi.vacDetails = "Fully";
        isValidVaccine = true;
      }
      else if(userInput != 1 && userInput != 2 && userInput != 3){
        cin.clear();
        cout << "----------------------------------" << endl;
        cout << "Fail! Please Only Enter 1/ 2/ 3!  " << endl;
        cout << "----------------------------------" << endl;
        cout << "Input: ";
      }
    }
  }while(!(isValidVaccine == true));
  
  cout << "---------------------------------" << endl; 
  cout << "           Risk Status           " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Please insert options to continue" << endl;
  cout << "1) Low                           " << endl;
  cout << "2) High                          " << endl;
  cout << "---------------------------------" << endl; 
  cout << "Risk Status: ";

  do{
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "---------------------------" << endl;
      cout << "Please insert number only! " << endl;
      cout << "---------------------------" << endl; 
      cout << "Input: ";
    }else{
      if (userInput == 1){
        indi.riskStat = "Low";
        isValidRisk = true;
      }
      else if(userInput == 2)
      {
        indi.riskStat = "High";
        isValidRisk = true;
      }
      else if(userInput != 1 && userInput != 2){
        cin.clear();
        cout << "----------------------------------" << endl;
        cout << "Fail! Please Only Enter 1 or 2!   " << endl;
        cout << "----------------------------------" << endl;
        cout << "Input: ";
      }
    }

  }while(!(isValidRisk == true));
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
    cout << "5) Logout                        " << endl;
    cout << "---------------------------------" << endl; 

    cin >> userOption;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      cout << "Please only key in 1, 2, 3, 4, or 5" << endl;   
    } else {
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
    }
  } while (!(userOption == 5));

  system("cls");
  cout << "--------------------------------------" << endl;
  cout << "      Individual Logged Out!          " << endl;
  cout << "--------------------------------------" << endl;
}

Person* getCovidPatHistory(){
  Person covidPat;
  static Person covidPatHistory[20];

  int i = 0;
  ifstream file("covid_pat.txt");
  while( file >> covidPat.venue >> covidPat.name >> covidPat.date >> covidPat.time >> covidPat.dependants >> covidPat.vacStatus >> covidPat.riskStatus)
  {
    covidPatHistory[i].venue = covidPat.venue;
    covidPatHistory[i].name = covidPat.name;
    covidPatHistory[i].date = covidPat.date;
    covidPatHistory[i].time = covidPat.time;
    covidPatHistory[i].dependants = covidPat.dependants;
    covidPatHistory[i].vacStatus = covidPat.vacStatus;
    covidPatHistory[i].riskStatus = covidPat.riskStatus;
    i++;
  }
  file.close();
  return covidPatHistory;
}

Person* getVictimHistory(){
  Person victim;
  static Person victimHistory[50];

  int i = 0;
  ifstream file("covid_victim.txt");
  while( file >> victim.venue >> victim.name >> victim.date >> victim.time >> victim.dependants >> victim.vacStatus >> victim.riskStatus)
  {
    victimHistory[i].venue = victim.venue;
    victimHistory[i].name = victim.name;
    victimHistory[i].date = victim.date;
    victimHistory[i].time = victim.time;
    victimHistory[i].dependants = victim.dependants;
    victimHistory[i].vacStatus = victim.vacStatus;
    victimHistory[i].riskStatus = victim.riskStatus;
    i++;
    amountOfVictimHistory++;
  }
  file.close();
  return victimHistory;
}

int linearSearchRisk(Person history[], int size, string searchValue){
 
  for(int i = 0; i < size; i ++){
    int k = searchValue.compare(history[i].riskStatus);

    if (k == 0){
      return i;
    }
  }

  return -1;
}

int* linearSearchVenue(Person history[], int size, string searchValue){

  static int victimIndex[50]; 

  for(int i = 0; i < size; i ++){
    int k = searchValue.compare(history[i].venue);

    if (k == 0){
      victimIndex[amountOfContact] = i;
      amountOfContact++;
    }
  }

  return victimIndex;
}

Person* arrSorting(Person history[], int size) {
  int i, j, min, timeDiff;
  string venue, name, date, time, dependants, vacStatus, riskStatus;

  for (i = 0; i < size; i++) {
    for (j = i+1; j < size; j++){
      if (history[j].timeDiff < history[min].timeDiff){

        timeDiff = history[i].timeDiff;
        venue = history[i].venue;
        name = history[i].name;
        date = history[i].date;
        time = history[i].time;
        dependants = history[i].dependants;
        vacStatus = history[i].vacStatus;
        riskStatus = history[i].riskStatus;

        history[i].venue = history[j].venue;
        history[i].name = history[j].name;
        history[i].date = history[j].date;
        history[i].time = history[j].time;
        history[i].dependants = history[j].dependants;
        history[i].vacStatus = history[j].vacStatus;
        history[i].riskStatus = history[j].riskStatus;

        history[j].venue = venue;
        history[j].name = name;
        history[j].date = date;
        history[j].time = time;
        history[j].dependants = dependants;
        history[j].vacStatus = vacStatus;
        history[j].riskStatus = riskStatus;
      }
    }
  }

  return history;
}

void adminFunction(){
  bool isHighRisk = false; bool isValidVenue = false; 
  string risk, venue, date, time; 
  int counterContactHistory = 0;
  Person* covidPat; Person* victim; Person* sortedHistory; Person contactHistory[50];

  amountOfContact = 0;
  amountOfVictimHistory = 0;

  covidPat = getCovidPatHistory();
  victim = getVictimHistory();

  cout << "-------------------------------------" << endl;
  cout << "         WELCOME TO ADMIN PAGE       " << endl;
  cout << "-------------------------------------" << endl;

  do{
    cout << "What are you looking for (Note: High) : ";
    cin >> risk;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "---------------------------" << endl;
      cout << "Please insert 'High' only! " << endl;
      cout << "---------------------------" << endl; 
      cout << "Input: ";
    }else{

      if (risk == "High"){
        isHighRisk = true;
      } else{
        cin.clear();
        cout << "----------------------------------" << endl;
        cout << "   Please insert 'High' only!     " << endl;
        cout << "----------------------------------" << endl;
      }
    }

  }while(!(isHighRisk == true));

  int result = linearSearchRisk(covidPat, 2, risk);

  if(result >= 0){
    system("cls");

    cout << "------------------------------" << endl;
    cout << "    High Risk Person Found!   " << endl;
    cout << "------------------------------" << endl;
    cout << "Person Name : " << covidPat[result].name << endl;
    cout << "Venue       : " << covidPat[result].venue << endl;
    cout << "Date        : " << covidPat[result].date << endl;
    cout << "Time        : " << covidPat[result].time << endl;
    cout << "Dependnts   : " << covidPat[result].dependants << endl;
    cout << "Risk Status : " << covidPat[result].riskStatus << endl;
    cout << "Vac Status  : " << covidPat[result].vacStatus << endl;
  }

  do{
    cout << "--------------------------------" << endl;
    cout << "Please insert High Risk Details! " << endl;
    cout << "--------------------------------" << endl; 
    cout << "Insert Venue: ";
    cin >> venue;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "---------------------------" << endl;
      cout << "Please insert Valid Venue! " << endl;
      cout << "---------------------------" << endl; 
      cout << "Insert Venue: ";
    }else{
      if (venue == covidPat[result].venue){
        isValidVenue = true;
      } else {
        system("cls");
        cout << "-------------------------------" << endl;
        cout << "  Only insert High Risk Venue! " << endl;
        cout << "-------------------------------" << endl;
        cout << "Person Name : " << covidPat[result].name << endl;
        cout << "Venue       : " << covidPat[result].venue << endl;
        cout << "Date        : " << covidPat[result].date << endl;
        cout << "Time        : " << covidPat[result].time << endl;
        cout << "Dependnts   : " << covidPat[result].dependants << endl;
        cout << "Risk Status : " << covidPat[result].riskStatus << endl;
        cout << "Vac Status  : " << covidPat[result].vacStatus << endl;
      }
    }

  }while(!(isValidVenue == true));

  int* data;
  data = linearSearchVenue(victim, amountOfVictimHistory, venue);

  cout << "Insert Date : ";
  cin >> date;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(!is_date_valid(date) || date != covidPat[result].date){
    cout << "-----------------------------------" << endl;
    cout << "           Invalid Date            " << endl;
    cout << "        Format 'DD-MM-YYYY'        " << endl; 
    cout << "-----------------------------------" << endl;
    cout << "Please insert Detected Date: ";
    cin.clear();
    cin >> date;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  cout << "Insert Time : ";
  cin >> time;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  while(!is_time_valid(time) || time != covidPat[result].time){
    cout << "-----------------------------------" << endl;
    cout << "           Invalid Time            " << endl;
    cout << "        Format 'HH:MM:SS'        " << endl; 
    cout << "-----------------------------------" << endl;
    cout << "Please insert Detected Time: ";
    cin.clear();
    cin >> time;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  string covidHour = time.substr(0,2);
  string covidMin = time.substr(3,2);
  string covidSec = time.substr(6,2);

  int covidTime = stoi(covidHour)*3600 + stoi(covidMin)*60 + stoi(covidSec);

  for (int i = 0; i < amountOfContact; i ++){
    if (date == (victim[data[i]].date)){

      string victimHour = (victim[data[i]].time).substr(0,2);
      string victimMin = (victim[data[i]].time).substr(3,2);
      string victimSec = (victim[data[i]].time).substr(6,2);

      int victimTime = stoi(victimHour)*3600 + stoi(victimMin)*60 + stoi(victimSec);
      int timeDiff = victimTime - covidTime;

      if (timeDiff <= 3600) {

        // victim[data[counterContactHistory]].riskStatus = "Close";
        contactHistory[counterContactHistory].name = victim[data[i]].name;
        contactHistory[counterContactHistory].venue = victim[data[i]].venue;
        contactHistory[counterContactHistory].date = victim[data[i]].date;
        contactHistory[counterContactHistory].time = victim[data[i]].time;
        contactHistory[counterContactHistory].dependants = victim[data[i]].dependants;
        contactHistory[counterContactHistory].vacStatus = victim[data[i]].vacStatus;
        contactHistory[counterContactHistory].riskStatus = "Close";
        contactHistory[counterContactHistory].timeDiff = timeDiff;
        counterContactHistory++;
        
      } else if (timeDiff <= 7200){
        // victim[data[counterContactHistory]].riskStatus = "Casual";
        contactHistory[counterContactHistory].name = victim[data[i]].name;
        contactHistory[counterContactHistory].venue = victim[data[i]].venue;
        contactHistory[counterContactHistory].date = victim[data[i]].date;
        contactHistory[counterContactHistory].time = victim[data[i]].time;
        contactHistory[counterContactHistory].dependants = victim[data[i]].dependants;
        contactHistory[counterContactHistory].vacStatus = victim[data[i]].vacStatus;
        contactHistory[counterContactHistory].riskStatus = "Casual";
        contactHistory[counterContactHistory].timeDiff = timeDiff;
        counterContactHistory++;
      } else {
        victim[data[counterContactHistory]].riskStatus = "Test";
      }
    }
  }

  sortedHistory = arrSorting(contactHistory, counterContactHistory);

  system("cls");
  
  cout << "Displaying Potential Covid Chain!" << endl;
  cout << "---------------------------------------------------------------------------------------" << endl;
  cout << "Venue   Name        Date        Time      Dependants     Vaccination       Risk Status " << endl;
  cout << "---------------------------------------------------------------------------------------" << endl;

  for (int i=0; i< counterContactHistory; i ++) {
    cout << left << setw(8) << setfill(' ') << sortedHistory[i].venue 
         << left << setw(12) << setfill(' ') << sortedHistory[i].name 
         << left << setw(12) << setfill(' ') << sortedHistory[i].date 
         << left << setw(10) << setfill(' ') << sortedHistory[i].time 
         << left << setw(15) << setfill(' ') << sortedHistory[i].dependants
         << left << setw(18) << setfill(' ') << sortedHistory[i].vacStatus 
         << left << setw(12) << setfill(' ') << sortedHistory[i].riskStatus << endl;
  }
  cout << "---------------------------------------------------------------------------------------" << endl;
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
    
    if(cin.fail()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      cout << "-----------------------------" << endl; 
      cout << "Please only key in 1, 2 or 3!" << endl;   
      cout << "-----------------------------" << endl;    
    } else {
      system("cls");
      switch(userLogin)
      {
        case 1 : indiFunction(); break;
        case 2 : adminFunction(); break;
        case 3 : break;
        default:
          cout << "-----------------------------" << endl; 
          cout << "Please only key in 1, 2 or 3!" << endl;   
          cout << "-----------------------------" << endl; 
          break;
      }
    }
  } while (!(userLogin == 3));

  cout << "--------------------------------------" << endl;
  cout << "      Application Exit! Goodbye!      " << endl;
  cout << "--------------------------------------" << endl;

  return 0;
}