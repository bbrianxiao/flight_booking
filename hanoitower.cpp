#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <exception>

using namespace std;

const int NUMBER_OF_DISKS = 5;
const int NUMBER_OF_TOWERS = 3;

class MyException : public exception
{
private:
    string exceptionMsg;

public:
    MyException(string msg)
    {
        this->exceptionMsg = msg;
    };

    virtual const char *what() const throw()
    {
        const char *c = exceptionMsg.c_str();
        return c;
    }
};

class Tower
{
private:
    string name;
    int disks[NUMBER_OF_DISKS];
    int pos = 0;

public:
    Tower()
    {
    }

    Tower(int serial)
    {
        this->name = "tower_" + to_string(serial);
        this->pos = 0;
    }

    Tower(int serial, int numberOfDisks)
    {
        this->name = "tower_" + to_string(serial);
        for (int i = 0; i < numberOfDisks; i++)
            this->disks[i] = numberOfDisks - i;
        this->pos = numberOfDisks;
    }

    // if the tower is in fully well built stage, return true
    bool isfinal()
    {
        if (this->pos != NUMBER_OF_DISKS)
            return false;
        for (int i = 0; i < this->pos; i++)
            if (this->disks[i] != this->pos - i)
                return false;
        return true;
    }

    // get the top positon of the tower
    int getPos()
    {
        return this->pos;
    }

    // add a disk on top of the tower
    int push(int disk)
    {
        this->disks[this->pos] = disk;
        this->pos++;
        return disk;
    }

    // remove a disk from top of the tower
    int pop()
    {
        return this->disks[--pos];
    }

    // get the disk from top of the tower but not remove it from the tower
    int peek()
    {
        return this->disks[pos - 1];
    }

    // print the status of the tower
    void display()
    {
        string str = "";
        cout << this->name << ": ";
        if (pos == 0)
            str = "empty";
        else
            for (int i = 0; i < pos; i++)
                str = str + to_string(this->disks[i]) + " ";
        cout << str << endl;
    }
};

class HanoiTower
{
private:
    Tower towers[NUMBER_OF_TOWERS];
    int numberOfTowers;
    int numberOfDisks;

public:
    HanoiTower(int numberOfTowers, int numberOfDisks)
    {
        this->numberOfTowers = numberOfTowers;
        this->numberOfDisks = numberOfDisks;
        for (int i = 1; i <= numberOfTowers; i++)
        {
            if (i == 1)
                this->towers[i - 1] = Tower(i, numberOfDisks);
            else
                this->towers[i - 1] = Tower(i);
        }
    };

    // print the status of the hanoi tower
    void display()
    {
        for (int i = 0; i < this->numberOfTowers; i++)
            this->towers[i].display();
        return;
    }

    // move a disk from the source rod (start) to the target rod (end)
    bool move(int start, int end)
    {
        if (start <= 0 || start > this->numberOfTowers ||
            end <= 0 || end > this->numberOfTowers)
            throw MyException(" source/target rod number is out of range. ");
        else if (this->towers[start - 1].getPos() == 0)
        {
            throw MyException("There are no disks at the source rod. ");
        }
        else if (start == end)
        {
            return true;
        }
        else
        {
            int sourceDisk = this->towers[start - 1].peek();
            int targetDisk = this->towers[end - 1].peek();
            if (targetDisk != 0 && sourceDisk > targetDisk)
                throw MyException("disk in the source rod is bigger than the one in the target rod. ");
            else
            {
                sourceDisk = this->towers[start - 1].pop();
                targetDisk = this->towers[end - 1].push(sourceDisk);
            }
        }
        return true;
    }

    // check if the hanoi tower is in the final stage.
    bool isSuccess()
    {
        for (int i = 0; i < this->numberOfTowers - 1; i++)
            if (this->towers[i].getPos() != 0)
                return false;
        if (this->towers[numberOfTowers - 1].isfinal())
            return true;
        return false;
    }
};

string leftTrim(string str);
string spaceTrim(string str);
string toLowerCase(string str);
bool stringToNumber(string numberString, int *number);
bool parsingCommand(string inputLine, string *command, int *id, int *number);

main()
{
    HanoiTower hanoiTower(NUMBER_OF_TOWERS, NUMBER_OF_DISKS);
    string command = "";
    string cmd = "";
    int fromRod, toRod;
    int steps = 0; // count the steps that player used
    while (command != "quit")
    {
        hanoiTower.display();
        cout << endl
             << "Action> ";
        getline(cin, command);
        if (!parsingCommand(command, &cmd, &fromRod, &toRod))
        {
            cout << "Invalid Command! The valid command format is [move # #], [m # #], [quit] or [q]" << endl;
        }
        else
        {
            if (cmd == "quit" || cmd == "q")
                break;
            if (cmd == "move" || cmd == "m")
            {
                try
                {
                    if (hanoiTower.move(fromRod, toRod))
                        steps++;
                    if (hanoiTower.isSuccess())
                    {
                        hanoiTower.display();
                        cout << "WELL DONE! You successfully complete the task in " << steps << " steps" << endl;
                        break;
                    }
                }
                catch (MyException &ex)
                {
                    cout << "Invalid move: " << ex.what() << std::endl;
                }
            }
        }
    }
    return 0;
}

// parsing user input to get command, fromRod, and toRod
// if the valid command, fromRod, and toRod are received, return true
// if the command is invalid, or the fromRod is not a valid number, or the toRod is not a valid number, return false
bool parsingCommand(string inputLine, string *command, int *fromRod, int *toRod)
{
    bool flag = false;
    string result = "";
    string cmd, from, to;

    stringstream X(toLowerCase(spaceTrim(leftTrim(inputLine))));

    while (getline(X, cmd, ' '))
    {
        if (cmd == "move" || cmd == "m")
        {
            flag = true;
            *command = cmd;
            getline(X, from, ' ');
            flag = stringToNumber(from, fromRod);
            if (!flag)
                break;
            getline(X, to, ' ');
            flag = stringToNumber(to, toRod);
            break;
        }
        else if (cmd == "quit" || cmd == "q")
        {
            *command = cmd;
            flag = true;
            break;
        }
    }
    return flag;
}

// remove all leading spaces from the string
// for example, string "   move 1 2" will be converted to "move 1 2"
string leftTrim(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            result = result + str.substr(i);
            break;
        }
    }
    return result;
}

// convert multipul spaces to a single space in a string
// for example, string "move   1    2" will be converted to "move 1 2"
string spaceTrim(string str)
{
    string result = "";
    bool isMultipleSpace = false;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            result = result + str[i];
            isMultipleSpace = false;
        }
        else
        {
            if (!isMultipleSpace)
            {
                result = result + " ";
                isMultipleSpace = true;
            }
        }
    }

    return result;
}

// convert all characters to lower case in a string
string toLowerCase(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        result.push_back(tolower(str[i]));
    }
    return result;
}

// convert a string to a number
// if a string is a valid number, convert it to an integer, return true.
// otherwise return false
// for example, string "123" will be converted to number 123 and return true
// string "123B", "A123", or "AB" will not be converted and return false
bool stringToNumber(string numberString, int *number)
{
    bool result = true;
    if (numberString.size() > 0 && isdigit(numberString[0]) == 0 && (numberString[0] != '-')) // first letter is not a digit nor a minus sign
    {
        result = false;
        return result;
    }
    for (int i = 1; i < numberString.size(); i++)
    {

        if ((isdigit(numberString[i]) == 0)) // not a digit
        {
            result = false;
            return result;
        }
    }
    try
    {
        *number = (stoi(numberString));
    }
    catch (const std::invalid_argument &ex)
    {
        result = false;
    }
    catch (const std::out_of_range &ex)
    {
        result = false;
    }

    return result;
}
