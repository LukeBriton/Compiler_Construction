int main() {
  int a;
  int b;
  int mod;

  a = 114;
  println_int(a);
  b = 514;
  println_int(b);
  mod = a % b;
  println_int(mod);
  a = mod;
  println_int(a);
  b = mod % mod;
  println_int(b);

  return 0;
}
