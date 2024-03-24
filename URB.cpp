#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int tu =0;
int R_Score=0,R_count=0;
void Master_Access(){
    while(1){
        int chc=0;
        cout<<"You Are Accessing Master Controls\n";
        cout<<"1. Show Me Users List\n";
        cout<<"2. Show Me Passwords List\n";
        cout<<"3. Clear Both The Accounts\n";
        cout<<"4. Exit\n";
        cin>>chc;
        if(chc == 1){
            ifstream mp("URBankUsers.txt");
            string line;
            cout<<"Current Users List:\n";
            cout<<"Total Users: "<<tu<<endl;
            int i=1;
            cout<<"Usernames(s)\t\t"<<"Account Number(s)"<<endl;
            while(getline(mp,line)){
                
                cout<<line<<"\t\t"<<i++<<endl;
            }

            mp.close();
        }
        else if(chc == 2){
            ifstream mp2("URBUP.txt");
            string line;
            cout<<"Current User's Password List:\n";
            while(getline(mp2,line)){
                cout<<line<<endl;
            }
            mp2.close();
        }
        else if(chc == 3){
            ofstream fo("URBankUsers.txt",ofstream::trunc);
            ofstream fo1("URBUP.txt",ofstream::trunc);
            ofstream fo2("URBankScoreFile.txt",ofstream::trunc);
            ofstream fo3("URBankLocker.txt",ofstream::trunc);
            ofstream fo4("URBankFeeds.txt",ofstream::trunc);
            fo.close();
            fo1.close();
            fo2.close();
            fo3.close();
            if(tu==0) cout<<"No Data Left To Clear!!!\n";
            else cout<<tu<<" User's Data Cleared Successfully!!!\n";
            tu=0;
        }
        else if(chc==4) break;
        else cout<<"Invalid Choice!. Try Again.\n";
    }
}
void checkBalance(int line){
    ifstream  fi("URBankLocker.txt");
    int l=0,amt=0;
    while(fi>>amt){
        l++;
        if(l== line){
            if(amt ==0 ) cout<<"EARN SOMETHING MAN!!!\n";
            else cout<<"Your Current Balance Is: "<<amt<<endl;
            break;
        }
    }
    fi.close();
}
void depositMoney(int line, int amt) {
    ifstream fin("URBankLocker.txt");
    vector<int> balances;
    int balance;

    while (fin >> balance) {
        balances.push_back(balance);
    }
    fin.close();

    if (line > 0 && line <= balances.size()) {
        balances[line - 1] += amt; 
    } else {
        cout << "Invalid user line number." << endl;
        return;
    }

    ofstream fout("URBankLocker.txt");
    for (int bal : balances) {
        fout << bal << "\n";
    }
    fout.close();

    cout << "Cash Deposited Successfully!!!\n";
}
void withdrawMoney(int line, int amt) {
    ifstream fin("URBankLocker.txt");
    vector<int> balances;
    int balance;

    while (fin >> balance) {
        balances.push_back(balance);
    }
    fin.close();

    if (line > 0 && line <= balances.size()) {
        if (balances[line - 1] >= amt) {
            balances[line - 1] -= amt; 
            cout << "Money Withdrawal Successful!!!\n";
        } else {
            cout << "Sorry! Insufficient Funds.\n";
            return;
        }
    } else {
        cout << "Invalid user line number." << endl;
        return;
    }
    ofstream fout("URBankLocker.txt");
    for (int bal : balances) {
        fout << bal << "\n";
    }
    fout.close();
}
void transferMoney(int u, int r,int amt){
    ifstream fin("URBankLocker.txt");
    vector<int> balances;
    int balance;

    while (fin >> balance) {
        balances.push_back(balance);
    }
    fin.close();

    if (u > 0 && u <= balances.size()) {
        if (balances[u - 1] >= amt) {
            balances[u - 1] -= amt; 
        } else {
            cout << "Sorry! Insufficient Funds.\n";
            return;
        }
    } else {
        cout << "Invalid user line number." << endl;
        return;
    }
    ofstream fout("URBankLocker.txt");
    for (int bal : balances) {
        fout << bal << "\n";
    }
    fout.close();
    ifstream fin1("URBankLocker.txt");
    vector<int> balances1;
    int balance1;

    while (fin1 >> balance1) {
        balances1.push_back(balance1);
    }
    fin1.close();

    if (r > 0 && r <= balances1.size()) {
        balances1[r - 1] += amt; 
    } else {
        cout << "Invalid user line number." << endl;
        return;
    }
    ofstream fout1("URBankLocker.txt");
    for (int bal1 : balances1) {
        fout1 << bal1 << "\n";
    }
    fout1.close();
    cout << "Money Transferred Successfully !\n";
}
void Manage_Account(int User_Line){
    cout<<"Now You Can Manage Your Account\nYour Account Number Is: "<<User_Line<<endl;
    int ch;
    while(1){
        cout<<"What you wish to Do? :\n";
        cout<<"1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Money\n5. Logout\n";
        cin>>ch;
        if(ch==1) checkBalance(User_Line);
        else if(ch==2) {
            int amt=0;
            cout<<"Enter Amount to be Deposited: ";
            cin>>amt;
            depositMoney(User_Line,amt);
        }
        else if(ch==3) {
            int wamt=0;
            cout<<"Enter Amount to be Withdrawn: ";
            cin>>wamt;
            withdrawMoney(User_Line,wamt);
        }
        else if(ch == 4){
            int rline,ramt;
            cout<<"Enter Recipient Account Number:";
            cin>>rline;
            cout<<"Enter amount to be transferred:";
            cin>>ramt;
            if(rline<0 || rline>tu) {cout<<"Invalid Account!, Please try again.\n"<<endl;}
            else transferMoney(User_Line,rline,ramt);

        }
        else if(ch==5) break;
    }
}
void Login(){
    string pname,pass;
    int pc=0;
    ifstream fin1("URBankUsers.txt");
    ifstream fin2("URBUP.txt");
    while(1){
        cout<<"Enter User Name:\n";
        cin>>pname;
        string line,line2;
        size_t found1;
        fin1.clear();
        fin1.seekg(0);
        int l=0;
        while(getline(fin1,line)){
            found1 = line.find(pname);
            l++;
            if(found1!=string::npos){
                break;
            }
        }  
        if(found1 == string::npos) {
            cout<<"Invalid Username!!!\n";
            break;
        }
        cout<<"Enter Password: (Attempts Left: "<<3-pc<<")\n";
        cin>>pass;
        int l2=1;
        fin2.clear();
        fin2.seekg(0);
        int sw=0;
        while(getline(fin2,line2)){
            if(l == l2) {
                if(line2 == pass);
                else sw=-1;
                break;
            }
            l2++;
        }
        if(sw ==-1){
            pc++;
            if(pc == 3)  {cout << "Account Locked!!!\nContact Admin for Unlocking the Account.\n";break;}
            cout<<"\nIncorrect Password!!!\nTry Again\n";
        }
        else{
            cout<<"Authentication Successful.\nWelcome to UR Bank Account\n";
            Manage_Account(l);
            break;
        }
    }
    fin1.close();
    fin2.close();
}
void New_Account(){
    cout<<"\t\t\t\t\t\t\tCreate New User Account\n";
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------\n";
    string uname="",pass="";
    ifstream fin3("URBankUsers.txt");
    while(1){
        cout<<"Enter User Name For Your Account: (Without Spaces)\n";
        cin>>uname;
        string line;
        size_t found = string::npos;
        fin3.clear();
        fin3.seekg(0);
        while(getline(fin3,line)){
            found = line.find(uname);
            if(found!=string::npos){
                cout<<"User Name Already Exists!!!\n";
                break;
            }
        }
        if(found == string::npos) {
            fin3.close();
            break;
        }
    }
    cin.ignore();
    cout<<"Create Your Password:(Everything is okay except Spaces!!!)\n";
    cin>>pass;
    while(pass.size()<5){
        cout<<"Password Should be atleast of length 5:\n";
        cin>>pass;
    }
    ofstream fout1("URBankUsers.txt", ios::app);
    fout1<<uname<<"\n";
    fout1.close();
    ofstream fout2("URBUP.txt",ios::app);
    fout2<<pass<<"\n";
    fout2.close();
    tu++;
    ofstream fout3("URBankLocker.txt",ios::app);
    fout3<<0<<"\n";
    cout<<"Your Account is Successfully Created!!!\n"<<endl;
}
int main(){
    ifstream fin("URBankScoreFile.txt");
    fin >> R_Score;
    fin >> R_count;
    fin >> tu;
    fin.close();
    cout << "\t\t\t\t\t\t\tWELCOME TO UR-BANK!!!\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    while(1){
        int choice=0;
        cout << "OUR CURRENT SERVICES ARE:\n";
        cout << "1. Open a new account.\t\t";
        cout << "2. Log In into your account.\t\t";
        cout << "3. Exit.\n";
        cin >> choice;
        if(choice == 1) 
            New_Account();
        else if(choice == 2) 
            Login();
        else if(choice == 3) 
            break;
        else if(choice == 99) 
            Master_Access();
        else 
            cout << "Invalid Choice!. Try Again.\n";
    }
    cout << "Will You Please Help Us Improve Our Services By Giving Your Feedback:\n(y or n)\n";
    char c;
    cin >> c;
    int CurScore=0;
    if(c == 'y'){
        cout << "Please Give Your Rating Between 1 ~ 5 Stars\n";
        cin >> CurScore;
        R_Score += CurScore;
        R_count++;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string paragraph;
        cout << "Please enter your Feed Back:\n";
        getline(cin, paragraph, '\n');

        ofstream fout2("URBankFeeds.txt", ios::app);
        fout2 << paragraph << endl;
        fout2.close();
    }
    ofstream fout("URBankScoreFile.txt");
    fout << R_Score << "\n";
    fout << R_count << "\n";
    fout << tu << "\n";
    fout.close();
    cout << "Please Visit Again!!!";
    return 0;
}