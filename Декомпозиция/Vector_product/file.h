#ifndef FILE_H_
#define FILE_H_
#include "geometry.h"
#include <fstream>
#include <iostream>

Point *read_file(int&, int&);

// task_2
void write(const long double area);
bool read_task2(long long &);

#endif // !FILE_H_
