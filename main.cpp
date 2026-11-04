#include <iostream>  //basic io functions
#include <sstream> //string stream classes btw
#include <vector> //vector is a dymamic memory block like thingy.
                  //extends based on the value of the var
#include <string> //the string variable
#include <unistd.h> //unix functions
#include <sys/wait.h> //wait lib. idk about this
#include <sys/sysinfo.h> //for out custom fetch . fortfetch
//sadly fortfetch will be aded later

using namespace std;

int main()
{
  struct sysinfo si;
  string command; //the comnand variable

  //welcome message
  cout << "welcome to fort.. the fast shell\n";
  cout << "by ammar... if you know c++ . please try contributing\n";
  while (true)
  {
    cout << "~/fort > ";
    getline(cin, command);
    //handle empty input situation
    if(command.empty()) continue;
    //exit comnand
    if (command == "exit" || command == "Exit" || command == "EXIT" || command == "termquit")
    {
      cout << "exiting .....\n";
      break;
    }
    if (command == "fortinfo")
    {
      cout << "fort v1 . made by ammar\n";
      cout << "fort is a fast simple and easy to use shell\n";
      continue;
    }
    if (command == "help")
    {
      cout << "help :\n";
      cout << "fortinfo, exit, help , etc\n";
      continue;
    }

    //parsing commnads and tokens btw
    stringstream ss(command);
    string arg;
    vector<string> args;
    while (ss >> arg)
    {
      args.push_back(arg);

    }
    //convert this to c style array btw
    vector<char*> c_args;
    for (auto &a: args)
    {
      c_args.push_back(&a[0]);

    }
    c_args.push_back(nullptr);
    //forking a new process now
    pid_t pid = fork();
    if (pid == 0)
    {
      //child process
      execvp(c_args[0], c_args.data());
      //if exec fails then we get here
      perror("FORTSHELL");
      exit(1);
    } else if (pid > 0)
    {
      //parent process
      wait(nullptr); //wait for the child to finish
                     //the kids parent arent strict
    }
    else
    {
      //fork failed ... you will get an A later bro
      perror("oops fork failed. shit");

    }
  }
  return 0;
}
