#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
//#include <conio.h>

using namespace std;
class MnAdr
{
public:
    char sca[35];
    MnAdr(string scamadr){
        strcpy (sca, scamadr.c_str());
    }

    void f()
    {
        cout << "MnAdr::f - " << sca << endl;
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
    vector<MnAdr> arr;
    vector<MnTxHash> txhash;
    FindMnList(){
        erasefirstisdone = false;
        lastcollateral = 0;
        arr.push_back( MnAdr("0000000000000000000000000000000000") );
        txhash.push_back( MnTxHash("0000000000000000000000000000000000000000000000000000000000000000") );
    }

    void reInitialyze(){
        if(erasefirstisdone){
            erasefirstisdone = false;
        }
        for(int k=0; k<this->sizeMn(); k++){
            arr[k] = MnAdr("0000000000000000000000000000000000");
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
        arr.push_back( MnAdr(adr) ); 
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
        return arr.size()/* * sizeof(MnAdr)*/;
    }

    int sizeHash(){
        return txhash.size()/* * sizeof(MnAdr)*/;
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
