#include "list.h"

#include <iostream>

//Iterator
List::Iterator::Iterator(const List * list)
{
    start_from_head = list->head;
}

const ListNode* List::Iterator::get() const
{
    return start_from_head;
}

void List::Iterator::set(const std::string &value, ListNode* const rand)
{
    start_from_head->data = value;
    if (rand != nullptr)
    {
        start_from_head->rand = rand;
    }

}

void List::Iterator::next()
{
    start_from_head = start_from_head->next;
}

bool List::Iterator::has_next() const
{
    if (start_from_head == nullptr)
    {
        return false;
    }
    return true;
}

// List
List::List()
{
    head = new ListNode();
    tail = head;
    count = 0;
}

List::~List()
{
    while (head != tail)
    {
        ListNode * temp = head;
        head = head->next;
        delete temp;
    }
    delete head;
}

void List::InsertTail(const std::string& str, ListNode* const rand)
{
    if (!tail->data.empty())
    {
        ListNode * temp = tail;
        tail = new ListNode();
        temp->next = tail;
        tail->prev = temp;

    }
    tail->data = str;
    if (rand != nullptr)
    {
        tail->rand = rand;
    }
    count++;
}

void List::InsertHead(const std::string& str, ListNode* const rand)
{
    if (!head->data.empty())
    {
        ListNode * temp = head;
        head = new ListNode();
        temp->prev = head;
        head->next = temp;
    }
    head->data = str;
    if (rand != nullptr)
    {
        head->rand = rand;
    }
    count++;
}


ListNode* List::AtIndex(int index)
{
    if (index > count)
    {
        return nullptr;
    }

    ListNode* temp = head;

    for (auto i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

int List::Size() const
{
    return count;
}

void List::PrintList()
{
    for (auto it = iterator(); it.has_next(); it.next())
    {
        auto temp = it.get();


        std::cout << "Str: " << temp->data << std::endl;

        if (temp->rand == nullptr)
        {
            std::cout << "Rand is nullptr"  << std::endl;
        }
        else
        {
            std::cout << "Rand is pointing on something"  << std::endl;
        }
    }
}

void List::Serialize(FILE * file)
{
    if (file == NULL)
    {
        std::cout << "Error opening file for writing" << std::endl;
        return;
    }
    else
    {
        std::cout << "Sucsess opening file for writing" << std::endl;
    }
    // count
    std::fwrite(&count, sizeof(int), 1, file); // count in file

    // data
    for (auto it = iterator(); it.has_next(); it.next())
    {
        auto temp = it.get();
        int size = temp->data.size();
        std::fwrite(&size, sizeof(int), 1, file);
        std::fwrite(temp->data.c_str(), sizeof(char), size, file);
    }

    // index for rand
    for (auto it = iterator(); it.has_next(); it.next())
    {
        auto temp = it.get();
        if (temp->rand == nullptr)
        {
            int num = -1;
            std::fwrite(&num, sizeof(int), 1, file);
        }
        else
        {
            int count = 0;
            for (auto it2 = this->iterator(); it2.has_next(); it2.next())
            {
                auto temp_2 = it2.get();
                if (temp_2 == temp->rand)
                {
                    std::fwrite(&count, sizeof(int), 1, file);
                    break;
                }
                count++;
            }
        }
    }
    // std::fclose(file);
}

void List::Deserialize(FILE * file)
{
    if (file == NULL)
    {
        std::cout << "Error opening file for reading" << std::endl;
        return;
    }
    else
    {
        std::cout << "Sucsess opening file for reading" << std::endl;
    }

    // remove old data
    while (head != tail)
    {
        ListNode * temp = head;
        head = head->next;
        delete temp;
    }
    delete head;

    // Count
    int count_temp = 0;
    std::fread(&count_temp, sizeof(int), 1, file);
    // std::cout << "Count: " << count_temp << std::endl;

    head = new ListNode();
    tail = head;
    count = 0;

    // Str
    for (auto i = 0; i < count_temp; i++)
    {
        if (!tail->data.empty())
        {
            ListNode * temp = tail;
            tail = new ListNode();
            temp->next = tail;
            tail->prev = temp;

        }
        int size = 0;
        std::fread(&size, sizeof(int), 1, file);

        char str[size];
        std::fread(&str[0], sizeof(char), size, file);
        tail->data = str;
        count++;

        // std::cout << tail->data << " ";
    }
    // std::cout << std::endl;

    //Indexes
    // std::cout << "Indexes: ";
    int indexes[count_temp];
    std::fread(&indexes, sizeof(int), count_temp, file);

    for (auto i = 0; i < count_temp; i++)
    {
        if (indexes[i] >= 0)
        {
            AtIndex(i)->rand = AtIndex(indexes[i]);
        }

        // std::cout << indexes[i] << " ";
    }
    // std::cout << std::endl;

    // std::fclose(file);
}