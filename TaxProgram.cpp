/*
 +-------------------------------------------+
 + Programmer  : Max Johnson					+
 + Cource      : Computer Science 101		+
 + Lab Section : 0108 (T TH at 2 pm)			+
 + Grader      : Professor Ghyam				+
 + Assignment  : Lab 4 (letter grade)		+
 + Due Date    : 3/24/2017					+
 +-------------------------------------------+
 Program statement
 *
 *
 ************************ Analysis *****************************
 1. Data needed
 Name
 input file
 output file
 
 
 2. Constants given
	tax braket
 
 3. Calculations
 verify ID number (that it's numeric)
 years earnings are numeric
 calculate income tax
 
 4. Print results
	dispaly name, ID, Gross income, amount in Taxes, net income (gross-taxes), (average, highest, and lowest net incomes)
 
 ************************ Algorithm *****************************
 Step 1: Input
 Prompt user for name
 first and last (getline)
 prompt user for input file ()
 prompt user for output file ()				*if data is bad print an error message and continue processing data*
 
 Step 2: Process
 
 **use if-else statements to use correct bracket
 tax braket:  $0 - $3,500 = $0 in taxes
 $3,500 - $8,000 = $0 + 6% of the amount over 3,500
 $8,000 - $20,000 = $270.00 + 11% of the amount over 8,000
 $20,000 - $34,000 = $1590.00 + 17% of the amount over 20,000
 $34,000 - $54,ooo = $3970.00 + 24% of the amount over 34,000
 $54,000 and up = $8770.00 + 32% of the amount over 52,000
 
 Step 3: Output
	display: name, ID, Gross Income, Taxes, Net Income (for each )
	average net income, Lowest net income, and highest net income,
	*each data type should have it's own column
 
 */
/* CODE */
#include <iostream>                                                                         // packages
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;


ifstream fin;																				// initialize variables
ofstream fout;
string INfile_Name;
string OUTfile_Name;
string Client_Name;
string IDfail = "****Invalid ID";
string IncomeFail = "****Invalid Income";
string HighEarner;
string LowEarner;
bool IDcheck = true;
bool IncomeCheck = true;
bool AcuarateAvg = true;
int IDnum;
int ClientCount = 0;
int dash_counter;
float HighIncome = 0;
float LowIncome = pow(10,45);
float annualIncome;
float TaxRate;
float TaxDue;
float NetIncome;
float totalNet;
float averageNet;

int main()
{															//input
    cout << "please enter file name that will be read: " ;									// get input file & verify
    fin >> INfile_Name;
    fin.open(INfile_Name.c_str());
    
    while (fin.fail()) {
        cout << endl << "BAD FILE NAME" << endl << "Renter file name: ";
        fin >> INfile_Name;
        fin.open(INfile_Name.c_str());
    }
    
    {
        cout << "enter file name where data will be stored: ";								// get output file
        fin >> OUTfile_Name ;
        fout.open(OUTfile_Name);
        fout << fixed << showpoint << setprecision(2) << left;
        fout << setw(15) << "Name" << setw(8) << "ID" << setw(15) << "Gross Income" << setw(14) << "Taxes" << setw(15) << "Net Income"<<endl ;
        for (dash_counter = 0 ; dash_counter < 50 ; dash_counter++)
            fout << '='<< endl;
        
        
        while (!fin.eof()){                 // start loop
            getline(fin, Client_Name);          // input
            fin >> IDnum ;
            
            if (!fin || IDnum < 0 || IDnum >9999){
                IDcheck = false;
                // check id is an intiger, if not print error
            }
            fin >> annualIncome;
												// process
            
            
            
												// calculate taxes
            if (annualIncome > 0 && annualIncome <= 3500){
                TaxRate = 0;
                TaxDue = 0;
            }
            else if (annualIncome > 3500 && annualIncome <= 8000){
                TaxRate = 0.06;
                TaxDue = (annualIncome - 3500) * TaxRate;
            }
            else if (annualIncome > 8000 && annualIncome <= 20000){
                TaxRate = 0.11;
                TaxDue = ((annualIncome - 8000) * TaxRate) + 270;
            }
            else if (annualIncome > 20000  && annualIncome <= 34000){
                TaxRate = 0.17;
                TaxDue = ((annualIncome - 20000) * TaxRate) + 1590;
            }
            else if (annualIncome > 34000  && annualIncome <= 54000 ){
                TaxRate = 0.24;
                TaxDue = ((annualIncome - 34000) * TaxRate) + 3970;
            }
            else if (annualIncome > 54000){
                TaxRate = 0.32;
                TaxDue = ((annualIncome - 54000) * TaxRate) + 8770;
            }
            else{
                IncomeCheck = false;
            }
            
            NetIncome = annualIncome - TaxDue;
            
            
            // display name , ID, Income, Taxes, After Taxes
            
            
												// output
            
            if (IDcheck == true && IncomeCheck == true){                            // show taxes and net income
                fout << setw(15) << Client_Name;
                fout << setw(8)  << IDnum << '$';
                fout << setw(14) << annualIncome << '$';
                fout << setw(13) << TaxDue << '$';
                fout << setw(14) << NetIncome;
            }
            else if (IDcheck == true && IncomeCheck == false){                      // show bad income
                fout << setw(15) << Client_Name;
                fout << setw(8) << IDnum << '$';
                fout << setw(14) << annualIncome;
                fout << IncomeFail;
            }
            else if (IDcheck == false && IncomeCheck == true){                      // show bad ID
                fout << setw(15) << Client_Name;
                fout << setw(8) << IDnum <<'$';
                fout << setw(14) << annualIncome;
                fout << IDfail;
            }
            else if (IDcheck == false && IncomeCheck == false){                     // show bad ID & bad income
                fout << setw(15) << Client_Name;
                fout << setw(8) << IDnum <<'$';
                fout << setw(15) << annualIncome;
                fout << IDfail << "  " << IncomeFail;
            }
            
            
            if (annualIncome >= HighIncome){                                         // keep track of high and low
                HighIncome = annualIncome;
                HighEarner = Client_Name;
            }
            if (annualIncome < LowIncome && annualIncome >= 0){
                LowIncome = annualIncome;
                LowEarner = Client_Name;
            }
            
            
            fin.ignore(128,'endl');                                                    // update conditions clear buffer
            if (IncomeCheck == false){
                AcuarateAvg = false;
            }
            IDcheck = true;
            IncomeCheck = true;
            totalNet += totalNet + NetIncome;
            ClientCount++;
        }
        // end loop
        
        averageNet = totalNet/ClientCount;                                          // calculate average net income
        
        // fout Average, Highest, lowest
        fout << endl << endl;
        if (AcuarateAvg == false)
            fout << setw(23) << "Average net income" << '$' << "**** Inacuarate Average";
        else
            fout << setw(23) << "Average net income" << '$' << averageNet;
        fout << setw(23) << "Highest Net income" << setw(27) << HighEarner << '$' << HighIncome;
        fout << setw(23) << "Lowest Net income" << setw(27) << LowEarner << '$' << LowIncome;
        
    }
    
    return (0);
}
