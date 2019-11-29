#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <time.h>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

inline time_t currentTime()
{
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}

const string timeToString(time_t t)
{
    tm tmStruct = *localtime(&t);
    ostringstream out;
    out << put_time(&tmStruct,"%H:%M:%S");
    return out.str();
}

const int nItems = 5;
static queue<pair<int, int>> inQue, tmpQue1, tmpQue2, outQue;
static mutex inMtx, tmpMtx1, tmpMtx2, outMtx, logMtx1;
static vector<pair<time_t, string>> logMessages;

void firstLine()
{
    bool finish = false;
    while (!finish)
    {
        inMtx.lock();
        if (!inQue.empty())
        {
            pair<int, int> curItem = inQue.front();
            inQue.pop();
            int index = curItem.first;
            int t0 = curItem.second;
            if (index != -1)
            {
                logMtx1.lock();
                string tmp = "Line 1: Starting processing item " + to_string(index) + ", value: " + to_string(t0) + " milliseconds";
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(t0));
                tmpMtx1.lock();
                tmpQue1.push({index, t0});
                tmpMtx1.unlock();

                logMtx1.lock();
                tmp = "Line 1: Finished processing item " + to_string(index);
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();
            }
            else
            {
                tmpMtx1.lock();
                tmpQue1.push({-1, -1});
                tmpMtx1.unlock();
                finish = true;
            }
        }
        inMtx.unlock();
    }
}

void secondLine()
{
    bool finish = false;
    while(!finish)
    {
        tmpMtx1.lock();
        if (!tmpQue1.empty())
        {
            pair<int, int> curItem = tmpQue1.front();
            int index = curItem.first;
            int t0 = curItem.second;
            tmpQue1.pop();
            if (t0 != -1)
            {
                logMtx1.lock();
                string tmp = "Line 2: Starting processing item " + to_string(index) + ", value: " + to_string(t0 * 2) + " milliseconds";
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();

                std::this_thread::sleep_for(std::chrono::milliseconds(t0 * 2));

                tmpMtx2.lock();
                tmpQue2.push({index, t0});
                tmpMtx2.unlock();

                logMtx1.lock();
                tmp = "Line 2: Finished processing item " + to_string(index);
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();
            }
            else
            {
                tmpMtx2.lock();
                tmpQue2.push({-1, -1});
                tmpMtx2.unlock();
                finish = true;
            }
        }
        tmpMtx1.unlock();
    }
}

void thirdLine()
{
    bool finish = false;
    while(!finish)
    {
        tmpMtx2.lock();
        if (!tmpQue2.empty())
        {
            pair<int, int> curItem = tmpQue2.front();
            int index = curItem.first;
            int t0 = curItem.second;
            tmpQue2.pop();
            if (t0 != -1)
            {
                logMtx1.lock();
                string tmp = "Line 3: Starting " + to_string(index) + " item, value: " + to_string(t0) + " milliseconds";
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(t0));
                outMtx.lock();
                outQue.push({index, t0});
                outMtx.unlock();
                logMtx1.lock();
                tmp = "Line 3: Finished processing item " + to_string(index);
                logMessages.push_back({currentTime(), tmp});
                logMtx1.unlock();
            }
            else
            {
                finish = true;
            }
        }
        tmpMtx2.unlock();
    }
}

void createLog(const string &fileName)
{
    ofstream file;
    file.open(fileName, ios_base::app);
    if (!file)
    {
        cout << "Error during opening log\n" << endl;
    }
    else
    {
        for (const auto &s : logMessages)
        {
            file << timeToString(s.first) << " " << s.second << '\n';
        }
        file.close();
    }
}

void sortLog()
{
    bool flag;
    for (size_t i = 0; i < logMessages.size(); i++)
    {
        flag = false;
        for (size_t j = 1; j < logMessages.size() - i; j ++)
        {
            if (logMessages[j].first < logMessages[j - 1].first)
            {
                pair<time_t, string> tmp = logMessages[j];
                logMessages[j] = logMessages[j - 1];
                logMessages[j - 1] = tmp;
                flag = true;
            }
        }
        if (!flag) return;
    }
}

int main()
{
    thread lineOne(&firstLine);
    thread lineTwo(&secondLine);
    thread lineThree(&thirdLine);
    for(int i = 0; i < nItems; ++i)
    {
        int inTime = 1000;
        cout << "Item: " << i << ", value: " << inTime << " was added." << endl;
        inMtx.lock();
        inQue.push({i, inTime});
        inMtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    inMtx.lock();
    inQue.push({-1, -1});
    inMtx.unlock();

    lineOne.join();
    lineTwo.join();
    lineThree.join();
    if (outQue.size() == nItems)
    {
        cout << "Conveyor finished his work successfully." << endl;
        sortLog();
        createLog("log.txt");
        cout << "Conveyor took: " << logMessages[logMessages.size() - 1].first - logMessages[0].first << " seconds." << endl;
    }
    else
    {
        cout << "Conveyor missed " << nItems - outQue.size() << " items.\n"<< endl;
    }
    return 0;
}
