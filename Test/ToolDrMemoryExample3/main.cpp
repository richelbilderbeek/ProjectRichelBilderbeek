void Good()
{
  int * p = new int[10];
  delete[] p;
}

void Bad()
{
  int * p = new int[10];
  delete p; //Bad: memory leak, should call delete[]
}

int main()
{
  Good();
  Bad();
  Good();
  Bad();
}
