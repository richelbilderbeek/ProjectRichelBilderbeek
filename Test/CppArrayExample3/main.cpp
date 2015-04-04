void iota(int a[], const int sz) {
  for (int i=0; i!=sz; ++i) {
    a[i] = i;
  }
}

int main() {
  int v[20];
  int w[10];
  iota(v,20);
  iota(w,20); //Oops
}
