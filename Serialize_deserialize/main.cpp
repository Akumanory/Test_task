#include <cstdio>
#include "list.h"

#include <iostream>

int main()
{
    List test;

    test.InsertTail("test_1");
    test.InsertTail("test_2", test.AtIndex(0));
    test.InsertTail("test_3");
    test.InsertTail("test_4", test.AtIndex(1));
    test.InsertTail("test_5");
    test.InsertHead("test_6", test.AtIndex(1));

    std::cout << "Before" << std::endl;
    test.PrintList();

    FILE * write_file = std::fopen("files/test_w", "wb");

    test.Serialize(write_file);
    std::fclose(write_file);

    FILE * read_file = std::fopen("files/test_w", "rb");

    test.Deserialize(read_file);
    std::fclose(read_file);

    std::cout << "After" << std::endl;
    test.PrintList();

    return 0;
}