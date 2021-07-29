#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

struct keeper{
    int flag;
    int stumps;
};

class Player{
protected:
    int pid;
    string name;
    int age;
    int matches;
    keeper wk;
    int team;
public:
    static int noOfPlayers;

    Player(){
        pid=noOfPlayers++;
        name="";
        age=0;
        matches=0;
        wk.flag=0;
        wk.stumps=0;
        team=-1;
    }
    Player(string n,int a,int m){
        pid=noOfPlayers++;
        name=n;
        age=a;
        matches=m;
        wk.flag=0;
        wk.stumps=0;
        team=-1;
    }
    Player(string n,int a,int m,int s){
        pid=noOfPlayers++;
        name=n;
        age=a;
        matches=m;
        wk.flag=1;
        wk.stumps=s;
        team=-1;
    }
    void assignToTeam(int tno){
        team=tno;
    }
    void incMatches(){
        matches++;
    }
    void incMatches(int i){
        matches+=i;
    }
    void incStumps(){
        wk.stumps++;
    }
    void incStumps(int i){
        wk.stumps+=i;
    }
    int getId(){
        return pid;
    }
    int getTid(){
        return team;
    }
    string getName(){
        return name;
    }
    int getMatches(){
        return matches;
    }
    int getFlag(){
        return wk.flag;
    }
    void displayName(){
        cout<<setw(20)<<left<<pid<<setw(30)<<right<<name<<endl;
    }
    virtual void forceAbstract()=0;
    virtual void display(){
        cout<<"Player ID : "<<pid
            <<"\nName : "<<name
            <<"\nAge : "<<age
            <<"\nTeam : "<<team
            <<"\nMatches : "<<matches<<endl;
        if(wk.flag)
            cout<<"Stumpings : "<<wk.stumps<<endl;
    };
    virtual float getRunRate(){};
    virtual void incRunsGiven(int){};
    virtual void incBall(){};
    virtual void incBalls(int){};
    virtual void incWicket(){};
    virtual void incWickets(int){};
    virtual void incOver(){};
    virtual void incOvers(int){};
    virtual float getAverage(){};
    virtual void incRuns(int r){};
    virtual void incInning(){};
    virtual void incInnings(int){};
    virtual void incrementFifty(){};
    virtual void incrementFifties(int){};
};
int Player::noOfPlayers=0;

class Batsman:virtual public Player{
    int innings;
    int runs;
    float strikeRate;
    int fifty;
public:
    Batsman(){
        innings=0;
        runs=0;
        strikeRate=0;
        fifty=0;
    }
    Batsman(string n,int a,int m,int i,int r,float sr,int f):Player(n,a,m){
        innings=i;
        runs=r;
        strikeRate=sr;
        fifty=f;
    }
    Batsman(string n,int a,int m,int s,int i,int r,float sr,int f):Player(n,a,m,s){
        innings=i;
        runs=r;
        strikeRate=sr;
        fifty=f;
    }
    void forceAbstract(){}
    float getAverage(){
        return runs*1.0/innings;
    }
    void display(int x){
        cout<<"Innings : "<<innings
            <<"\nRuns Scored : "<<runs
            <<"\nAverage : "<<getAverage()
            <<"\nStrike Rate : "<<strikeRate
            <<"\nFifties : "<<fifty<<endl;
    }
    void display(){
        Player::display();
        display(0);
    }
    void incInning(){
        innings++;
    }
    void incInnings(int i){
        innings+=i;
    }
    void incRuns(int r){
        runs+=r;
    }
    void incrementFifty(){
        fifty++;
    }
    void incrementFifties(int f){
        fifty+=f;
    }
};

class Bowler:virtual public Player{
    float overs;
    int runs_given;
    int wickets;
public:
    Bowler(){
        overs=0;
        runs_given=0;
        wickets=0;
    }
    Bowler(string n,int a,int m,float o,int r,int w):Player(n,a,m){
        overs=o;
        runs_given=r;
        wickets=w;
    }
    Bowler(string n,int a,int m,int s,float o,int r,int w):Player(n,a,m,s){
        overs=o;
        runs_given=r;
        wickets=w;
    }
    void forceAbstract(){}
    float getRunRate(){
        float x=(overs-(int)overs)*10/6;
        return runs_given/(x+(int)overs);
    }
    void display(int x){
        cout<<"Overs : "<<overs
            <<"\nRuns : "<<runs_given
            <<"\nWickets : "<<wickets
            <<"\nRun rate : "<<getRunRate()<<endl;
    }
    void display(){
        Player::display();
        display(0);
    }
    void incBall(){
        if(overs-(int)overs<0.5)
            overs+=0.1;
        else
            overs=(int)++overs;
    }
    void incBalls(int b){
        for(int i=0;i<b;i++)
            incBall();
    }
    void incOver(){
        overs++;
    }
    void incOvers(float o){
        overs+=(int)o;
        incBalls((o-(int)o)*10);
    }
    void incRunsGiven(int r){
        runs_given+=r;
    }
    void incWicket(){
        wickets++;
    }
    void incWickets(int w){
        wickets+=w;
    }
    friend ostream& operator<<(ostream& stream,const Bowler& b);
};
ostream& operator<<(ostream& stream,const Bowler& b){
    stream<<"Name : "<<b.name<<endl<<"Age : "<<b.age;
    return stream;
}

class AllRounder:public Bowler,public Batsman{
public:
    AllRounder(){}
    AllRounder(string n,int a,int m,float o,int rg,int w,int i,int r,float sr,int f):Player(n,a,m),Bowler(n,a,m,o,rg,w),Batsman(n,a,m,i,r,sr,f){}
    AllRounder(string n,int a,int m,int s,float o,int rg,int w,int i,int r,float sr,int f):Player(n,a,m,s),Bowler(n,a,m,s,o,rg,w),Batsman(n,a,m,s,i,r,sr,f){}
    void forceAbstract(){}
    void display(){
        Batsman::display();
        Bowler::display(0);
    }
};

struct PlayerRec{
    int id;
    string name;
    int teamId;
    int played;             //Acts as bool in match records and counter in tournament record
    int batted;             //Acts as batting position in match records and counter for innings in tournament record
    int stumps;
    int runsScored;
    int fifty;
    float oversFaced;
    int runsGiven;
    int wickets;
    float oversBowled;
    void reset(){
        played=0;
        stumps=0;
        batted=0;
        runsScored=0;
        fifty=0;
        oversFaced=0;
        runsGiven=0;
        wickets=0;
        oversBowled=0;
    }
    PlayerRec(Player *p){
        id=p->getId();
        name=p->getName();
        teamId=p->getTid();
        reset();
    }
    void incBallFaced(){
        if(oversFaced-(int)oversFaced<0.5)
            oversFaced+=0.1;
        else
            oversFaced=(int)++oversFaced;
    }
    void incBallsFaced(int b){
        for(int i=0;i<b;i++)
            incBallFaced();
    }
    void incOversFaced(float o){
        oversFaced+=(int)o;
        incBallsFaced((o-(int)o)*10);
    }
    void incBallBowled(){
        if(oversBowled-(int)oversBowled<0.5)
            oversBowled+=0.1;
        else
            oversBowled=(int)++oversBowled;
    }
    void incBallsBowled(int b){
        for(int i=0;i<b;i++)
            incBallBowled();
    }
    void incOversBowled(float o){
        oversBowled+=(int)o;
        incBallsBowled((o-(int)o)*10);
    }
    int getBallsFaced(){
        return ((int)oversFaced)*6+(oversFaced-(int)oversFaced)*10;
    }
    float getStrikeRate(){
        if(oversFaced)
            return runsScored*100.0/getBallsFaced();
        return 0;
    }
    int getBallsBowled(){
        return ((int)oversBowled)*6+(oversFaced-(int)oversBowled)*10;
    }
    float getRunRate(){
        if(oversBowled)
            return (runsGiven*1.0/getBallsBowled())*6;
        return 0;
    }
    static bool compareTeam(PlayerRec& pr1,PlayerRec pr2){
        return pr1.teamId<pr2.teamId;
    }
    static bool compareBatted(PlayerRec& pr1,PlayerRec pr2){
        return pr1.batted<pr2.batted;
    }
    static bool compareBowled(PlayerRec& pr1,PlayerRec pr2){
        return pr1.oversBowled>pr2.oversBowled;
    }
    static bool compareRunsScored(PlayerRec& pr1,PlayerRec pr2){
        return pr1.runsScored>pr2.runsScored;
    }
    static bool compareWickets(PlayerRec& pr1,PlayerRec pr2){
        return pr1.wickets>pr2.wickets;
    }
};
