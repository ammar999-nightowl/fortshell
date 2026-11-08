#include <iostream>  //basic io functions
#include <sstream> //string stream classes btw
#include <vector> //vector is a dymamic memory block like thingy.
                  //extends based on the value of the var
#include <string> //the string variable
#include <unistd.h> //unix functions
#include <sys/wait.h> //wait lib. idk about this
#include <sys/sysinfo.h> //for out custom fetch . fortfetch
//sadly fortfetch relies on fastfetch for now
#include <cstdlib> //for executing fastfetch inside fortfetch
#include <signal.h> //the libs gonna be for ctrl + c protection
//credit to fastfetch developers
// a hats off !!

using namespace std;

int main()
{

  string command; //the comnand variable
  //lets disable sigint(ctrl + c)
  signal(SIGINT, SIG_IGN);
  //welcome message
  cout << "=====================================================\n";
  cout << "#                 FORTSHELL                         #\n";
  cout << "=====================================================\n";
  while (true)
  {
    cout << "~/fortshell -> ";
    getline(cin, command);
    //handle empty input situation
    if(command.empty()) continue;
    //exit comnand
    if (command == "exit" || command == "Exit" || command == "EXIT" || command == "termquit")
    {
      cout << "shell successfully exited....\n";
      break;
    }
    if (command == "fortinfo")
    {
      cout << "fort v2 . made by ammar\n";
      cout << "fort is a fast simple and easy to use shell\n";
      continue;
    }
    if (command == "fortfetch")
    {
        int result = system("fastfetch");
        //i forgot to continue it
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
    //the built in cd .. yay
    if (!args.empty() && args[0] == "cd")
    {
      if (args.size() < 2)
      {
        chdir(getenv("HOME"));
        cout << "no arguments detected . so switched to home\n";

      } else 
      {
        if (chdir(args[1].c_str()) != 0)
        {
          perror("oops cd failed...");

        }
      }
      continue;
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
      //setting ctrl + c behaviour to default. execvp is lazy
      //default for child. the parent ignores ctrl + c
      signal(SIGINT, SIG_DFL);
      //child process
      execvp(c_args[0], c_args.data());
      //if exec fails then we get here
      perror("forterr");
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
