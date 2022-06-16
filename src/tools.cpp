#include "tools.h"

void readBin(std::string path, float *data, int len)
{
    double fnum[len] = {0};
    std::ifstream in(path, std::ios::in | std::ios::binary);
    in.read((char *) &fnum, sizeof fnum);
    for(int i=0; i<len; i++)
    {
        data[i] = (float)fnum[i];
    }
    in.close();
}

void writeTxt(std::string path, float *buf, int size)
{
  std::ofstream outfile(path, std::ios::trunc);
  for (int i = 0; i < size; i++)
  {
       outfile << buf[i] << " ";
  }
  outfile.close();
  
}

void readTxt(std::string path, float * buf, int size)
{
    std::ifstream myfile(path);
    for (int i = 0; i < size; i++)
    {
        myfile >> buf[i];
        /* code */
    }
    
}