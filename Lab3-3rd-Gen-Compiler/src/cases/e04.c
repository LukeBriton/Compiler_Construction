int test(int arg1, int arg2) { return (arg1 + arg2) * arg1 / arg2 & arg1; }

int main(){
    int a = 114, b = 514;
    println_int(1+test(a*b, a+b));
    return 0;
}
