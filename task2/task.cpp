// 9 номер
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "Library.h"

std::ofstream report;

void getBook(int readerId, Book &book)
{
    book.setReaderId(readerId);
    book.setAvailable(false);
}

void lifecycle(int lifetime, Library &lib)
{
    for (int i = 0; i < lifetime; i++)
    {
        std::cout << "Day " << i << ":" << std::endl;
        report << "Day " << i << ":" << std::endl;
        lib.day(report);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void createReport()
{
    char prefix[] = "reports/report";
    char timeStr[] = __TIME__;
    char ext[] = ".txt";
    char filename[100];

    timeStr[2] = '_';
    timeStr[5] = '_';

    int i = 0, j = 0;
    while (prefix[j])
        filename[i++] = prefix[j++];

    j = 0;
    while (timeStr[j])
        filename[i++] = timeStr[j++];

    j = 0;
    while (ext[j])
        filename[i++] = ext[j++];

    filename[i] = '\0';

    std::ofstream outFile(filename);
    report = std::move(outFile);
}

int main()
{
    createReport();

    Library lib;
    lib.initLibrary();

    int lifetime = 50;
    std::cout << "Lifetime: ";
    std::cin >> lifetime;
    lifecycle(lifetime, lib);

    lib.printStatistic(report);

    report.close();

    std::cout << "Press Enter to close...";
    std::cin.get();
    std::cin.get();

    return 0;
}