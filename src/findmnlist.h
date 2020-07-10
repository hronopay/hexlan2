#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
//#include <conio.h>

using namespace std;
class Char35Adr
{
public:
    char sca[35];
    Char35Adr(string scamadr){
        strcpy (sca, scamadr.c_str());
    }

    void f()
    {
        //cout << "Char35Adr::f - " << sca << endl;
        LogPrintf("Char35Adr::f -  %s \n", sca); 

    }

    string toString()
    {
        return sca;
    }

    int elemsize(){
        return sizeof(sca);
    }
};


class MnTxHash
{
public:
    char txha[65];
    MnTxHash(string txhash){
        strcpy (txha, txhash.c_str());
    }

    void f()
    {
        cout << "MnTxHash::f - " << txha << endl;
    }

    string toString()
    {
        return txha;
    }

    int elemsize(){
        return sizeof(txha);
    }
};


class FindMnList
{
private:
    bool erasefirstisdone;
    int lastcollateral;
 
public:
    vector<Char35Adr> arr;
    vector<MnTxHash> txhash;
    FindMnList(){
        erasefirstisdone = false;
        lastcollateral = 0;
        arr.push_back( Char35Adr("0000000000000000000000000000000000") );
        txhash.push_back( MnTxHash("0000000000000000000000000000000000000000000000000000000000000000") );
    }

    void reInitialyze(){
        if(erasefirstisdone){
            erasefirstisdone = false;
        }
        for(int k=0; k<this->sizeMn(); k++){
            arr[k] = Char35Adr("0000000000000000000000000000000000");
            txhash[k] = MnTxHash("0000000000000000000000000000000000000000000000000000000000000000");
        }
        for(int k=(this->sizeMn()-1); k>0; k--){
            this->erase(k);
            LogPrintf("reInitialyze(): ERASE k=%d \n", k);
        }
    }

    void checkCollateral(int currentColl){
        if(!lastcollateral) lastcollateral = currentColl;  // if this is first collateral we only initialyze lastcollateral value 
        else if(currentColl != lastcollateral) {
            lastcollateral = currentColl;
            this->reInitialyze();
        }
    }

    void vinit(string adr, string hash){
        arr.push_back( Char35Adr(adr) ); 
        txhash.push_back( MnTxHash(hash) ); 
    }

    void eraseFirst(){
        if(!erasefirstisdone){
            arr.erase(arr.begin());
            txhash.erase(txhash.begin());
            erasefirstisdone = true;
        }
        else {
            LogPrintf("   ___eraseFirst()___  HAS BEEN ERASED ALREADY \n");
        }

        return;
    }


    void erase(int k){
        arr.erase(arr.begin()+k);
        txhash.erase(txhash.begin()+k);
        LogPrintf("   ___erase()___  done\n");
        return;
    }


    void print()
    {
        for(unsigned i = 0; i < arr.size(); ++i)
        {
            arr[i].f();
            txhash[i].f();
        }
    }

    string getValueMn(int i)
    {
        return arr[i].toString();
    }


    string getValueHash(int i)
    {
        return txhash[i].toString();
    }

    int sizeMn(){
        return arr.size()/* * sizeof(Char35Adr)*/;
    }

    int sizeHash(){
        return txhash.size()/* * sizeof(Char35Adr)*/;
    }
 /*
    void txtWrite(string path){
        ofstream fout;
        fout.open(path, ios::out | ios::trunc );  
        if(!fout.is_open()){
            cout << "txtWrite(): open out-file error" << endl;
        }
        else {
            if ( (fout.rdstate() & std::ofstream::failbit ) != 0 ) 
                cout << "txtWrite(): Error opening 'myfile.txt'\n";

            cout << "txtWrite(): out-file " << path << " was opened" << endl;
            //fout << "txtWrite(): Writing this to a file.\n";
            for(unsigned i=0; i<arr.size(); i++) fout << arr[i].toString() << "\n";
        }
        fout.close();
        return;
    }

    void binWrite(string path){
        ofstream fout;
        //    fout.open(path, ofstream::app);   //   ios::out | ios::app | ios::binary
        fout.open(path, ios::out | ios::trunc | ios::binary);  
        if(!fout.is_open()){
            cout << "binWrite(): open out-file error" << endl;
        }
        else {
            if ( (fout.rdstate() & std::ofstream::failbit ) != 0 ) cout << "binWrite(): Error opening 'myfile.bin'\n";

            cout << "binWrite(): out-file " << path << " was opened" << endl;
            fout.write((char*)&this->arr, this->size());
            cout << "binWrite(): " << this->size() << " bytes were written down" << endl;
        }
        fout.close();
        return;
    }


    void binRead(string path){
        ifstream fin;
        fin.open(path, ios::binary);
        if(!fin.is_open()){
            cout << "binRead(): open in-file error" << endl;
        }
        else {
            cout << "binRead(): in-file " << path << " was opened" << endl;
            cout << "binRead(): inadr.size is " << this->size() << endl;
            fin.read( (char*)&this->arr, this->size() );
        }
        fin.close();
        return;
    }
 */
};
 


/*
int main()
{
    // make vector supposedMnList  and fill the data in vector supposedMnList
    FindMnList supposedMnList;

    supposedMnList.vinit("BYJpT4Xv3zUCkL1E4bc1SYty99GBx5EoNR");
    supposedMnList.vinit("BrApRfvHQLN33azFBGzTDcxoHMxrvrvqdm");
    supposedMnList.vinit("BUTSSfbuMEQz8TwepxvseRuUWLDcUJSJuw");

    supposedMnList.eraseFirst();

    // file name for dumping vector supposedMnList data in binary mode
    string path = "filename.bin";

    // dump vector supposedMnList data in binary mode to that file
    supposedMnList.binWrite(path);

    // pause
    getch();

    // make empty data vector inadr
    FindMnList inadr;

    // fill vector inadr with vector supposedMnList data from that file (path)
    inadr.binRead(path);

    // print to screen vector inadr content
    inadr.print();

    // print to path2 file the vector inadr content in text mode for  additional checking up
    string path2 = "myfile4.txt";
    inadr.txtWrite(path2);

    return (0);
    //return a.exec();
}
*/



 
class CLockAdr
{
private:
    bool erasefirstisdone;
    unsigned int signalOnVal;
    unsigned int signalOffVal;

public:
    vector<Char35Adr> scammeradr;
    bool islockerset;
    bool istxlistset;
    int txlistsetuntil;
    CLockAdr(){
        signalOnVal = 12343200;  // 0.123432
        signalOffVal = 12131400; // 0.121314
        erasefirstisdone = false;
        islockerset = false;
        istxlistset = false;
        txlistsetuntil = 4;
        scammeradr.push_back( Char35Adr("0000000000000000000000000000000000") );
    }

    int getTxListSetUntill(){
        return txlistsetuntil;
    }

    void setTxListSetUntill(int height){
        txlistsetuntil = height;
    }

    int getOnVal(){
        return this->signalOnVal;
    }

    int getOffVal(){
        return this->signalOffVal;
    }


    void reInitialyze(){
        if(erasefirstisdone){
            erasefirstisdone = false;
        }
        for(int k=0; k<this->sizeMn(); k++){
            scammeradr[k] = Char35Adr("0000000000000000000000000000000000");
        }
        for(int k=(this->sizeMn()-1); k>0; k--){
            this->erase(k);
            LogPrintf("LockAdr reInitialyze(): ERASE k=%d \n", k);
        }
    }

    void vinit(string adr){
        scammeradr.push_back( Char35Adr(adr) ); 
    }

    void eraseFirst(){
        if(!erasefirstisdone){
            scammeradr.erase(scammeradr.begin());
            erasefirstisdone = true;
        }
        else {
            LogPrintf("LockAdr   ___eraseFirst()___  HAS BEEN ERASED ALREADY \n");
        }

        return;
    }


    void erase(int k){
        scammeradr.erase(scammeradr.begin()+k);
        LogPrintf("LockAdr   ___erase()___  done\n");
        return;
    }


    void print()
    {
        for(unsigned i = 0; i < scammeradr.size(); ++i)
        {
            scammeradr[i].f();
        }
    }

    void print(int i)
    {
            scammeradr[i].f();
    }

    string getAdrValue(int i)
    {
        return scammeradr[i].toString();
    }

    int sizeMn(){
        return scammeradr.size()/* * sizeof(Char35Adr)*/;
    }

};
 


class CBlList
{
private:

public:
    CLockAdr scad;
    vector<int> timestamp;
    vector<int> on;
    CBlList(){
        // initialyze for 1st
        timestamp.push_back(0);

        int t=1581348040;

        // initialyze next
        this->add("BYJpT4Xv3zUCkL1E4bc1SYty99GBx5EoNR", t, 1);
        this->add("BrApRfvHQLN33azFBGzTDcxoHMxrvrvqdm", t, 1);
        this->add("BUTSSfbuMEQz8TwepxvseRuUWLDcUJSJuw", t, 1);
        this->add("Bg63V2LyaJgWxrTJvhmBJrMK2cR4G2puTD", t, 1);
        this->add("HYjhEeUUkLBWEKy7q2ECWckWAoEsMTsRtT", t, 1);
    }

    void add(string adr, int time, int task){
        scad.vinit(adr);
        timestamp.push_back(time);
        on.push_back(task);
    }

    void del(int n){
        scad.erase(n);
        timestamp.erase(timestamp.begin()+n);
        on.erase(on.begin()+n);
    }

    void removeCanceled(){
        for(unsigned i = 0; i < this->sizeoflist(); ++i)
        {
            for(unsigned j = i+1; j < this->sizeoflist(); ++j)
            {
                if(address(i) == address(j)) {
                    this->removeOneOrBoth(i,j);
                    this->removeCanceled(); // iteractive call
                }
            }
        }
    }

    void removeOneOrBoth(unsigned i, unsigned j){
        // on[i] > on[j]
        if      ( on[i] > on[j] && timestamp[i] > timestamp[j]) this->del(j);
        else if ( on[i] > on[j] && timestamp[j] >= timestamp[i]) { 
            this->del(j);
            this->del(j);
        }
        // on[i] < on[j]
        else if ( on[i] < on[j] && timestamp[i] > timestamp[j]) { 
            this->del(j);
            this->del(j);
        }
        else if ( on[i] < on[j] && timestamp[i] <= timestamp[j]) this->del(i);

        // on[i] = on[j]
        else if ( on[i] == on[j] ) {
            if(timestamp[i] <= timestamp[j]) 
                this->del(j);
            else  
                this->del(i);
        }

    }

    unsigned int sizeoflist(){
        return scad.sizeMn();
    }

    string address(int k){
        return scad.getAdrValue(k);
    }

    int timeStamp(int k){
        return timestamp[k];
    }

    void timestampoutput(int k)
    {
        //cout << "timestampoutput::f - " << timestamp[k] << endl;
        LogPrintf("timestamp %d = %s ", timestamp[k], DateTimeStrFormat("%x %H:%M:%S", timestamp[k])); 
    }

    void onOutput(int k)
    {
        //cout << "timestampoutput::f - " << timestamp[k] << endl;
        LogPrintf(" on= %d\n", on[k]); 
    }

    void printList()
    {
        for(unsigned i = 0; i < this->sizeoflist(); ++i)
        {
            scad.print(i);
            this->timestampoutput(i);
            this->onOutput(i);
        }
    }



};

