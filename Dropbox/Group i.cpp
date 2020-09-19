#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <time.h>
#include <stdio.h>
using namespace std;

int day = 0;
bool headerprinted = false;
string		filename;
string		filepath;
ofstream	fout;
ifstream print;

void Patientfile();
void MainMenu();
void MS1();
void MS2();
void MS3();
void LOGIN();
void Printfile();


// Function to get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


int main(){
	
LOGIN();

}


void LOGIN(){
system ("CLS");

	string username,cmpuser;
	string password,cmppass;
	
	ifstream comparelogin;
	comparelogin.open("C:\\Dropbox\\HealthSystem\\Admins\\admin.txt");
	
	cout<<"Enter Admin Username: ";
	cin>>username;
	
	cout<<"Enter Admin Password: ";
	cin>>password;

while (!(comparelogin.eof())){
	comparelogin>>cmpuser;
	comparelogin>>cmppass;
	
	if ((username==cmpuser)&&(password==cmppass))
		Patientfile();    //if correct password then open file for patient.		
	}

cout<<"Wrong credentials\n\n";
system("PAUSE");
system ("CLS");
LOGIN();

}

void MainMenu() //Main Menu screen
{	
system ("CLS");	
headerprinted = false;
	int select;
	system ("CLS");
	cout<<"\n========= Welcome to Frontis Health Management System =========";
	cout<<"\n====                                                       ====";
	cout<<"\n====   Please Select An option:                            ====";
	cout<<"\n====        1. BP , ECG and Pulse Rate Monitoring System   ====";
	cout<<"\n====        2. Suger Level Monitoring                      ====";
	cout<<"\n====        3. Body Tempreture Monitoring                  ====";
	cout<<"\n====        4. Compare data                                ====";
	cout<<"\n====        5. Change Profile                              ====";
	cout<<"\n====        6. Exit                                        ====";
	cout<<"\n===============================================================\n\n";
		cout<<"     Pateint Profile:"<<filename<<endl;
		cout<<"		Selection: ";
		cin>>select;
			if (select < 1 || select > 6) 
				MainMenu();
	
	

	
	switch (select){
		case 1 :
				MS1();
				break;
				
		case 2 :
				MS2();
				break;
				
		case 3 :
				MS3();
				break;
		case 4 :
				 Printfile();
				 break;		
		case 5 :
				 Patientfile();
				 break;
		case 6 :
				 exit(0);
				 break;				
				}
				
		
	
	}
	
void Patientfile(){
	
fout.close();
system ("CLS");
	
	string 		Name,cmpName;
	char 		ans;
	int 		flag = 0;
	
	
	
	ifstream	cmppatient;
	cmppatient.open("C:\\Dropbox\\HealthSystem\\Patients\\Patients List\\list.txt");
	
	do{
	cout<<"Add New Patient(Y/N) ? ";
	cin>>ans;
	system ("CLS");
	ans = toupper(ans);
	}while((ans !='N') && (ans !='Y'));
	
	
	
	if (ans == 'Y'){
		cout<<"Enter new patient name: ";
		cin>>Name;
		while (!(cmppatient.eof())){
			
			getline(cmppatient, cmpName);
			
			if (Name == cmpName){
			Name 	 = Name + "0";        // compiler issue.
			filename = Name;
			}
		else
			filename = Name;	
			
    	}
    	
    ofstream	addpatient;
	addpatient.open("C:\\Dropbox\\HealthSystem\\Patients\\Patients List\\list.txt",std::fstream::app); //std::fstream::app  //open for append
	addpatient <<filename<<endl; 
	addpatient.close();
    	
    
}
	
	if (ans == 'N'){
		int i =1;
		string pName; //to print name
		
		cout<<"Select Profile: \n\n";
		while (!(cmppatient.eof())){
			getline(cmppatient, pName);
				if(cmppatient.eof())
					break;
			cout<<"	"<<i<<". "<<pName<<endl;
			i += 1;
		
		
		}
		cmppatient.close();
		cmppatient.open("C:\\Dropbox\\HealthSystem\\Patients\\Patients List\\list.txt");

		
		cout<<"\nEnter Patient name: ";
		cin>>Name;
		
		
		while (!(cmppatient.eof())){
			getline(cmppatient, cmpName);
			if (Name == cmpName){		//Check if the name is in the file.
				filename = Name;
				flag = 0;
				break;				//has to exit loop now.
				}				 
			else
				flag = 1;			//follow up if statement
		}	
				
		if (flag == 1){
			cout<<"Patient Not found !\n\n";		//else if no names on the whole list then,	
			system("PAUSE");
			
			cmppatient.close();						//tell admin and then repeat void function.
			Patientfile();
		}
	}
	


	//its time to open the text file for that patient!
	
	
	
	filepath = "C:\\Dropbox\\HealthSystem\\Patients\\Patient Data\\";
	filepath.append(filename);
	filepath.append(".txt");
	

	fout.open(filepath.c_str(),ios::app);     //THE FILE IS OPEN!        
	cout<<"File Name: "<<filename<<".txt is open\n\n";
	system("PAUSE");
	MainMenu();

}

void MS1()      //monitoring system 1
{
	system ("CLS");
	int BP, ECG, PR;
	int flag = 0;
	string  Time;
		
	 do{
	 	cout<<"To go back to the main menu, enter a zero.\n\n";
		do{
			cout << "\n1. Please enter reading of Blood Pressure          : ";
			cin >> BP; 
		  }while(BP < 0);
			if (BP == 0) {headerprinted = false; MainMenu();}; 
		
		do{		
			cout << "\n2. Please enter reading of Electrocardiogram (ECG) : ";
			cin >> ECG;
			}while(ECG < 0);
			if (ECG == 0){headerprinted = false; MainMenu();};
			
		do{
			cout << "\n3. Please enter reading of Pulse Rate              : ";
			cin >> PR;
	    }while(PR < 0);
			if (PR == 0){headerprinted = false; MainMenu();};
			
		if (headerprinted==false){
			fout <<"\n\nTimeStamp		BloodPressure(80-120mmHg)	ECG(120-200MS)	PulseRate(65-75bpm)\n";
			headerprinted = true;
		}
		Time = currentDateTime();
		fout <<Time<<"	";
		cout<<"\n============================================";
		
		fout << BP;
			if ((BP < 80)||(BP > 120)){
				cout << "\nBlood Pressure is Abnormal!" << endl;
				fout<<"(Abnormal)";
				}
			else{
				cout << "\nBlood pressure is Normal" << endl;
				fout <<"(Normal)";
				}
	//////////////////////////////////////////////////////////////////////
			fout<<"\t\t\t"<<ECG;
			if ((ECG < 120) || (ECG >200)){
				cout << "\nECG is Abnormal!" << endl;
				fout <<"(Abnormal)";
				}
			else {
				cout << "\nECG is Normal" << endl;
				fout<<"(Normal)";
				}
	//////////////////////////////////////////////////////////////////////		
	fout<<"\t"<<PR;		
			if ((PR < 65) || (PR > 75)){
				cout << "\nPulse Rate is Abnormal!" << endl;
				fout <<"(Abnormal)\n";
				}		
			else{
				cout << "\nPulse Rate is Normal" << endl;
				fout <<"(Normal)\n";
			}
	//////////////////////////////////////////////////////////////////////		
			cout<<"============================================\n\n";
			fout.flush();
		system("pause");
		system ("CLS");
		
		}while(flag == 0);

}
void MS2()      //monitoring system 2
{
	system ("CLS");
	int before,after;                           //DECLARATION VARIABLES
	int flag = 0;
	int streak = 0;
		
	do{
		day += 1;                                    //DAY WILL BE PLUS ONE
		cout<<"To go back to the main menu, enter a zero.\n\n";
			
		cout << "DAY " << day ;
			
		do{
		cout << "\n	1.Please enter the sugar level before breakfast : ";
		cin >> before;
		}while(before<0);
		if (before == 0){
		day -= 1;headerprinted = false;
		MainMenu();
		}
		
		do{
		cout << "\n	2.Please enter the sugar level after breakfast  : ";
		cin >>after;
		}while(after<0);
		if (after == 0){
		day -= 1;headerprinted = false;
		MainMenu();
		}
		
		if (headerprinted == false){
			fout<<"\n\n\nTimeStamp		SugerBeforeLunch(75-110)	SugerBeforeLunch(130-145)	Status\n";
			headerprinted = true;
		}
		
		fout<<currentDateTime()<<"\t";
		
		cout << "===============================================================" << endl;
		cout << "\nSugar level readings for Day " << day << " have been received!\n\n";   
		cout << "===============================================================\n" << endl;             
		system("pause");
		system("CLS");
		
		fout<<before<<"mg/dL";
		if ((before < 75) || (before > 100))
			fout<<"(Abnormal)";
		else
			fout<<"(Normal)";
			
			fout<<"\t\t";
			fout<<after<<"mg/dL";
		if ((after < 130) || (after > 145))
			fout<<"(Abnormal)";
		else
			fout<<"(Normal)";
		
		if( ((before < 75) || (before > 100)) || ((after < 130 ) || (after > 145)) )            //CONDITION BEFORE BREAKFAST EITHER THE READINGS IS LESS THAN 75 OR MORE THAN 100	
			streak += 1;			 										  			 	    //AND AFTER BREAKFAST EITHER LESS THAN 130 OR MORE THAN 145		                                    
		else
			streak = 0;
			
					
		if (streak >= 3){                  //CONDITION IF THE STREAK IS 3 TIMES IN A ROW 
					//flag = 1;  
			cout << "\n===============================================================" << endl;	
			cout << "\n   ALERT!!! \n   Your Suger level readings were fluctuating.\n   The docter has been informed. "<<  endl;  //IF THE SUGAR LEVEL HAS EXCEED 3 TIMES IN A ROW                                     
		    cout << "\n===============================================================\n" << endl;
		    fout<<"\tAlert!!!\n";
		    fout.flush();
			system("pause");
			system("CLS");
			}
			else{
				fout<<"\t\tOK\n";
				fout.flush();
				};
		
 
	}while (flag == 0);
	
	
}
void MS3()      //monitoring system 3
{	
	float bodyTemp;
	int flag = 0;
	
system ("CLS");
headerprinted == false;
	do{	
		cout<<"To go back to the main menu, enter a zero.\n\n";
		do{
		cout << "Please input Body Temperature in Fahrenheit: ";
		cin  >> bodyTemp;
		}while(bodyTemp < 0);
		
		if (bodyTemp == 0) MainMenu();
		
		if (headerprinted == false){
		fout<<"\n\nTimeStamp		BodyTemp(<98.3F)		TemperatureStatus\n";
		headerprinted = true;
		}
		
		fout<<currentDateTime()<<"\t"<<bodyTemp<<"F"<<"\t\t\t\t";
			
		
		
		cout <<endl;
		if ((bodyTemp >= 98.3) && (bodyTemp < 100)){
			cout << "Alert !, paitent has a low fever.\n"<<endl;
			fout<<"Low Alert\n";
	    }
	    
		else if (bodyTemp >= 100){
			cout <<"ALERT !!!"<<endl
				 <<"Paitent has a high fever, "<<endl
				 <<"Patient is advised to see a doctor immediately!\n"<<endl;	 
			fout<<"High Alert!!!\n";
		}
		else if (bodyTemp<97){
			cout<<"Low body temperature!\n";
			fout<<"Low\n";
			}
		else{ 
			cout << "Body temperature is normal\n"<<endl;
			fout<<"OK\n";
			}
		
		system("pause");
		system("CLS");
		fout.flush();
		
	 }while(flag == 0);
	 
	 
	 
}

void Printfile(){

system ("CLS");
cout << "Patient Profile: " << filename;



  string line;
  print.open(filepath.c_str());     //THE FILE IS OPEN!  
  
  if (print.is_open())
  {
    while ( print.good() )
    {
      getline (print,line);
      cout << line << endl;
    }
   	print.close();
  }

  else cout << "\nUnable to open file\n"; 



system("pause");
MainMenu();

}
