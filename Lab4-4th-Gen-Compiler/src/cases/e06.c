int main() {
    int i = 0;

    while (i < 11) {
        if (i % 7 == 3) {
            println_int(i);
            break;
        }
        
        if (i % 2 == 0) {
            println_int(i);
        }

        i = i + 1;
    }
    
    return 0;
}
