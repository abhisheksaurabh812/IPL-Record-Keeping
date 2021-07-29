#include"ipl.cpp"

using namespace std;

void loadPlayersAndTeams(vector<Batsman>&,vector<Bowler>&,vector<AllRounder>&,vector<Team>&);

int main(){
    int i,n;
    vector<Bowler> bo;
    vector<Batsman> ba;
    vector<AllRounder> babo;
    vector<Team> t;
    bo.reserve(50);
    ba.reserve(50);
    babo.reserve(50);
    t.reserve(10);
    loadPlayersAndTeams(ba,bo,babo,t);
    IPL *x=new IPL("IPL 2020",bo,ba,babo,t);
    IPL::Tournament *tour=new IPL::Tournament();
    x->assignTeams();
    cout<<"               Welcome\n";
    string pn;
    int ch,ch2;
    do{
        cout<<"**************************************\n";
        cout<<"1. Display Teams\n2. Search Player\n3. Edit player records\n4. Edit team records\n5. Enter Tournament\n";
        cout<<"**************************************\n";
        cout<<"Enter your choice\n";
        cin>>ch;
        switch(ch){
            case 0: break;
            case 1: x->displayTeams();
                    break;
            case 2: cout<<"Enter player name to be searched\n";
                    fflush(stdin);
                    getline(cin,pn);
                    x->displayPlayer(pn);
                    break;
            case 5: tour->continueTournament(*x);
                    break;
        }
        cin.sync();
        if(ch!=5)
            cin.get();
        system("CLS");
    }while(ch);
}

void loadPlayersAndTeams(vector<Batsman> &ba,vector<Bowler> &bo,vector<AllRounder> &babo,vector<Team> &t){
    int n;
    char c;
    string t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11;
    t0=t1=t2=t3=t4=t5=t6=t7=t8=t9=t10=t11="";
    ifstream myFile;
    myFile.open("Batsmen.txt");
    while(myFile.get(c)&&c!='\n')
        t0+=c;
    n=stoi(t0);
    while(n--){
        while(myFile.get(c)&&c!=',')
            t1+=c;
        while(myFile.get(c)&&c!=',')
            t2+=c;
        while(myFile.get(c)&&c!=',')
            t3+=c;
        while(myFile.get(c)&&c!=',')
            t4+=c;
        while(myFile.get(c)&&c!=',')
            t5+=c;
        while(myFile.get(c)&&c!=',')
            t6+=c;
        while(myFile.get(c)&&c!=',')
            t7+=c;
        while(myFile.get(c)&&c!='\n')
            t8+=c;
        if(t4=="")
            ba.emplace_back(t1,stoi(t2),stoi(t3),stoi(t5),stoi(t6),stof(t7),stoi(t8));
        else
            ba.emplace_back(t1,stoi(t2),stoi(t3),stoi(t4),stoi(t5),stoi(t6),stof(t7),stoi(t8));
        t1=t2=t3=t4=t5=t6=t7=t8="";
    }
    myFile.close();
    t0="";
    myFile.open("Bowlers.txt");
    while(myFile.get(c)&&c!='\n')
        t0+=c;
    n=stoi(t0);
    while(n--){
        while(myFile.get(c)&&c!=',')
            t1+=c;
        while(myFile.get(c)&&c!=',')
            t2+=c;
        while(myFile.get(c)&&c!=',')
            t3+=c;
        while(myFile.get(c)&&c!=',')
            t4+=c;
        while(myFile.get(c)&&c!=',')
            t5+=c;
        while(myFile.get(c)&&c!=',')
            t6+=c;
        while(myFile.get(c)&&c!='\n')
            t7+=c;
        if(t4=="")
            bo.emplace_back(t1,stoi(t2),stoi(t3),stof(t5),stoi(t6),stoi(t7));
        else
            bo.emplace_back(t1,stoi(t2),stoi(t3),stoi(t4),stof(t5),stoi(t6),stoi(t7));
        t1=t2=t3=t4=t5=t6=t7="";
    }
    myFile.close();
    t0="";
    myFile.open("AllRounders.txt");
    while(myFile.get(c)&&c!='\n')
        t0+=c;
    n=stoi(t0);
    while(n--){
        while(myFile.get(c)&&c!=',')
            t1+=c;
        while(myFile.get(c)&&c!=',')
            t2+=c;
        while(myFile.get(c)&&c!=',')
            t3+=c;
        while(myFile.get(c)&&c!=',')
            t4+=c;
        while(myFile.get(c)&&c!=',')
            t5+=c;
        while(myFile.get(c)&&c!=',')
            t6+=c;
        while(myFile.get(c)&&c!=',')
            t7+=c;
        while(myFile.get(c)&&c!=',')
            t8+=c;
        while(myFile.get(c)&&c!=',')
            t9+=c;
        while(myFile.get(c)&&c!=',')
            t10+=c;
        while(myFile.get(c)&&c!='\n')
            t11+=c;
        if(t4=="")
            babo.emplace_back(t1,stoi(t2),stoi(t3),stof(t5),stoi(t6),stoi(t7),stoi(t8),stoi(t9),stof(t2),stoi(t11));
        else
            babo.emplace_back(t1,stoi(t2),stoi(t3),stoi(t4),stof(t5),stoi(t6),stoi(t7),stoi(t8),stoi(t9),stof(t2),stoi(t11));
        t1=t2=t3=t4=t5=t6=t7=t8=t9=t10=t11="";
    }
    myFile.close();
    t0="";
    myFile.open("Teams.txt");
    while(myFile.get(c)&&c!='\n')
        t0+=c;
    n=stoi(t0);
    while(n--){
        t1=t2=t3=t4=t5="";
        while(myFile.get(c)&&c!=',')
            t1+=c;
        while(myFile.get(c)&&c!=',')
            t2+=c;
        while(myFile.get(c)&&c!=',')
            t3+=c;
        while(myFile.get(c)&&c!=',')
            t4+=c;
        while(myFile.get(c)&&c!='\n')
            t5+=c;
        t.emplace_back(t1,stoi(t2),stoi(t3),stoi(t4),stoi(t5));
    }
}
