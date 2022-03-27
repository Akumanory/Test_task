#include <cstdio>
#include "list.h"

#include <iostream>

int main()
{
    List test;

    test.InsertTail("test_1");
    test.InsertTail("test_2");

    FILE* file_write = std::fopen("files/test_w", "wb");
    test.Serialize(file_write);

    FILE* file_read = std::fopen("files/test_w", "rb");
    test.Deserialize(file_read);

    // std::cout << test.AtIndex(1)->data << std::endl;

    // test.InsertTail("test_3");
    // test.PrintList();



    // std::cout << "Size: " << test.Size() << std::endl;

    // for (auto it = test.iterator(); it.has_next(); it.next())
    // {
    //     auto temp = it.get();

    //     std::cout << "Str: " << temp->data << std::endl;
    //     if (temp->rand == nullptr)
    //     {
    //         std::cout << "Rand is nullptr"  << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "Rand is pointing on something"  << std::endl;
    //     }
    // }




    return 0;
}