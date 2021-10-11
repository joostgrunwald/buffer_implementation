/**
  * Assignment: synchronization
  * Operating Systems
  */

/**
  Hint: F2 (or Control-klik) on a functionname to jump to the definition
  Hint: Ctrl-space to auto complete a functionname/variable.
  */

//dependencies
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
//includes from here one are our own
#include <string>

using namespace std;

// ! Global variables
vector<int> buffer;
vector<string> logger;
bool bounded = false;
int bufferbound = 0;

// * This function writes a single log to the log vector
void writeToLog(string log)
{
  logger.push_back(log);
}

// * This function reads a specific log sample, by using an index as input
string readFromLog(int index)
{
  //? if size = 1, we index 0
  if (logger.size() >= index + 1)
  {
    return logger[index];
  }
  else if (logger.size() < index + 1)
  {
    cout << "ERROR: index out of bounds" << endl;
    return "ERROR: index out of bounds";
  }
  else
  {
    //? not in size and not higher then size so negative
    cout << "ERROR: negative index" << endl;
    return "ERROR: negative index";
  }
}

// * This function prints the entire log onto the terminal
void printLog()
{
  for (string element : logger)
    std::cout << element << ' ';
  std::cout << endl;
}

// * This function writes to the buffer, it therefore
// * Checks wether or not it is already full if bounden
// * the function also updates the log with operation about its success
void writeToBuffer(int element)
{
  if (bounded == true)
  {
    if (buffer.size() < bufferbound)
    {
      // ? There is room left so we push
      buffer.push_back(element);
      writeToLog("operation succeeded, added: " + to_string(element) + " to buffer");
    }
    else if (buffer.size() == bufferbound)
    {
      writeToLog("operation failed: The buffer has already reached its bound");
    }
  }
  else // ? not bounded
  {
    buffer.push_back(element);
    writeToLog("operation succeeded, added: " + to_string(element) + " to buffer");
  }
}

// * This function sets the max bound of the buffer
// * as base case we check for legitimate inputs
// * It also provides the log with information about its success
void setBufferBound(int userbound)
{
  if (userbound == 0)
  {
    writeToLog("operation failed: invalid value 0 for parameter userbound");
    cout << "you are putting in an invalid value (0), bound has to be > 0" << endl;
  }
  else if (userbound < 0)
  {
    writeToLog("operation failed: negative value for parameter userbound");
    cout << "you are putting in an invalid value (negative), bound has to be > 0" << endl;
  }
  else
  {
    writeToLog("operation succeeded: set: " + to_string(userbound) + " as buffer bound");
    bounded = true;
    bufferbound = userbound;

    // ! Case where buffer > new bound, we remove elements exceeding bound
    if (buffer.size() > bufferbound)
    {
      //? we basicly remove range(userbound --> end of buffer)
      buffer.erase(buffer.begin() + userbound, buffer.end())
    }
  }
}

// * This function removes the buffer bound
void removeBufferBound()
{
  bounded = false;
  // we do not have to reset the bound (because it will be reassigned when enabled again)
}

// * This function prints out the entire buffer to the screen
void printBuffer()
{
  for (int element : buffer)
    std::cout << element << ' ';
  std::cout << endl;
}

// * This function removes a specific element from the buffer
void removeFromBuffer(int index)
{
  buffer.erase(buffer.begin() + index);
}

// * This function is used for testing some buffer operations
void buffertests()
{
  std::cout << "empty buffer: " << endl;
  printBuffer();
  writeToBuffer(3);
  writeToBuffer(4);
  writeToBuffer(5);
  std::cout << "filled buffer: " << endl;
  printBuffer();
  removeFromBuffer(0);
  std::cout << "buffer - elem 0: " << endl;
  printBuffer();
}

// * This is the main function, it is called when the program is ran
int main(int argc, char *argv[])
{
  buffertests();
  return 0;
}
