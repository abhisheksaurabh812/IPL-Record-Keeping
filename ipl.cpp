#include"team.cpp"
#include<algorithm>
#include<fstream>

using namespace std;

class IPL{
    string heading;
    vector<Bowler> bowlers;
    vector<Batsman> batsmen;
    vector<AllRounder> allrounders;
    vector<Team> teams;
public:
    class Match{
        Team *team1;
        Team *team2;
        MatchState mState;
        vector<PlayerRec> mRec;
        MatchResult mr1;
        MatchResult mr2;
        bool swapped;
    public:
        Match(IPL &x,string t1,string t2){
            team1=x.getTeam(t1);
            team2=x.getTeam(t2);
            mRec.reserve(30);
            swapped=false;
        }
        void displayHead(){
            cout<<setw(29)<<left<<team1->getName()<<"vs"<<setw(29)<<right<<team2->getName()<<endl;
        }
        int getState(){
            return mState.sFlag;
        }
        int getRecIndex(int n){
            int i,ms=mRec.size();
            for(i=0;i<ms;i++)
                if(mRec[i].id==n)
                    return i;
        }
        void swapCurrTeam(){
            Team *t=team1;
            team1=team2;
            team2=t;
            swapped=(swapped)?false:true;
        }
        void setup0(){
            int ch;
            cout<<"Starting Match: "<<team1->getName()<<" vs "<<team2->getName()<<endl;
            cout<<setw(20)<<left<<"Team ID"<<setw(30)<<right<<"NAME"<<endl;
            team1->setupMatchRec(mRec);
            team2->setupMatchRec(mRec);
            cout<<setw(10)<<left<<"1."<<setw(30)<<right<<team1->getName()<<endl;
            cout<<setw(10)<<left<<"2."<<setw(30)<<right<<team2->getName()<<endl;
            cout<<"Enter the id of the team to bat first\n";
            cin>>ch;
            if(ch==2)
                swapCurrTeam();
        }
        void setup1(){
            int cb1,cb2,cb,ck;
            team1->displayMembers();
            cout<<"Enter the player IDs of the opening batsmen\n";
            cin>>cb1>>cb2;
            mRec[getRecIndex(cb1)].batted=1;
            mRec[getRecIndex(cb2)].batted=2;
            team2->displayMembers();
            cout<<"Enter the player IDs of opening bowler and wicket keeper\n";
            cin>>cb>>ck;
            mState.init(cb1,cb2,cb,ck);
        }
        void displayBatting(Team *te){
            int ms=mRec.size();
            sort(mRec.begin(),mRec.end(),PlayerRec::compareBatted);
            cout<<setw(30)<<left<<"NAME"<<setw(10)<<right<<"Runs"<<setw(10)<<right<<"Balls"<<setw(12)<<right<<"St. Rate\n";
            for(PlayerRec& pr:mRec)
                if(te->search(pr.id) && pr.batted>0)
                    cout<<setw(30)<<left<<pr.name<<setw(10)<<right<<pr.runsScored
                        <<setw(10)<<right<<pr.getBallsFaced()<<setw(12)<<right<<pr.getStrikeRate()<<endl;
        }
        void displayBowling(Team *te){
            int ms=mRec.size();
            sort(mRec.begin(),mRec.end(),PlayerRec::compareBowled);
            cout<<setw(30)<<left<<"NAME"<<setw(10)<<right<<"Runs"<<setw(12)<<right<<"Overs"<<setw(12)<<right<<"Run Rate\n";
            for(PlayerRec& pr:mRec)
                if(te->search(pr.id) && pr.oversBowled>0)
                    cout<<setw(30)<<left<<pr.name<<setw(10)<<right<<pr.runsGiven
                        <<setw(10)<<right<<pr.oversBowled<<setw(10)<<right<<pr.getRunRate()<<endl;
        }
        void displayStats(){
            int ch;
            Team *te;
            do{
                cout<<setw(20)<<left<<"Team ID"<<setw(30)<<right<<"NAME"<<endl;
                cout<<setw(20)<<left<<"1."<<setw(30)<<right<<team1->getName()<<endl;
                cout<<setw(20)<<left<<"2."<<setw(30)<<right<<team2->getName()<<endl;
                cout<<"Enter team number\n";
                cin>>ch;
                te=(ch==1)?team1:team2;
                cout<<"Welcome to match stats, Which stats do you want to display\n1. Batting Stats\n2. Bowling Stats\n";
                cin>>ch;
                if(ch==2&&getState()==1)
                    te=team2;
                switch(ch){
                    case 1: displayBatting(te);
                            break;
                    case 2: displayBowling(te);
                            break;
                }
                cout<<"Press 0  to return to match menu and 1 to display more stats\n";
                cin>>ch;
            }while(ch);
        }
        void displayScore(){
                cout<<team1->getName()<<" : "<<mState.runs<<"/"<<mState.wickets<<"\t"<<mState.overs<<"overs\n";
                if(mState.overs!=0)
                    cout<<"Projected Score : "<<mState.getProjected()<<endl;
                if(getState()==2)
                    cout<<"Need "<<1+mr1.runs-mState.runs<<" from "<<1200-(((int)mState.overs*6)+(mState.overs-(int)mState.overs)*10)<<" balls\n";
        }
        void displayResult(){
            if(swapped){
                cout<<setw(30)<<left<<team2->getName()<<mr1.runs<<"/"<<mr1.wickets<<" in "<<mr1.overs<<"overs\n";
                cout<<setw(30)<<left<<team1->getName()<<mr2.runs<<"/"<<mr2.wickets<<" in "<<mr2.overs<<"overs\n";
                if(mr1.runs>mr2.runs)
                    cout<<team2->getName()<<" won by "<<mr1.runs-mr2.runs<<" runs\n";
                else if(mr2.runs>mr1.runs)
                    cout<<team1->getName()<<" won by "<<10-mr2.wickets<<" wickets\n";
                else
                    cout<<"The match ended in a draw\n";
            }
            else
            {
                cout<<setw(30)<<left<<team1->getName()<<mr1.runs<<"/"<<mr1.wickets<<" in "<<mr1.overs<<"overs\n";
                cout<<setw(30)<<left<<team2->getName()<<mr2.runs<<"/"<<mr2.wickets<<" in "<<mr2.overs<<"overs\n";
                if(mr1.runs>mr2.runs)
                    cout<<team1->getName()<<" won by "<<mr1.runs-mr2.runs<<" runs\n";
                else if(mr2.runs>mr1.runs)
                    cout<<team2->getName()<<" won by "<<10-mr2.wickets<<" wickets\n";
                else
                    cout<<"The match ended in a draw\n";
            }

        }
        void displayResult1(){
            mr1.runs=mState.runs;
            mr1.wickets=mState.wickets;
            mr1.overs=mState.overs;
            cout<<team1->getName()<<" : "<<mState.runs<<"/"<<mState.wickets<<"\t"<<mState.overs<<"overs\n";
            cout<<team2->getName()<<" Needs "<<mState.runs+1<<" runs from 20 overs\n";
        }
        void displayResult2(){
            mr2.runs=mState.runs;
            mr2.wickets=mState.wickets;
            mr2.overs=mState.overs;
            swapCurrTeam();
            mState.sFlag=3;
            if(mr1.runs>mr2.runs)
                cout<<team2->getName()<<" won by "<<mr1.runs-mr2.runs<<" runs\n";
            else if(mr2.runs>mr1.runs)
                cout<<team1->getName()<<" won by "<<10-mr2.wickets<<" wickets\n";
            else
                cout<<"The match ended in a draw\n";
        }
        void wicket(int &cb1,int &cb2,int &cb,int &ck){
            int ch,r;
            mState.wickets++;
            cout<<"Was it a:\n1. Bowled/catch/LBW\n2. Stump\n3. Run out\n";
            cin>>ch;
            switch(ch){
                case 1: mRec[cb].wickets++;
                        team1->displayMembers();
                        cout<<"Enter the player ID of the next batsmen\n";
                        cin>>mState.currBat1;
                        cb1=getRecIndex(mState.currBat1);
                        mRec[cb1].batted=mState.wickets+2;
                        break;
                case 2: mRec[ck].stumps++;
                        team1->displayMembers();
                        cout<<"Enter the player ID of the next batsmen\n";
                        cin>>mState.currBat1;
                        cb1=getRecIndex(mState.currBat1);
                        mRec[cb1].batted=mState.wickets+2;
                        break;
                case 3: cout<<"How many runs were taken?\n";
                        cin>>r;
                        mState.runs+=r;
                        mRec[cb1].runsScored+=r;
                        if(!mRec[cb1].fifty && mRec[cb1].runsScored>50)
                            mRec[cb1].fifty=1;
                        mRec[cb].runsGiven+=r;
                        if(r%2)
                            mState.swapBat(cb1,cb2);
                        cout<<"Who got out?\n";
                        cout<<setw(10)<<left<<"1."<<setw(30)<<right<<team1->getPlayerName(mState.currBat1)<<endl;
                        cout<<setw(10)<<left<<"2."<<setw(30)<<right<<team1->getPlayerName(mState.currBat2)<<endl;
                        cin>>ch;
                        team1->displayMembers();
                        cout<<"Enter the player ID of the next batsmen\n";
                        if(ch==1){
                            cin>>mState.currBat1;
                            cb1=getRecIndex(mState.currBat1);
                            mRec[cb1].batted=mState.wickets+2;
                        }
                        else{
                            cin>>mState.currBat2;
                            cb2=getRecIndex(mState.currBat2);
                            mRec[cb2].batted=mState.wickets+2;
                        }

            }
        }
        void proceed(){
            int cb1,cb2,cb,ck,ch,r;
            if(!getState()){
                setup0();
                setup1();
            }
            do{
                displayScore();
                if(mState.overs==20 || mState.wickets==10){
                    if(getState()!=2){
                        displayResult1();
                        swapCurrTeam();
                        setup1();
                    }
                    else{
                        displayResult2();
                        cin.sync();
                        cin.get();
                        return;
                    }
                }
                else if(getState()==2 && mState.runs>mr1.runs){
                    displayResult2();
                    cin.sync();
                    cin.get();
                    return;
                }
                else if(mState.overs==(int)mState.overs&&mState.overs)
                {
                    mState.swapBat(cb1,cb2);
                    team2->displayMembers();
                    cout<<"Enter the player ID of the next bowler\n";
                    cin>>mState.currBow;
                }
                cb1=getRecIndex(mState.currBat1);
                cb2=getRecIndex(mState.currBat2);
                cb=getRecIndex(mState.currBow);
                ck=getRecIndex(mState.currKeep);
                cout<<"What happened?\n1. Runs taken\n2. Four\n3. Six\n4. Wicket\n5. Wide\n6. No Ball\n0. Match Menu\n";
                cin>>ch;
                switch(ch){
                    case 1: mState.incBall();
                            cout<<"How many runs?\n";
                            cin>>r;
                            mState.runs+=r;
                            mRec[cb1].runsScored+=r;
                            if(!mRec[cb1].fifty && mRec[cb1].runsScored>50)
                                mRec[cb1].fifty=1;
                            mRec[cb1].incBallFaced();
                            mRec[cb].incBallBowled();
                            mRec[cb].runsGiven+=r;
                            if(r%2)
                                mState.swapBat(cb1,cb2);
                            break;
                    case 2: mState.incBall();
                            mState.runs+=4;
                            mRec[cb1].runsScored+=4;
                            if(!mRec[cb1].fifty && mRec[cb1].runsScored>50)
                                mRec[cb1].fifty=1;
                            mRec[cb1].incBallFaced();
                            mRec[cb].incBallBowled();
                            mRec[cb].runsGiven+=4;
                            break;
                    case 3: mState.incBall();
                            mState.runs+=6;
                            mRec[cb1].runsScored+=6;
                            if(!mRec[cb1].fifty && mRec[cb1].runsScored>50)
                                mRec[cb1].fifty=1;
                            mRec[cb1].incBallFaced();
                            mRec[cb].incBallBowled();
                            mRec[cb].runsGiven+=6;
                            break;
                    case 4: mState.incBall();
                            mRec[cb1].incBallFaced();
                            mRec[cb].incBallBowled();
                            wicket(cb1,cb2,cb,ck);
                            break;
                    case 5: mState.runs++;
                            mRec[cb].runsGiven++;
                            break;
                    case 6: mState.runs++;
                            mRec[cb].runsGiven++;
                            cout<<"Was a free hit given\n1. Yes\n2. No\n";
                            cin>>r;
                            if(r==2){

                            }
                }
            }while(ch);
        }
        void displayState(){
            int cb1,cb2,cb,ck;
            cb1=getRecIndex(mState.currBat1);
            cb2=getRecIndex(mState.currBat2);
            cb=getRecIndex(mState.currBow);
            ck=getRecIndex(mState.currKeep);
            cout<<"Batting at striker's end : "<<mRec[cb1].name<<endl;
            cout<<"Batting at non-striker's end : "<<mRec[cb2].name<<endl;
            cout<<"Bowler : "<<mRec[cb].name<<endl;
            cout<<"Keeper : "<<mRec[ck].name<<endl;
        }
        void displayMatchMenu(){
            int s=getState();
            cout<<"                 Match Menu:\n";
                cout<<team1->getName()<<" vs "<<team2->getName()<<endl;
            switch(s){
                case 0: cout<<"\n1. Start Match\n";
                        break;
                case 1:
                case 2: cout<<"1. Start record keeping\n";
                        cout<<"2. Display stats\n";
                        cout<<"3. Skip 18 overs\n";
                        cout<<"4. Change keeper\n";
                        cout<<"5. Display match state\n";
                        cout<<"6. Restart match\n";
                        break;
                case 3: cout<<"1. Display result\n";
                        cout<<"2. Display stats\n";
            }
            cout<<"0. Go back to tournament menu\n";
        }
        int enterMatch(){
            int ch,i;
            do{
                system("CLS");
                displayMatchMenu();
                cin>>ch;
                switch(ch){
                    case 1: system("CLS");
                            if(getState()==3)
                                displayResult();
                            else
                                proceed();
                            break;
                    case 2: displayStats();
                            break;
                    case 3: if(getState()!=3)
                                mState.incOvers(18);
                            break;
                    case 4: team2->displayMembers();
                            cout<<"Enter the player id of the new keeper\n";
                            cin>>mState.currKeep;
                            break;
                    case 5: displayState();
                            break;
                    case 6: mState.reset();
                            for(PlayerRec& pr:mRec)
                                pr.reset();
                            cout<<"Match data erased, you can now restart the match.\nPress enter to continue\n";
                            break;
                    case 0: if(getState()==3)
                                return 1;
                            return 0;
                }
                cin.sync();
                if(ch!=1&&ch!=2)
                    cin.get();
            }while(1);
        }
        int getResult(){
            if(mr1.runs>mr2.runs)
                return 1;
            else if(mr2.runs>mr1.runs)
                return 2;
            else
                return 0;
        }
        int getTeamId(int i){
            if(i==1)
                return team1->getId();
            else
                return team2->getId();
        }
        int getRecSize(){
            return mRec.size();
        }
        PlayerRec& getRec(int i){
            return mRec[i];
        }
    };

    class Tournament{
        string year;
        vector<PlayerRec> pRec;
        vector<TeamRec> tRec;
        vector<Match> matchList;
        int cmno;
    public:
        Tournament(){
            pRec.reserve(Player::noOfPlayers);
            tRec.reserve(Team::noOfTeams);
            matchList.reserve(20);
            cmno=-1;
        }
        void setupRec(IPL &x){
            pRec.clear();
            tRec.clear();
            int i,bas=x.batsmen.size(),bos=x.bowlers.size(),alls=x.allrounders.size(),tes=x.teams.size();
            for(i=0;i<bas;i++)
                pRec.emplace_back(&(x.batsmen[i]));
            for(i=0;i<bos;i++)
                pRec.emplace_back(&(x.bowlers[i]));
            for(i=0;i<alls;i++)
                pRec.emplace_back(&(x.allrounders[i]));
            for(i=0;i<tes;i++)
                tRec.emplace_back(&(x.teams[i]));
            //for(Player* p:&(x.allrounders))
            //    pRec.emplace_back(p); - Not Working
        }
        void attachMatchList(IPL &x){
            matchList.clear();
            int n;
            char c;
            string t0,t1,t2;
            t0=t1=t2="";
            ifstream myFile;
            myFile.open("Matches.txt");
            while(myFile.get(c)&&c!='\n')
                t0+=c;
            n=stoi(t0);
            while(n--){
                while(myFile.get(c)&&c!=',')
                    t1+=c;
                while(myFile.get(c)&&c!='\n')
                    t2+=c;
                matchList.emplace_back(x,t1,t2);
                t1=t2="";
            }
            setupRec(x);
        }
        int getTRecIndex(int n){
            int i,ts=tRec.size();
            for(i=0;i<ts;i++)
                if(tRec[i].id==n)
                    return i;
        }
        int getPRecIndex(int n){
            int i,ps=pRec.size();
            for(i=0;i<ps;i++)
                if(pRec[i].id==n)
                    return i;
        }
        void flush(){
            int i,j,r,ms=matchList[cmno].getRecSize();
            for(i=0;i<ms;i++){
                PlayerRec& rec=matchList[cmno].getRec(i);
                j=getPRecIndex(rec.id);
                if(rec.played)
                    pRec[j].played++;
                if(rec.batted)
                    pRec[j].batted++;
                if(rec.fifty)
                    pRec[j].fifty++;
                pRec[j].stumps+=rec.stumps;
                pRec[j].runsScored+=rec.runsScored;
                pRec[j].incOversFaced(rec.oversFaced);
                pRec[j].runsGiven+=rec.runsGiven;
                pRec[j].incOversBowled(rec.oversBowled);
                pRec[j].wickets+=rec.wickets;
            }
            i=getTRecIndex(matchList[cmno].getTeamId(1));
            j=getTRecIndex(matchList[cmno].getTeamId(2));
            r=matchList[cmno].getResult();
            tRec[i].matches++;
            tRec[j].matches++;
            switch(r){
                case 1: tRec[i].wins++;
                        tRec[j].loss++;
                        break;
                case 2: tRec[i].loss++;
                        tRec[j].wins++;
                        break;
                default:tRec[i].draw++;
                        tRec[j].draw++;
            }
            cmno++;
        }
        void displayPointsTable(){
            sort(tRec.begin(),tRec.end(),TeamRec::comparePoints);
            cout<<setw(30)<<left<<"TEAM"<<setw(10)<<right<<"MATCHES"<<setw(10)<<right<<"WINS"
                <<setw(10)<<right<<"LOSSES"<<setw(10)<<right<<"DRAWS"<<setw(10)<<right<<"POINTS"<<endl;
            for(TeamRec& tr:tRec)
                cout<<setw(30)<<left<<tr.name<<setw(10)<<right<<tr.matches<<setw(10)<<right<<tr.wins
                    <<setw(10)<<right<<tr.loss<<setw(10)<<right<<tr.draw<<setw(10)<<right<<tr.getPoints()<<endl;
        }
        void displayMatchList(){
            cout<<setw(30)<<left<<"TEAM 1"<<setw(30)<<right<<"Team 2"<<endl;
            for(IPL::Match& m:matchList)
                m.displayHead();
        }
        void displayAllPlayerStats(){
            sort(pRec.begin(),pRec.end(),PlayerRec::compareTeam);
            cout<<setw(30)<<left<<"NAME"<<setw(10)<<right<<"Matches"<<setw(10)<<right<<"Stumpings"<<setw(15)<<right<<"Innings Batted"
                <<setw(15)<<right<<"Runs Scored"<<setw(10)<<right<<"Fifties"<<setw(15)<<right<<"Overs Bowled"<<setw(15)<<right<<"Runs Given"<<setw(10)<<right<<"Wickets"<<endl<<endl;
            for(PlayerRec& p:pRec)
                cout<<setw(30)<<left<<p.name<<setw(10)<<right<<p.played<<setw(10)<<right<<p.stumps<<setw(15)<<right<<p.batted
                <<setw(15)<<right<<p.runsScored<<setw(10)<<right<<p.fifty<<setw(15)<<right<<p.oversBowled<<setw(15)<<right<<p.runsGiven<<setw(10)<<right<<p.wickets<<endl;
        }
        void displayOrangeCap(){
            sort(pRec.begin(),pRec.end(),PlayerRec::compareRunsScored);
            cout<<setw(30)<<left<<"NAME"<<setw(15)<<right<<"Runs Scored"<<endl<<endl;
            for(int i=0;i<10;i++)
                cout<<setw(30)<<left<<pRec[i].name<<setw(15)<<right<<pRec[i].runsScored<<endl;
        }
        void displayPurpleCap(){
            sort(pRec.begin(),pRec.end(),PlayerRec::compareWickets);
            cout<<setw(30)<<left<<"NAME"<<setw(15)<<right<<"Wickets"<<endl<<endl;
            for(int i=0;i<10;i++)
                cout<<setw(30)<<left<<pRec[i].name<<setw(15)<<right<<pRec[i].wickets<<endl;
        }
        void displayStats(){
            int ch;
            do{
                system("CLS");
                cout<<"              Tournament Stats\n";
                cout<<"1. Display all player stats\n2. Orange Cap\n3. Purple Cap\n0. Back to tournament menu\nEnter your choice\n";
                cin>>ch;
                switch(ch){
                    case 1: displayAllPlayerStats();
                            break;
                    case 2: displayOrangeCap();
                            break;
                    case 3: displayPurpleCap();
                }
                cin.sync();
                if(!ch)
                    cin.get();
            }while(ch);
        }
        void continueTournament(IPL &x){
            int ch;
            if(cmno==-1){
                attachMatchList(x);
                cmno=0;
            }
            do{
                system("CLS");
                cout<<"               Tournament Menu\n";
                cout<<"1. Display points table\n2. Enter current match\n3. Display stats\n4. Display Match List\n0. Back\n";
                cin>>ch;
                switch(ch){
                    case 1: displayPointsTable();
                            break;
                    case 2: ch=matchList[cmno].enterMatch();
                            if(ch)
                                flush();
                            ch=2;
                            continue;
                    case 3: displayStats();
                            break;
                    case 4: displayMatchList();
                            break;
                }
                cin.sync();
                if(ch||ch!=2)
                    cin.get();
            }while(ch);
        }
    };

    IPL(string h,vector<Bowler> &bo,vector<Batsman> &ba,vector<AllRounder> &babo,vector<Team> &t)
        :heading(h),bowlers(bo),batsmen(ba),allrounders(babo),teams(t){}

    void displayHead(){
        cout<<heading<<endl;
    }
    void assignTeams(){
        int i,j,max=0,maxj,bos=bowlers.size(),bas=batsmen.size(),alls=allrounders.size(),ts=teams.size();
        for(i=0;i<bas;i++){
            batsmen[i].assignToTeam(i%ts);
            teams[i%ts].addPlayer(&batsmen[i]);
        }
        for(i=0;i<bos;i++){
            bowlers[i].assignToTeam(i%ts);
            teams[i%ts].addPlayer(&bowlers[i]);
        }
        for(i=0;i<alls;i++){
            teams[i%ts].addPlayer(&allrounders[i]);
            allrounders[i].assignToTeam(i%ts);
        }
        for(i=0;i<ts;i++)
            teams[i].autoCap();
    }
    Team* getTeam(string tn){
        for(Team& t:teams)
            if(!t.getName().compare(tn))
                return &t;
    }
    string getTeamName(int i){
        for(Team& t:teams)
            if(t.getId()==i)
                return t.getName();
    }
    void displayPlayer(string pn){
        for(Bowler& bo:bowlers){
            if(!bo.getName().compare(pn)){
                bo.display();
                return;
            }
        }
        for(Batsman& ba:batsmen){
            if(!ba.getName().compare(pn)){
                ba.display();
                return;
            }
        }
        for(AllRounder& all:allrounders){
            if(!all.getName().compare(pn)){
                all.display();
                return;
            }
       }
       cout<<"Player not found, press enter to continue\n";
       cin.get();
    }
    void displayTeams(){
        cout<<setw(30)<<left<<"Name"<<setw(30)<<left<<"Captian"<<setw(10)<<right<<"Matches"
            <<setw(10)<<right<<"Wins"<<setw(10)<<right<<"Losses"<<setw(10)<<right<<"Draws"<<endl;
        for(Team& t:teams){
            t.display();
        }
    }
};

