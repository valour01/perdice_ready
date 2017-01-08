#include <iostream>
#include <list>
using namespace std;

#include "s2e.h"

#include <fstream>
using std::ifstream;

#include <string.h>

//argv[1]: input pdf file
//argv[2]: output pdf file
char buf[1];
char out[512000];
int count=0;
int main(int argc, char* argv[])
{
ifstream fin;
ofstream fout;

fin.open(argv[1], ios::in|ios::binary); // open the file need to be converted
fout.open(argv[2], ios::out|ios::binary); 
if ((!fin.good()) || (!fout.good())) return 1; // exit if file not found 
  while (!fin.eof())
  {
    // read an entire line into memory    
    fin.read(buf, 1);	
    out[count]=buf[0];
    s2e_make_concolic(&out[count],1,"sym_byte");
    s2e_disable_forking();    
    count++;
  }
  fout.write(out, count);	   
fin.close();
fout.close();
return 0;
}