extern "C"
{
    int printf(const char *format, ...);
}

void binary_representaion(int value)
{
    for (auto i = (int)sizeof(value) * 8 - 1; i >= 0; i--)
    {
        printf ("%d", ((value >> i) & 1));
    }
    printf ("\n");
}

int main()
{
    binary_representaion(-2147483648);
    binary_representaion(-1073741824);
    binary_representaion(2147483647);
    binary_representaion(2147483647 >> 1);
    binary_representaion(2);
    binary_representaion(-2);

    return 0;
}