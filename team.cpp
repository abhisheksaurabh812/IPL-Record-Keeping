#include<vector>
#include"player.cpp"

using namespace std;

class Team{
    int tid;
    string name;
    int matches;
    int wins;
    int loss;
    int draw;
    Player *cap;
    vector<Player*> members;
public:
    static int noOfTeams;

    Team(){
        tid=noOfTeams++;
        name="";
        matches=0;
        wins=0;
        loss=0;
        draw=0;
        cap=NULL;
    }
    Team(string &n,int m,int w,int l,int d):name(n),matches(m),wins(w),loss(l),draw(d){
        tid=noOfTeams++;
        cap=NULL;
        members.reserve(15);
    }
    int getId(){
        return tid;
    }
    string getName(){
        return name;
    }
    int getSize(){
        return members.size();
    }
    int incWins(){
        wins++;
        matches++;
    }
    int incWins(int i){
        wins+=i;
        matches+=i;
    }
    int incLoss(){
        loss++;
        matches++;
    }
    int incLoss(int i){
        loss+=i;
        matches+=i;
    }
    int incDraws(){
        draw++;
        matches++;
    }
    int incDraws(int i){
        draw+=i;
        matches+=i;
    }
    int search(int id){
        for(Player* p:members)
            if(p->getId()==id)
                return 1;
        return 0;
    }
    int searchPlayer(string pn){
        for(Player* p:members)
            if(!p->getName().compare(pn))
                return p->getId();
    }
    string getPlayerName(int id){
        for(Player* p:members)
            if(p->getId()==id)
                return p->getName();
    }
    void addPlayer(Player* m){
        members.push_back(m);
    }
    void assignCap(Player *c){
        cap=c;
    }
    void autoCap(){
        assignCap(members[0]);
    }
    void setupMatchRec(vector<PlayerRec> &mr){
        int ch,i,s=mr.size();
        for(Player* p:members)
            mr.emplace_back(p);
        cout<<name<<" Setup\nPress 1 to Auto select top 11 players or press 0 to select manually\n";
        displayMembers();
        cin>>ch;
        if(ch)
            for(int i=0;i<3;i++)
                mr[s+i].played=1;
        else;
    }
    void display(){
        cout<<setw(30)<<left<<name<<setw(30)<<left<<cap->getName()<<setw(10)<<right<<matches
            <<setw(10)<<right<<wins<<setw(10)<<right<<loss<<setw(10)<<right<<draw<<endl;
    }
    void displayMembers(){
        cout<<setw(20)<<left<<"Player ID"<<setw(30)<<right<<"NAME"<<endl;
        for(Player* m:members)
            m->displayName();
    }
};
int Team::noOfTeams=0;

struct TeamRec{
    int id;
    string name;
    int matches;
    int wins;
    int loss;
    int draw;
    void reset(){
        matches=0;
        wins=0;
        loss=0;
        draw=0;
    }
    TeamRec(Team *t){
        id=t->getId();
        name=t->getName();
        reset();
    }
    int getPoints(){
        return 2*wins+draw;
    }
    static bool comparePoints(TeamRec& tr1,TeamRec tr2){
        return tr1.getPoints()>tr2.getPoints();
    }
};

struct MatchState{
    int sFlag;
    int runs;
    int wickets;
    int currBat1;
    int currBat2;
    int currBow;
    int currKeep;
    float overs;
    void reset(){
        currBat1=-1;
        currBat2=-1;
        currBow=-1;
        currKeep=-1;
        overs=0;
        runs=0;
        wickets=0;
        sFlag=0;
    }
    MatchState(){
        reset();
    }
    void init(int cb1,int cb2,int cb,int ck){
        currBat1=cb1;
        currBat2=cb2;
        currBow=cb;
        currKeep=ck;
        overs=0;
        runs=0;
        wickets=0;
        if(!sFlag)
            sFlag=1;
        else
            sFlag=2;
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
    void incOvers(float o){
        overs+=(int)o;
        incBalls((o-(int)o)*10);
    }
    void swapBat(int &cb1,int &cb2){
        int p=currBat1;
        currBat1=currBat2;
        currBat2=p;
        p=cb1;
        cb1=cb2;
        cb2=p;
    }
    int getProjected(){
        int b=((int)overs*6)+((overs-(int)overs)*10);
        float rr=runs*1.0/b;
        return (int)(runs+rr*(1200-b));
    }
};
struct MatchResult{
    int runs;
    int wickets;
    float overs;
};
