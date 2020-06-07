//#include <QCoreApplication>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <conio.h>

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
 
class FindMnList
{
private:
 
public:
    vector<MnAdr> arr;
    FindMnList(){
        arr.push_back( MnAdr("0000000000000000000000000000000000") );
    }

    FindMnList(string adr){
        arr.push_back( MnAdr(adr) ); 
    }

    void vinit(string adr){
        arr.push_back( MnAdr(adr) ); 
    }

    void eraseFirst(){
        arr.erase(arr.begin());
    }

/*
    void vinit()
    {
        arr[0] = MnAdr("BYJpT4Xv3zUCkL1E4bc1SYty99GBx5EoNR");
        arr[1] = MnAdr("BrApRfvHQLN33azFBGzTDcxoHMxrvrvqdm");
        arr[2] = MnAdr("BUTSSfbuMEQz8TwepxvseRuUWLDcUJSJuw");
        arr[3] = MnAdr("Bg63V2LyaJgWxrTJvhmBJrMK2cR4G2puTD");
    } */

    void print()
    {
        for(unsigned i = 0; i < arr.size(); ++i)
        {
            arr[i].f();
        }
    }

    int size(){
        return arr.size() * sizeof(MnAdr);
    }

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

};
 



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
